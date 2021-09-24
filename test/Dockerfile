FROM dyne/devuan:chimaera

RUN apt-get update -y -q && apt-get install -y -q luarocks gcc cmake 

COPY . /lua-zenroom/

WORKDIR /lua-zenroom

RUN make check
