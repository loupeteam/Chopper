/*
 * File: ChopReplace.c
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
#include "Internal.h"

#ifdef __cplusplus
	};
#endif

/* Replaces var in template */
signed long ChopReplace(UDINT _pTemplate, UDINT pTag, UDINT Address, UDINT Type)
{
	if((pTag == 0) 
	|| (Address == 0)
	|| (_pTemplate) == 0) {
		return CHOP_ERR_INVALID_INPUT;
	}
	
	Chop_Template_typ* pTemplate = (Chop_Template_typ*)_pTemplate;
	int i;
	
	for(i = 0; i < pTemplate->iSnippet; i++) {
		if(strcmp(pTemplate->snippet[i].pv.name, (char*)pTag) == 0) {
			pTemplate->snippet[i].pv.address = Address;
			pTemplate->snippet[i].pv.dataType  = Type;
			ChopGetPrintFlag(pTemplate->snippet[i].flags, pTemplate->snippet[i].pv.dataType);
		}
	}
	
	return 0;
}
