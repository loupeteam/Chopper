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

/* ProtoTypes */
signed long appendTo(UDINT pdest, UDINT dsize, UDINT* offset, UDINT psource, UDINT ssize);

/* Renders template into pDest */
signed long ChopRender(UDINT pDest, UDINT _pTemplate, UDINT maxDestLength, UDINT pRenderLength)
{
	if((_pTemplate == 0) || (pDest == 0) || (maxDestLength == 0)) return CHOP_ERR_INVALID_INPUT;
	
	Chop_Template_typ* pTemplate = (Chop_Template_typ*) _pTemplate;
	UDINT offset = 0, i;
	DINT status = 0;
	
	if(pTemplate->compiled == 0) return CHOP_ERR_NOT_COMPILED;
	
	//Read Var
	for(i = 0; i < pTemplate->iSnippet; i++){		
		// Append prefix
		status = appendTo(pDest, maxDestLength, &offset, pTemplate->snippet[i].prefixStart, pTemplate->snippet[i].prefixLen);
	
		// If variable is invalid skip getting value
		if(pTemplate->snippet[i].hasVar == 0)
			continue;
		
		//Get snippet value
		if(pTemplate->snippet[i].pv.dataType != VAR_TYPE_UNDEFINED)
			varGetValue((UDINT)&(pTemplate->snippet[i].pv));
		
		switch (pTemplate->snippet[i].pv.dataType)
		{
			case VAR_TYPE_STRING:
				// String could be longer than sizeof pv.value 
				status = appendTo(pDest, maxDestLength, &offset, pTemplate->snippet[i].pv.address, strlen((char*)pTemplate->snippet[i].pv.address));
				break;
			
			case VAR_TYPE_WSTRING:
				{ // Add curly braces to add scope so we can declare a variable 
					char tempString[pTemplate->snippet[i].pv.length / 2]; // TODO: Remove the need for a temp variable
					wstring2string(tempString, pTemplate->snippet[i].pv.address, sizeof(tempString));
					// WString can be longer than pv.value and pv.value is a string
					status = appendTo(pDest, maxDestLength, &offset, tempString, strlen(tempString));
				}
				break;
			
			case VAR_TYPE_UNDEFINED:
				status = appendTo(pDest, maxDestLength, &offset, (UDINT)&("\"undefined\""), sizeof("\"undefined\"") - 1); 
				break;
			
			default:
				status = appendTo(pDest, maxDestLength, &offset, (UDINT)&pTemplate->snippet[i].pv.value, strlen(pTemplate->snippet[i].pv.value));
				break;
			
		}
		
		if(status != 0)
			break;
	}
	
	//Fill Render Length
	if(pRenderLength != 0)
		*((UDINT*)pRenderLength) = offset - 1; //Offset includes \0
	
	return status;
}

/** appendTo
* Concats 2 strings while keeping track of offset (length)
*/
signed long appendTo(UDINT pdest, UDINT dsize, UDINT* poffset, UDINT psource, UDINT ssize) {
	if((pdest == 0)
		|| (poffset == 0)
		|| (psource == 0))
		return CHOP_ERR_INTERNAL;
	
	if(ssize == 0) return 0;
	
	// If space left in buffer after Append is >= 0
	// (Space left) - space to copy
	if((DINT) ((DINT)(dsize - *poffset) - ssize) >= 0) {
		//Append
		memcpy((void*)(pdest+*poffset), (void*)(psource), ssize);
		*poffset += ssize;
		
		return 0;
		
	} else {
		//Append until dest is full
		DINT copySize = ((DINT)(dsize - *poffset)-4);
		if(copySize >= 0) {
			memcpy((void*)(pdest+*poffset), (void*)(psource), copySize);
		} 
		
		//Append "...\0" to end of dest
		if(dsize >= 4) {
			memcpy((void*)(pdest+dsize-4), &"...", 4); //"...\0" = 4
			*poffset = dsize;
		} else {
			if(dsize != 0) {
				((char*)pdest)[0] = '\0'; 
			}
			// poffset needs to include null char 
			*poffset = 1;
		}
	}
	
	return CHOP_ERR_DEST_LENGTH;
}
