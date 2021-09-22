# Lua cryptolang

This is the port of cryptolang language ported out of [Zenroom](https://zenroom.org)'s VM to run on Lua 5.1 and all derivates (including Tarantool)

Lua cryptolang is a portable cryptographic module to execute secure cryptographic computations within [distributed computing](https://en.wikipedia.org/wiki/Distributed_computing) environments.

This Lua module works only on 64-bit systems. For 32-bit support please use the Zenroom VM.

[![software by Dyne.org](https://files.dyne.org/software_by_dyne.png)](http://www.dyne.org)

# Usage

Build:

```
luarocks build cryptolang-scm-1.rockspec
```

Test:
```
make check
```

Launch:
```
lua -l cryptolang
```

Use:
```
pk = cryptolang.keygen()
```

## WORK IN PROGRESS

# Credits

Lua cryptolang is Copyright (C) 2020-2021 by the Dyne.org foundation

Designed, written and maintained by Denis "Jaromil" Roio.

More contact information is on [Zenroom.org](https://zenroom.org)

This software Includes the cryptographic library Milagro released
under the Apache License, Version 2.0
- Copyright (C) 2016 MIRACL UK Ltd
- Copyright (C) 2019 The Apache Software Foundation

## Licensing

Copyright (C) 2020-2021 Dyne.org foundation

Designed and written by Denis Roio with the help of Puria Nafisi Azizi and Andrea D'Intino.

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

## Support

Enterprise level support contracts are available upon request, as
well customisations and license exceptions: you are welcome to get
in touch with us at https://zenroom.org
