#  lua-zenroom (GNU Makefile build system)
#
#  (c) Copyright 2020-2021 Dyne.org foundation
#  designed, written and maintained by Denis Roio <jaromil@dyne.org>
#
#  This program is free software: you can redistribute it and/or
#  modify it under the terms of the GNU General Public License version
#  3 as published by the Free Software Foundation.
#
#  This program is distributed in the hope that it will be useful, but
#  WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see
#  <http://www.gnu.org/licenses/>.

SOURCES := zenroom.o \
	encoding.o base58.c \
	randombytes.o prng.o \
	zen_octet.o zen_hash.o zen_aes.o \
	zen_parse.o zen_error.o \
	zen_ecdh.o zen_ecdh_factory.o \
	zen_big.o zen_ecp.o zen_ecp2.o zen_fp12.o \
	compat-5.3.o


amcl := ../lib/milagro-crypto-c

all: CFLAGS += -fPIC -I/usr/include/lua5.1 -I${amcl}/build/include -I${amcl}/include
all: ${SOURCES}
	${CC} ${CFLAGS} ${SOURCES} -o libzenroom.so ${LDFLAGS} ${LDADD}

check: NIST := ../test/nist
check:
	lua${LUAVER} -l zenroom ../test/compat53.lua
	lua${LUAVER} -l zenroom ../test/octet_conversion.lua
	lua${LUAVER} -l zenroom ../test/octet.lua
	lua${LUAVER} -l zenroom ../test/hash.lua
	lua${LUAVER} -l zenroom ${NIST}/aes_ctr.lua
	lua${LUAVER} -l zenroom ${NIST}/aes_gcm.lua
	lua${LUAVER} -l zenroom ${NIST}/check_rsp.lua
	lua${LUAVER} -l zenroom ${NIST}/aes_cbc.lua
	lua${LUAVER} -l zenroom ../test/ecdh.lua
	lua${LUAVER} -l zenroom ../test/ecp_generic.lua



gdb:
	gdb --args lua${LUAVER} -l zenroom -i

clean:
	rm -f *.o
	rm -f *.so

.c.o:
	${CC} ${CFLAGS} -I. -c $< -o $@ -DVERSION=\"${VERSION}\"
