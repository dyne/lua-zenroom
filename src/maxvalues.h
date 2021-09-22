/*
 * This file is part of Zenroom (https://zenroom.org)
 * 
 * Copyright (C) 2021 Dyne.org foundation
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

#ifndef __MAXVALUES_H__
#define __MAXVALUES_H__

#define MAX_LINE 1024 // 1KiB maximum length for a newline terminated line (Zencode)

#ifndef MAX_ZENCODE_LINE
#define MAX_ZENCODE_LINE 512
#endif

#ifndef MAX_CONFIG // for the configuration parser
#define MAX_CONFIG 512
#endif

#ifndef MAX_ZENCODE // maximum size of a zencode script
#define MAX_ZENCODE 16384
#endif

#ifndef MAX_FILE // for cli.c
#define MAX_FILE 2048000 // load max 2MiB files
#endif

#ifndef MAX_STRING // mostly for cli.c
#define MAX_STRING 20480 // max 20KiB strings
#endif

#ifndef MAX_OCTET
#define MAX_OCTET 4096000 // max 4MiB for octets
#endif

#define LUA_BASELIBNAME "_G"

#define ZEN_BITS 32
#ifndef SIZE_MAX
#if ZEN_BITS == 32
#define SIZE_MAX 4294967296
#elif ZEN_BITS == 8
#define SIZE_MAX 65536
#endif
#endif

#endif
