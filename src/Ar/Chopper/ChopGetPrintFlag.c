/*
 * File: ChopGetPrintFlag.c
 * Copyright (c) 2023 Loupe
 * https://loupe.team
 * 
 * This file is part of Chopper, licensed under the MIT License.
 * 
 */

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include <string.h>
#include "Chopper.h"

#ifdef __cplusplus
	};
#endif


/* Gets the defualt printf flag for type and copies it into pDest */
void ChopGetPrintFlag(char* dest, UDINT type) {
	// Note we dont generate a flag for each type
	// Only types that NEED a flag to render. Types that do not need a flag or dont support a flag will instead have an empty string
	switch (type)
	{
		case VAR_TYPE_LREAL:
		case VAR_TYPE_REAL:
			strcpy(dest, "%f");
			break;
		case VAR_TYPE_SINT:
		case VAR_TYPE_INT:
		case VAR_TYPE_DINT:
			strcpy(dest, "%d");
			break;
		case VAR_TYPE_USINT:
		case VAR_TYPE_UINT:
		case VAR_TYPE_UDINT:
			strcpy(dest, "%u");
			break;
		default:
			strcpy(dest, "");
			break;
	}
}
