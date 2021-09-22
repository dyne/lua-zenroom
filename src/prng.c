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
 * on Wednesday, 22nd September 2021
 */

#include <inttypes.h>
#include <time.h>
#include <string.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <amcl.h>

#include <randombytes.h>

// exported PRNG
// easier name (csprng comes from amcl.h in milagro)
static csprng rng;

csprng *PRNG() { return(&rng); }

static uint8_t random_seed[256];

void prng_init() {
	randombytes(random_seed, 252); // last 4 bytes from time
	uint32_t ttmp = (uint32_t) time(NULL);
	random_seed[252] = (ttmp >> 24) & 0xff;
	random_seed[253] = (ttmp >> 16) & 0xff;
	random_seed[254] = (ttmp >>  8) & 0xff;
	random_seed[255] =  ttmp & 0xff;
	char tseed[256]; // RAND_seed is destructive, preserve seed here
	memcpy(tseed,random_seed,256);
	RAND_seed(&rng, 256, tseed);
}

int rng_uint8(lua_State *L) {
	uint8_t res = RAND_byte(&rng);
	lua_pushinteger(L, (lua_Integer)res);
	return(1);
}

int rng_uint16(lua_State *L) {
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
