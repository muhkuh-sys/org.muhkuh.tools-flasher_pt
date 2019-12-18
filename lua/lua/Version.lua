--- A version number.
-- @author cthelen@hilscher.com
-- @copyright 2016 Hilscher Gesellschaft für Systemautomation mbH


-- Create the class.
local class = require 'pl.class'
local Version = class()



function Version:_init()
  -- The "penlight" module is used to parse the configuration file.
  self.pl = require'pl.import_into'()
end



--- Convert a string to a positive integer.
-- This function converts one component of a version from a string to a number.
-- The components of a version are separated by dots ("."). One component must
-- be a positive integer.
-- @param strComponent The string to be converted.
-- @return If an error occured, it returns nil and an error message as a string.
--         If the function succeeded it returns the converted number.
function Version:_componentToNumber(strComponent)
  -- Be pessimistic.
  local tResult = nil
  local strError = nil

  -- Try to convert the component to a number.
  local uiNumber = tonumber(strComponent)
  if uiNumber==nil then
    -- Failed to convert the component to a number.
    strError = string.format('"%s" is no number!', strComponent)
  elseif uiNumber<0 then
    -- The component is a negative number. This is invalid!
    strError = string.format('"%s" is negativ!', strComponent)
  else
    -- The component is a positive integer.
    tResult = uiNumber
  end

  return tResult, strError
end



function Version:_convertStringToList(strVersion)
  local tResult = true
  local strError = nil
  local auiComponents = {}


  -- Split the version string by dots.
  local astrComponents = self.pl.stringx.split(strVersion, '.')

  -- Convert all components to numbers.
  for _, strComponent in ipairs(astrComponents) do
    local uiNumber, strMsg = self:_componentToNumber(strComponent)
    if uiNumber==nil then
      tResult = nil
      strError = strMsg
      break
    else
      table.insert(auiComponents, uiNumber)
    end
  end

  if tResult==true then
    -- Does the list contain at least one version number?
    if #auiComponents==0 then
      tResult = nil
      strError = string.format("Invalid version: the string '%s' contains no version components.", strVersion)
    else
      tResult = auiComponents
    end
  end

  return tResult, strError
end



--- Compare with another version.
-- This function compares the current version ("A") with another version ("B").
-- @param tVersion The other version "B" to compare with.
-- @return  -1 if A < B
--           0 if A == B
--           1 if A > B
function Version.compare(tVersionA, tVersionB)
  -- Get quick links to the versions.
  local atVersionA = tVersionA.atVersion
  local atVersionB = tVersionB.atVersion

  -- Get the size of both versions.
  local sizVersionA = #atVersionA
  local sizVersionB = #atVersionB

  -- Get the maximum size.
  local sizMax = math.max(sizVersionA, sizVersionB)

  -- Compare both versions.
  local iResult = 0
  for uiPos=1,sizMax do
    -- Get the next version component or 0 if not enough digits are present.
    local uiComponentA = atVersionA[uiPos] or 0
    local uiComponentB = atVersionB[uiPos] or 0

    -- Get the difference of the version components
    local iDiff = uiComponentA - uiComponentB
    if iDiff<0 then
      iResult = -1
      break
    elseif iDiff>0 then
      iResult = 1
      break
    end
  end

  return iResult
end



function Version:get()
  local strRepr = ''

  if self.atVersion~=nil then
    strRepr = table.concat(self.atVersion, '.')
  end

  return strRepr
end



function Version:set(tVersion)
  local tResult
  local strError

  -- A parameter of "nil" allows to clear the version.
  if type(tVersion)=='nil' then
    self.atVersion = nil
    tResult = true

  elseif type(tVersion)=='string' then
    tResult, strError = self:_convertStringToList(tVersion)
    if tResult~=nil then
      self.atVersion = tResult
      tResult = true
    end

  elseif type(tVersion)=='table' then
    -- Is this a Version object or a plain version table?
    if type(tVersion.is_a)=='function' and tVersion:is_a(Version)==true then
      self.atVersion = tVersion.atVersion
      tResult = true
    else
      local strVersion = table.concat(tVersion, '.')
      tResult, strError = self:_convertStringToList(strVersion)
      if tResult~=nil then
        self.atVersion = tResult
        tResult = true
      end
    end
  end

  return tResult, strError
end



function Version:__tostring()
  return string.format('Version(%s)', self:get())
end



return Version
