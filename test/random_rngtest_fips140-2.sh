#!/bin/sh

# this test requires rng-tools

times=1000
which rngtest
if ! [ $? = 0 ]; then
	echo "rngtest not found, FIPS140-2 random test skipped"
	return 0
fi
# 1000 blocks of 20000 bits (2500 bytes)
# 32 bits / 4 bytes rngtest header
cat <<EOF | lua5.1 -l zenroom | rngtest -c $times
o = OCTET.random(4 + (2500 * $times))
print(#o)
STR.raw_print(o)
EOF
