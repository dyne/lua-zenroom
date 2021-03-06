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
 * on Monday, 27th September 2021
 */

#include <string.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <compat-5.3.h>

#include <amcl.h>

#include <zen_error.h>

static int traceback(lua_State *L) {
    lua_getfield(L, LUA_GLOBALSINDEX, "debug");
    lua_getfield(L, -1, "traceback");
    lua_pushvalue(L, 1);
    lua_pushinteger(L, 2);
    lua_call(L, 2, 1);
    warning(L,"%s", lua_tostring(L, -1));
    return 1;
}


static const char *lua_findtable (lua_State *L, int idx,
				  const char *fname, int szhint) {
	const char *e;
	if (idx) lua_pushvalue(L, idx);
	do {
		e = strchr(fname, '.');
		if (e == NULL) e = fname + strlen(fname);
		lua_pushlstring(L, fname, (size_t)(e - fname));
		if (lua_rawget(L, -2) == LUA_TNIL) {  /* no such field? */
			lua_pop(L, 1);  /* remove this nil */
			lua_createtable(L, 0, (*e == '.' ? 1 : szhint)); /* new table for field */
			lua_pushlstring(L, fname, (size_t)(e - fname));
			lua_pushvalue(L, -2);
			lua_settable(L, -4);  /* set new table into field */
		}
		else if (!lua_istable(L, -1)) {  /* field has a non-table value? */
			lua_pop(L, 2);  /* remove table and value */
			return fname;  /* return problematic part of the name */
		}
		lua_remove(L, -2);  /* remove previous table */
		fname = e + 1;
	} while (*e == '.');
	return NULL;
}

#define LUA_LOADED_TABLE        "_LOADED"
void lua_add_class(lua_State *L, char *name,
		   const luaL_Reg *_class, const luaL_Reg *methods) {
	char classmeta[512] = "zenroom.";
	strncat(classmeta, name, 511);
	luaL_newmetatable(L, classmeta);
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);  /* pushes the metatable */
	lua_settable(L, -3);  /* metatable.__index = metatable */
	if(methods) luaL_setfuncs(L,methods,0);

	lua_findtable(L, LUA_REGISTRYINDEX, LUA_LOADED_TABLE, 1);
	if (lua_getfield(L, -1, name) != LUA_TTABLE) {
		// no LOADED[modname]?
		lua_pop(L, 1);  // remove previous result
		// try global variable (and create one if it does not exist)
		lua_pushglobaltable(L);
		// TODO: 'sizehint' 1 here is for new() constructor. if more
		// than one it should be counted on the class
		if (lua_findtable(L, 0, name, 1) != NULL)
		  luaL_error(L, "name conflict for module '%s'", name);
		lua_pushvalue(L, -1);
		lua_setfield(L, -3, name);  /* LOADED[modname] = new table */
	}
	lua_remove(L, -2);  /* remove LOADED table */

	// in lua 5.1 was: luaL_pushmodule(L,name,1);

	lua_insert(L,-1);
	luaL_setfuncs(L,_class,0);
}


extern luaL_Reg rng_class;
extern luaL_Reg rng_methods;

extern luaL_Reg octet_class;
extern luaL_Reg octet_methods;

extern luaL_Reg hash_class;
extern luaL_Reg hash_methods;

extern luaL_Reg aes_class;
extern luaL_Reg aes_methods;

extern luaL_Reg vfastr_class;
extern luaL_Reg vfastr_methods;

extern luaL_Reg ecdh_class;
extern luaL_Reg ecdh_methods;
extern void ecdh_init();

extern luaL_Reg big_class;
extern luaL_Reg big_methods;
extern luaL_Reg ecp_class;
extern luaL_Reg ecp_methods;
extern luaL_Reg ecp2_class;
extern luaL_Reg ecp2_methods;
extern luaL_Reg fp12_class;
extern luaL_Reg fp12_methods;

LUALIB_API int luaopen_libzenroom (lua_State *L){
  // register classes
  lua_add_class(L, "rng", &rng_class, &rng_methods );
  lua_add_class(L, "vfastr", &vfastr_class, &vfastr_methods );
  lua_add_class(L, "octet", &octet_class, &octet_methods);
  lua_add_class(L, "hash", &hash_class, &hash_methods);
  lua_add_class(L, "aes", &aes_class, &aes_methods);
  ecdh_init();  // ecdh requires init for function pointers
  lua_add_class(L, "ecdh", &ecdh_class, &ecdh_methods);
  lua_add_class(L, "big", &big_class, &big_methods);
  lua_add_class(L, "ecp", &ecp_class, &ecp_methods);
  lua_add_class(L, "ecp2", &ecp2_class, &ecp2_methods);
  lua_add_class(L, "fp12", &fp12_class, &fp12_methods);
  
  lua_pushcfunction(L, traceback);
  return 1;
}

