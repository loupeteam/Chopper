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
//		case VAR_TYPE_STRING:
//			strcpy(dest, "%s");
//			break;
		default:
			strcpy(dest, "");
			break;
	}
}

