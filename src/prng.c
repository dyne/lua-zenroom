/*
 * This file is part of Zenroom (https://zenroom.org)
 * 
 * Copyright (C) 2020-2021 Dyne.org foundation
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

#include <inttypes.h>
#include <time.h>
#include <string.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <amcl.h>

#include <zen_error.h>
#include <encoding.h>
#include <randombytes.h>

extern void push_buffer_to_octet(lua_State *L, char *p, size_t len);

// exported PRNG
// easier name (csprng comes from amcl.h in milagro)
static csprng rng;
static int initialized = 0;

csprng *PRNG(lua_State *L) {
  if(!initialized) {
    error(L,"Random generator not initialized, use: RNG.seed()");
    return NULL;
  }
  return(&rng);
}

int rng_int8(lua_State *L) {
	uint8_t res = RAND_byte(&rng);
	lua_pushinteger(L, (lua_Integer)res);
	return(1);
}

int rng_int16(lua_State *L) {
	uint16_t res =
		RAND_byte(&rng)
		| (uint32_t) RAND_byte(&rng) << 8;
	lua_pushinteger(L, (lua_Integer)res);
	return(1);
}

int rng_int32(lua_State *L) {
	uint32_t res =
		RAND_byte(&rng)
		| (uint32_t) RAND_byte(&rng) << 8
		| (uint32_t) RAND_byte(&rng) << 16
		| (uint32_t) RAND_byte(&rng) << 24;
	lua_pushinteger(L, (lua_Integer)res);
	return(1);
}

int rng_int64(lua_State *L) {
	uint64_t res =
		RAND_byte(&rng)
		| (uint64_t) RAND_byte(&rng) << 8
		| (uint64_t) RAND_byte(&rng) << 16
		| (uint64_t) RAND_byte(&rng) << 24
		| (uint64_t) RAND_byte(&rng) << 32
		| (uint64_t) RAND_byte(&rng) << 40
		| (uint64_t) RAND_byte(&rng) << 48
		| (uint64_t) RAND_byte(&rng) << 56;
	lua_pushinteger(L, (lua_Integer)res);
	return(1);
}

int rng_seed(lua_State *L) {
  const char *s = lua_tostring(L, 1);
  uint8_t random_seed[256];
  int seedlen;
  if(s) {
    act(L,"Init RNG from input hex string (%u chars)", strlen(s)); // luaL_argcheck(L, s != NULL, 1, "string expected");
    seedlen = hex2buf(random_seed, s);
    func(L,"HEX string converted to %u bytes",seedlen);
    RAND_seed(&rng, seedlen, random_seed);
  } else {
    act(L,"Init RNG from system random");
    randombytes(random_seed, 252); // last 4 bytes from time
    uint32_t ttmp = (uint32_t) time(NULL);
    random_seed[252] = (ttmp >> 24) & 0xff;
    random_seed[253] = (ttmp >> 16) & 0xff;
    random_seed[254] = (ttmp >>  8) & 0xff;
    random_seed[255] =  ttmp & 0xff;
    RAND_seed(&rng, 256, random_seed);
  }
  initialized = 1;
	// expose the random seed for optional determinism
	push_buffer_to_octet(L, random_seed, seedlen);
	lua_setglobal(L, "RNGSEED");
  return(0);
}

const struct luaL_Reg rng_class [] = {
  {"seed",  rng_seed },
  {"int8",  rng_int8  },
  {"int16", rng_int16 },
  {"int32", rng_int32 },
  {"int64", rng_int64 },

  // TODO: compat with zenroom from lua
  /* {"random_int8",  rng_uint8  }, */
  /* {"random_int16", rng_uint16 }, */
  /* {"random_int32", rng_int32 }, */
  /* {"random8",  rng_uint8  }, */
  /* {"random16", rng_uint16 }, */
  /* {"random32", rng_int32 }, */
  /* {"random",  rng_uint16  }, */
  /* {"runtime_random256", rng_rr256 }, */
  {NULL, NULL}
};
const struct luaL_Reg rng_methods[] = {
  {NULL, NULL}
};
