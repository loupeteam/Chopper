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

/* Parses string into template */
signed long ChopCompile(UDINT _pTemplate, UDINT pSource)
{
	if(_pTemplate == 0 || pSource == 0) return CHOP_ERR_INVALID_INPUT;
	
	// TODO: Consider memset pTemplate to 0 here 
	Chop_Template_typ* pTemplate = (Chop_Template_typ*)_pTemplate;
	pTemplate->iSnippet = 0; 
	pTemplate->compiled = 0;
	
	const char ds[3] = "{{"; //Delimiter Start Symbol
	const char de[3] = "}}"; //Delimiter End Symbol
	const UDINT dSize = 2; //Delimiter Size
	
	//const char es[4] = "{{{"; //Escaped Start Symbol (must start with ds)
	//const char ee[4] = "}}}"; //Escaped End Symbol (must start with de)
	//const UDINT eSize = 3; //Escaped Size
	
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
	char *token; 
	UDINT nextStart = (UDINT)&pTemplate->source;
	USINT varLen;
	
	token = strstr((char*)&pTemplate->source,ds); // Get first Token

	// This while loop num of iterations is limited by CHOP_TEMPLATE_MAX_VARIABLES
	// May cause cycle time violations. Possible change to for loop with max iterations
	while (token != NULL) 
	{
		// Check for Cache full
		if(pTemplate->iSnippet >= CHOP_TEMPLATE_MAX_VARIABLES)
			return CHOP_ERR_TEMPLATE_FULL;
			
		/* In string */
		/* Prefix >{{{var}}} Suffix*/
		
		// Use inner most deliminator
		while (token[dSize] == '{') // Assumes Delimiter is curly braces
		{
			// For case of {{{{}}
			token++;
		}
		
		// Record Start/End offsets
		pTemplate->snippet[pTemplate->iSnippet].prefixStart = nextStart;
		pTemplate->snippet[pTemplate->iSnippet].prefixLen = ((UDINT)token - (UDINT)nextStart);

		// Get end braces after var
		token = strstr(token+dSize, de);
		
		/* Prefix {{var>}} Prefix*/
		
		if(token == NULL) return CHOP_ERR_NO_END_OF_VAR;
		
		// In Variable
		varLen = (UDINT)token - (pTemplate->snippet[pTemplate->iSnippet].prefixStart + pTemplate->snippet[pTemplate->iSnippet].prefixLen + dSize); // Current position pointer - End position pointer
				
		// Cache Variable
		memset(&pTemplate->snippet[pTemplate->iSnippet].pv, 0, sizeof(pTemplate->snippet[pTemplate->iSnippet].pv)); // Clear variable 
		if(varLen > 0) {
			memcpy((void*)pTemplate->snippet[pTemplate->iSnippet].pv.name, (void*)(pTemplate->snippet[pTemplate->iSnippet].prefixStart + pTemplate->snippet[pTemplate->iSnippet].prefixLen + dSize), varLen);
		}
		pTemplate->snippet[pTemplate->iSnippet].hasVar = 1;
		
		nextStart = ((UDINT)token) + dSize;
				
		// Increment Cache
		pTemplate->iSnippet++;
		// Get next ds
		token = strstr(token+dSize, ds);
	}
	
	// Check for Cache full
	if(pTemplate->iSnippet >= CHOP_TEMPLATE_MAX_VARIABLES)
		return CHOP_ERR_TEMPLATE_FULL;

	// Copy Trailing string after last var
	// This will contain '\0'
	/* Prefix {{var>}} Suffix */
	// Record Start/End pointers
	pTemplate->snippet[pTemplate->iSnippet].prefixStart = nextStart;
	pTemplate->snippet[pTemplate->iSnippet].prefixLen = (sourceLen + 1 + (UDINT)&pTemplate->source) - nextStart; // Note: This will always be non zero becuase of NULL char
	pTemplate->snippet[pTemplate->iSnippet].hasVar = 0;
	memset(&pTemplate->snippet[pTemplate->iSnippet].pv, 0, sizeof(pTemplate->snippet[pTemplate->iSnippet].pv));

	pTemplate->iSnippet++;
	
	pTemplate->compiled = 1;

	return 0;
}
