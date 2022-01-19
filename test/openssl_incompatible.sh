#!/bin/sh

res=`echo "print(O.random(32):hex())" | tarantool -l zenroom`
# 32 bytes of zeros
zeros="0000000000000000000000000000000000000000000000000000000000000000"

if [ "x$res" = "x$zeros" ]; then
  echo "FAILED"
  return 1
fi
