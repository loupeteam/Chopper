/*
 * File: Chop.c
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

#include "Chopper.h"

#ifdef __cplusplus
	};
#endif

/* Builds and Renders Template */
void Chopper(struct Chopper* t)
{
	if(t == 0)
		return;
	
	if((t->pTemplate == 0)
	|| (t->pDest == 0) 
	|| (t->maxDestLength == 0)) {
		t->status = CHOP_ERR_INVALID_INPUT;
		return;
	}
	
	// Compile to Template
	if( ((((Chop_Template_typ*)t->pTemplate)->compiled == 0) && (t->compileStatus == 0))
	|| t->recompile) {
		
		// Compile
		t->compileStatus = ChopCompile(t->pTemplate, t->pSource);
		
		// Enable double precision if specified
		if(t->pTemplate && t->doublePrecision) ((Chop_Template_typ*)t->pTemplate)->doublePrecision = 1;
		
		// Reset ReCompile CMD
		t->recompile = 0;
		
		// Return if error
		if(t->compileStatus != 0) {
			t->status = t->compileStatus;
			return;
		}
		
	}
	
	//Read Var
	t->status = ChopRender(t->pDest, t->pTemplate, t->maxDestLength, (UDINT)&t->renderLength);
}
