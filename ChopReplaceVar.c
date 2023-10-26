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
signed long ChopReplaceVar(UDINT _pTemplate, UDINT pTag, UDINT pVarName)
{
	if((pTag == 0) 
	|| (pVarName == 0)
	|| (_pTemplate) == 0) {
		return CHOP_ERR_INVALID_INPUT;
	}
	
	Chop_Template_typ* pTemplate = (Chop_Template_typ*)_pTemplate;
	int i;
	
	
	for(i = 0; i < pTemplate->iSnippet; i++) {
		if(strcmp(pTemplate->snippet[i].pv.name, (char*)pTag) == 0) {
			// Clear pv and fill the name
			memset((void*)&pTemplate->snippet[i].pv, 0, sizeof(pTemplate->snippet[0].pv));
			strcpy(pTemplate->snippet[i].pv.name, (char*)pVarName);	
			
			// Get variable address and type
			varGetInfo((UDINT)&pTemplate->snippet[i].pv);
			
			ChopGetDefaultFormatter(pTemplate->snippet[i].flags, pTemplate->snippet[i].pv.dataType);
		}
	}
	
	return 0;
}
