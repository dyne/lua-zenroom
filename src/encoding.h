/*
 * This file is part of Zenroom (https://zenroom.org)
 * 
 * Copyright (C) 2019-2021 Dyne.org foundation
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

#ifndef __ENCODING_H__
#define __ENCODING_H__

#include <stddef.h>

int hex2buf(char *dst, const char *hex);
void buf2hex(char *dst, const char *buf, const size_t len);

int is_url64(const char *in);

int B64decoded_len(int len);
int U64decode(char *dest, const char *src);

int B64encoded_len(int len);
void U64encode(char *dest, const char *src, int len);


#endif
