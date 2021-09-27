<p align="center">
  <a href="https://zenroom.org">
    <img alt="Zenroom" src="./docs/zenroom-logotype.png" width="640" />
  </a>
</p>

# Crypto primitives for Lua5.1

<p align="center">
  <a href="https://dyne.org">
    <img src="https://img.shields.io/badge/%3C%2F%3E%20with%20%E2%9D%A4%20by-Dyne.org-blue.svg" alt="Dyne.org">
  </a>
</p>

<br><br>

[💾 Install](#-install)
•
[🎮 Quick start](#-quick-start)
•
[🐝 API](#-api)
• 
[📋 Testing](#-testing)
• 
[😍 Acknowledgements](#-acknowledgements)
•
[🌐 Links](#-links)
•
[👤 Contributing](#-contributing)
•
[💼 Disclaimer](#-disclaimer)

This is the port of zenroom language ported out of [Zenroom](https://zenroom.org)'s VM to run on Lua 5.1 and all derivates (including Luajit, Nginx, Openresty and Tarantool)

Lua Zenroom is a portable cryptographic module aiming to execute secure cryptographic computations within [distributed computing](https://en.wikipedia.org/wiki/Distributed_computing) environments that can be easily scripted by Lua.

This Lua module works only on 64-bit systems. For 32-bit support please use the Zenroom VM.

## 💾 Install

To build from source the following dependencies are needed:
```
gcc make cmake zsh
```

Then simply run the default targets of `Makefile`:
```
make && make install
```
Lua Zenroom will be installed in `/usr/local/lib/lua/5.1/libzenroom.so` and `/usr/local/share/lua/5.1/zenroom/`.

Luarocks spec file and upload is work in progress.

---
## 🎮 Quick start

To see Lua-Zenroom in action you can fire up the Lua interpreter loading `zenroom`

```
luajit -l zenroom
```

As a working example you can now generate an ECDH keypair

```
keypair = ECDH.keygen()
print(keypair.private)
print(keypair.public)
```

If you prefer to print them out in `base58` or `hex` encoding:

```
print(keypair.private:base58())
print(keypair.public:hex())
```

A [tutorial about crypto modeling with Zenroom in Lua](https://dev.zenroom.org/#/pages/lua) is also available.

---
## 🐝 API

Look at the [Zenroom internal API in Lua](https://dev.zenroom.org/#/pages/ldoc/o/README) to see the current API, more documentation will come soon.

You are welcome to join the [Zenroom telegram channel](https://t.me/zenroom) and ask for help.

---
## 📋 Testing

Run the test with

```
make check
```

The above includes NIST tests on hashing algorithms SHA256 and SHA512.

Random quality tests (FIPS140) need `rng-tools` to be installed, then run:

```
make check-random
```

---
## 🐛 Troubleshooting & debugging

There are some known issues under analysis:
- SHA3 functions are not yet passing NIST tests
- RNG determinism works but is not yet compatible with Zenroom VM

If you find any problem or suspicious behaviours please [open an issue](../../issues)

If you intend to use lua-zenroom in production please consider getting in touch with us.

---
## 😍 Acknowledgements

Copyright © 2020-2021 by [Dyne.org](https://www.dyne.org) foundation, Amsterdam.

**Lua Zenroom is licensed as AGPLv3; we are open to grant license exceptions for specific needs.**

Designed, written and maintained by Denis "[Jaromil](https://jaromil.dyne.org)" Roio

with help by Puria Nafisi Azizi and Andrea D'Intino

Enterprise level support contracts are available upon request, as well customisations and license exceptions: you are welcome to [get in touch with us](https://forkbomb.eu).

---
## 🌐 Links

- [Zenroom](https://zenroom.org): the main project this Lua module stems from
- [Zenroom on Github](https://github.com/dyne/zenroom): the main code repository for Zenroom
- [DECODE](https://decodeproject.eu): the European resewarch project that gave birth to Zenroom
- [Zencode documentation](https://dev.zenroom.org): the Zencode DSL uses Zenroom primitives
- [Dyne.org](https://dyne.org): the foundation behind all this, established in 1999

---
## 👥 Contributing

Please first take a look at the [Dyne.org - Contributor License Agreement](CONTRIBUTING.md) then

1.  🔀 [FORK IT](../../fork)
2.  Create your feature branch `git checkout -b feature/branch`
3.  Commit your changes `git commit -am 'Add some fooBar'`
4.  Push to the branch `git push origin feature/branch`
5.  Create a new Pull Request
6.  🙏 Thank you

---
## 💼 Disclaimer

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.
 
This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public
License along with this program.  If not, see
<https://www.gnu.org/licenses/>.

This software Includes the cryptographic library Milagro released
under the Apache License, Version 2.0
- Copyright (C) 2016 MIRACL UK Ltd
- Copyright (C) 2019 The Apache Software Foundation
