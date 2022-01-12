--[[
--This file is part of zenroom
--
--Copyright (C) 2018-2021 Dyne.org foundation
--designed, written and maintained by Denis Roio <jaromil@dyne.org>
--
--This program is free software: you can redistribute it and/or modify
--it under the terms of the GNU Affero General Public License v3.0
--
--This program is distributed in the hope that it will be useful,
--but WITHOUT ANY WARRANTY; without even the implied warranty of
--MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--GNU Affero General Public License for more details.
--
--Along with this program you should have received a copy of the
--GNU Affero General Public License v3.0
--If not, see http://www.gnu.org/licenses/agpl.txt
--
--Last modified by Denis Roio
--on Tuesday, 28th September 2021
--]]

require'libzenroom'
-- TODO: set version from C
ZENROOM_VERSION = '2.0.0-lua'

RNG = require'rng'
RNG.seed() -- init with system random

BIG = require'big'
ECDH = require'ecdh'
AES = require'aes'

OCTET = require'zenroom.zenroom_octet'
ECP = require'zenroom.zenroom_ecp'
ECP2 = require'zenroom.zenroom_ecp2'
HASH = require'zenroom.zenroom_hash'

O = OCTET -- alias
INT = BIG -- alias
H = HASH -- alias

STR = require'vfastr'
trim = STR.trim
trimq = STR.trimq
strcasecmp = STR.strcasecmp
parse_prefix = STR.parse_prefix
printerr = STR.printerr

_G['split'] = function(src,pat)
   local tbl = {}
   src:gsub(pat, function(x) tbl[#tbl+1]=x end)
   return tbl
end
_G['strtok'] = function(src, pat)
   if not src then return { } end
   pat = pat or "%S+"
   assert(type(src) == "string", "strtok error: argument is not a string")
   return split(src, pat)
end
luatype = type
_G['type'] = function(var)
   local simple = luatype(var)
   if simple == "userdata" then
	  local meta = getmetatable(var)
	  if meta then return(meta.__name)
	  else return("unknown") end
   else return(simple) end
end
-- TODO: optimise in C
function iszen(n)
   if not n then return false end
   for _ in n:gmatch("zenroom") do
	  return true
   end
   return false
end
-- workaround for a ternary conditional operator
function fif(condition, if_true, if_false)
  if condition then return if_true else return if_false end
end
