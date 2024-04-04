
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	templateDynamic.snippet = &snippetDynamic[0];
	templateDynamic.maxSnippets = sizeof(snippetDynamic)/sizeof(snippetDynamic[0]);
	templateDynamic.source = &sourceDynamic;
	templateDynamic.maxSrcLen = sizeof(sourceDynamic);
	
}

void _CYCLIC ProgramCyclic(void)
{
	if(cmd.legacyCompile) {
		cmd.legacyCompile = 0;
		compileStatusLegacy = ChopCompile(&templateLegacy, sourceLegacy);	
	}
	if(cmd.legacyRender) {
		cmd.legacyRender = 0;
		renderStatusLegacy = ChopRender(destLegacy, &templateLegacy, sizeof(destLegacy), &renderLenLegacy);
	}
	
	if(cmd.staticCompile) {
		cmd.staticCompile = 0;
		compileStatusStatic = ChopCompile(&templateStatic, sourceStatic);	
	}
	if(cmd.staticRender) {
		cmd.staticRender = 0;
		renderStatusStatic = ChopRender(destStatic, &templateStatic, sizeof(destStatic), &renderLenLegacy);
	}
	
	if(cmd.dynamicCompile) {
		cmd.dynamicCompile = 0;
		compileStatusDynamic = ChopCompileGeneric(&templateDynamic, sourceDynamic);	
	}
	if(cmd.dynamicRender) {
		cmd.dynamicRender = 0;
		renderStatusDynamic = ChopRender(destDynamic, &templateDynamic, sizeof(destDynamic), &renderLenDynamic);
	}

}

void _EXIT ProgramExit(void)
{

}

