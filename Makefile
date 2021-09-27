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

version=0.1.0
pwd := $(shell pwd)
ARCH=$(shell uname -m)
system := Linux
gcc := gcc
luaver := 5.1
ldflags := -fPIC -shared
ar := $(shell which ar) # cmake requires full path
ranlib := ranlib
ld := ld
platform := posix

# ----------------
# milagro settings
rsa_bits := ""
ecdh_curve := "SECP256K1"
ecp_curve  := "BLS381"
milagro_cmake_flags := -DBUILD_SHARED_LIBS=OFF -DBUILD_PYTHON=OFF -DBUILD_DOXYGEN=OFF -DBUILD_DOCS=OFF -DBUILD_BENCHMARKS=OFF -DBUILD_EXAMPLES=OFF -DWORD_SIZE=64 -DBUILD_PAILLIER=ON -DBUILD_X509=OFF -DBUILD_WCC=OFF -DBUILD_MPIN=OFF -DAMCL_CURVE=${ecdh_curve},${ecp_curve} -DAMCL_RSA="" -DCMAKE_SHARED_LIBRARY_LINK_FLAGS="" -DC99=1 
milagro_cflags := -fPIC

milib := ${pwd}/lib/milagro-crypto-c/build/lib
ldadd += ${milib}/libamcl_curve_${ecp_curve}.a
ldadd += ${milib}/libamcl_pairing_${ecp_curve}.a
ldadd += ${milib}/libamcl_curve_${ecdh_curve}.a
ldadd += ${milib}/libamcl_paillier.a
ldadd += ${milib}/libamcl_core.a

all: milagro codegen zenroom

codegen:
	cd src && ./codegen_ecdh_factory.sh ${ecdh_curve}
	cd src && ./codegen_ecp_factory.sh ${ecp_curve}

debug: milagro codegen
	CC="${gcc}" AR="${ar}" \
		LDFLAGS="${ldflags}" LDADD="${ldadd}" CFLAGS="-O0 -ggdb -DDEBUG=3" \
		VERSION="${version}" \
		make -C src

zenroom:
	CC="${gcc}" AR="${ar}" \
		LDFLAGS="${ldflags}" LDADD="${ldadd}" \
		VERSION="${version}" \
		make -C src

milagro:
	@echo "-- Building milagro (${system})"
	if ! [ -r ${pwd}/lib/milagro-crypto-c/build/CMakeCache.txt ]; then \
		cd ${pwd}/lib/milagro-crypto-c && \
		mkdir -p build && \
		cd build && \
		CC=${gcc} LD=${ld} \
		cmake ../ -DCMAKE_C_FLAGS="${cflags} ${milagro_cflags}" \
		-DCMAKE_SYSTEM_NAME="${system}" \
		-DCMAKE_AR=${ar} -DCMAKE_C_COMPILER=${gcc} ${milagro_cmake_flags}; \
	fi
	if ! [ -r ${pwd}/lib/milagro-crypto-c/build/lib/libamcl_core.a ]; then \
		CC=${gcc} CFLAGS="${cflags}" AR=${ar} RANLIB=${ranlib} LD=${ld} \
		make -C ${pwd}/lib/milagro-crypto-c/build; \
	fi

check: cflags += -O0 -ggdb -DDEBUG
check: milagro zenroom
	LUAVER=${luaver} make -C src check

check-random:
	if ! command -v rngtest; then echo "No rngtest found, install rng-tools"; fi
	./test/random_rngtest_fips140-2.sh

gdb:
	LUAVER=${luaver} make -C src gdb

clean:
	rm -rf ${pwd}/lib/milagro-crypto-c/build
	make clean -C ${pwd}/src

install: PREFIX ?= /usr/local
install: DEST_LIBDIR ?= ${PREFIX}/lib/lua/5.1
install: DEST_SHAREDIR ?= ${PREFIX}/share/lua/5.1
install:
	install src/libzenroom.so ${DEST_LIBDIR}/libzenroom.so
	install src/lua/init.lua -D ${DEST_SHAREDIR}/zenroom/init.lua
	cp -v src/lua/zenroom_*.lua ${DEST_SHAREDIR}/zenroom/

