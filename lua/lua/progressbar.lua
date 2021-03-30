-- Create the ProgressBar class.
local class = require "pl.class"
local ProgressBar = class()

function ProgressBar:_init(tLog, tparam)
    self.pl = require "pl.import_into"()

    self.tLog = tLog

    self.defaultTermSize = 80 -- termlib.termCol()

    -- attention: nil values are negleted in pl.Map but its not importent due to a call of the value is still nil
    local default_tparam =
        self.pl.Map {
        mode = nil,
        decimals = 1,
        fill = "█",
        prefix = "Progress:",
        suffix = " Complete",
        length = 50,
        printEnd = "\n",
        ProgressBarFinished = false,
        printLine = "",
        ProcessAlgo = "MultiLine", --or UnequalByteSingleLine or SingleLine
        totalByteSize = 1,
        sumByteIteration = 0,
        SL_Iteration = 1,
        SL_Total = 1,
        repeatProgress = false,
        showTotalProgress = false
    }

    self.default_tparam = default_tparam

    self:__UpdateParam(tparam)

    local this = self
    self.fnProgressBar = function(ulCnt, ulMax)
        return this:__ProgressBar_callback_progress(ulCnt, ulMax)
    end

    self.fnMessageProgressBar = function(a, b)
        return this:__ProgressBar_callback_message(a, b)
    end
end

function ProgressBar:__UpdateParam(tparam)
    local default_tparam = self.default_tparam
    local pl = self.pl

    tparam = tparam or {{}}
    if #tparam == 0 then
        tparam = {tparam}
    end

    local tparamAll = {}
    for key, value in ipairs(tparam) do
        tparamAll[key] = pl.Map(default_tparam)
        tparamAll[key]:update(value)
    end

    self.tparamAll = tparamAll
    self.tparam = self.tparamAll[1]
    self.iteration = 1
    self.total = #self.tparamAll

    return self
end

function ProgressBar:__getSizeProgressBar(ulMax)
    local total
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
                                    "|" ..
                                        "100." ..
                                            "% " ..
                                                "(" ..
                                                    total ..
                                                        "/" ..
                                                            total .. ")" .. self.tparam.suffix .. self.tparam.printEnd
    else
        totalProgressBar =
            self.tparam.prefix ..
            "|" ..
                "|" ..
                    "100." .. "% " .. "(" .. total .. "/" .. total .. ")" .. self.tparam.suffix .. self.tparam.printEnd
    end

    -- size of progress bar
    local sizeProgress = #totalProgressBar + self.tparam.decimals + self.tparam.length

    -- too large
    while sizeProgress > self.defaultTermSize do
        self.tparam.length = self.tparam.length - 1
        sizeProgress = sizeProgress - 1
    end

    -- too small
    while sizeProgress < self.defaultTermSize do
        self.tparam.length = self.tparam.length + 1
        sizeProgress = sizeProgress + 1
    end
end

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
        elseif self.tparam.ProcessAlgo == "MultiLine" then
            ulTerm = (ulCnt / ulMax)
            ulPercent = string.format(str_temp, 100 * ulTerm)
            ulFilledLength = math.floor(self.tparam.length * ulTerm)
        elseif self.tparam.ProcessAlgo == "UnequalByteSingleLine" then
            ulTerm =
                (ulCnt / ulMax) * (ulMax / self.tparam.totalByteSize) +
                ((self.tparam.sumByteIteration) / self.tparam.totalByteSize)
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
                self.tparam.sumByteIteration = self.tparam.sumByteIteration + ulMax
                if self.tparam.sumByteIteration >= self.tparam.totalByteSize then
                    self.iteration = self.iteration + 1
                    self.tparam.sumByteIteration = 0
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
            self.tparam.sumByteIteration = 0
            self.tparam.ProgressBarFinished = false
        end
    end

    return true
end

function ProgressBar:__ProgressBar_callback_message(a, b)
    local tLog = self.tLog

    if type(a) == "string" and string.len(a) > 0 then
        local strCnt, strMax = string.match(a, "%% ([%x%X]+)/([%x%X]+)")
        if strCnt and strMax then
            local ulCnt = tonumber(strCnt, 16)
            local ulMax = tonumber(strMax, 16)
            if ulCnt and ulMax then
                self:__getSizeProgressBar(ulMax)
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
