------------------------------------------------------------------------------


-- Create the Shell class.
local class = require 'pl.class'
local Shell = class()


function Shell:_init(tLog)
  self.linenoise = require 'linenoise'
  local lpeg = require 'lpeg'
  self.lpeg = lpeg
  self.pl = require 'pl.import_into'()
  self.term = require 'term'
  self.colors = self.term.colors
  self.tFlasher = require 'flasher'(tLog)
  self.tLog = tLog

  -- No connection yet.
  self.tPlugin = nil
  self.aAttr = nil
  self.__aBoardInfo = {}

  -- Set some styles.
  self.strStyle_Hints = self.colors.magenta
  self.strStyle_FlasherMessages = self.colors.bright .. self.colors.black

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

  -- Match at least one character of whitespace.
  local Space = lpeg.S(" \t")^1
  -- Match optional whitespace.
  local OptionalSpace = lpeg.S(" \t")^0

  -- Match an integer. This can be decimal or hexadecimal.
  -- The "unfinished" variant accepts also unfinished hexadecimal numbers
  -- like "0x".
  local DecimalInteger = lpeg.R('09')^1
  local HexInteger = lpeg.P("0x") * (lpeg.R('09') + lpeg.R('af'))^1
  local UnfinishedHexInteger = lpeg.P("0x") * (lpeg.R('09') + lpeg.R('af'))^0
  local Integer = HexInteger + DecimalInteger
  local UnfinishedInteger = UnfinishedHexInteger + DecimalInteger

  -- A plugin name consists of alphanumeric characters and the underscore.
  local PluginName = (lpeg.R('az') + lpeg.R('AZ') + lpeg.R('09') + lpeg.P('_'))^1

  -- A device name consists of alphanumeric characters and the underscore.
  local DeviceName = (lpeg.R('az') + lpeg.R('AZ') + lpeg.R('09') + lpeg.P('_'))^1

  self.tMatchBusUnitCs = lpeg.Ct(
    lpeg.P('B') * lpeg.Cg(Integer / tonumber, 'bus') *
    lpeg.P('_U') * lpeg.Cg(Integer / tonumber, 'unit') *
    lpeg.P('_C') * lpeg.Cg(Integer / tonumber, 'cs') *
    -1
  )

  ---------------------------------------------------------------------------
  --
  -- Create a grammar to parse a line.
  --

  -- A filename simply matches the rest of the line. This has one important
  -- reason: if a path contains spaces, it should be encosed in quotes, but
  -- there is no simple way to insert a quote somewhere before the cursor in
  -- linenoise (if there is a way, please tell me :D ).
  local Filename = (1 - lpeg.S('\n\r'))^1

  -- Range is either...
  --   1) the keyword "all"
  --   2) a start and end address
  --   3) a start and length separated by "+"
  local Range = lpeg.Cg(lpeg.P('all'), 'all') +
          (lpeg.Cg(Integer / tonumber, 'startaddress') * Space *
            (
              lpeg.Cg(Integer / tonumber, 'endaddress') +
              (lpeg.P('+') * OptionalSpace * lpeg.Cg(Integer / tonumber, 'length'))
            )
          )

  -- A comment starts with a hash and covers the rest of the line.
  local Comment = lpeg.P('#')

  -- All available commands and their handlers.
  local atCommands = {
    {
      cmd = 'connect',
      pattern = OptionalSpace * lpeg.Cg(lpeg.P('connect'), 'cmd') * Space * lpeg.Cg(PluginName, 'plugin') * OptionalSpace * -1,
      run = self.__run_connect
    },
    {
      cmd = 'disconnect',
      pattern = OptionalSpace * lpeg.Cg(lpeg.P('disconnect'), 'cmd') * OptionalSpace * -1,
      run = self.__run_disconnect
    },
    {
      cmd = 'read',
      pattern = OptionalSpace * lpeg.Cg(lpeg.P('read'), 'cmd') * Space * lpeg.Cg(DeviceName, 'device') * Space * Range * Space * lpeg.Cg(Filename, 'filename') * OptionalSpace * -1,
      run = self.__run_read
    },
    {
      cmd = 'write',
      pattern = OptionalSpace * lpeg.Cg(lpeg.P('write'), 'cmd') * Space * lpeg.Cg(DeviceName, 'device') * Space * lpeg.Cg(Integer, 'startaddress') * Space * lpeg.Cg(Filename, 'filename') * OptionalSpace * -1,
      run = self.__run_write
    },
    {
      cmd = 'erase',
      pattern = OptionalSpace * lpeg.Cg(lpeg.P('erase'), 'cmd') * Space * lpeg.Cg(DeviceName, 'device') * Space * Range * OptionalSpace * -1,
      run = self.__run_erase
    },
    {
      cmd = 'iserased',
      pattern = OptionalSpace * lpeg.Cg(lpeg.P('iserased'), 'cmd') * Space * lpeg.Cg(DeviceName, 'device') * Space * Range * OptionalSpace * -1,
      run = self.__run_iserased
    },
    {
      cmd = 'verify',
      pattern = OptionalSpace * lpeg.Cg(lpeg.P('verify'), 'cmd') * Space * lpeg.Cg(DeviceName, 'device') * Space * lpeg.Cg(Integer, 'startaddress') * Space * lpeg.Cg(Filename, 'filename') * OptionalSpace * -1,
      run = self.__run_verify
    },
    {
      cmd = 'hash',
      pattern = OptionalSpace * lpeg.Cg(lpeg.P('hash'), 'cmd') * Space * lpeg.Cg(DeviceName, 'device') * Space * Range * OptionalSpace * -1,
      run = self.__run_hash
    },
    {
      cmd = 'scan',
      pattern = OptionalSpace * lpeg.Cg(lpeg.P('scan'), 'cmd') * OptionalSpace * -1,
      run = self.__run_scan
    },
    {
      cmd = 'help',
      pattern = OptionalSpace * lpeg.Cg(lpeg.P('help'), 'cmd') * (Space * lpeg.Cg(lpeg.R('az')^1, 'topic'))^-1 * OptionalSpace * -1,
      run = self.__run_help
    },
    {
      cmd = 'quit',
      pattern = OptionalSpace * lpeg.Cg(lpeg.P('quit'), 'cmd') * OptionalSpace * -1,
      run = self.__run_quit
    }
  }
  self.__atCommands = atCommands

  -- Combine all commands.
  local AllCommands
  for _, tCommand in ipairs(atCommands) do
    local pattern = tCommand.pattern
    if AllCommands==nil then
      AllCommands = pattern
    else
      AllCommands = AllCommands + pattern
    end
  end

  self.__lineGrammar = lpeg.Ct((AllCommands * (Comment^-1)) + Comment)

  -- Create a table with all commands as a string.
  local astrCommandWords = {}
  for _, tCommand in ipairs(atCommands) do
    table.insert(astrCommandWords, tCommand.cmd)
  end
  self.__astrCommandWords = astrCommandWords

  -- Create a table with all help topics as a string.
  local astrHelpTopicWords = {}
  for _, tTopic in ipairs(self.__atHelpTopics) do
    local strTopic = tTopic.topic
    if strTopic~=nil and strTopic~='' then
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
      pattern = OptionalSpace * lpeg.Cg(lpeg.R('az')^0) * -1,
      words = self.__astrCommandWords
    },

    -- Connect command.
    {
      pattern = OptionalSpace * lpeg.P('connect') * Space * -1,
      hint = function() return '[plugin]  possible values: ' .. table.concat(self.__astrPluginNames, ', ') end,
      words = function() return self.__astrPluginNames end
    },
    {
      pattern = OptionalSpace * lpeg.P('connect') * Space * lpeg.Cg(PluginName) * -1,
      words = function() return self.__astrPluginNames end
    },

    -- Read command.
    {
      pattern = OptionalSpace * lpeg.P('read') * Space * -1,
      hint = function() return '[device]  possible values: ' .. table.concat(self.__aSanitizedBoardNames, ', ') end,
      words = function() return self.__aSanitizedBoardNames end
    },
    {
      pattern = OptionalSpace * lpeg.P('read') * Space * lpeg.Cg(DeviceName) * -1,
      words = function() return self.__aSanitizedBoardNames end
    },
    {
      pattern = OptionalSpace * lpeg.P('read') * Space * DeviceName * Space * -1,
      hint = 'all  or  [startaddress] [endaddress]  or  [startaddress] + [length]',
      words = { 'all' }
    },
    {
      pattern = OptionalSpace * lpeg.P('read') * Space * DeviceName * Space * lpeg.Cg(lpeg.P('al') + lpeg.P('a')) * -1,
      words = { 'all' }
    },
    {
      pattern = OptionalSpace * lpeg.P('read') * Space * DeviceName * Space * UnfinishedInteger * -1,
      hint = '    this is the startaddress'
    },
    {
      pattern = OptionalSpace * lpeg.P('read') * Space * DeviceName * Space * Integer * Space * -1,
      hint = '[endaddress]  or  + [length]'
    },
    {
      pattern = OptionalSpace * lpeg.P('read') * Space * DeviceName * Space * Integer * Space * UnfinishedInteger * -1,
      hint = '    this is the endaddress'
    },
    {
      pattern = OptionalSpace * lpeg.P('read') * Space * DeviceName * Space * Integer * Space * lpeg.P('+') * OptionalSpace * -1,
      hint = '[length]'
    },
    {
      pattern = OptionalSpace * lpeg.P('read') * Space * DeviceName * Space * Integer * Space * lpeg.P('+') * Space * UnfinishedInteger * -1,
      hint = '    this is the length'
    },
    {
      pattern = OptionalSpace * lpeg.P('read') * Space * DeviceName * Space * (lpeg.P('all') + (Integer * Space * (Integer + (lpeg.P('+') * OptionalSpace * Integer)))) * Space * -1,
      hint = '[filename]',
      words = function(strMatch) return self:__getFilenameWords(strMatch) end
    },
    {
      pattern = OptionalSpace * lpeg.P('read') * Space * DeviceName * Space * (lpeg.P('all') + (Integer * Space * (Integer + (lpeg.P('+') * OptionalSpace * Integer)))) * Space * lpeg.Cg(Filename) * -1,
      words = function(strMatch) return self:__getFilenameWords(strMatch) end
    },

    -- Write command.
    {
      pattern = OptionalSpace * lpeg.P('write') * Space * -1,
      hint = function() return '[device]  possible values: ' .. table.concat(self.__aSanitizedBoardNames, ', ') end,
      words = function() return self.__aSanitizedBoardNames end
    },
    {
      pattern = OptionalSpace * lpeg.P('write') * Space * lpeg.Cg(DeviceName) * -1,
      words = function() return self.__aSanitizedBoardNames end
    },
    {
      pattern = OptionalSpace * lpeg.P('write') * Space * DeviceName * Space * -1,
      hint = '[startaddress]'
    },
    {
      pattern = OptionalSpace * lpeg.P('write') * Space * DeviceName * Space * UnfinishedInteger * -1,
      hint = '    this is the startaddress'
    },
    {
      pattern = OptionalSpace * lpeg.P('write') * Space * DeviceName * Space * Integer * Space * -1,
      hint = '[filename]',
      words = function(strMatch) return self:__getFilenameWords(strMatch) end
    },
    {
      pattern = OptionalSpace * lpeg.P('write') * Space * DeviceName * Space * Integer * Space * lpeg.Cg(Filename) * -1,
      words = function(strMatch) return self:__getFilenameWords(strMatch) end
    },

    -- Erase command.
    {
      pattern = OptionalSpace * lpeg.P('erase') * Space * -1,
      hint = function() return '[device]  possible values: ' .. table.concat(self.__aSanitizedBoardNames, ', ') end,
      words = function() return self.__aSanitizedBoardNames end
    },
    {
      pattern = OptionalSpace * lpeg.P('erase') * Space * lpeg.Cg(DeviceName) * -1,
      words = function() return self.__aSanitizedBoardNames end
    },
    {
      pattern = OptionalSpace * lpeg.P('erase') * Space * DeviceName * Space * -1,
      hint = 'all  or  [startaddress] [endaddress]  or  [startaddress] + [length]',
      words = { 'all' }
    },
    {
      pattern = OptionalSpace * lpeg.P('erase') * Space * DeviceName * Space * lpeg.Cg(lpeg.P('al') + lpeg.P('a')) * -1,
      words = { 'all' }
    },
    {
      pattern = OptionalSpace * lpeg.P('erase') * Space * DeviceName * Space * UnfinishedInteger * -1,
      hint = '    this is the startaddress'
    },
    {
      pattern = OptionalSpace * lpeg.P('erase') * Space * DeviceName * Space * Integer * Space * -1,
      hint = '[endaddress]  or  + [length]'
    },
    {
      pattern = OptionalSpace * lpeg.P('erase') * Space * DeviceName * Space * Integer * Space * UnfinishedInteger * -1,
      hint = '    this is the endaddress'
    },
    {
      pattern = OptionalSpace * lpeg.P('erase') * Space * DeviceName * Space * Integer * Space * lpeg.P('+') * OptionalSpace * -1,
      hint = '[length]'
    },
    {
      pattern = OptionalSpace * lpeg.P('erase') * Space * DeviceName * Space * Integer * Space * lpeg.P('+') * Space * UnfinishedInteger * -1,
      hint = '    this is the length'
    },

    -- IsErased command.
    {
      pattern = OptionalSpace * lpeg.P('iserased') * Space * -1,
      hint = function() return '[device]  possible values: ' .. table.concat(self.__aSanitizedBoardNames, ', ') end,
      words = function() return self.__aSanitizedBoardNames end
    },
    {
      pattern = OptionalSpace * lpeg.P('iserased') * Space * lpeg.Cg(DeviceName) * -1,
      words = function() return self.__aSanitizedBoardNames end
    },
    {
      pattern = OptionalSpace * lpeg.P('iserased') * Space * DeviceName * Space * -1,
      hint = 'all  or  [startaddress] [endaddress]  or  [startaddress] + [length]',
      words = { 'all' }
    },
    {
      pattern = OptionalSpace * lpeg.P('iserased') * Space * DeviceName * Space * lpeg.Cg(lpeg.P('al') + lpeg.P('a')) * -1,
      words = { 'all' }
    },
    {
      pattern = OptionalSpace * lpeg.P('iserased') * Space * DeviceName * Space * UnfinishedInteger * -1,
      hint = '    this is the startaddress'
    },
    {
      pattern = OptionalSpace * lpeg.P('iserased') * Space * DeviceName * Space * Integer * Space * -1,
      hint = '[endaddress]  or  + [length]'
    },
    {
      pattern = OptionalSpace * lpeg.P('iserased') * Space * DeviceName * Space * Integer * Space * UnfinishedInteger * -1,
      hint = '    this is the endaddress'
    },
    {
      pattern = OptionalSpace * lpeg.P('iserased') * Space * DeviceName * Space * Integer * Space * lpeg.P('+') * OptionalSpace * -1,
      hint = '[length]'
    },
    {
      pattern = OptionalSpace * lpeg.P('iserased') * Space * DeviceName * Space * Integer * Space * lpeg.P('+') * Space * UnfinishedInteger * -1,
      hint = '    this is the length'
    },

    -- Verify command.
    {
      pattern = OptionalSpace * lpeg.P('verify') * Space * -1,
      hint = function() return '[device]  possible values: ' .. table.concat(self.__aSanitizedBoardNames, ', ') end,
      words = function() return self.__aSanitizedBoardNames end
    },
    {
      pattern = OptionalSpace * lpeg.P('verify') * Space * lpeg.Cg(DeviceName) * -1,
      words = function() return self.__aSanitizedBoardNames end
    },
    {
      pattern = OptionalSpace * lpeg.P('verify') * Space * DeviceName * Space * -1,
      hint = '[startaddress]'
    },
    {
      pattern = OptionalSpace * lpeg.P('verify') * Space * DeviceName * Space * UnfinishedInteger * -1,
      hint = '    this is the startaddress'
    },
    {
      pattern = OptionalSpace * lpeg.P('verify') * Space * DeviceName * Space * Integer * Space * -1,
      hint = '[filename]',
      words = function(strMatch) return self:__getFilenameWords(strMatch) end
    },
    {
      pattern = OptionalSpace * lpeg.P('verify') * Space * DeviceName * Space * Integer * Space * lpeg.Cg(Filename) * -1,
      words = function(strMatch) return self:__getFilenameWords(strMatch) end
    },

    -- Hash command.
    {
      pattern = OptionalSpace * lpeg.P('hash') * Space * -1,
      hint = function() return '[device]  possible values: ' .. table.concat(self.__aSanitizedBoardNames, ', ') end,
      words = function() return self.__aSanitizedBoardNames end
    },
    {
      pattern = OptionalSpace * lpeg.P('hash') * Space * lpeg.Cg(DeviceName) * -1,
      words = function() return self.__aSanitizedBoardNames end
    },
    {
      pattern = OptionalSpace * lpeg.P('hash') * Space * DeviceName * Space * -1,
      hint = 'all  or  [startaddress] [endaddress]  or  [startaddress] + [length]',
      words = { 'all' }
    },
    {
      pattern = OptionalSpace * lpeg.P('hash') * Space * DeviceName * Space * lpeg.Cg(lpeg.P('al') + lpeg.P('a')) * -1,
      words = { 'all' }
    },
    {
      pattern = OptionalSpace * lpeg.P('hash') * Space * DeviceName * Space * UnfinishedInteger * -1,
      hint = '    this is the startaddress'
    },
    {
      pattern = OptionalSpace * lpeg.P('hash') * Space * DeviceName * Space * Integer * Space * -1,
      hint = '[endaddress]  or  + [length]'
    },
    {
      pattern = OptionalSpace * lpeg.P('hash') * Space * DeviceName * Space * Integer * Space * UnfinishedInteger * -1,
      hint = '    this is the endaddress'
    },
    {
      pattern = OptionalSpace * lpeg.P('hash') * Space * DeviceName * Space * Integer * Space * lpeg.P('+') * OptionalSpace * -1,
      hint = '[length]'
    },
    {
      pattern = OptionalSpace * lpeg.P('hash') * Space * DeviceName * Space * Integer * Space * lpeg.P('+') * Space * UnfinishedInteger * -1,
      hint = '    this is the length'
    },

    -- Help command.
    {
      pattern = OptionalSpace * lpeg.P('help') * Space * -1,
      hint = function() return '[topic]  possible values: ' .. table.concat(self.__astrHelpTopicWords, ', ') end,
      words = function() return self.__astrHelpTopicWords end
    },
    {
      pattern = OptionalSpace * lpeg.P('help') * Space * lpeg.Cg(lpeg.R('az')^1) * -1,
      words = function() return self.__astrHelpTopicWords end
    }
  }

end



function Shell:__getNetxPath()
  local pl = self.pl

  local strPathNetx

  -- Split the Lua module path.
  local astrPaths = pl.stringx.split(package.path, ';')
  for _, strPath in ipairs(astrPaths) do
    -- Only process search paths which end in "?.lua".
    if string.sub(strPath, -5)=='?.lua' then
      -- Cut off the "?.lua" part.
      -- Expect the "netx" folder one below the module folder.
      local strPath = pl.path.join(pl.path.dirname(pl.path.dirname(pl.path.abspath(strPath))), 'netx')
      if pl.path.exists(strPath)~=nil and pl.path.isdir(strPath)==true then
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

  if strDir=='' then
    -- An empty match is special. Use the current working folder.
    strDir = pl.path.currentdir()
    strPrintPrefix = ''
    self:__getFolderEntries(strDir, strPrintPrefix, astrWords)

  else
    -- Expand a "~".
    strDir = pl.path.expanduser(strDir)

    local strLastElement = pl.path.basename(strDir)

    -- Does the folder exist?
    if strLastElement~='.' and pl.path.exists(strDir)~=nil and pl.path.isdir(strDir)==true then
      -- Yes -> add all elements of this folder.
      self:__getFolderEntries(strDir, strPrintPrefix, astrWords)

    else
      -- The folder does not exist. Try to cut off the last path element.
      local strDirName = pl.path.dirname(strDir)

      if strDirName=='' then
        if pl.path.isabs(strDir) then
          -- TODO: port this to windows.
          strDir = strSep
          strPrintPrefix = strSep
          self:__getFolderEntries(strDir, strPrintPrefix, astrWords)
        else
          strDir = pl.path.currentdir()
          strPrintPrefix = ''
          self:__getFolderEntries(strDir, strPrintPrefix, astrWords)
        end

      elseif pl.path.exists(strDirName)~=nil and pl.path.isdir(strDirName)==true then
        strDir = strDirName

        -- Cut off the last Element from the print prefix.
        strPrintPrefix = string.sub(strPrintPrefix, 1, -1-string.len(strLastElement))
        self:__getFolderEntries(strDir, strPrintPrefix, astrWords)
      end
    end
  end

  return astrWords
end



Shell.__atHelpTopics = {
  {
    topic = '',
    text = [[
Welcome to the help.

The "help" command alone shows this message. It can also combined with a
topic.

The following example shows help about the "read" command:

  help read

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
  $(strTopic) $(string.rep(' ', sizMax-string.len(strTopic))) : $(tTopic.description)
#   end
# end
    ]]
  },

  {
    topic = 'start',
    description = 'Getting started.',
    text = [[
Getting started.

TODO...
    ]]
  },

  {
    topic = 'quit',
    description = 'The quit command.',
    text = [[
The quit command.

It quits the application without a safety question.
A connection to a netx is closed.
    ]]
  }
}



------------------------------------------------------------------------------


function Shell:__run_help(tCmd)
  -- Get the topic. If no topic was specified, set the topic to the empty
  -- string - which selects the main page.
  local strTopic = tCmd.topic or ''

  -- Search the topic.
  local tTopic
  for _, tTopicCnt in ipairs(self.__atHelpTopics) do
    if tTopicCnt.topic==strTopic then
      tTopic = tTopicCnt
      break
    end
  end
  if tTopic==nil then
    -- Topic not found. Show an error.
    print(string.format('Unknown help topic "%s".', strTopic))
  else
    -- Process the template.
    local strText, strError = self.pl.template.substitute(
      tTopic.text,
      {
        ipairs = ipairs,
        pairs = pairs,
        string = string,

        topics = self.__atHelpTopics
      }
    )
    if strText==nil then
      -- Failed to process the template. Show an error message.
      print('Failed to render the help text: ' .. tostring(strError))
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
  local fOk=true
  local ucBus
  local ucUnit
  local ucCS

  -- Try to parse the device as a general "Bxxx_Uxxx_Cxxx" ID.
  local tMatch = lpeg.match(self.tMatchBusUnitCs, strDevice)
  if tMatch~=nil then
    ucBus = tMatch.bus
    ucUnit = tMatch.unit
    ucCS = tMatch.cs
    if ucBus<0 or ucBus>255 then
      print(string.format('The bus exceeds the allowed range of an 8 bit number: %d', ucBus))
      fOk = false
    end
    if ucUnit<0 or ucUnit>255 then
      print(string.format('The unit exceeds the allowed range of an 8 bit number: %d', ucUnit))
      fOk = false
    end
    if ucCS<0 or ucCS>255 then
      print(string.format('The chip select exceeds the allowed range of an 8 bit number: %d', ucCS))
      fOk = false
    end

  else

    -- Search the ID in the list of known devices.
    for _,tDeviceInfo in ipairs(self.__aBoardInfo) do
      if strDevice==tDeviceInfo.id then
        ucBus = tDeviceInfo.bus
        ucUnit = tDeviceInfo.unit
        ucCS = tDeviceInfo.cs
        break
      end
    end
    if ucBus==nil then
      print(string.format('Unknown device ID "%s".', strDevice))
      fOk = false
    end
  end

  -- Invalidate the bus, unit and chip select if something went wrong.
  if fOk~=true then
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

  if tPlugin==nil or aAttr==nil then
    print('Not connected.')

  elseif tCmd.all~=nil then
    ulStart = 0
    ulLength = tFlasher:getFlashSize(tPlugin, aAttr)

  else
    ulStart = tCmd.startaddress
    ulLength = tCmd.length
    if ulLength==nil then
      local ulEnd = tCmd.endaddress
      if ulEnd<ulStart then
        print('The end address must not be smaller than the start address.')
        ulStart = nil
      else
        ulLength = ulEnd - ulStart
      end
    end
  end

  return ulStart, ulLength
end



function Shell:__switchToDevice(ucBus, ucUnit, ucCS)
  local tFlasher = self.tFlasher
  local tPlugin = self.tPlugin
  local aAttr = self.aAttr
  local tResult

  if tPlugin==nil or aAttr==nil then
    print('Not connected.')
    tResult = false

  elseif ucBus==self.__ucCurrentBus and ucUnit==self.__ucCurrentUnit and ucCS==self.__ucCurrentCS then
    print(string.format('Continue to use bus %d, unit %d, CS %d.', ucBus, ucUnit, ucCS))
    tResult = true

  else
    print(string.format('Switch to bus %d, unit %d, CS %d.', ucBus, ucUnit, ucCS))

    local fOk = tFlasher:detect(tPlugin, aAttr, ucBus, ucUnit, ucCS)
    if fOk~=true then
      print('Failed to detect a device')
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

  -- Prepare for flasher output.
  io.write(self.colors.reset .. self.strStyle_FlasherMessages)

  if tPlugin==nil or aAttr==nil then
    print(self.colors.bright .. self.colors.white .. 'Not connected.')

  else
    -- Get the bus, unit and chipselect.
    local strDevice = tCmd.device
    local ucBus, ucUnit, ucCS = self:__getBusUnitCs(strDevice)
    if ucBus~=nil then
      print(string.format('Using bus %d, unit %d, CS %d.', ucBus, ucUnit, ucCS))

      local tResult = self:__switchToDevice(ucBus, ucUnit, ucCS)
      if tResult==true then
        local ulStart, ulLength = self:__getRange(tCmd)
        if ulStart~=nil then
          local ulEnd = ulStart+ulLength
          print(string.format('Reading [0x%08x,0x%08x[ .', ulStart, ulEnd))

          local strBin, strMsg = tFlasher:readArea(tPlugin, aAttr, ulStart, ulEnd)
          if strBin==nil then
            print(self.colors.bright .. self.colors.white .. 'Failed to read: ' .. tostring(strMsg))

          else
            tResult, strMsg = pl.utils.writefile(tCmd.filename, strBin, true)
            if tResult==true then
              print(self.colors.bright .. self.colors.white .. 'OK')
            else
              print(self.colors.bright .. self.colors.white .. string.format('Failed to write the data to the file "%s": %s', tCmd.filename, strMsg))
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

  -- Prepare for flasher output.
  io.write(self.colors.reset .. self.strStyle_FlasherMessages)

  if tPlugin==nil or aAttr==nil then
    print(self.colors.bright .. self.colors.white .. 'Not connected.')

  else
    -- Get the bus, unit and chipselect.
    local strDevice = tCmd.device
    local ucBus, ucUnit, ucCS = self:__getBusUnitCs(strDevice)
    if ucBus~=nil then
      print(string.format('Using bus %d, unit %d, CS %d.', ucBus, ucUnit, ucCS))

      local tResult = self:__switchToDevice(ucBus, ucUnit, ucCS)
      if tResult==true then
        local ulStart = tCmd.startaddress

        local strFilename = tCmd.filename
        if pl.path.exists(strFilename)==nil then
          print(self.colors.bright .. self.colors.white .. string.format('The file "%s" does not exist.', strFilename))
        elseif pl.path.isfile(strFilename)~=true then
          print(self.colors.bright .. self.colors.white .. string.format('The path "%s" is not a file.', strFilename))
        else
          print(string.format('Verify "%s" at offset 0x%08x...', strFilename, ulStart))

          local strBin, strMsg = pl.utils.readfile(strFilename, true)
          if strBin==nil then
            print(self.colors.bright .. self.colors.white .. string.format('Failed to read "%s" : ', strFilename, tostring(strMsg)))

          else
            -- Erase the area.
            tResult, strMsg = tFlasher:verifyArea(tPlugin, aAttr, ulStart, strBin)
            if tResult==true then
              print(self.colors.bright .. self.colors.white .. string.format('Verify OK. The data in the flash at offset 0x%08x equals the file "%s".', ulStart, strFilename))
            else
              print(self.colors.bright .. self.colors.white .. string.format('Verify error. The flash contents at offset 0x%08x differ from the file "%s".', ulStart, strFilename))
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

  -- Prepare for flasher output.
  io.write(self.colors.reset .. self.strStyle_FlasherMessages)

  if tPlugin==nil or aAttr==nil then
    print(self.colors.bright .. self.colors.white .. 'Not connected.')

  else
    -- Get the bus, unit and chipselect.
    local strDevice = tCmd.device
    local ucBus, ucUnit, ucCS = self:__getBusUnitCs(strDevice)
    if ucBus~=nil then
      print(string.format('Using bus %d, unit %d, CS %d.', ucBus, ucUnit, ucCS))

      local tResult = self:__switchToDevice(ucBus, ucUnit, ucCS)
      if tResult==true then
        local ulStart = tCmd.startaddress

        local strFilename = tCmd.filename
        if pl.path.exists(strFilename)==nil then
          print(self.colors.bright .. self.colors.white .. string.format('The file "%s" does not exist.', strFilename))
        elseif pl.path.isfile(strFilename)~=true then
          print(self.colors.bright .. self.colors.white .. string.format('The path "%s" is not a file.', strFilename))
        else
          print(string.format('Writing "%s" to offset 0x%08x...', strFilename, ulStart))

          local strBin, strMsg = pl.utils.readfile(strFilename, true)
          if strBin==nil then
            print(self.colors.bright .. self.colors.white .. string.format('Failed to read "%s" : ', strFilename, tostring(strMsg)))

          else
            -- Get the size of the data in bytes.
            local sizBin = string.len(strBin)

            -- Erase the area.
            tResult, strMsg = tFlasher:eraseArea(tPlugin, aAttr, ulStart, sizBin)
            if tResult~=true then
              print('Failed to erase the area: ' .. tostring(strMsg))

            else
              -- Flash the data. This includes a verify.
              tResult, strMsg = tFlasher:flashArea(tPlugin, aAttr, ulStart, strBin)
              if tResult~=true then
                print('Failed to write the area: ' .. tostring(strMsg))

              end
            end

            if tResult==true then
              print(self.colors.bright .. self.colors.white .. 'OK')
            else
              print(self.colors.bright .. self.colors.white .. string.format('Failed to write the data: %s', strMsg))
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

  -- Prepare for flasher output.
  io.write(self.colors.reset .. self.strStyle_FlasherMessages)

  if tPlugin==nil or aAttr==nil then
    print(self.colors.bright .. self.colors.white .. 'Not connected.')

  else
    -- Get the bus, unit and chipselect.
    local strDevice = tCmd.device
    local ucBus, ucUnit, ucCS = self:__getBusUnitCs(strDevice)
    if ucBus~=nil then
      print(string.format('Using bus %d, unit %d, CS %d.', ucBus, ucUnit, ucCS))

      local tResult = self:__switchToDevice(ucBus, ucUnit, ucCS)
      if tResult==true then
        local ulStart, ulLength = self:__getRange(tCmd)
        if ulStart~=nil then
          local ulEnd = ulStart + ulLength
          -- Erase the area.
          local strMsg
          tResult, strMsg = tFlasher:eraseArea(tPlugin, aAttr, ulStart, ulEnd)
          if tResult==true then
            print(self.colors.bright .. self.colors.white .. 'OK')
          else
            print(self.colors.bright .. self.colors.white .. string.format('Failed to erase the data: %s', strMsg))
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

  -- Prepare for flasher output.
  io.write(self.colors.reset .. self.strStyle_FlasherMessages)

  if tPlugin==nil or aAttr==nil then
    print(self.colors.bright .. self.colors.white .. 'Not connected.')

  else
    -- Get the bus, unit and chipselect.
    local strDevice = tCmd.device
    local ucBus, ucUnit, ucCS = self:__getBusUnitCs(strDevice)
    if ucBus~=nil then
      print(string.format('Using bus %d, unit %d, CS %d.', ucBus, ucUnit, ucCS))

      local tResult = self:__switchToDevice(ucBus, ucUnit, ucCS)
      if tResult==true then
        local ulStart, ulLength = self:__getRange(tCmd)
        if ulStart~=nil then
          local ulEnd = ulStart + ulLength
          -- Erase the area.
          local strMsg
          tResult, strMsg = tFlasher:isErased(tPlugin, aAttr, ulStart, ulEnd)
          if tResult==true then
            print(self.colors.bright .. self.colors.white .. 'Clean. The area is erased.')
          else
            print(self.colors.bright .. self.colors.white .. 'Dirty. The area is not erased.')
          end
        end
      end
    end
  end

  return true
end



function Shell:__str2hex(strData)
  local astrHex = {}
  for uiCnt=1,string.len(strData) do
    table.insert(astrHex, string.format(string.byte(strData, uiCnt)))
  end
  return table.concat(astrHex)
end



function Shell:__run_hash(tCmd)
  local tFlasher = self.tFlasher
  local tPlugin = self.tPlugin
  local aAttr = self.aAttr

  -- Prepare for flasher output.
  io.write(self.colors.reset .. self.strStyle_FlasherMessages)

  if tPlugin==nil or aAttr==nil then
    print(self.colors.bright .. self.colors.white .. 'Not connected.')

  else
    -- Get the bus, unit and chipselect.
    local strDevice = tCmd.device
    local ucBus, ucUnit, ucCS = self:__getBusUnitCs(strDevice)
    if ucBus~=nil then
      print(string.format('Using bus %d, unit %d, CS %d.', ucBus, ucUnit, ucCS))

      local tResult = self:__switchToDevice(ucBus, ucUnit, ucCS)
      if tResult==true then
        local ulStart, ulLength = self:__getRange(tCmd)
        if ulStart~=nil then
          local ulEnd = ulStart + ulLength
          -- Erase the area.
          local strMsg
          tResult, strMsg = tFlasher:hashArea(tPlugin, aAttr, ulStart, ulEnd)
          if tResult~=nil then
            print(self.colors.bright .. self.colors.white .. 'OK. SHA1SUM = ' .. self:str2hex(tResult))
          else
            print(self.colors.bright .. self.colors.white .. string.format('Failed to hash the data: %s', strMsg))
          end
        end
      end
    end
  end

  return true
end

------------------------------------------------------------------------------


function Shell:__run_scan()
  -- Clear all previously detected devices.
  self.__atDetectedDevices = {}
  self.__astrPluginNames = {}

  -- Prepare for output from the scan process.
  io.write(self.colors.reset .. self.strStyle_FlasherMessages)

  print('Scanning for devices...')
  local aDetectedInterfaces = {}
  local sizNumberOfAvailablePlugins = 0
  if _G.__MUHKUH_PLUGINS~=nil then
    sizNumberOfAvailablePlugins = #_G.__MUHKUH_PLUGINS
    for _,v in ipairs(_G.__MUHKUH_PLUGINS) do
      print(string.format("Detecting interfaces with plugin %s", v:GetID()))
      local iDetected = v:DetectInterfaces(aDetectedInterfaces)
      print(string.format("Found %d interfaces with plugin %s", iDetected, v:GetID()))
    end
  end
  print()
  print(string.format("Found a total of %d interfaces with %d plugins", #aDetectedInterfaces, sizNumberOfAvailablePlugins))
  for _, tPlugin in ipairs(aDetectedInterfaces) do
    print(string.format('  %s', tPlugin:GetName()))
  end
  print()

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

  -- Prepare for output from the scan process.
  io.write(self.colors.reset .. self.strStyle_FlasherMessages)

  local atDetectedDevices = self.__atDetectedDevices
  if #atDetectedDevices==0 then
    print 'No devices detected to connect to. Run "scan" to search for devices again.'
  else
    self:__run_disconnect()

    local strPlugin = tCmd.plugin

    -- The argument to the command must be a valid device.
    for _, tDevice in pairs(atDetectedDevices) do
      if tDevice:GetName()==strPlugin then
        local tPlugin = tDevice:Create()
        if tPlugin==nil then
          print 'Failed to open to the device.'
        else
          -- Connect to the netX.
          local tResult, strMsg = pcall(tPlugin.Connect, tPlugin)
          if tResult~=true then
            print('Failed to connect: ' .. tostring(strMsg))

          else
            -- Download the flasher binary to the netX.
            local aAttr
            tResult, aAttr = pcall(tFlasher.download, tFlasher, tPlugin, self.__strPathNetx)
            if tResult~=true or aAttr==nil then
              print('Failed to download the flasher to the netX: ' .. tostring(aAttr))
              tPlugin:Disconnect()
            else
              -- Get the board info.
              local aBoardInfo = tFlasher:getBoardInfo(tPlugin, aAttr)
              if aBoardInfo==nil then
                print 'Failed to get the board info.'
                tPlugin:Disconnect()
              else
                -- Get all IDs for the flashes.
                local aSanitizedBoardNames = {}
                for _,tDeviceInfo in ipairs(aBoardInfo) do
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
  -- Prepare for output from the scan process.
  io.write(self.colors.reset .. self.strStyle_FlasherMessages)

  local tPlugin = self.tPlugin
  if tPlugin==nil then
    print 'Not connected, no need to disconnect...'
  else
    print(string.format('Disconnecting from %s.', tPlugin:GetName()))
    tPlugin:Disconnect()
    self.tPlugin = nil
    self.aAttr = nil
    self.__aBoardInfo = {}
    self.__aSanitizedBoardNames = {}
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
  if sizMatch==0 then
    -- Add all available words.
    for _, strWord in ipairs(astrWords) do
      tCompletions:add(strLine .. strWord)
    end
  else
    -- Get the prefix of the line without the match.
    local strPrefix = string.sub(strLine, 1, -1-string.len(strMatch))
    -- Add the devices matching the input.
    for _, strWord in pairs(astrWords) do
      local sizWord = string.len(strWord)
      if sizWord>=sizMatch and string.sub(strWord, 1, sizMatch)==strMatch then
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
    if sizWord>=sizMatch and string.sub(strWord, 1, sizMatch)==strMatch then
      -- Do not add the complete argument for the first match. It completes the typed letters.
      if #atHints==0 then
        table.insert(atHints, string.sub(strWord, sizMatch+1))
      else
        table.insert(atHints, strWord)
      end
    end
  end

  local strHint
  if #atHints>0 then
    strHint = table.concat(atHints, ' ')
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
    if strMatchType=='number' then
      tMatch = ''
      strMatchType = type(tMatch)
    end
    if strMatchType=='string' then
      -- Yes, the pattern matches.
      if tPattern.words~=nil then
        -- Is this a function or a table?
        local astrWords
        local strType = type(tPattern.words)
        if strType=='table' then
          astrWords = tPattern.words
        elseif strType=='function' then
          astrWords = tPattern.words(tMatch)
        end
        if astrWords~=nil then
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
  if sizLine>0 then
    -- Loop over all available patterns.
    for _, tPattern in ipairs(self.__atInteractivePatterns) do
      -- Does the pattern match?
      local tMatch = lpeg.match(tPattern.pattern, strLine)
      -- The match is either the index if there are no captures or a string if
      -- there is one capture. Pattern can also return a table of captures, but
      -- this is not supported here.
      local strMatchType = type(tMatch)
      -- Replace matches without captures by the empty string.
      if strMatchType=='number' then
        tMatch = ''
        strMatchType = type(tMatch)
      end
      if strMatchType=='string' then
        -- Yes, the pattern matches.
        if tPattern.hint~=nil then
          local strType = type(tPattern.hint)
          if strType=='string' then
            strHint = tPattern.hint
          elseif strType=='function' then
            strHint = tPattern.hint(tMatch)
          end
        elseif tPattern.words~=nil then
          -- Is this a function or a table?
          local astrWords
          local strType = type(tPattern.words)
          if strType=='table' then
            astrWords = tPattern.words
          elseif strType=='function' then
            astrWords = tPattern.words(tMatch)
          end
          if astrWords~=nil then
            strHint = self:__getMatchingHints(astrWords, tMatch)
          end
        end
        if strHint~=nil then
          strHint = self.strStyle_Hints .. strHint
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
  local strHistory = 'history.txt'
  local tLog = self.tLog

  local strPathNetx = self:__getNetxPath()
  if strPathNetx==nil then
    error('Failed to find the "netx" folder.')
  end
  tLog.debug('Found the netX path at "%s".', strPathNetx)
  self.__strPathNetx = strPathNetx

  linenoise.historyload(strHistory) -- load existing history
--  linenoise.enableutf8()

  print(colors.bright .. colors.blue .. 'Welcome to FlaSH, the flasher shell v0.0.1 .')
  print 'Written by Christoph Thelen in 2018.'
  print 'The flasher shell is distributed under the GPL v3 license.'
  print 'Type "help" to get started. Use tab to complete commands.'
  print ''

  -- Scan for available devices.
  self:__run_scan()

  local fRunning = true
  while fRunning do
    -- Set the current prompt. It depends on the connection.
    local tPlugin = self.tPlugin
    local strPlugin = 'not connected'
    if tPlugin~=nil then
      strPlugin = tPlugin:GetName()
    end
    self.strPrompt = colors.bright .. colors.blue .. strPlugin .. '> ' .. colors.white

    linenoise.setcompletion(function(tCompletions, strLine)
        self:__completer(tCompletions, strLine)
      end
    )
    linenoise.sethints(function(strLine)
        return self:__hints(strLine)
      end
    )

    local strLine, strError = linenoise.linenoise(self.strPrompt)
    if strLine==nil then
      if strError~=nil then
        tLog.error('Error: %s', tostring(strError))
      end
      fRunning = false
    elseif #strLine > 0 then
      linenoise.historyadd(strLine)
      linenoise.historysave(strHistory)

      -- Parse the line.
      local tCmd = lpeg.match(tGrammar, strLine)
      if tCmd==nil then
        print('Failed to parse the line.')
      else
        pl.pretty.dump(tCmd)

        -- There should be a command at the "cmd" key.
        -- If there is no command, this is a comment.
        local strCmd = tCmd.cmd
        if strCmd~=nil then
          -- Search the command.
          local tCmdHit
          for _, tCmdCnt in ipairs(atCommands) do
            if tCmdCnt.cmd==strCmd then
              tCmdHit = tCmdCnt
              break
            end
          end
          if tCmdHit==nil then
            print('Command not found.')
          else
            -- Run the command.
            fRunning = tCmdHit.run(self, tCmd)
          end
        end
      end
    end
  end
end


-- Create a dummy logger object for the flasher.
local tLog = {
  emerg = function(...) print('[EMERG] ' .. string.format(...)) end,
  alert = function(...) print('[ALERT] ' .. string.format(...)) end,
  fatal = function(...) print('[FATAL] ' .. string.format(...)) end,
  error = function(...) print('[ERROR] ' .. string.format(...)) end,
  warning = function(...) print('[WARNING] ' .. string.format(...)) end,
  notice = function(...) print('[NOTICE] ' .. string.format(...)) end,
  info = function(...) print('[INFO] ' .. string.format(...)) end,
  debug = function(...) print('[DEBUG] ' .. string.format(...)) end,
  trace = function(...) print('[TRACE] ' .. string.format(...)) end,
}


local astrPlugins = {
  'romloader_eth',
  'romloader_usb',
  'romloader_uart',
  'romloader_jtag'
}
for _, strPlugin in ipairs(astrPlugins) do
  tLog.debug('Loading plugin "%s"...', strPlugin)
  require(strPlugin)
end

-- Run the shell.
local tShell = Shell(tLog)
tShell:run()
os.exit(0)
