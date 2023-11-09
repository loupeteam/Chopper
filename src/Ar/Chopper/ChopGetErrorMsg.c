/*
 * File: ChopGetErrorMsg.c
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


/* Gets error text for ErrorId and copies it into pDest */
signed long ChopGetErrorMsg(UDINT pDest, UDINT maxDestLength, DINT errorID)
{
	if(pDest == 0) return CHOP_ERR_INVALID_INPUT;
	
	// Get copy length
	// Copy a max of 30 chars because all messages are shorter than that
	USINT cpyLen = maxDestLength < 30 ? maxDestLength : 30;
	
	switch (errorID)
	{
		case 0: strncpy((char*)pDest, (char*)"Ok", cpyLen); break;
		case CHOP_ERR_INVALID_INPUT: strncpy((char*)pDest, (char*)"Input to function is invalid", cpyLen); break;
		case CHOP_ERR_SOURCE_LENGTH: strncpy((char*)pDest, (char*)"Source string is too long", cpyLen); break;
		case CHOP_ERR_TEMPLATE_FULL: strncpy((char*)pDest, (char*)"Template variables full", cpyLen); break;
		case CHOP_ERR_NO_END_OF_VAR: strncpy((char*)pDest, (char*)"No end of variable detected", cpyLen); break;
		case CHOP_ERR_NOT_COMPILED: strncpy((char*)pDest, (char*)"Template not compiled", cpyLen); break;
		case CHOP_ERR_DEST_LENGTH: strncpy((char*)pDest, (char*)"Destination buffer too small", cpyLen); break;
		case CHOP_ERR_INTERNAL: strncpy((char*)pDest, (char*)"Internal Error", cpyLen); break;
		default: strncpy((char*)pDest,(char*)"Unknown error", cpyLen); break;
	}
	
	((char*)pDest)[cpyLen-1] = '\0';
	
	return 0;
     
}
