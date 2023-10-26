
FUNCTION ChopCompile : DINT
	VAR_INPUT
		pTemplate : UDINT; (*Address of Template*)
		pSource : UDINT; (*Address of Source*)
	END_VAR
END_FUNCTION

FUNCTION ChopRender : DINT
	VAR_INPUT
		pDest : UDINT;
		pTemplate : UDINT;
		maxDestLength : UDINT;
		pRenderLength : UDINT;
	END_VAR
END_FUNCTION

FUNCTION_BLOCK Chopper
	VAR_INPUT
		pDest : UDINT;
		pTemplate : UDINT;
		pSource : UDINT;
		maxDestLength : UDINT;
		recompile : BOOL;
	END_VAR
	VAR_OUTPUT
		renderLength : UDINT;
		status : DINT;
	END_VAR
	VAR
		compileStatus : DINT;
	END_VAR
END_FUNCTION_BLOCK

FUNCTION ChopReplace : DINT
	VAR_INPUT
		pTemplate : UDINT;
		pTag : UDINT;
		address : UDINT;
		type : UDINT;
	END_VAR
END_FUNCTION

FUNCTION ChopReplaceVar : DINT
	VAR_INPUT
		pTemplate : UDINT;
		pTag : UDINT;
		pVarName : UDINT;
	END_VAR
END_FUNCTION

FUNCTION ChopGetErrorMsg : DINT
	VAR_INPUT
		pDest : UDINT;
		maxDestLength : UDINT;
		errorID : DINT;
	END_VAR
END_FUNCTION
