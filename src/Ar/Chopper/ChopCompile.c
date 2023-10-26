/*
 * File: ChopCompile.c
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

#ifndef _SG4
#define _SG4
#endif
#include <string.h>
#include "Chopper.h"
#include <ctype.h>
#include "Internal.h"

#ifdef __cplusplus
	};
#endif

// Deliminator Start Char
#define DSChar '{'
// Deliminator End Char
#define DEChar '}'
// Deliminator Number of Characters
#define DNChars 2
// Format Deliminator Char
#define FDChar ','

#define min(X, Y) (((X) < (Y)) ? (X) : (Y))

/* Parses string into template */
signed long ChopCompile(UDINT _pTemplate, UDINT pSource)
{
	if(_pTemplate == 0 || pSource == 0) return CHOP_ERR_INVALID_INPUT;
	
	// TODO: Consider memset pTemplate to 0 here 
	Chop_Template_typ* pTemplate = (Chop_Template_typ*)_pTemplate;
	pTemplate->iSnippet = 0; 
	pTemplate->compiled = 0;
	
	UINT sourceLen;
	
	// Get Source String
	if( ((UDINT)&(pTemplate->source)) != pSource) { //Dont copy if we are already using source in template
		sourceLen = strlen((char*)pSource);
		
		// Check sources will fit into template's source
		if(sourceLen < sizeof(pTemplate->source)) {
			memcpy(pTemplate->source, (void*)pSource, sourceLen);
			pTemplate->source[sourceLen] = '\0';
		}
		else {
			return CHOP_ERR_SOURCE_LENGTH;	
		}
	}
	
	/* Build Template */
	// Init Values 
	char *token = pTemplate->source; 
	char *prefixStart = token;
	char *varStart, *varEnd, *formatStart = 0, *formatEnd = 0, *prefixEnd;
	UDINT varLen, formatLen, prefixLen;
	USINT inVar = 0, inFormat = 0, prefixData = 0; // these will be treated as bools
	
	while(*token) {
		if(*token == DSChar && token[1] == DSChar && !inVar && !inFormat) { // New Variable
			while(*token == DSChar) token++; // Step past '{', note there may be more than dSize
			
			prefixEnd = token - DNChars; // Get end of prefix
			varStart = token;
			
			inVar = 1;
		}
		else if(*token == DEChar && token[1] == DEChar && (inVar || inFormat)) { // End of Variable && Format
			if(inVar) {
				varEnd = token;
			}
			else { //inFormat
				formatEnd = token;
			}
			
			// trim whitespace from variable name, whitespace will cause variable to not be found
			while(isspace(*varStart)){varStart++;}
			while(isspace(*(varEnd-1))){varEnd--;}
			
			// trim whitespace from format, whitespace will cause extra space once rendered
			if(formatStart && formatEnd) {
				while(isspace(*formatStart)){formatStart++;}
				while(isspace(*(formatEnd-1))){formatEnd--;}
			}
			else {
				formatStart = formatEnd = 0;
			}
			
			// Calc lens
			varLen = min(varEnd - varStart, sizeof(pTemplate->snippet[0].pv.name)-1);
			formatLen = min(formatEnd - formatStart, sizeof(pTemplate->snippet[0].flags)-1);
			prefixLen = prefixEnd - prefixStart;
			
			// Check space in template
			if(pTemplate->iSnippet >= CHOP_TEMPLATE_MAX_VARIABLES)
				return CHOP_ERR_TEMPLATE_FULL;
			
			// --- Save variable ---
			pTemplate->snippet[pTemplate->iSnippet].prefixStart = prefixStart;
			pTemplate->snippet[pTemplate->iSnippet].prefixLen = prefixLen;
			memset(&pTemplate->snippet[pTemplate->iSnippet].pv, 0, sizeof(pTemplate->snippet[pTemplate->iSnippet].pv)); // Clear variable 
			memcpy((void*)pTemplate->snippet[pTemplate->iSnippet].pv.name, varStart, varLen);
			pTemplate->snippet[pTemplate->iSnippet].hasVar = 1;
			varGetInfo(&pTemplate->snippet[pTemplate->iSnippet].pv); // So we have the type
			
			if(formatLen > 0) { // Has format defined
				memcpy((void*)pTemplate->snippet[pTemplate->iSnippet].flags, formatStart, formatLen);
				pTemplate->snippet[pTemplate->iSnippet].flags[formatLen] = 0;
			}
			else { // Use defualt format for var type
				ChopGetPrintFlag(pTemplate->snippet[pTemplate->iSnippet].flags, pTemplate->snippet[pTemplate->iSnippet].pv.dataType);
			}
			
			
			// Set status for next variable
			pTemplate->iSnippet++;
			token += (DNChars-1); // Step past all '}' but one, it will be stepped at the end
			prefixStart = token+1;
			inVar = 0;
			inFormat = 0;
			prefixData = 0;
			formatStart = formatEnd = 0;
			
		}
		else if(*token == FDChar && inVar && !inFormat) { // Start of Format
			varEnd = token;
			formatStart = token+1;
			
			inVar = 0;
			inFormat = 1;
		}
		else if(!prefixData && !inVar && !inFormat) { // Prefix data avialable
			prefixData = 1; // Not currently used as we always assume there is prefix data as that is how we get null char at end
		}
		
		token++;
	}
	
	if(inVar || inFormat) {
		return CHOP_ERR_NO_END_OF_VAR;
	}
	
	//if(prefixData) {
	// Check for Cache full
	if(pTemplate->iSnippet >= CHOP_TEMPLATE_MAX_VARIABLES)
		return CHOP_ERR_TEMPLATE_FULL;

	// Copy Trailing string after last var
	// This will contain '\0'
	pTemplate->snippet[pTemplate->iSnippet].prefixStart = prefixStart;
	pTemplate->snippet[pTemplate->iSnippet].prefixLen = token - prefixStart + 1; // Note: This needs to be non zero because we want to include the NULL char
	pTemplate->snippet[pTemplate->iSnippet].hasVar = 0;
	memset(&pTemplate->snippet[pTemplate->iSnippet].pv, 0, sizeof(pTemplate->snippet[pTemplate->iSnippet].pv));
	pTemplate->snippet[pTemplate->iSnippet].flags[0] = '\0';
	pTemplate->iSnippet++;
	
	//}
	
	pTemplate->compiled = 1;

	return 0;
}
