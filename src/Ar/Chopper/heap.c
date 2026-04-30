/*
 * File: heap_redirect.c
 * Copyright (c) 2023 Loupe
 * https://loupe.team
 *
 * This file is part of Chopper, licensed under the MIT License.
 *
 * Note (AS6 migration): The malloc redirect to tlsf has been removed because
 * AS6's libburc++.a now provides _malloc_r/_free_r/_realloc_r/_calloc_r and
 * defining them here causes "multiple definition" link errors. The library
 * now uses the standard heap. The bur_heap_size weak symbol is preserved so
 * the AR memory heap initialization can resolve it.
 */

#include <stddef.h>

size_t bur_heap_size = 0xffff; /* variable 'bur_heap_size' as dummy */
