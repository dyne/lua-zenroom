/*
 * This file is part of Zenroom (https://zenroom.org)
 * 
 * Copyright (C) 2017-2021 Dyne.org foundation
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>

#if defined(_WIN32)
/* Windows */
# include <windows.h>
#include <intrin.h>
#include <malloc.h>
#endif

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <zen_error.h>

// ANSI colors for terminal
const char* ANSI_RED     = "\x1b[1;31m";
const char* ANSI_GREEN   = "\x1b[1;32m";
const char* ANSI_YELLOW  = "\x1b[1;33m";
const char* ANSI_BLUE    = "\x1b[1;34m";
const char* ANSI_MAGENTA = "\x1b[35m";
const char* ANSI_CYAN    = "\x1b[36m";
const char* ANSI_RESET   = "\x1b[0m";

static char pfx[MAX_STRING];

int zen_write_err_va(const char *fmt, va_list va) {
	return(vfprintf(stderr,fmt,va)); // no init yet, print to stderr
}

int lerror(lua_State *L, const char *fmt, ...) {
	va_list argp;
	va_start(argp, fmt);
	error(0,fmt,argp);
	luaL_where(L, 1);
	lua_pushvfstring(L, fmt, argp);
	va_end(argp);
	lua_concat(L, 2);
	return lua_error(L);
}

void notice(lua_State *L, const char *format, ...) {
	va_list arg;
	snprintf(pfx, MAX_STRING-1, "[*] %s\n",format);
	va_start(arg, format);
	zen_write_err_va(pfx, arg);
	va_end(arg);
}

void func(void *L, const char *format, ...) {
	va_list arg;
	snprintf(pfx, MAX_STRING-1, "[D] %s\n",format);
	va_start(arg, format);
	zen_write_err_va(pfx, arg);
	va_end(arg);

}

void error(lua_State *L, const char *format, ...) {
	if(!format) return;
	va_list arg;
	snprintf(pfx, MAX_STRING-1, "[!] %s\n",format);
	va_start(arg, format);
	zen_write_err_va(pfx, arg);
	va_end(arg);
	// exit(1); // calls teardown (signal 11) TODO: check if OK with seccomp
}

void act(lua_State *L, const char *format, ...) {
	va_list arg;
	snprintf(pfx, MAX_STRING-1, " .  %s\n",format);
	va_start(arg, format);
	zen_write_err_va(pfx, arg);
	va_end(arg);
}

void warning(lua_State *L, const char *format, ...) {
	va_list arg;
	snprintf(pfx, MAX_STRING-1, "[W] %s\n",format);
	va_start(arg, format);
	zen_write_err_va(pfx, arg);
	va_end(arg);
}
