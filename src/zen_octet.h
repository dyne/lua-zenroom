/*
 * This file is part of Zenroom (https://zenroom.org)
 * 
 * Copyright (C) 2021 Dyne.org foundation
 * designed, written and maintained by Denis Roio <jaromil@dyne.org>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License v3.0
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * Along with this program you should have received a copy of the
 * GNU Affero General Public License v3.0
 * If not, see http://www.gnu.org/licenses/agpl.txt
 * 
 * Last modified by Denis Roio
 * on Wednesday, 22nd September 2021
 */

#ifndef __ZEN_OCTET_H__
#define __ZEN_OCTET_H__

#include <amcl.h>

// REMEMBER: o_new and o_dup push a new object in lua's stack
octet* o_new(lua_State *L, const int size);

octet *o_dup(lua_State *L, octet *o);

octet* o_arg(lua_State *L,int n);

void push_octet_to_hex_string(lua_State *L, octet *o);
void push_buffer_to_octet(lua_State *L, char *p, size_t len);

#endif

