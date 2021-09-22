FROM dyne/devuan:chimaera

RUN apt-get update -y -q && apt-get install -y -q luarocks gcc cmake 

COPY . /lua-cryptolang/

WORKDIR /lua-cryptolang

RUN make check
