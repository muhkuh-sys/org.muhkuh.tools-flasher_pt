------------------------------------------------------------------------------

-- Create the Shell class.
local class = require "pl.class"
local Shell = class()

local debugMode_ProgressBar = false
local debugMode = false

function Shell:_init()
  local tLogWriter_consoleFilter
  if debugMode == false then
    tLogWriter_consoleFilter = require "log.writer.filter".new("info", require "log.writer.console.color".new())
  else
    tLogWriter_consoleFilter = require "log.writer.console.color".new()
  end

  local strLogDir = "./logs"
  local strLogFilename = ".log_Data.log"

  self.strLogDir = strLogDir
  self.strLogFilename = strLogFilename

  local tLogWriter =
    require "log.writer.list".new(
    tLogWriter_consoleFilter,
    require "log.writer.file".new {
      log_dir = strLogDir, --   log dir
      log_name = strLogFilename, --   current log name
      max_rows = 100000,
      max_size = 1000000, --   max file size in bytes
      roll_count = 10 --   count files
    }
  )

  local tLog =
    require "log".new(
    -- maximum log level
    "trace",
    -- writer
    require "log.writer.prefix".new("[FSH] ", tLogWriter),
    -- Formatter
    require "log.formatter.format".new()
  )

  local tLog_ProgressBar =
    require "log".new(
    -- maximum log level
    "trace",
    -- writer
    require "log.writer.prefix".new("[CALLBACK] ", tLogWriter),
    -- Formatter
    require "log.formatter.concat".new()
  )

  local tLog_Flasher =
    require "log".new(
    -- maximum log level
    "trace",
    -- writer
    require "log.writer.prefix".new("[FLASHER] ", tLogWriter),
    -- Formatter
    require "log.formatter.format".new()
  )

   -- overwrite the tLog.error to overcome the problem of printing error messages at the end of Progress Bars
   local tLog_ProgressBar_error = tLog_ProgressBar.error
   tLog_ProgressBar.error = function(...)
     print()
     tLog_ProgressBar_error(...)
   end
 
   local tLog_Flasher_error = tLog_Flasher.error
   tLog_Flasher.error = function(...)
     print()
     tLog_Flasher_error(...)
   end
 
   local tLog_error = tLog.error
   tLog.error = function(...)
     print()
     tLog_error(...)
   end
 
  for _, strPlugin in ipairs(self.astrPlugins) do
    tLog.debug('Loading plugin "%s"...', strPlugin)
    require(strPlugin)
  end

  self.linenoise = require "linenoise"
  local lpeg = require "lpeg"
  self.lpeg = lpeg
  self.pl = require "pl.import_into"()
  self.term = require "term"
  -- self.termlib = require "libterminalSize"
  self.colors = self.term.colors
  self.tFlasher = require "flasher"(tLog_Flasher)

  self.tLog = tLog
  self.tLog_ProgressBar = tLog_ProgressBar

  self.tCmd_input = self.pl.List()
  self.list_cmd = false

  -- No connection yet.
  self.tPlugin = nil
  self.aAttr = nil
  self.__aBoardInfo = {}

  self.__atDetectedDevices = {}
  self.__astrPluginNames = {}
  self.__aSanitizedBoardNames = {}

  self.__ucCurrentBus = nil
  self.__ucCurrentUnit = nil
  self.__ucCurrentCS = nil

  ---------------------------------------------------------------------------
  --
  -- Define a set of LPEG helpers.
  --

  -- save typing function names with "lpeg" in front of them:
  local P, V, Cg, Ct, Cc, S, R, C, Cf, Cb, Cs =
    lpeg.P,
    lpeg.V,
    lpeg.Cg,
    lpeg.Ct,
    lpeg.Cc,
    lpeg.S,
    lpeg.R,
    lpeg.C,
    lpeg.Cf,
    lpeg.Cb,
    lpeg.Cs

  -- Match at least one character of whitespace.
  local Space = S(" \t") ^ 1
  -- Match optional whitespace.
  local OptionalSpace = S(" \t") ^ 0

  -- Match an integer. This can be decimal or hexadecimal.
  -- The "unfinished" variant accepts also unfinished hexadecimal numbers
  -- like "0x".
  local DecimalInteger = R("09") ^ 1
  local HexInteger = P("0x") * (R("09", "af", "AF")) ^ 1
  local UnfinishedHexInteger = P("0x") * R("09", "af", "AF") ^ 0
  local Integer = HexInteger + DecimalInteger
  local UnfinishedInteger = UnfinishedHexInteger + DecimalInteger

  -- A plugin name consists of alphanumeric characters and the underscore.
  local PluginName = (R("az", "AZ", "09") + S("_-@,:")) ^ 1

  -- A device name consists of alphanumeric characters and the underscore.
  local DeviceName = (R("az", "AZ", "09") + P("_")) ^ 1

  self.tMatchBusUnitCs =
    Ct(
    P("B") * Cg(Integer / tonumber, "bus") * P("_U") * Cg(Integer / tonumber, "unit") * P("_C") *
      Cg(Integer / tonumber, "cs") *
      -1
  )

  ---------------------------------------------------------------------------
  --
  -- Create a grammar to parse a line.
  --

  -- A filename simply matches the rest of the line. This has one important
  -- reason: if a path contains spaces, it should be enclosed in quotes, but
  -- there is no simple way to insert a quote somewhere before the cursor in
  -- linenoise (if there is a way, please tell me :D ).
  local Filename =
    P {
    "start", --> this tells LPEG which rule to process first
    start = V "filename",
    filename = V "allWords" * (Space * V "filename") ^ 0,
    allWords = (1 - S(" \t\n\r")) ^ 1
  }

  -- Range is either...
  --   1) the keyword "all"
  --   2) a start and end address
  --   3) a start and length separated by "+"
  local Range =
    Cg(P("all"), "all") +
    (Cg(Integer / tonumber, "startaddress") * Space *
      (Cg(Integer / tonumber, "endaddress") + (P("+") * OptionalSpace * Cg(Integer / tonumber, "length"))))

  -- possible choices of debug command
  local Cmds_debug = Cg(P("watch"), "watch") + Cg(P("save"), "save") * Space * Cg(Filename, "filename")
  self.AllCommands_debug = {"watch", "save"}

  -- possible choices of list command
  local Cmds_list = Cg(P("run"), "run") + Cg(P("save"), "save") * Space * Cg(Filename, "filename")
  self.AllCommands_list = {"run", "save"}

  -- A comment starts with a hash and covers the rest of the line.
  local Comment = P("#")

  -- All available commands and their handlers.
  local atCommands = {
    {
      cmd = "connect",
      pattern = OptionalSpace * Cg(P("connect"), "cmd") * Space * Cg(PluginName, "plugin") * OptionalSpace * -1,
      run = self.__run_connect
    },
    {
      cmd = "disconnect",
      pattern = OptionalSpace * Cg(P("disconnect"), "cmd") * OptionalSpace * -1,
      run = self.__run_disconnect
    },
    {
      cmd = "read",
      pattern = OptionalSpace * Cg(P("read"), "cmd") * Space * Cg(DeviceName, "device") * Space * Range * Space *
        Cg(Filename, "filename") *
        OptionalSpace *
        -1,
      run = self.__run_read
    },
    {
      cmd = "write",
      pattern = OptionalSpace * Cg(P("write"), "cmd") * Space * Cg(DeviceName, "device") * Space *
        Cg(Integer / tonumber, "startaddress") *
        Space *
        Cg(Filename, "filename") *
        OptionalSpace *
        -1,
      run = self.__run_write
    },
    {
      cmd = "erase",
      pattern = OptionalSpace * Cg(P("erase"), "cmd") * Space * Cg(DeviceName, "device") * Space * Range * OptionalSpace *
        -1,
      run = self.__run_erase
    },
    {
      cmd = "iserased",
      pattern = OptionalSpace * Cg(P("iserased"), "cmd") * Space * Cg(DeviceName, "device") * Space * Range *
        OptionalSpace *
        -1,
      run = self.__run_iserased
    },
    {
      cmd = "verify",
      pattern = OptionalSpace * Cg(P("verify"), "cmd") * Space * Cg(DeviceName, "device") * Space *
        Cg(Integer / tonumber, "startaddress") *
        Space *
        Cg(Filename, "filename") *
        OptionalSpace *
        -1,
      run = self.__run_verify
    },
    {
      cmd = "hash",
      pattern = OptionalSpace * Cg(P("hash"), "cmd") * Space * Cg(DeviceName, "device") * Space * Range * OptionalSpace *
        -1,
      run = self.__run_hash
    },
    {
      cmd = "scan",
      pattern = OptionalSpace * Cg(P("scan"), "cmd") * OptionalSpace * -1,
      run = self.__run_scan
    },
    {
      cmd = "help",
      pattern = OptionalSpace * Cg(P("help"), "cmd") * (Space * Cg(R("az") ^ 1, "topic")) ^ -1 * OptionalSpace * -1,
      run = self.__run_help
    },
    {
      cmd = "quit",
      pattern = OptionalSpace * Cg(P("quit"), "cmd") * OptionalSpace * -1,
      run = self.__run_quit
    },
    {
      cmd = "input",
      pattern = OptionalSpace * Cg(P("input"), "cmd") * Space * Cg(Filename, "filename") * OptionalSpace * -1,
      run = self.__run_input
    },
    {
      cmd = "debug",
      pattern = OptionalSpace * Cg(P("debug"), "cmd") * Space * Cmds_debug * OptionalSpace * -1,
      run = self.__run_debug
    },
    {
      cmd = "list",
      pattern = OptionalSpace * Cg(P("list"), "cmd") * Space * Cmds_list * OptionalSpace * -1,
      run = self.__run_list
    },
    {
      -- command for list command only
      cmd = "end",
      pattern = OptionalSpace * Cg(P("end"), "cmd") * OptionalSpace * -1,
      run = function()
        return true
      end
    },
    {
      -- command for list command only
      cmd = "clear",
      pattern = OptionalSpace * Cg(P("clear"), "cmd") * Space * (Cg(P("all"), "all") + Cg(Integer / tonumber, "number")) *
        OptionalSpace *
        -1,
      run = function()
        return true
      end
    }
  }
  self.__atCommands = atCommands

  -- Combine all commands.
  local AllCommands
  local AllCommands_withListCmd
  for _, tCommand in ipairs(atCommands) do
    local pattern = tCommand.pattern
    if AllCommands == nil then
      if tCommand.cmd ~= "end" and tCommand.cmd ~= "clear" then
        AllCommands = pattern
      end
      AllCommands_withListCmd = pattern
    else
      if tCommand.cmd ~= "end" and tCommand.cmd ~= "clear" then
        AllCommands = AllCommands + pattern
      end
      AllCommands_withListCmd = AllCommands_withListCmd + pattern
    end
  end

  self.__AllCommands = AllCommands
  self.__lineGrammar = Ct((AllCommands * (Comment ^ -1)) + Comment)
  self.__lineGrammar_withListCmd = Ct((AllCommands_withListCmd * (Comment ^ -1)) + Comment)

  -- Create a table with all commands as a string.
  local astrCommandWords = {}
  local astrCommandWords_withListCmd = {}
  for _, tCommand in ipairs(atCommands) do
    if tCommand.cmd ~= "end" and tCommand.cmd ~= "clear" then
      table.insert(astrCommandWords, tCommand.cmd)
    end
    table.insert(astrCommandWords_withListCmd, tCommand.cmd)
  end

  self.__astrCommandWords = astrCommandWords
  self.astrCommandWords_withListCmd = astrCommandWords_withListCmd

  -- Create a table with all help topics as a string.
  local astrHelpTopicWords = {}
  for _, tTopic in ipairs(self.__atHelpTopics) do
    local strTopic = tTopic.topic
    if strTopic ~= nil and strTopic ~= "" then
      table.insert(astrHelpTopicWords, strTopic)
    end
  end
  self.__astrHelpTopicWords = astrHelpTopicWords

  ---------------------------------------------------------------------------
  -- Create a lookup table for completers and hints. It is used when the
  -- command lines are typed in and not read from a file.
  -- See here for more info on completion and hints:
  --   https://github.com/antirez/linenoise#completion
  --   https://github.com/antirez/linenoise#hints
  --
  -- All entries must have a "pattern" key. This is an LPEG pattern which
  -- matches one specific state of the input. For example if the input line
  -- matches zero or more characters in the range a-z with nothing else
  -- before and after, the user is currently typing the command.
  --
  -- An entry can have a "hint" key. This must be either a string or a
  -- function. The string is directly used as the hint text. The function
  -- gets an eventual match from the pattern as argument and must return
  -- either the hint text as a string or nil.
  --
  -- An entry can have a "words" key. This must be either a table or a
  -- function. The table must only contain strings. The function gets an
  -- eventual match from the pattern as argument and must return a table of
  -- strings.
  --
  -- The completer function looks for the first matching pattern in the
  -- table. If the table entry has a "words" key, it is used to complete the
  -- current line.
  --
  -- The hints function also looks for the first matching pattern in the
  -- table. If the table entry has a "hint" key, it is used as the hint text.
  -- If the table has no "hint" key but "words", this is used together with
  -- an eventually available match to display all available completions in the
  -- hint text.
  self.__atInteractivePatterns = {
    -- Typing a command. This also matches an empty line.
    {
      pattern = OptionalSpace * Cg(R("az") ^ 0) * -1,
      words = function()
        if self.list_cmd == true then
          return self.astrCommandWords_withListCmd
        else
          return self.__astrCommandWords
        end
      end
    },
    -- Connect command.
    {
      pattern = OptionalSpace * P("connect") * Space * -1,
      hint = function()
        return "[plugin]  possible values: " .. table.concat(self.__astrPluginNames, ", ")
      end,
      words = function()
        return self.__astrPluginNames
      end
    },
    {
      pattern = OptionalSpace * P("connect") * Space * Cg(PluginName) * -1,
      words = function()
        return self.__astrPluginNames
      end
    },
    -- Read command.
    {
      pattern = OptionalSpace * P("read") * Space * -1,
      hint = function()
        return "[device]  possible values: " .. table.concat(self.__aSanitizedBoardNames, ", ")
      end,
      words = function()
        return self.__aSanitizedBoardNames
      end
    },
    {
      pattern = OptionalSpace * P("read") * Space * Cg(DeviceName) * -1,
      words = function()
        return self.__aSanitizedBoardNames
      end
    },
    {
      pattern = OptionalSpace * P("read") * Space * DeviceName * Space * -1,
      hint = "all  or  [startaddress] [endaddress]  or  [startaddress] + [length]",
      words = {"all"}
    },
    {
      pattern = OptionalSpace * P("read") * Space * DeviceName * Space * Cg(P("al") + P("a")) * -1,
      words = {"all"}
    },
    {
      pattern = OptionalSpace * P("read") * Space * DeviceName * Space * UnfinishedInteger * -1,
      hint = "    this is the startaddress"
    },
    {
      pattern = OptionalSpace * P("read") * Space * DeviceName * Space * Integer * Space * -1,
      hint = "[endaddress]  or  + [length]"
    },
    {
      pattern = OptionalSpace * P("read") * Space * DeviceName * Space * Integer * Space * UnfinishedInteger * -1,
      hint = "    this is the endaddress"
    },
    {
      pattern = OptionalSpace * P("read") * Space * DeviceName * Space * Integer * Space * P("+") * OptionalSpace * -1,
      hint = "[length]"
    },
    {
      pattern = OptionalSpace * P("read") * Space * DeviceName * Space * Integer * Space * P("+") * Space *
        UnfinishedInteger *
        -1,
      hint = "    this is the length"
    },
    {
      pattern = OptionalSpace * P("read") * Space * DeviceName * Space *
        (P("all") + (Integer * Space * (Integer + (P("+") * OptionalSpace * Integer)))) *
        Space *
        -1,
      hint = "[filename]",
      words = function(strMatch)
        return self:__getFilenameWords(strMatch)
      end
    },
    {
      pattern = OptionalSpace * P("read") * Space * DeviceName * Space *
        (P("all") + (Integer * Space * (Integer + (P("+") * OptionalSpace * Integer)))) *
        Space *
        Cg(Filename) *
        -1,
      words = function(strMatch)
        return self:__getFilenameWords(strMatch)
      end
    },
    -- Write command.
    {
      pattern = OptionalSpace * P("write") * Space * -1,
      hint = function()
        return "[device]  possible values: " .. table.concat(self.__aSanitizedBoardNames, ", ")
      end,
      words = function()
        return self.__aSanitizedBoardNames
      end
    },
    {
      pattern = OptionalSpace * P("write") * Space * Cg(DeviceName) * -1,
      words = function()
        return self.__aSanitizedBoardNames
      end
    },
    {
      pattern = OptionalSpace * P("write") * Space * DeviceName * Space * -1,
      hint = "[startaddress]"
    },
    {
      pattern = OptionalSpace * P("write") * Space * DeviceName * Space * UnfinishedInteger * -1,
      hint = "    this is the startaddress"
    },
    {
      pattern = OptionalSpace * P("write") * Space * DeviceName * Space * Integer * Space * -1,
      hint = "[filename]",
      words = function(strMatch)
        return self:__getFilenameWords(strMatch)
      end
    },
    {
      pattern = OptionalSpace * P("write") * Space * DeviceName * Space * Integer * Space * Cg(Filename) * -1,
      words = function(strMatch)
        return self:__getFilenameWords(strMatch)
      end
    },
    -- Erase command.
    {
      pattern = OptionalSpace * P("erase") * Space * -1,
      hint = function()
        return "[device]  possible values: " .. table.concat(self.__aSanitizedBoardNames, ", ")
      end,
      words = function()
        return self.__aSanitizedBoardNames
      end
    },
    {
      pattern = OptionalSpace * P("erase") * Space * Cg(DeviceName) * -1,
      words = function()
        return self.__aSanitizedBoardNames
      end
    },
    {
      pattern = OptionalSpace * P("erase") * Space * DeviceName * Space * -1,
      hint = "all  or  [startaddress] [endaddress]  or  [startaddress] + [length]",
      words = {"all"}
    },
    {
      pattern = OptionalSpace * P("erase") * Space * DeviceName * Space * Cg(P("al") + P("a")) * -1,
      words = {"all"}
    },
    {
      pattern = OptionalSpace * P("erase") * Space * DeviceName * Space * UnfinishedInteger * -1,
      hint = "    this is the startaddress"
    },
    {
      pattern = OptionalSpace * P("erase") * Space * DeviceName * Space * Integer * Space * -1,
      hint = "[endaddress]  or  + [length]"
    },
    {
      pattern = OptionalSpace * P("erase") * Space * DeviceName * Space * Integer * Space * UnfinishedInteger * -1,
      hint = "    this is the endaddress"
    },
    {
      pattern = OptionalSpace * P("erase") * Space * DeviceName * Space * Integer * Space * P("+") * OptionalSpace * -1,
      hint = "[length]"
    },
    {
      pattern = OptionalSpace * P("erase") * Space * DeviceName * Space * Integer * Space * P("+") * Space *
        UnfinishedInteger *
        -1,
      hint = "    this is the length"
    },
    -- IsErased command.
    {
      pattern = OptionalSpace * P("iserased") * Space * -1,
      hint = function()
        return "[device]  possible values: " .. table.concat(self.__aSanitizedBoardNames, ", ")
      end,
      words = function()
        return self.__aSanitizedBoardNames
      end
    },
    {
      pattern = OptionalSpace * P("iserased") * Space * Cg(DeviceName) * -1,
      words = function()
        return self.__aSanitizedBoardNames
      end
    },
    {
      pattern = OptionalSpace * P("iserased") * Space * DeviceName * Space * -1,
      hint = "all  or  [startaddress] [endaddress]  or  [startaddress] + [length]",
      words = {"all"}
    },
    {
      pattern = OptionalSpace * P("iserased") * Space * DeviceName * Space * Cg(P("al") + P("a")) * -1,
      words = {"all"}
    },
    {
      pattern = OptionalSpace * P("iserased") * Space * DeviceName * Space * UnfinishedInteger * -1,
      hint = "    this is the startaddress"
    },
    {
      pattern = OptionalSpace * P("iserased") * Space * DeviceName * Space * Integer * Space * -1,
      hint = "[endaddress]  or  + [length]"
    },
    {
      pattern = OptionalSpace * P("iserased") * Space * DeviceName * Space * Integer * Space * UnfinishedInteger * -1,
      hint = "    this is the endaddress"
    },
    {
      pattern = OptionalSpace * P("iserased") * Space * DeviceName * Space * Integer * Space * P("+") * OptionalSpace *
        -1,
      hint = "[length]"
    },
    {
      pattern = OptionalSpace * P("iserased") * Space * DeviceName * Space * Integer * Space * P("+") * Space *
        UnfinishedInteger *
        -1,
      hint = "    this is the length"
    },
    -- Verify command.
    {
      pattern = OptionalSpace * P("verify") * Space * -1,
      hint = function()
        return "[device]  possible values: " .. table.concat(self.__aSanitizedBoardNames, ", ")
      end,
      words = function()
        return self.__aSanitizedBoardNames
      end
    },
    {
      pattern = OptionalSpace * P("verify") * Space * Cg(DeviceName) * -1,
      words = function()
        return self.__aSanitizedBoardNames
      end
    },
    {
      pattern = OptionalSpace * P("verify") * Space * DeviceName * Space * -1,
      hint = "[startaddress]"
    },
    {
      pattern = OptionalSpace * P("verify") * Space * DeviceName * Space * UnfinishedInteger * -1,
      hint = "    this is the startaddress"
    },
    {
      pattern = OptionalSpace * P("verify") * Space * DeviceName * Space * Integer * Space * -1,
      hint = "[filename]",
      words = function(strMatch)
        return self:__getFilenameWords(strMatch)
      end
    },
    {
      pattern = OptionalSpace * P("verify") * Space * DeviceName * Space * Integer * Space * Cg(Filename) * -1,
      words = function(strMatch)
        return self:__getFilenameWords(strMatch)
      end
    },
    -- Hash command.
    {
      pattern = OptionalSpace * P("hash") * Space * -1,
      hint = function()
        return "[device]  possible values: " .. table.concat(self.__aSanitizedBoardNames, ", ")
      end,
      words = function()
        return self.__aSanitizedBoardNames
      end
    },
    {
      pattern = OptionalSpace * P("hash") * Space * Cg(DeviceName) * -1,
      words = function()
        return self.__aSanitizedBoardNames
      end
    },
    {
      pattern = OptionalSpace * P("hash") * Space * DeviceName * Space * -1,
      hint = "all  or  [startaddress] [endaddress]  or  [startaddress] + [length]",
      words = {"all"}
    },
    {
      pattern = OptionalSpace * P("hash") * Space * DeviceName * Space * Cg(P("al") + P("a")) * -1,
      words = {"all"}
    },
    {
      pattern = OptionalSpace * P("hash") * Space * DeviceName * Space * UnfinishedInteger * -1,
      hint = "    this is the startaddress"
    },
    {
      pattern = OptionalSpace * P("hash") * Space * DeviceName * Space * Integer * Space * -1,
      hint = "[endaddress]  or  + [length]"
    },
    {
      pattern = OptionalSpace * P("hash") * Space * DeviceName * Space * Integer * Space * UnfinishedInteger * -1,
      hint = "    this is the endaddress"
    },
    {
      pattern = OptionalSpace * P("hash") * Space * DeviceName * Space * Integer * Space * P("+") * OptionalSpace * -1,
      hint = "[length]"
    },
    {
      pattern = OptionalSpace * P("hash") * Space * DeviceName * Space * Integer * Space * P("+") * Space *
        UnfinishedInteger *
        -1,
      hint = "    this is the length"
    },
    -- input command.
    {
      pattern = OptionalSpace * P("input") * Space * -1,
      hint = "[filename]",
      words = function(strMatch)
        return self:__getFilenameWords(strMatch)
      end
    },
    {
      pattern = OptionalSpace * P("input") * Space * Cg(Filename) * -1,
      words = function(strMatch)
        return self:__getFilenameWords(strMatch)
      end
    },
    -- Help command.
    {
      pattern = OptionalSpace * P("help") * Space * -1,
      hint = function()
        return "[topic]  possible values: " .. table.concat(self.__astrHelpTopicWords, ", ")
      end,
      words = function()
        return self.__astrHelpTopicWords
      end
    },
    {
      pattern = OptionalSpace * P("help") * Space * Cg(R("az") ^ 1) * -1,
      words = function()
        return self.__astrHelpTopicWords
      end
    },
    -- debug command.
    {
      pattern = OptionalSpace * P("debug") * Space * -1,
      hint = function()
        return "[Command]  possible values: " .. table.concat(self.AllCommands_debug, ", ")
      end,
      words = function()
        return self.AllCommands_debug
      end
    },
    {
      pattern = OptionalSpace * P("debug") * Space * Cg(R("az", "AZ") ^ 1) * -1,
      words = function()
        return self.AllCommands_debug
      end
    },
    {
      pattern = OptionalSpace * P("debug") * Space * P("save") * Space * -1,
      hint = "[filename]",
      words = function(strMatch)
        return self:__getFilenameWords(strMatch)
      end
    },
    {
      pattern = OptionalSpace * P("debug") * Space * P("save") * Space * Cg(Filename) * -1,
      words = function(strMatch)
        return self:__getFilenameWords(strMatch)
      end
    },
    -- list command.
    {
      pattern = OptionalSpace * P("list") * Space * -1,
      hint = function()
        return "[Command]  possible values: " .. table.concat(self.AllCommands_list, ", ")
      end,
      words = function()
        return self.AllCommands_list
      end
    },
    {
      pattern = OptionalSpace * P("list") * Space * Cg(R("az", "AZ") ^ 1) * -1,
      words = function()
        return self.AllCommands_list
      end
    },
    {
      pattern = OptionalSpace * P("list") * Space * P("save") * Space * -1,
      hint = "[filename]",
      words = function(strMatch)
        return self:__getFilenameWords(strMatch)
      end
    },
    {
      pattern = OptionalSpace * P("list") * Space * P("save") * Space * Cg(Filename) * -1,
      words = function(strMatch)
        return self:__getFilenameWords(strMatch)
      end
    },
    -- clear command (list command only)
    {
      pattern = OptionalSpace * P("clear") * Space * -1,
      hint = function()
        if self.list_cmd == true then
          return "all  or  [number to clear]"
        end
      end,
      words = function()
        if self.list_cmd == true then
          return {"all"}
        end
      end
    },
    {
      pattern = OptionalSpace * P("clear") * Space * Cg(P("al") + P("a")) * -1,
      words = function()
        if self.list_cmd == true then
          return {"all"}
        end
      end
    },
    {
      pattern = OptionalSpace * P("clear") * Space * UnfinishedInteger * -1,
      hint = function()
        if self.list_cmd == true then
          return "    this is the number of the list to clear"
        end
      end
    }
  }
end

function Shell:__getNetxPath()
  local pl = self.pl

  local strPathNetx

  -- Split the Lua module path.
  local astrPaths = pl.stringx.split(package.path, ";")
  for _, strPath in ipairs(astrPaths) do
    -- Only process search paths which end in "?.lua".
    if string.sub(strPath, -5) == "?.lua" then
      -- Cut off the "?.lua" part.
      -- Expect the "netx" folder one below the module folder.
      local strPath = pl.path.join(pl.path.dirname(pl.path.dirname(pl.path.abspath(strPath))), "netx")
      if pl.path.exists(strPath) ~= false and pl.path.isdir(strPath) == true then
        -- Append a directory separator at the end of the path.
        -- Otherwise the flasher will not be happy.
        strPathNetx = strPath .. pl.path.sep
        break
      end
    end
  end
  return strPathNetx
end

function Shell:__getFolderEntries(strFolder, strPrintPrefix, astrWords)
  local pl = self.pl
  local strSep = pl.path.sep

  -- Use the "walk" function here to get plain lists of files and folders
  -- which are not combined with the path yet. "walk" returns an iterator, so
  -- the result of walk is called again.
  local _, astrFolders, astrFiles = pl.dir.walk(strFolder, false, false)()
  table.sort(astrFolders)
  table.sort(astrFiles)
  for _, strFolder in ipairs(astrFolders) do
    table.insert(astrWords, pl.path.join(strPrintPrefix, strFolder) .. strSep)
  end
  for _, strFile in ipairs(astrFiles) do
    table.insert(astrWords, pl.path.join(strPrintPrefix, strFile))
  end
end

function Shell:__getFilenameWords(strMatch)
  local pl = self.pl
  local strSep = pl.path.sep
  local astrWords = {}

  local strDir = strMatch
  local strPrintPrefix = strMatch

  if strDir == "" then
    -- An empty match is special. Use the current working folder.
    strDir = pl.path.currentdir()
    strPrintPrefix = ""
    self:__getFolderEntries(strDir, strPrintPrefix, astrWords)
  else
    -- Expand a "~".
    strDir = pl.path.expanduser(strDir)

    local strLastElement = pl.path.basename(strDir)

    -- Does the folder exist?
    if strLastElement ~= "." and pl.path.exists(strDir) ~= false and pl.path.isdir(strDir) == true then
      -- Yes -> add all elements of this folder.
      self:__getFolderEntries(strDir, strPrintPrefix, astrWords)
    else
      -- The folder does not exist. Try to cut off the last path element.
      local strDirName = pl.path.dirname(strDir)

      if strDirName == "" then
        if pl.path.isabs(strDir) then
          -- TODO: port this to windows.
          strDir = strSep
          strPrintPrefix = strSep
          self:__getFolderEntries(strDir, strPrintPrefix, astrWords)
        else
          strDir = pl.path.currentdir()
          strPrintPrefix = ""
          self:__getFolderEntries(strDir, strPrintPrefix, astrWords)
        end
      elseif pl.path.exists(strDirName) ~= false and pl.path.isdir(strDirName) == true then
        strDir = strDirName

        -- Cut off the last Element from the print prefix.
        strPrintPrefix = string.sub(strPrintPrefix, 1, -1 - string.len(strLastElement))
        self:__getFolderEntries(strDir, strPrintPrefix, astrWords)
      end
    end
  end

  return astrWords
end

Shell.__HelpTopics_templete = {
  text = [[
#if tTopic.name ~= nil then
$(string.upper('name'))
  $(tTopic.name)
# end

#if tTopic.synopsis ~= nil then
$(string.upper('synopsis'))
  $(tTopic.synopsis)
# end

#if tTopic.description ~= nil then
$(string.upper('description'))
  $(tTopic.description)
# end

#if tTopic.options ~= nil then
$(string.upper('options'))
# local sizMax = 0
# for _,tOption in ipairs(tTopic.options) do
#   local sizTopic = string.len(tOption.key)
#   if sizTopic>sizMax then
#     sizMax = sizTopic
#   end
# end 
# for _, tOption in ipairs(tTopic.options) do
  $(tOption.key) $(string.rep(' ', sizMax-string.len(tOption.key))) : $(tOption.description)
# end
#end

# if tTopic.examples ~= nil then
$(string.upper('examples'))
  $(tTopic.examples)
# end
    ]]
}

Shell.__atHelpTopics = {
  {
    topic = "",
    text = [[
    
Welcome to the help.

The help command alone shows this message. It can also combined with a
topic.

The help command has several topics:

# local sizMax = 0
# for _, tTopic in ipairs(topics) do
#   local sizTopic = string.len(tTopic.topic)
#   if sizTopic>sizMax then
#     sizMax = sizTopic
#   end
# end
# for _, tTopic in ipairs(topics) do
#   local strTopic = tTopic.topic
#   if strTopic~='' then
  $(strTopic) $(string.rep(' ', sizMax-string.len(strTopic))) : $(tTopic.name)
#   end
# end

The following example shows help about the read command:

  help read
  
# local tTopic = {}
# for _, tTopicCnt in ipairs(topics) do
#   local strTopic = tTopicCnt.topic
#   if strTopic == 'read' then
#     tTopic = tTopicCnt
#     break
#   end
# end
]] ..
      Shell.__HelpTopics_templete.text
  },
  {
    topic = "start",
    name = "Getting started with the flasher application",
    text = [[
    
This is a short description to getting started with the flasher application. 
To get started with this application, the command scan is required to get an overview of all possible plugins:

  scan

with a result e.g.:

  Found a total of 2 interfaces with 4 plugins:
    romloader_uart_ttyS4
    romloader_uart_ttyUSB0

After the scan command, the connect command with one of the previous displayed plugins is necessary. To utilize the list of commands as shown by using of the help command, like read, write or erase, a connection must be established. After a successful connection with the plugin, like for example:

  connect romloader_uart_ttyUSB0
  
a connection with the plugin is available and the previous mentioned list of commands are possible.
    ]]
  },
  {
    topic = "read",
    name = "The read command",
    synopsis = "read [device] [all | [startaddress][endaddress] | [startaddress] + [length]] [filename]",
    description = "The read command reads the data of the device at the specified address into the stated filename.",
    options = {
      {key = "[device]", description = "the given device"},
      {key = "[all]", description = "the complete flash size"},
      {key = "[startaddress][endaddress]", description = "start- and endaddress of the flash"},
      {key = "[startaddress] + [length]", description = "Start offset in flash plus data size"},
      {key = "[filename]", description = "the given filename"}
    },
    examples = [[read IF01 0x00000000 + 0x00001000 ~/Test/TestData.txt
  read IF1 0x00000000 0x00002000 ~/Test/TestData.txt
  read B2_U3_C0 all ~/Test/TestData.txt
    ]],
    text = Shell.__HelpTopics_templete.text
  },
  {
    topic = "verify",
    name = "The verify command",
    synopsis = "verify [device] [startaddress] [filename]",
    description = "The verify command checks whether the data of the stated file is written in the device at the startdaddress.",
    options = {
      {key = "[device]", description = "the given device"},
      {key = "[startaddress]", description = "startdaddress of the flash"},
      {key = "[filename]", description = "the given filename"}
    },
    examples = [[verify IF01 0x00000000 ~/Test/TestData.txt]],
    text = Shell.__HelpTopics_templete.text
  },
  {
    topic = "write",
    name = "The write command",
    synopsis = "write [device] [startaddress] [filename]",
    description = "The write command writes the data of the stated file into the device at the specified startaddress.",
    options = {
      {key = "[device]", description = "the given device"},
      {key = "[startaddress]", description = "startaddress of the flash"},
      {key = "[filename]", description = "the given filename"}
    },
    examples = [[write IF01 0x00002000 ~/Test/TestData.txt
  write IF1 0x00003000 ~/Test/TestData.txt
  write B2_U3_C0 0x1000 ~/Test/TestData.txt
    ]],
    text = Shell.__HelpTopics_templete.text
  },
  {
    topic = "erase",
    name = "The erase command",
    synopsis = "erase [device] [all | [startaddress][endaddress] | [startaddress] + [length]]",
    description = "The erase command delete the data of the device at the specified address.",
    options = {
      {key = "[device]", description = "the given device"},
      {key = "[all]", description = "the complete flash size"},
      {key = "[startaddress][endaddress]", description = "start- and endaddress of the flash"},
      {key = "[startaddress] + [length]", description = "Start offset in flash plus data size"}
    },
    examples = [[erase IF01 0x00000000 + 0x00001000
  erase IF1 0x00000000 0x00002000
  erase B2_U3_C0 all
    ]],
    text = Shell.__HelpTopics_templete.text
  },
  {
    topic = "iserased",
    name = "The iserased command",
    synopsis = "iserased [device] [all | [startaddress][endaddress] | [startaddress] + [length]]",
    description = "The iserased command checks whether the data is deleted of the device at the specified address.",
    options = {
      {key = "[device]", description = "the given device"},
      {key = "[all]", description = "the complete flash size"},
      {key = "[startaddress][endaddress]", description = "start- and endaddress of the flash"},
      {key = "[startaddress] + [length]", description = "Start offset in flash plus data size"}
    },
    examples = [[iserased IF01 0x00000000 + 0x00001000 
  iserased IF1 0x00000000 0x00002000 
  iserased B2_U3_C0 all
    ]],
    text = Shell.__HelpTopics_templete.text
  },
  {
    topic = "hash",
    name = "The hash command",
    synopsis = "hash [device] [all | [startaddress][endaddress] | [startaddress] + [length]]",
    description = "The hash command returns the SHA1 checksum of the specified address.",
    options = {
      {key = "[device]", description = "the given device"},
      {key = "[all]", description = "the complete flash size"},
      {key = "[startaddress][endaddress]", description = "start- and endaddress of the flash"},
      {key = "[startaddress] + [length]", description = "Start offset in flash plus data size"}
    },
    examples = [[hash IF01 0x00000000 + 0x00001000 
  hash IF1 0x00000000 0x00002000 
  hash B2_U3_C0 all
    ]],
    text = Shell.__HelpTopics_templete.text
  },
  {
    topic = "scan",
    name = "The scan command",
    synopsis = "scan",
    description = "The scan command searches for devices and lists all possibilities of plugins.",
    text = Shell.__HelpTopics_templete.text
  },
  {
    topic = "connect",
    name = "The connect command",
    synopsis = "connect [plugin]",
    description = "The connect command establishes a connection with the plugin.",
    options = {
      {key = "[plugin]", description = "the given plugins"}
    },
    examples = [[connect romloader_uart_ttyUSB0
    ]],
    text = Shell.__HelpTopics_templete.text
  },
  {
    topic = "disconnect",
    name = "The disconnect command",
    synopsis = "disconnect",
    description = "The disconnect command disconnects from the plugin.",
    text = Shell.__HelpTopics_templete.text
  },
  {
    topic = "input",
    name = "The input command",
    synopsis = "input [filename]",
    description = "The input command reads a specified input file and verify whether each line is a valid command. This command makes it easier to enter repetitive command blocks.",
    options = {
      {key = "[filename]", description = "file with list of commands - line by line"}
    },
    examples = [[The input file should be, for example, in the following format:

  connect romloader_uart_ttyUSB0 
  erase IF01 all 
  iserased IF01 all 
  write IF01 0x00000000 TestData/testDataA.txt 
  verify IF01 0x00000000 testDataA.txt 
    ]],
    text = Shell.__HelpTopics_templete.text
  },
  {
    topic = "quit",
    name = "The quit command",
    description = [[The quit command quits the application without a safety question.
A connection to a netx is closed.]],
    text = Shell.__HelpTopics_templete.text
  }
}

------------------------------------------------------------------------------

function Shell:__run_help(tCmd)
  -- Get the topic. If no topic was specified, set the topic to the empty
  -- string - which selects the main page.
  local strTopic = tCmd.topic or ""
  local tLog = self.tLog

  -- Search the topic.
  local tTopic
  for _, tTopicCnt in ipairs(self.__atHelpTopics) do
    if tTopicCnt.topic == strTopic then
      tTopic = tTopicCnt
      break
    end
  end
  if tTopic == nil then
    -- Topic not found. Show an error.
    tLog.error('Unknown help topic "%s".', strTopic)
  else
    -- Process the template.
    local strText, strError =
      self.pl.template.substitute(
      tTopic.text,
      {
        ipairs = ipairs,
        pairs = pairs,
        string = string,
        tTopic = tTopic,
        topics = self.__atHelpTopics
      }
    )
    if strText == nil then
      -- Failed to process the template. Show an error message.
      tLog.error("Failed to render the help text: " .. tostring(strError))
    else
      -- Show the generated help text.
      print(strText)
    end
  end

  return true
end

------------------------------------------------------------------------------

function Shell:__getBusUnitCs(strDevice)
  local lpeg = self.lpeg
  local tLog = self.tLog
  local fOk = true
  local ucBus
  local ucUnit
  local ucCS

  -- Try to parse the device as a general "Bxxx_Uxxx_Cxxx" ID.
  local tMatch = lpeg.match(self.tMatchBusUnitCs, strDevice)
  if tMatch ~= nil then
    ucBus = tMatch.bus
    ucUnit = tMatch.unit
    ucCS = tMatch.cs
    if ucBus < 0 or ucBus > 255 then
      tLog.error("The bus exceeds the allowed range of an 8 bit number: %d", ucBus)
      fOk = false
    end
    if ucUnit < 0 or ucUnit > 255 then
      tLog.error("The unit exceeds the allowed range of an 8 bit number: %d", ucUnit)
      fOk = false
    end
    if ucCS < 0 or ucCS > 255 then
      tLog.error("The chip select exceeds the allowed range of an 8 bit number: %d", ucCS)
      fOk = false
    end
  else
    -- Search the ID in the list of known devices.
    for _, tDeviceInfo in ipairs(self.__aBoardInfo) do
      if strDevice == tDeviceInfo.id then
        ucBus = tDeviceInfo.bus
        ucUnit = tDeviceInfo.unit
        ucCS = tDeviceInfo.cs
        break
      end
    end
    if ucBus == nil then
      tLog.error('Unknown device ID "%s".', strDevice)
      fOk = false
    end
  end

  -- Invalidate the bus, unit and chip select if something went wrong.
  if fOk ~= true then
    ucBus = nil
    ucUnit = nil
    ucCS = nil
  end

  return ucBus, ucUnit, ucCS
end

function Shell:__getRange(tCmd)
  local tFlasher = self.tFlasher
  local tPlugin = self.tPlugin
  local aAttr = self.aAttr
  local ulStart
  local ulLength
  local ulDeviceSize
  local tLog = self.tLog
  local pl = self.pl
  local tLog_ProgressBar = self.tLog_ProgressBar
  local tProgressBars =
    pl.Map {
    netx = require "progressbar"(
      tLog_ProgressBar,
      {mode = (not debugMode_ProgressBar) and "debug" or nil, prefix = "[NETX]: ", repeatProgress = true}
    ),
    switchToDevice = require "progressbar"(
      tLog_ProgressBar,
      {mode = (not debugMode_ProgressBar) and "debug" or nil, prefix = "[getRange] : "}
    )
  }

  if tPlugin == nil or aAttr == nil then
    tLog.info("Not connected.")
  elseif tCmd.all ~= nil then
    ulStart = 0
    ulDeviceSize =
    tFlasher:getFlashSize(
    tPlugin,
    aAttr,
    tProgressBars:get("netx").fnMessageProgressBar,
    tProgressBars:get("switchToDevice").fnProgressBar
  )
  if ulDeviceSize then
    tLog.debug("Flash size: 0x%08x bytes", ulDeviceSize)
    ulLength = ulDeviceSize
  else
    tLog.error("Could not determine the flash size!")
  end
else -- in the case of: start adress, end adress AND start adress + length AND start adress
  ulDeviceSize =
    tFlasher:getFlashSize(
    tPlugin,
    aAttr,
    tProgressBars:get("netx").fnMessageProgressBar,
    tProgressBars:get("switchToDevice").fnProgressBar
  )
  if not ulDeviceSize then
    tLog.error("Could not determine the flash size!")
  else
    tLog.debug("Flash size: 0x%08x bytes", ulDeviceSize)

    ulStart = tCmd.startaddress
    ulLength = tCmd.length

    if ulStart > ulDeviceSize then
      tLog.error("The given startaddress 0x%08x exceeds the size of the device.", ulStart)
      return nil, nil
    end

    if ulLength ~= nil and ulStart + ulLength > ulDeviceSize then
      ulLength = ulDeviceSize - ulStart
      tLog.debug(
        "The given length + startaddress is greater than the size of the device. The length is set to: 0x%08x",
        ulLength
      )
    end

    if ulLength == nil then
      local ulEnd = tCmd.endaddress

       if ulEnd ~= nil then
          if ulEnd > ulDeviceSize then
            ulEnd = ulDeviceSize
            tLog.debug(
              "The given endaddress is greater than the size of the device. The endaddress is set to: 0x%08x",
              ulEnd
            )
          elseif ulEnd < ulStart then
        tLog.error("The startaddress must be smaller than the endaddress.")
        ulStart = nil
      else
        ulLength = ulEnd - ulStart
      end
    end
  end
 end
end

  return ulStart, ulLength
end

function Shell:__switchToDevice(ucBus, ucUnit, ucCS)
  local tFlasher = self.tFlasher
  local tPlugin = self.tPlugin
  local aAttr = self.aAttr
  local tLog = self.tLog
  local tResult
  local pl = self.pl
  local tLog_ProgressBar = self.tLog_ProgressBar
  local tProgressBars =
    pl.Map {
    netx = require "progressbar"(
      tLog_ProgressBar,
      {mode = (not debugMode_ProgressBar) and "debug" or nil, prefix = "[NETX]: ", repeatProgress = true}
    ),
    switchToDevice = require "progressbar"(
      tLog_ProgressBar,
      {mode = (not debugMode_ProgressBar) and "debug" or nil, prefix = "[switchToDevice] : "}
    )
  }

  if tPlugin == nil or aAttr == nil then
    tLog.info("Not connected.")
    tResult = false
  elseif ucBus == self.__ucCurrentBus and ucUnit == self.__ucCurrentUnit and ucCS == self.__ucCurrentCS then
    tLog.debug("Continue to use bus %d, unit %d, CS %d.", ucBus, ucUnit, ucCS)
    tResult = true
  else
    tLog.debug("Switch to bus %d, unit %d, CS %d.", ucBus, ucUnit, ucCS)

    local fOk =
    tFlasher:detect(
    tPlugin,
    aAttr,
    ucBus,
    ucUnit,
    ucCS,
    tProgressBars:get("netx").fnMessageProgressBar,
    tProgressBars:get("switchToDevice").fnProgressBar
  )
    if fOk ~= true then
      tLog.error("Failed to detect a device")
      tResult = false
    else
      -- Switched to the new device. Remember the bus, unit and CS for next time.
      self.__ucCurrentBus = ucBus
      self.__ucCurrentUnit = ucUnit
      self.__ucCurrentCS = ucCS

      tResult = true
    end
  end

  return tResult
end

function Shell:__run_read(tCmd)
  local tFlasher = self.tFlasher
  local tPlugin = self.tPlugin
  local aAttr = self.aAttr
  local pl = self.pl
  local tLog = self.tLog
  local tLog_ProgressBar = self.tLog_ProgressBar
  local tProgressBars =
    pl.Map {
    netx = require "progressbar"(
      tLog_ProgressBar,
      {mode = (not debugMode_ProgressBar) and "debug" or nil, prefix = "[NETX]: ", repeatProgress = true}
    ),
    TotalProgress = require "progressbar"(
      tLog_ProgressBar,
      {
        {
          prefix = "Device ",
          SL_Iteration = 0,
          SL_Total = 3,
          showTotalProgress = true,
          printEnd = (not debugMode_ProgressBar and not debugMode) and "\n" or "",
          printLine = (not debugMode_ProgressBar and not debugMode) and "" or "\n",
          ProcessAlgo = "SingleLine"
        },
        {
          prefix = "readArea ",
          SL_Iteration = 1,
          SL_Total = 2,
          showTotalProgress = true,
          printEnd = (not debugMode_ProgressBar and not debugMode) and "\n" or "",
          printLine = (not debugMode_ProgressBar and not debugMode) and "" or "\n",
          ProcessAlgo = "SingleLine"
        },
        {
          prefix = "Result ",
          suffix = " OK",
          showTotalProgress = true
        },
        {
          prefix = "WriteData ",
          SL_Iteration = 0,
          SL_Total = 1,
          showTotalProgress = true,
          printEnd = (not debugMode_ProgressBar and not debugMode) and "\n" or "",
          printLine = (not debugMode_ProgressBar and not debugMode) and "" or "\n",
          ProcessAlgo = "SingleLine"
        },
        {
          prefix = "Result ",
          suffix = " OK",
          showTotalProgress = true
        }
      }
    )
  }

  tProgressBars:get("TotalProgress").fnProgressBar()

  if tPlugin == nil or aAttr == nil then
    print()
    tLog.info("Not connected.")
  else
    -- Get the bus, unit and chipselect.
    local strDevice = tCmd.device
    local ucBus, ucUnit, ucCS = self:__getBusUnitCs(strDevice)
    if ucBus ~= nil then
      tLog.debug("Using bus %d, unit %d, CS %d.", ucBus, ucUnit, ucCS)
      tProgressBars:get("TotalProgress").fnProgressBar()
      local tResult = self:__switchToDevice(ucBus, ucUnit, ucCS)
      if tResult == true then
        tProgressBars:get("TotalProgress").fnProgressBar()
        local ulStart, ulLength = self:__getRange(tCmd)
        if ulStart ~= nil and ulLength ~= nil then
          tProgressBars:get("TotalProgress").fnProgressBar()
          local ulEnd = ulStart + ulLength
          tLog.debug("Reading [0x%08x,0x%08x[ .", ulStart, ulEnd)

           -- simulate readArea to calculate total of progress bar
           local SL_Total = function()
            local ultotal_offset = 0
            local ultotal = 0
            local ulBufferLen = aAttr.ulBufferLen
            local ulSize = ulLength
            local ulChunkSize

            if ulSize == 0xffffffff then
              ultotal_offset = 1
              ulSize =
                tFlasher:getFlashSize(
                tPlugin,
                aAttr,
                function()
                  return true
                end,
                function()
                  return true
                end
              )
              if ulSize then
                ulSize = ulSize - ulStart
              end
            end
            while ulSize > 0 do
              ulChunkSize = math.min(ulSize, ulBufferLen)
              ulSize = ulSize - ulChunkSize
              ultotal = ultotal + 1
            end
            return 2 * ultotal + ultotal_offset
          end

          tProgressBars:get("TotalProgress").tparam.SL_Total = SL_Total()

          -- tProgressBars:get("readArea").tparam.totalByteSize = ulLength

          local strBin, strMsg =
            tFlasher:readArea(
            tPlugin,
            aAttr,
            ulStart,
            ulLength,
            tProgressBars:get("netx").fnMessageProgressBar,
            tProgressBars:get("TotalProgress").fnProgressBar
          )

          if strBin == nil then
            tProgressBars:get("TotalProgress").tparam.suffix = " Failed"
            tProgressBars:get("TotalProgress").fnProgressBar()
            tLog.error("Failed to read: " .. tostring(strMsg))
          else
            tProgressBars:get("TotalProgress").fnProgressBar()

            tProgressBars:get("TotalProgress").fnProgressBar()
            local strFilename = pl.path.expanduser(tCmd.filename)
            tResult, strMsg = pl.utils.writefile(strFilename, strBin, true)
            tProgressBars:get("TotalProgress").fnProgressBar()
            if tResult == true then
              tProgressBars:get("TotalProgress").fnProgressBar()
              tLog.info("OK. Data [0x%08x,0x%08x[ written to the file '%s'", ulStart, ulEnd, strFilename)
            else
              tProgressBars:get("TotalProgress").tparam.suffix = " Failed"
              tProgressBars:get("TotalProgress").fnProgressBar()
              tLog.error('Failed to write the data to the file "%s": %s', strFilename, strMsg)
            end
          end
        end
      end
    end
  end

  return true
end

function Shell:__run_verify(tCmd)
  local tFlasher = self.tFlasher
  local tPlugin = self.tPlugin
  local aAttr = self.aAttr
  local pl = self.pl
  local tLog = self.tLog
  local tLog_ProgressBar = self.tLog_ProgressBar
  local tProgressBars =
    pl.Map {
    netx = require "progressbar"(
      tLog_ProgressBar,
      {mode = (not debugMode_ProgressBar) and "debug" or nil, prefix = "[NETX]: ", repeatProgress = true}
    ),
    TotalProgress = require "progressbar"(
      tLog_ProgressBar,
      {
        {
          prefix = "Device ",
          SL_Iteration = 0,
          SL_Total = 3,
          showTotalProgress = true,
          printEnd = (not debugMode_ProgressBar and not debugMode) and "\n" or "",
          printLine = (not debugMode_ProgressBar and not debugMode) and "" or "\n",
          ProcessAlgo = "SingleLine"
        },
        {
          prefix = "LoadData ",
          SL_Iteration = 0,
          SL_Total = 2,
          showTotalProgress = true,
          printEnd = (not debugMode_ProgressBar and not debugMode) and "\n" or "",
          printLine = (not debugMode_ProgressBar and not debugMode) and "" or "\n",
          ProcessAlgo = "SingleLine"
        },
        {
          prefix = "verifyArea ",
          SL_Iteration = 1,
          SL_Total = 2,
          showTotalProgress = true,
          printEnd = (not debugMode_ProgressBar and not debugMode) and "\n" or "",
          printLine = (not debugMode_ProgressBar and not debugMode) and "" or "\n",
          ProcessAlgo = "SingleLine"
        },
        {
          prefix = "Result ",
          suffix = " OK",
          showTotalProgress = true
        }
      }
    )
  }

  tProgressBars:get("TotalProgress").fnProgressBar()

  if tPlugin == nil or aAttr == nil then
    print()
    tLog.info("Not connected.")
  else
    -- Get the bus, unit and chipselect.
    local strDevice = tCmd.device
    local ucBus, ucUnit, ucCS = self:__getBusUnitCs(strDevice)
    if ucBus ~= nil then
      tLog.debug("Using bus %d, unit %d, CS %d.", ucBus, ucUnit, ucCS)
      tProgressBars:get("TotalProgress").fnProgressBar()

      local tResult = self:__switchToDevice(ucBus, ucUnit, ucCS)
      if tResult == true then
        tProgressBars:get("TotalProgress").fnProgressBar()
        
        local ulStart = self:__getRange(tCmd)
        if ulStart ~= nil then
        tProgressBars:get("TotalProgress").fnProgressBar()

          tProgressBars:get("TotalProgress").fnProgressBar()
        local strFilename = pl.path.expanduser(tCmd.filename)
        if pl.path.exists(strFilename) == false then
          tLog.error('The file "%s" does not exist.', strFilename)
        elseif pl.path.isfile(strFilename) ~= true then
          tLog.error('The path "%s" is not a file.', strFilename)
        else
          tProgressBars:get("TotalProgress").fnProgressBar()
          tLog.debug('Verify "%s" at offset 0x%08x...', strFilename, ulStart)

          local strBin, strMsg = pl.utils.readfile(strFilename, true)
          if strBin == nil then
            tLog.error('Failed to read "%s" : ', strFilename, tostring(strMsg))
          else
            tProgressBars:get("TotalProgress").fnProgressBar()

              -- simulate verifyArea to calculate total of progress bar
              local SL_Total = function()
                local ultotal = 0
                local ulDataOffset = 0
                local ulDataByteSize = strBin:len()
                local ulBufferLen = aAttr.ulBufferLen
                local ulChunkSize
                local strChunk
                while ulDataOffset < ulDataByteSize do
                  strChunk = strBin:sub(ulDataOffset + 1, ulDataOffset + ulBufferLen)
                  ulChunkSize = strChunk:len()
                  ulDataOffset = ulDataOffset + ulChunkSize
                  ultotal = ultotal + 1
                end
                return 2 * ultotal
              end

              tProgressBars:get("TotalProgress").tparam.SL_Total = SL_Total()

            -- Erase the area.
            tResult, strMsg =
                tFlasher:verifyArea(
                tPlugin,
                aAttr,
                ulStart,
                strBin,
                tProgressBars:get("netx").fnMessageProgressBar,
                tProgressBars:get("TotalProgress").fnProgressBar
              )
            if tResult == true then
              tProgressBars:get("TotalProgress").fnProgressBar()
              tLog.info(
                  'Verify OK. The data in the flash at offset 0x%08x is equals to the file "%s".',
                  ulStart,
                  strFilename
                )
            else
              tProgressBars:get("TotalProgress").tparam.suffix = " Failed"
                tProgressBars:get("TotalProgress").fnProgressBar()
              tLog.error(
                  'Verify error. The flash contents at offset 0x%08x differ from the file "%s".',
                  ulStart,
                  strFilename
                )
            end
          end
        end
      end
    end
  end
end

  return true
end

function Shell:__run_write(tCmd)
  local tFlasher = self.tFlasher
  local tPlugin = self.tPlugin
  local aAttr = self.aAttr
  local pl = self.pl
  local tLog = self.tLog
  local tLog_ProgressBar = self.tLog_ProgressBar
  local tProgressBars =
    pl.Map {
    netx = require "progressbar"(
      tLog_ProgressBar,
      {mode = (not debugMode_ProgressBar) and "debug" or nil, prefix = "[NETX]: ", repeatProgress = true}
    ),
    TotalProgress = require "progressbar"(
      tLog_ProgressBar,
      {
        {
          prefix = "Device ",
          SL_Iteration = 0,
          SL_Total = 3,
          showTotalProgress = true,
          printEnd = (not debugMode_ProgressBar and not debugMode) and "\n" or "",
          printLine = (not debugMode_ProgressBar and not debugMode) and "" or "\n",
          ProcessAlgo = "SingleLine"
        },
        {
          prefix = "LoadData ",
          SL_Iteration = 0,
          SL_Total = 2,
          showTotalProgress = true,
          printEnd = (not debugMode_ProgressBar and not debugMode) and "\n" or "",
          printLine = (not debugMode_ProgressBar and not debugMode) and "" or "\n",
          ProcessAlgo = "SingleLine"
        },
        {
          prefix = "eraseArea ",
          SL_Iteration = 1,
          SL_Total = 4,
          showTotalProgress = true,
          printEnd = (not debugMode_ProgressBar and not debugMode) and "\n" or "",
          printLine = (not debugMode_ProgressBar and not debugMode) and "" or "\n",
          ProcessAlgo = "SingleLine"
        },
        {
          prefix = "Result ",
          suffix = " OK",
          showTotalProgress = true
        },
        {
          prefix = "flashArea ",
          SL_Iteration = 1,
          SL_Total = 2,
          showTotalProgress = true,
          printEnd = (not debugMode_ProgressBar and not debugMode) and "\n" or "",
          printLine = (not debugMode_ProgressBar and not debugMode) and "" or "\n",
          ProcessAlgo = "SingleLine"
        },
        {
          prefix = "Result ",
          suffix = " OK",
          showTotalProgress = true
        }
      }
    )
  }

  tProgressBars:get("TotalProgress").fnProgressBar()

  if tPlugin == nil or aAttr == nil then
    print()
    tLog.info("Not connected.")
  else
    -- Get the bus, unit and chipselect.
    local strDevice = tCmd.device
    local ucBus, ucUnit, ucCS = self:__getBusUnitCs(strDevice)
    if ucBus ~= nil then
      tLog.debug("Using bus %d, unit %d, CS %d.", ucBus, ucUnit, ucCS)
      tProgressBars:get("TotalProgress").fnProgressBar()

      local tResult = self:__switchToDevice(ucBus, ucUnit, ucCS)
      if tResult == true then
        tProgressBars:get("TotalProgress").fnProgressBar()
        
        local ulStart = self:__getRange(tCmd)
        if ulStart ~= nil then
        tProgressBars:get("TotalProgress").fnProgressBar()

        tProgressBars:get("TotalProgress").fnProgressBar()
        local strFilename = pl.path.expanduser(tCmd.filename)
        if pl.path.exists(strFilename) == false then
          tLog.error('The file "%s" does not exist.', strFilename)
        elseif pl.path.isfile(strFilename) ~= true then
          tLog.error('The path "%s" is not a file.', strFilename)
        else
          tProgressBars:get("TotalProgress").fnProgressBar()
          tLog.debug('Writing "%s" to offset 0x%08x...', strFilename, ulStart)

          local strBin, strMsg = pl.utils.readfile(strFilename, true)
          if strBin == nil then
            tLog.error('Failed to read "%s" : ', strFilename, tostring(strMsg))
          else
            tProgressBars:get("TotalProgress").fnProgressBar()
            -- Get the size of the data in bytes.
            local sizBin = string.len(strBin)

            -- Erase the area.
            tResult, strMsg =
            tFlasher:eraseArea(
            tPlugin,
            aAttr,
            ulStart,
            sizBin,
            tProgressBars:get("netx").fnMessageProgressBar,
            tProgressBars:get("TotalProgress").fnProgressBar
          )

          tProgressBars:get("TotalProgress").tparam.printLine = ""
          tProgressBars:get("TotalProgress").tparam.printEnd = "\n"
          while tProgressBars:get("TotalProgress").tparam.ProgressBarFinished == false and
            tProgressBars:get("TotalProgress").iteration == 3 do
            tProgressBars:get("TotalProgress").fnProgressBar()
          end

            if tResult ~= true then
              tProgressBars:get("TotalProgress").tparam.suffix = " Failed"
              tProgressBars:get("TotalProgress").fnProgressBar()
              tLog.error("Failed to erase the area: " .. tostring(strMsg))
            else
              tProgressBars:get("TotalProgress").fnProgressBar()

                -- simulate flashArea to calculate total of the progress bar
                local SL_Total = function()
                  local ultotal = 0
                  local ulDataOffset = 0
                  local ulDataByteSize = strBin:len()
                  local ulChunkSize
                  local strChunk
                  local ulBufferLen = aAttr.ulBufferLen
                  while ulDataOffset < ulDataByteSize do
                    local ulEnd = ulDataOffset + ulBufferLen
                    if ulEnd < ulDataByteSize then
                      ulEnd = ulEnd - (ulEnd % 16)
                    end
                    strChunk = strBin:sub(ulDataOffset + 1, ulEnd)
                    ulChunkSize = strChunk:len()

                    ulDataOffset = ulDataOffset + ulChunkSize
                    ultotal = ultotal + 1
                  end
                  return 2 * ultotal
                end

                tProgressBars:get("TotalProgress").tparam.SL_Total = SL_Total()

              -- Flash the data. This includes a verify.
              tResult, strMsg =
              tFlasher:flashArea(
              tPlugin,
              aAttr,
              ulStart,
              strBin,
              tProgressBars:get("netx").fnMessageProgressBar,
              tProgressBars:get("TotalProgress").fnProgressBar
            )
              if tResult ~= true then
                tProgressBars:get("TotalProgress").tparam.suffix = " Failed"
                tProgressBars:get("TotalProgress").fnProgressBar()
                tLog.error("Failed to write the area: " .. tostring(strMsg))
              end
            end

            if tResult == true then
              tProgressBars:get("TotalProgress").fnProgressBar()
              local ulEndadress = ulStart + strBin:len()
              tLog.info("OK. Data '%s' written to [0x%08x,0x%08x[ ", strFilename, ulStart, ulEndadress)
            else
              tProgressBars:get("TotalProgress").tparam.suffix = " Failed"
                tProgressBars:get("TotalProgress").fnProgressBar()
              tLog.error("Failed to write the data: %s", strMsg)
            end
          end
        end
      end
    end
  end
end

  return true
end

function Shell:__run_erase(tCmd)
  local tFlasher = self.tFlasher
  local tPlugin = self.tPlugin
  local aAttr = self.aAttr
  local tLog = self.tLog
  local pl = self.pl
  local tLog_ProgressBar = self.tLog_ProgressBar
  local tProgressBars =
    pl.Map {
    netx = require "progressbar"(
      tLog_ProgressBar,
      {mode = (not debugMode_ProgressBar) and "debug" or nil, prefix = "[NETX]: ", repeatProgress = true}
    ),
    TotalProgress = require "progressbar"(
      tLog_ProgressBar,
      {
        {
          prefix = "Device ",
          SL_Iteration = 0,
          SL_Total = 3,
          showTotalProgress = true,
          printEnd = (not debugMode_ProgressBar and not debugMode) and "\n" or "",
          printLine = (not debugMode_ProgressBar and not debugMode) and "" or "\n",
          ProcessAlgo = "SingleLine"
        },
        {
          prefix = "eraseArea ",
          SL_Iteration = 1,
          SL_Total = 4,
          showTotalProgress = true,
          printEnd = (not debugMode_ProgressBar and not debugMode) and "\n" or "",
          printLine = (not debugMode_ProgressBar and not debugMode) and "" or "\n",
          ProcessAlgo = "SingleLine"
        },
        {
          prefix = "Result ",
          suffix = " OK",
          showTotalProgress = true
        }
      }
    )
  }

  tProgressBars:get("TotalProgress").fnProgressBar()

  if tPlugin == nil or aAttr == nil then
    print()
    tLog.info("Not connected.")
  else
    -- Get the bus, unit and chipselect.
    local strDevice = tCmd.device
    local ucBus, ucUnit, ucCS = self:__getBusUnitCs(strDevice)
    if ucBus ~= nil then
      tLog.debug("Using bus %d, unit %d, CS %d.", ucBus, ucUnit, ucCS)
      tProgressBars:get("TotalProgress").fnProgressBar()
      local tResult = self:__switchToDevice(ucBus, ucUnit, ucCS)
      if tResult == true then
        tProgressBars:get("TotalProgress").fnProgressBar()
        local ulStart, ulLength = self:__getRange(tCmd)
        if ulStart ~= nil and ulLength ~= nil then
          tProgressBars:get("TotalProgress").fnProgressBar()
          -- Erase the area.
          local strMsg
          tResult, strMsg =
            tFlasher:eraseArea(
            tPlugin,
            aAttr,
            ulStart,
            ulLength,
            tProgressBars:get("netx").fnMessageProgressBar,
            tProgressBars:get("TotalProgress").fnProgressBar
          )

          tProgressBars:get("TotalProgress").tparam.printLine = ""
          tProgressBars:get("TotalProgress").tparam.printEnd = "\n"
          while tProgressBars:get("TotalProgress").tparam.ProgressBarFinished == false and
            tProgressBars:get("TotalProgress").iteration == 2 do
            tProgressBars:get("TotalProgress").fnProgressBar()
          end

          if tResult == true then
            tProgressBars:get("TotalProgress").fnProgressBar()
            tLog.info("OK. The area [0x%08x,0x%08x[ is erased", ulStart, ulStart + ulLength)
          else
            tProgressBars:get("TotalProgress").tparam.suffix = " Failed"
            tProgressBars:get("TotalProgress").fnProgressBar()
            tLog.error("Failed to erase the data: %s", strMsg)
          end
        end
      end
    end
  end

  return true
end

function Shell:__run_iserased(tCmd)
  local tFlasher = self.tFlasher
  local tPlugin = self.tPlugin
  local aAttr = self.aAttr
  local tLog = self.tLog
  local pl = self.pl
  local tLog_ProgressBar = self.tLog_ProgressBar
  local tProgressBars =
    pl.Map {
    netx = require "progressbar"(
      tLog_ProgressBar,
      {mode = (not debugMode_ProgressBar) and "debug" or nil, prefix = "[NETX]: ", repeatProgress = true}
    ),
    TotalProgress = require "progressbar"(
      tLog_ProgressBar,
      {
        {
          prefix = "Device ",
          SL_Iteration = 0,
          SL_Total = 3,
          showTotalProgress = true,
          printEnd = (not debugMode_ProgressBar and not debugMode) and "\n" or "",
          printLine = (not debugMode_ProgressBar and not debugMode) and "" or "\n",
          ProcessAlgo = "SingleLine"
        },
        {
          prefix = "isErased ",
          showTotalProgress = true
        }
      }
    )
  }

  tProgressBars:get("TotalProgress").fnProgressBar()

  if tPlugin == nil or aAttr == nil then
    print()
    tLog.info("Not connected.")
  else
    -- Get the bus, unit and chipselect.
    local strDevice = tCmd.device
    local ucBus, ucUnit, ucCS = self:__getBusUnitCs(strDevice)
    if ucBus ~= nil then
      tLog.debug("Using bus %d, unit %d, CS %d.", ucBus, ucUnit, ucCS)
      tProgressBars:get("TotalProgress").fnProgressBar()

      local tResult = self:__switchToDevice(ucBus, ucUnit, ucCS)
      if tResult == true then
        tProgressBars:get("TotalProgress").fnProgressBar()
        local ulStart, ulLength = self:__getRange(tCmd)
        if ulStart ~= nil and ulLength ~= nil then
          tProgressBars:get("TotalProgress").fnProgressBar()
          local ulEnd = ulStart + ulLength
          -- is area Erased
          -- strMsg entfernen
          local strMsg  -- is always nil because isErased only returns tResult true/false
          tResult, strMsg =
            tFlasher:isErased(
            tPlugin,
            aAttr,
            ulStart,
            ulEnd,
            tProgressBars:get("netx").fnMessageProgressBar,
            tProgressBars:get("TotalProgress").fnProgressBar
          )
          if tResult == true then
            tLog.info("Clean. The area is erased.")
          else
            tLog.info("Dirty. The area is not erased.")
          end
        end
      end
    end
  end

  return true
end

-- Return the input String as Hex value
function Shell:__str2hex(strData)
  -- one of the magic characters: '.' represents any single character
  return (strData:gsub(
    ".",
    function(c)
      return string.format("%02x", string.byte(c))
    end
  ))
end

function Shell:__run_hash(tCmd)
  local tFlasher = self.tFlasher
  local tPlugin = self.tPlugin
  local aAttr = self.aAttr
  local tLog = self.tLog
  local pl = self.pl
  local tLog_ProgressBar = self.tLog_ProgressBar
  local tProgressBars =
    pl.Map {
    netx = require "progressbar"(
      tLog_ProgressBar,
      {mode = (not debugMode_ProgressBar) and "debug" or nil, prefix = "[NETX]: ", repeatProgress = true}
    ),
    TotalProgress = require "progressbar"(
      tLog_ProgressBar,
      {
        {
          prefix = "Device ",
          SL_Iteration = 0,
          SL_Total = 3,
          showTotalProgress = true,
          printEnd = (not debugMode_ProgressBar and not debugMode) and "\n" or "",
          printLine = (not debugMode_ProgressBar and not debugMode) and "" or "\n",
          ProcessAlgo = "SingleLine"
        },
        {
          prefix = "HashArea ",
          SL_Iteration = 1,
          SL_Total = 2,
          showTotalProgress = true,
          printEnd = (not debugMode_ProgressBar and not debugMode) and "\n" or "",
          printLine = (not debugMode_ProgressBar and not debugMode) and "" or "\n",
          ProcessAlgo = "SingleLine"
        },
        {
          prefix = "Result ",
          suffix = " OK",
          showTotalProgress = true
        }
      }
    )
  }

  tProgressBars:get("TotalProgress").fnProgressBar()
  if tPlugin == nil or aAttr == nil then
    print()
    tLog.info("Not connected.")
  else
    -- Get the bus, unit and chipselect.
    local strDevice = tCmd.device
    local ucBus, ucUnit, ucCS = self:__getBusUnitCs(strDevice)
    if ucBus ~= nil then
      tLog.debug("Using bus %d, unit %d, CS %d.", ucBus, ucUnit, ucCS)
      tProgressBars:get("TotalProgress").fnProgressBar()
      local tResult = self:__switchToDevice(ucBus, ucUnit, ucCS)
      if tResult == true then
        tProgressBars:get("TotalProgress").fnProgressBar()
        local ulStart, ulLength = self:__getRange(tCmd)
        if ulStart ~= nil and ulLength ~= nil then
          tProgressBars:get("TotalProgress").fnProgressBar()

        if ulLength == 0xffffffff then
          tProgressBars:get("TotalProgress").tparam.SL_Total = 3
        end

        -- Hash the area.
        local strMsg
        tResult, strMsg =
          tFlasher:hashArea(
          tPlugin,
          aAttr,
          ulStart,
          ulLength,
          tProgressBars:get("netx").fnMessageProgressBar,
          tProgressBars:get("TotalProgress").fnProgressBar -- hashArea
        )
          if tResult ~= nil then
            tProgressBars:get("TotalProgress").fnProgressBar()
            tLog.info("OK. SHA1 SUM = " .. self:__str2hex(tResult))
          else
            tProgressBars:get("TotalProgress").tparam.suffix = " Failed"
            tProgressBars:get("TotalProgress").fnProgressBar()
            tLog.error("Failed to hash the data: %s", strMsg)
          end
        end
      end
    end
  end

  return true
end

------------------------------------------------------------------------------

function Shell:__run_scan()
  local tLog = self.tLog

  -- Clear all previously detected devices.
  self.__atDetectedDevices = {}
  self.__astrPluginNames = {}

  tLog.debug("Scanning for devices...")
  local aDetectedInterfaces = {}
  local sizNumberOfAvailablePlugins = 0
  if _G.__MUHKUH_PLUGINS ~= nil then
    sizNumberOfAvailablePlugins = #_G.__MUHKUH_PLUGINS
    for _, v in ipairs(_G.__MUHKUH_PLUGINS) do
      tLog.debug("Detecting interfaces with plugin %s", v:GetID())
      local iDetected = v:DetectInterfaces(aDetectedInterfaces)
      tLog.debug("Found %d interfaces with plugin %s", iDetected, v:GetID())
    end
  end
  tLog.debug("")
  tLog.debug("Found a total of %d interfaces with %d plugins", #aDetectedInterfaces, sizNumberOfAvailablePlugins)
  for _, tPlugin in ipairs(aDetectedInterfaces) do
    tLog.debug("  %s", tPlugin:GetName())
  end
  tLog.debug("")
  local astrPluginNames = {}
  for _, tPlugin in ipairs(aDetectedInterfaces) do
    table.insert(astrPluginNames, tPlugin:GetName())
  end

  self.__atDetectedDevices = aDetectedInterfaces
  self.__astrPluginNames = astrPluginNames

  return true
end

------------------------------------------------------------------------------

function Shell:__run_connect(tCmd)
  local tFlasher = self.tFlasher
  local tLog = self.tLog
  local pl = self.pl
  local tLog_ProgressBar = self.tLog_ProgressBar
  local tProgressBars =
    pl.Map {
    netx = require "progressbar"(
      tLog_ProgressBar,
      {mode = (not debugMode_ProgressBar) and "debug" or nil, prefix = "[NETX]: ", repeatProgress = true}
    ),
    TotalProgress = require "progressbar"(
      tLog_ProgressBar,
      {
        {
          prefix = "Connect ",
          SL_Iteration = 0,
          SL_Total = 3,
          showTotalProgress = true,
          printEnd = "",
          printLine = "\n",
          ProcessAlgo = "SingleLine"
        },
        {
          prefix = "Download ",
          showTotalProgress = true
        },
        {
          prefix = "Result ",
          suffix = " OK",
          showTotalProgress = true
        },
        {
          prefix = "BoardInfo ",
          SL_Iteration = 1,
          SL_Total = 2,
          showTotalProgress = true,
          printEnd = (not debugMode_ProgressBar and not debugMode) and "\n" or "",
          printLine = (not debugMode_ProgressBar and not debugMode) and "" or "\n",
          ProcessAlgo = "SingleLine"
        },
        {
          prefix = "Result ",
          suffix = " OK",
          showTotalProgress = true
        }
      }
    )
  }

  -- intial progress bar
  tProgressBars:get("TotalProgress").fnProgressBar()

  local atDetectedDevices = self.__atDetectedDevices

  if #atDetectedDevices == 0 then
    tLog.error('No devices detected to connect to. Run "scan" to search for devices again.')
  else
    self:__run_disconnect()

    tProgressBars:get("TotalProgress").fnProgressBar()

    local strPlugin = tCmd.plugin

    -- The argument to the command must be a valid device.
    for _, tDevice in pairs(atDetectedDevices) do
      if tDevice:GetName() == strPlugin then
        local tPlugin = tDevice:Create()
        if tPlugin == nil then
          tLog.error("Failed to open to the device.")
        else
          tProgressBars:get("TotalProgress").fnProgressBar()
          -- Connect to the netX.
          local tResult, strMsg = pcall(tPlugin.Connect, tPlugin)
          if tResult ~= true then
            tLog.error("Failed to connect: " .. tostring(strMsg))
          else
            -- Download the flasher binary to the netX.
            
            tProgressBars:get("TotalProgress").fnProgressBar()
            local aAttr
            tResult, aAttr =
              pcall(
              tFlasher.download,
              tFlasher,
              tPlugin,
              self.__strPathNetx,
              tProgressBars:get("TotalProgress").fnProgressBar -- Download
            )
            if tResult ~= true or aAttr == nil then
              tLog.error("Failed to download the flasher to the netX: " .. tostring(aAttr))
              tPlugin:Disconnect()
            else
              -- Get the board info.
              tProgressBars:get("TotalProgress").fnProgressBar()
              local aBoardInfo =
                tFlasher:getBoardInfo(
                tPlugin,
                aAttr,
                tProgressBars:get("netx").fnMessageProgressBar,
                tProgressBars:get("TotalProgress").fnProgressBar -- BoardInfo
              )
              if aBoardInfo == nil then
                tLog.error("Failed to get the board info.")
                tPlugin:Disconnect()
              else
                tProgressBars:get("TotalProgress").fnProgressBar()
                -- Get all IDs for the flashes.
                local aSanitizedBoardNames = {}
                for _, tDeviceInfo in ipairs(aBoardInfo) do
                  table.insert(aSanitizedBoardNames, tDeviceInfo.id)
                end
                self.tPlugin = tPlugin
                self.aAttr = aAttr
                self.__aBoardInfo = aBoardInfo
                self.__aSanitizedBoardNames = aSanitizedBoardNames
              end
            end
          end
        end
        break
      end
    end
  end

  return true
end

------------------------------------------------------------------------------

function Shell:__run_disconnect()
  local tPlugin = self.tPlugin
  local tLog = self.tLog
  if tPlugin == nil then
    tLog.info("Not connected, no need to disconnect...")
  else
    tLog.info("Disconnecting from %s.", tPlugin:GetName())
    tPlugin:Disconnect()
    self.tPlugin = nil
    self.aAttr = nil
    self.__aBoardInfo = {}
    self.__aSanitizedBoardNames = {}
  end

  return true
end

------------------------------------------------------------------------------

-- reads the specified input file and verify whether each line is a valid command
function Shell:__run_input(tCmd)
  local pl = self.pl
  local tLog = self.tLog
  local lpeg = self.lpeg
  local AllCommands = self.__AllCommands

  if type(tCmd.filename) ~= "string" then
    tLog.error("The file name must be a string")
  else
    local strFilename = pl.path.expanduser(tCmd.filename)

    if pl.path.exists(strFilename) == false then
      tLog.error("The specified path does not exist")
    else
      if pl.path.isfile(strFilename) == false then
        tLog.error("The specified path does not contain a file name")
      else
        -- read every line in the file and extend the list tCmd_input by appending all the items in the given list.
        self.tCmd_input:extend(pl.utils.readlines(strFilename))

        -- filters all lines of the input file with the given command patters
        self.tCmd_input =
          self.tCmd_input:filter(
          function(x)
            return (lpeg.match(AllCommands, x) ~= nil)
          end,
          AllCommands,
          lpeg.match
        )
        if self.tCmd_input:len() == 0 then
          tLog.error("Invalid File Format")
        end
      end
    end
  end

  return true
end

------------------------------------------------------------------------------

--
function Shell:__run_debug(tCmd)
  local pl = self.pl
  local tLog = self.tLog
  local strFile

  -- display the complete debug information
  if tCmd.watch ~= nil then
    -- save the complete debug information to the file
    strFile = pl.utils.readfile(self.strLogDir .. "/" .. self.strLogFilename, false)
    print(strFile)
  elseif tCmd.save ~= nil then
    local strFilename = pl.path.expanduser(tCmd.filename)

    strFile = pl.utils.readfile(self.strLogDir .. "/" .. self.strLogFilename, false)

    tResult, strMsg = pl.utils.writefile(strFilename, strFile, true)
    if tResult == true then
      tLog.info("OK. The debug information was written to the file '%s'", tCmd.filename)
    else
      tLog.error('Failed to write the data to the file "%s": %s', strFilename, strMsg)
    end
  end

  return true
end

------------------------------------------------------------------------------

--
function Shell:__run_list(tCmd)
  local atCommands = self.__atCommands
  local tGrammar = self.__lineGrammar_withListCmd
  local colors = self.colors
  local linenoise = self.linenoise -- same object as in run - dont matter if require is used
  local lpeg = self.lpeg
  local pl = self.pl
  local tListCmds = pl.List()
  -- local strHistory = ".fsh_history.txt"
  local tLog = self.tLog

  self.list_cmd = true

  linenoise.clearscreen()

  -- nicht laden damit beim ausführen des Befehls jedesmal eine neue list geschrieben wird
  -- linenoise.historyload(strHistory) -- load existing history

  tLog.warning("This is the list command. To adequately close this command and execute the selection, write 'end'.")
  tLog.warning("To clear the list it is possible to use the clear command.")
  tLog.warning("Synopsis:  clear [all | [number to clear]] ")

  --initialization of setcompletion and sethints of linenoise
  -- can be vanishsed, only for test purposes
  linenoise.setcompletion(
    function(tCompletions, strLine)
      self:__completer(tCompletions, strLine)
    end
  )
  linenoise.sethints(
    function(strLine)
      return self:__hints(strLine), {color = 31, bold = false}
    end
  )

  local fRunning = true
  while fRunning do
    if tListCmds:len() > 0 then
      print(string.format("List of all commands:"))
      for k, v in ipairs(tListCmds) do
        print(string.format("[%d] %s", k, v))
      end
    end

    self.strPrompt = colors.bright .. colors.blue .. "List " .. "> " .. colors.white

    local strLine, strError = linenoise.linenoise(self.strPrompt)

    if strLine == nil then
      if strError ~= nil then
        tLog.error("Error: %s", tostring(strError))
      end
      fRunning = false
    elseif #strLine > 0 then
      -- linenoise.historyadd(strLine)
      -- linenoise.historysave(strHistory)
      -- Parse the line.
      local tCmd_temp = lpeg.match(tGrammar, strLine)
      if tCmd_temp == nil then
        tLog.error("Failed to parse the line.")
      else
        -- There should be a command at the "cmd" key.
        -- If there is no command, this is a comment.
        local strCmd = tCmd_temp.cmd
        if strCmd ~= nil then
          -- Search the command.
          local tCmdHit
          for _, tCmdCnt in ipairs(atCommands) do
            if tCmdCnt.cmd == strCmd then
              tCmdHit = tCmdCnt
              break
            end
          end
          if tCmdHit == nil then
            tLog.error("Command not found.")
          elseif strCmd == "end" then
            self.list_cmd = false
            fRunning = false
            if tCmd.run ~= nil then
              self.tCmd_input:extend(tListCmds)
              tLog.info("process the list of commands:")
            elseif tCmd.save ~= nil then
              local strFilename = pl.path.expanduser(tCmd.filename)
              local strFile = ""

              for _,v in ipairs(tListCmds) do
                strFile = strFile .. v .. '\n'
              end

              tResult, strMsg = pl.utils.writefile(strFilename, strFile, true)
              if tResult == true then
                tLog.info("OK. The list of commands was written to the file '%s'", tCmd.filename)
              else
                tLog.error('Failed to write the data to the file "%s": %s', strFilename, strMsg)
              end
            end
          elseif strCmd == "clear" then
            if tCmd_temp.all ~= nil then
              tListCmds:clear()
            elseif tCmd_temp.number ~= nil then
              if tCmd_temp.number > tListCmds:len() then
                tLog.error("The number to clear is greater than the size of the list.")
              elseif tCmd_temp.number == 0 then
                tLog.error("The starting index of the list is 1.")
              else
                tListCmds:remove(tCmd_temp.number)
              end
            end
          else
            tListCmds:append(strLine)
          end
        end
      end
    end
  end

  return true
end

------------------------------------------------------------------------------

function Shell:__run_quit()
  -- Disconnect any existing plugin.
  self:__run_disconnect()

  -- Quit the application.
  return false
end

------------------------------------------------------------------------------

function Shell:__getCompletions(tCompletions, strLine, astrWords, strMatch)
  local sizMatch = string.len(strMatch)
  if sizMatch == 0 then
    -- Add all available words.
    for _, strWord in ipairs(astrWords) do
      tCompletions:add(strLine .. strWord)
    end
  else
    -- Get the prefix of the line without the match.
    local strPrefix = string.sub(strLine, 1, -1 - string.len(strMatch))
    -- Add the devices matching the input.
    for _, strWord in pairs(astrWords) do
      local sizWord = string.len(strWord)
      if sizWord >= sizMatch and string.sub(strWord, 1, sizMatch) == strMatch then
        tCompletions:add(strPrefix .. strWord)
      end
    end
  end
end

function Shell:__getMatchingHints(astrWords, strMatch)
  local sizMatch = string.len(strMatch)

  local atHints = {}
  for _, strWord in pairs(astrWords) do
    local sizWord = string.len(strWord)
    -- Does the word start with the match?
    if sizWord >= sizMatch and string.sub(strWord, 1, sizMatch) == strMatch then
      -- Do not add the complete argument for the first match. It completes the typed letters.
      if #atHints == 0 then
        table.insert(atHints, string.sub(strWord, sizMatch + 1))
      else
        table.insert(atHints, strWord)
      end
    end
  end

  local strHint
  if #atHints > 0 then
    strHint = table.concat(atHints, " ")
  end

  return strHint
end

function Shell:__completer(tCompletions, strLine)
  local lpeg = self.lpeg

  -- Loop over all available patterns.
  for _, tPattern in ipairs(self.__atInteractivePatterns) do
    -- Does the pattern match?
    local tMatch = lpeg.match(tPattern.pattern, strLine)
    -- The match is either the index if there are no captures or a string if
    -- there is one capture. Pattern can also return a table of captures, but
    -- this is not supported here.
    local strMatchType = type(tMatch)
    -- Replace matches without captures by the empty string.
    if strMatchType == "number" then
      tMatch = ""
      strMatchType = type(tMatch)
    end
    if strMatchType == "string" then
      -- Yes, the pattern matches.
      if tPattern.words ~= nil then
        -- Is this a function or a table?
        local astrWords
        local strType = type(tPattern.words)
        if strType == "table" then
          astrWords = tPattern.words
        elseif strType == "function" then
          astrWords = tPattern.words(tMatch)
        end
        if astrWords ~= nil then
          self:__getCompletions(tCompletions, strLine, astrWords, tMatch)
        end
      end
      break
    end
  end
end

function Shell:__hints(strLine)
  local strHint
  local sizLine = string.len(strLine)
  local lpeg = self.lpeg

  -- Do not give a hint for the empty line. This does not work for the initial prompt.
  if sizLine > 0 then
    -- Loop over all available patterns.
    for _, tPattern in ipairs(self.__atInteractivePatterns) do
      -- Does the pattern match?
      local tMatch = lpeg.match(tPattern.pattern, strLine)
      -- The match is either the index if there are no captures or a string if
      -- there is one capture. Pattern can also return a table of captures, but
      -- this is not supported here.
      local strMatchType = type(tMatch)
      -- Replace matches without captures by the empty string.
      if strMatchType == "number" then
        tMatch = ""
        strMatchType = type(tMatch)
      end
      if strMatchType == "string" then
        -- Yes, the pattern matches.
        if tPattern.hint ~= nil then
          local strType = type(tPattern.hint)
          if strType == "string" then
            strHint = tPattern.hint
          elseif strType == "function" then
            strHint = tPattern.hint(tMatch)
          end
        elseif tPattern.words ~= nil then
          -- Is this a function or a table?
          local astrWords
          local strType = type(tPattern.words)
          if strType == "table" then
            astrWords = tPattern.words
          elseif strType == "function" then
            astrWords = tPattern.words(tMatch)
          end
          if astrWords ~= nil then
            strHint = self:__getMatchingHints(astrWords, tMatch)
          end
        end
        break
      end
    end
  end

  return strHint
end

function Shell:run()
  local atCommands = self.__atCommands
  local colors = self.colors
  local linenoise = self.linenoise
  local lpeg = self.lpeg
  local tGrammar = self.__lineGrammar
  local pl = self.pl
  local strHistory = ".fsh_history.txt"
  local tLog = self.tLog

  linenoise.historysetmaxlen(100) -- max length of the linenoise history

  local strPathNetx = self:__getNetxPath()
  if strPathNetx == nil then
    error('Failed to find the "netx" folder.')
  end
  tLog.debug('Found the netX path at "%s".', strPathNetx)
  self.__strPathNetx = strPathNetx

  linenoise.historyload(strHistory) -- load existing history
  --  linenoise.enableutf8()

  tLog.info("Welcome to FlaSH, the flasher shell v0.0.1 .")
  tLog.info("Written by Christoph Thelen in 2018.")
  tLog.info("The flasher shell is distributed under the GPL v3 license.")
  tLog.info('Type "help" to get started. Use tab to complete commands.')
  tLog.info("")

  -- Scan for available devices.
  self:__run_scan()

  local fRunning = true
  while fRunning do
    -- Set the current prompt. It depends on the connection.
    local tPlugin = self.tPlugin
    local strPlugin = "not connected"
    if tPlugin ~= nil then
      strPlugin = tPlugin:GetName()
    end
    self.strPrompt = colors.bright .. colors.blue .. strPlugin .. "> " .. colors.white

      -- initialization of setcompletion and sethints of linenoise
  linenoise.setcompletion(
    function(tCompletions, strLine)
      self:__completer(tCompletions, strLine)
    end
  )
  linenoise.sethints(
    function(strLine)
      return self:__hints(strLine), {color = 35, bold = false}
    end
  )

    local strLine, strError

    if self.tCmd_input:len() ~= 0 then
      strLine = self.tCmd_input:pop(1)
      strError = ""
    else
      strLine, strError = linenoise.linenoise(self.strPrompt)
    end

    if strLine == nil then
      if strError ~= nil then
        tLog.error("Error: %s", tostring(strError))
      end
      fRunning = false
    elseif #strLine > 0 then
      linenoise.historyadd(strLine)
      linenoise.historysave(strHistory)

      -- Parse the line.
      local tCmd = lpeg.match(tGrammar, strLine)
      if tCmd == nil then
        tLog.error("Failed to parse the line.")
      else
        -- There should be a command at the "cmd" key.
        -- If there is no command, this is a comment.
        local strCmd = tCmd.cmd
        if strCmd ~= nil then
          -- Search the command.
          local tCmdHit
          for _, tCmdCnt in ipairs(atCommands) do
            if tCmdCnt.cmd == strCmd then
              tCmdHit = tCmdCnt
              break
            end
          end
          if tCmdHit == nil then
            tLog.error("Command not found.")
          else
            -- Run the command.
            fRunning = tCmdHit.run(self, tCmd)
          end
        end
      end
    end
  end
end

Shell.astrPlugins = {
  "romloader_eth",
  "romloader_usb",
  "romloader_uart",
  "romloader_jtag"
}

-- Run the shell.
local tShell = Shell()
tShell:run()
os.exit(0)
