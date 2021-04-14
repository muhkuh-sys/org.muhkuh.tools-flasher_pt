----------------------
-- Support by initializing and displaying of progress bar informationen.
-- @author Simon Truber
-- @copyright
-- @license
-- @release
-- @classmod progressbar

-- Create the ProgressBar class.
local class = require "pl.class"

local ProgressBar = class()

--- Initialize a ProgressBar instance upon creation. The default value of term size is 80 chars.
-- @param tLog initial logger object
-- @param tparam initial parameter table of the progress bar
-- @see __UpdateParam
function ProgressBar:_init(tLog, tparam)
    self.pl = require "pl.import_into"()

    self.tLog = tLog

    -- default value of term size
    self.defaultTermSize = 80 -- termlib.termCol()

    -- Attention: nil values are negleted in pl.Map but its not importent due to a call of the value is still nil.

    --- Default paramter table of the progress bar.
    -- @field mode nil or 'debug' (default: nil)
    -- @field decimals decimal places percent (default: 1)
    -- @field fill (default: "█")
    -- @field prefix (default: "Progress:")
    -- @field suffix (default: "Complete:")
    -- @field length of progress bar (default: 50)
    -- @field printEnd final print (default: "\n")
    -- @field ProgressBarFinished (default: false)
    -- @field printLine at the end of each process step (default: "")
    -- @field ProcessAlgo  "Simple" or "SingleLine" or "UnequalByteSingleLine" (default: "Simple")
    -- @field totalByteSize for UnequalByteSingleLine algorithm (default: 1)
    -- @field SL_Iteration for SingleLine algorithm (default: 1)
    -- @field SL_Total for SingleLine algorithm (default: 1)
    -- @field repeatProgress repeat the progress bar (default: false)
    -- @field showTotalProgress total progress after prefix symbol (default: false)
    -- @table ProgressBar.default_tparam
    local default_tparam =
        self.pl.Map {
        mode = nil,
        decimals = 1,
        fill = "█",
        prefix = "Progress:",
        suffix = " Complete",
        length = 50,
        printEnd = "\n", -- final print
        ProgressBarFinished = false,
        printLine = "", -- at the end of each process step
        ProcessAlgo = "Simple", --or UnequalByteSingleLine or SingleLine
        totalByteSize = 1, -- for UnequalByteSingleLine algorithm
        SL_Iteration = 1, -- for SingleLine algorithm
        SL_Total = 1, -- for SingleLine algorithm
        repeatProgress = false,
        showTotalProgress = false -- e.g. in the case of SingleLine algorithm and more than one progress should be shown
    }

    self.default_tparam = default_tparam

    -- for UnequalByteSingleLine algorithm
    self.sumByteIteration = 0

    -- initialize the table of paramter
    self:__UpdateParam(tparam)

    -- initialize the callback functions
    local this = self
    self.fnProgressBar = function(ulCnt, ulMax)
        return this:__ProgressBar_callback_progress(ulCnt, ulMax)
    end

    self.fnMessageProgressBar = function(a, b)
        return this:__ProgressBar_callback_message(a, b)
    end
end

--- Update the table of parameters of the progress bar with default and given paramters.
-- @param tparam table of parameter of the progress bar
-- @return the object of the progress bar with the updated parameters
function ProgressBar:__UpdateParam(tparam)
    local default_tparam = self.default_tparam
    local pl = self.pl

    tparam = tparam or {{}}
    if #tparam == 0 then
        tparam = {tparam}
    end

    -- all given progress bars in tparam are saved in tparamAll with updated default paramters. 
    local tparamAll = {}
    for key, value in ipairs(tparam) do
        -- initialize tparamAll[key] with default parameters
        tparamAll[key] = pl.Map(default_tparam)
        -- update tparamAll[key] with given progress bars paramters in tparam[key]
        tparamAll[key]:update(value)
    end

    self.tparamAll = tparamAll
    self.tparam = self.tparamAll[1]
    
    -- starting iteration
    self.iteration = 1

    -- total number of given progress bars
    self.total = #self.tparamAll

    -- for UnequalByteSingleLine algorithm
    self.sumByteIteration = 0

    return self
end

--- Determine the size of the progress bar depending on default size of the term. The default size of the term is set to 80.
-- @param ulMax maximum value - total number of bytes
function ProgressBar:__getSizeProgressBar(ulMax)
    local total
    local tLog = self.tLog

    if self.tparam.ProcessAlgo == "SingleLine" then
        total = self.tparam.SL_Total
    else
        total = ulMax
    end

    -- construct complete string of process bar to calculate total length
    local totalProgressBar
    if self.tparam.showTotalProgress == true then
        totalProgressBar =
            self.tparam.prefix ..
            "[" ..
                self.iteration ..
                    "/" ..
                        self.total ..
                            "]: " ..
                                "|" ..
                                    "|" .. "100." .. "% " .. "(" .. total .. "/" .. total .. ")" .. self.tparam.suffix --.. self.tparam.printEnd
    else
        totalProgressBar =
            self.tparam.prefix ..
            "|" .. "|" .. "100." .. "% " .. "(" .. total .. "/" .. total .. ")" .. self.tparam.suffix --.. self.tparam.printEnd
    end

    -- size of progress bar
    local sizeProgress = #totalProgressBar + self.tparam.decimals + self.tparam.length

    -- too large
    while sizeProgress > self.defaultTermSize do
        self.tparam.length = self.tparam.length - 1
        sizeProgress = sizeProgress - 1
        -- tLog.debug("too large - ","Prefix: ",self.tparam.prefix," - size progress bar: ",sizeProgress)
    end

    -- too small
    while sizeProgress < self.defaultTermSize do
        self.tparam.length = self.tparam.length + 1
        sizeProgress = sizeProgress + 1
        -- tLog.debug(" too small - ","Prefix: ",self.tparam.prefix," - size progress bar: ",sizeProgress)
    end
end

--- Construct and display the progress bar as callback function.
-- Different algorithm can be used: "Simple", "SingleLine" or "UnequalByteSingleLine"
--
-- "Simple": a total progress bar for one event.
--
-- "SingleLine": multiple events (SL_Total) in one progress bar. The starting iteration is SL_Iteration.
--
-- "UnequalByteSingleLine": multiple events with different known byte size (sum = totalByteSize) in one progress bar.
-- @param ulCnt counter value - number of processed bytes
-- @param ulMax maximum value - total number of bytes
-- @see __getSizeProgressBar
function ProgressBar:__ProgressBar_callback_progress(ulCnt, ulMax)
    local tLog = self.tLog
    ulCnt = ulCnt or 1
    ulMax = ulMax or 1

    self:__getSizeProgressBar(ulMax)

    -- in the case of an excess of the total size
    if (self.iteration <= self.total) and (ulCnt <= ulMax) then
        local str_temp = "%." .. self.tparam.decimals .. "f"
        local ulPercent
        local ulFilledLength
        local ulTerm

        -- build up bar percent and filled length
        if self.tparam.ProcessAlgo == "SingleLine" then
            ulTerm =
                (ulCnt / ulMax) * (1 / self.tparam.SL_Total) + ((self.tparam.SL_Iteration - 1) / self.tparam.SL_Total)
            ulPercent = string.format(str_temp, 100 * ulTerm)
            ulFilledLength = math.floor(self.tparam.length * ulTerm)
        elseif self.tparam.ProcessAlgo == "Simple" then
            ulTerm = (ulCnt / ulMax)
            ulPercent = string.format(str_temp, 100 * ulTerm)
            ulFilledLength = math.floor(self.tparam.length * ulTerm)
        elseif self.tparam.ProcessAlgo == "UnequalByteSingleLine" then
            ulTerm =
                (ulCnt / ulMax) * (ulMax / self.tparam.totalByteSize) +
                ((self.sumByteIteration) / self.tparam.totalByteSize)
            ulPercent = string.format(str_temp, 100 * ulTerm)
            ulFilledLength = math.floor(self.tparam.length * ulTerm)
        end

        local strBar =
            string.rep(self.tparam.fill, ulFilledLength) .. string.rep("-", self.tparam.length - ulFilledLength)

        -- number of processed iterations / total iterations
        local ulIteration
        local ulTotal
        if self.tparam.ProcessAlgo == "SingleLine" then
            ulIteration = self.tparam.SL_Iteration
            ulTotal = self.tparam.SL_Total
        else
            ulIteration = ulCnt
            ulTotal = ulMax
        end

        -- complete string of progress bar
        local strProgressBar
        -- with active showTotalProgress
        if self.tparam.showTotalProgress == true then
            strProgressBar =
                "\r" ..
                self.tparam.prefix ..
                    "[" ..
                        self.iteration ..
                            "/" ..
                                self.total ..
                                    "]: " ..
                                        "|" ..
                                            strBar ..
                                                "|" .. ulPercent .. "% " .. "(" .. ulIteration .. "/" .. ulTotal .. ")"
        else
            strProgressBar =
                "\r" ..
                self.tparam.prefix ..
                    "|" .. strBar .. "|" .. ulPercent .. "% " .. "(" .. ulIteration .. "/" .. ulTotal .. ")"
        end

        -- final progress Bar with suffix and printEnd
        if ulCnt >= ulMax then
            if self.tparam.ProcessAlgo == "SingleLine" and self.tparam.SL_Iteration >= self.tparam.SL_Total then
                strProgressBar = strProgressBar .. self.tparam.suffix .. self.tparam.printEnd
                self.tparam.ProgressBarFinished = true
            elseif self.tparam.ProcessAlgo ~= "SingleLine" and self.tparam.mode ~= "debug" then
                strProgressBar = strProgressBar .. self.tparam.suffix .. self.tparam.printEnd
                self.tparam.ProgressBarFinished = true
            elseif self.tparam.ProcessAlgo ~= "SingleLine" and self.tparam.mode == "debug" then
                -- without printEnd for debug mode due to double /n at the end
                strProgressBar = strProgressBar .. self.tparam.suffix
                self.tparam.ProgressBarFinished = true
            end
        end

        -- io.write for different modes and ProcessAlgo
        if self.tparam.mode == "debug" and ulCnt >= ulMax then
            tLog.debug(strProgressBar)
        elseif self.tparam.ProcessAlgo == "UnequalByteSingleLine" or self.tparam.ProcessAlgo == "SingleLine" then
            -- self.tparam.printLine due to multi line Progress Bar
            if ulCnt >= ulMax then
                io.write(strProgressBar .. self.tparam.printLine)
                io.flush()
            else
                io.write(strProgressBar)
                io.flush()
            end
        elseif self.tparam.mode == nil then
            io.write(strProgressBar .. self.tparam.printLine)
            io.flush()
        end

        -- count up the iteration state for differ ProcessAlgo
        if ulCnt >= ulMax then
            if self.tparam.ProcessAlgo == "UnequalByteSingleLine" then
                self.sumByteIteration = self.sumByteIteration + ulMax
                if self.sumByteIteration >= self.tparam.totalByteSize then
                    self.iteration = self.iteration + 1
                    self.sumByteIteration = 0
                    if #self.tparamAll >= self.iteration then
                        self.tparam = self.tparamAll[self.iteration]
                    end
                end
            elseif self.tparam.ProcessAlgo == "SingleLine" then
                if self.tparam.SL_Iteration >= self.tparam.SL_Total then
                    self.iteration = self.iteration + 1
                    self.tparam.SL_Iteration = 0

                    if #self.tparamAll >= self.iteration then
                        self.tparam = self.tparamAll[self.iteration]
                    end
                else
                    self.tparam.SL_Iteration = self.tparam.SL_Iteration + 1
                end
            else
                self.iteration = self.iteration + 1
                if #self.tparamAll >= self.iteration then
                    self.tparam = self.tparamAll[self.iteration]
                end
            end
        end

        -- repeat progress bar
        if self.tparam.repeatProgress == true and self.iteration > self.total then
            self.iteration = 1
            self.tparam.SL_Iteration = 1
            self.sumByteIteration = 0
            self.tparam.ProgressBarFinished = false
        end
    end

    return true
end

--- The callback message function of the netx - either a string or progress bar information
-- @param a return value/string of NetX
-- @param b return value/string of NetX (dummy value)
function ProgressBar:__ProgressBar_callback_message(a, b)
    local tLog = self.tLog

    if type(a) == "string" and string.len(a) > 0 then
        local strCnt, strMax = string.match(a, "%% ([%x%X]+)/([%x%X]+)")
        if strCnt and strMax then
            local ulCnt = tonumber(strCnt, 16)
            local ulMax = tonumber(strMax, 16)
            if ulCnt and ulMax then
                return self:__ProgressBar_callback_progress(ulCnt, ulMax)
            end
        else
            if string.sub(a, -1) == "\n" then
                a = string.sub(a, 1, -2)
            end
            self.tLog.debug("[NETX] %s", a)
        end
    end

    return true
end

return ProgressBar
