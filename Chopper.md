![Automation Resources Group](http://automationresourcesgroup.com/dist/img/logos/_headerLogo/ARG-Logo-Black-RGB.png)

# Chopper Library

Chopper allows for building of strings with variable values. With choppers use of templates strings can be rendered efficiently. 

# Usage

To use Chopper, a template of type **Chop\_Template\_typ** will need to be declared. Optionally a function block of type **Chopper** can be used instead of functions.   

## Chopper FUB

### Initialization

Declare a variable *template* of type **Chop\_Template\_typ** and a variable *Chop* of type **Chopper**. Before using *Chop*, set *pSource*, *pTemplate*, *pDest*, and *destSize*. *template* is not required to be compiled before using *Chop*.  

	variable.text:= 'Chopper FUB';
	source:= 'This is a {{var.text}} example!';
	
	Chop.pSource:= 		ADR(source);
	Chop.pTemplate:= 	ADR(template);
	Chop.pDest:= 		ADR(destination);
	Chop.destSize:= 	SIZEOF(destination);

### Operation

Each time *Chop* is called it will compile *pTemplate* if not already compiled or *recompile* is true, and render to *pDest*. *Chop* will render in a single call and can be called multiple times per a cycle. A single fub can be used to compile/render multiple templates. 

	Chop();
	// destination = 'This is a Chopper Fub example!'

### Inputs

* **pTemplate** - pointer to **Chop\_Template\_typ**. Where compiled data is stored.
* **pDest** - pointer to destination where rendered string is written to. 
* **destSize** - size of destination.
* **pSource** - pointer to Source to be compiled. Only required when a compile is needed. 
* **recompile** - force a compile.

### Outputs 

* **renderLength** - length of last render.
* **Status** - status of last fub call. Refer to Status below. 


## ChopCompile(pTemplate, pSource)

**ChopCompile** does a compile from *pSource* into *pTemplate*. Returns function status as DINT. Refer to status for more information. Variables in source should be surrounded by double curly braces "{{", "}}", and should be specified in format TaskName:VarName for local variables and VarName for global variables. Only variables declared in .var files can be used by name.

Chopper Compiles can take an some time for larger sources. It is recommended to use caution when compiling in a fast cyclic. 

	variable.text:= 'Chopper';
	source:= 'This is a {{var.text}} example!';
	ChopCompile(ADR(template), ADR(source));

## ChopRender(pDest, pTemplate, DestSize, pRenderLength)

**ChopRender** does render from *pTemplate* into *pDest*. If renderLength is larger than *destSize* then a the *pDest* will end with '...', followed by a null character. If *pRenderLength* is not 0 then it will be filled with renderLength. 

Chopper Renders are quick when using a precompiled template and are okay to use in fast cyclics. 

	variable.text:= 'Chopper';
	source:= 'This is a {{var.text}} example!';
	ChopCompile(ADR(template), ADR(source));
	ChopRender(ADR(destination), ADR(template), SIZEOF(destination), ADR(length));
	// destination = 'This is a Chopper example!'
	// length = 26

**NOTE:** Any variable that can not be found is replaced with "undefined" when rendered.

## ChopReplaceVar(pTemplate, pTag, pVarName)

**ChopRepalceVar** replaces all *pTag* in *pTemplate* with variable specified by name in *pVarName*. Variable name is in format TaskName:VarName for local variables and VarName for global variables.

	firstVar:= 1;
	secondVar:= 2;

	ChopCompile(ADR(template), ADR('My variable value is {{firstVar}}'));
	ChopRender(ADR(dest), ADR(template), SIZEOF(template), ADR(renderLength)); 
	//dest= 'My variable value is 1'

	ChopReplaceVar(ADR(template),ADR('firstVar'),ADR('secondVar'));
	ChopRender(ADR(dest), ADR(template), SIZEOF(template), ADR(renderLength));
	//dest= 'My variable value is 2'

## ChopReplace(pTemplate, pTag, address, type)

**ChopRepalce** replaces all *pTag* in *pTemplate* with a new variable. Specified by address and type. Types are specified as *VAR\_TYPE\_enum*, refer to *VarTools* documentation for more information.

	firstVar:= 1;
	secondVar:= 2;

	ChopCompile(ADR(template), ADR('My variable value is {{firstVar}}'));
	ChopRender(ADR(dest), ADR(template), SIZEOF(template), ADR(renderLength)); 
	//dest= 'My variable value is 1'

	ChopReplace(ADR(template),ADR('firstVar'),ADR(secondVar),VAR_TYPE_USINT);
	ChopRender(ADR(dest), ADR(template), SIZEOF(template), ADR(renderLength));
	//dest= 'My variable value is 2'

## ChopGetErrorMsg(pDest, errorID)

**ChopGetErrorMsg** retrieves text for given *errorID* and copies it to *pDest*. *pDest* is required to be a string of length at least 29. Less could result in memory overflow. **ChopGetErrorMsg** returns a status. 

	ChopGetErrorMsg(ADR(msg), 50000);
	// msg = Input to function is invalid  

# Status

0 - OK

50000 - CHOP\_ERR\_INVALID\_INPUT - Input to function is invalid. 

50001 - CHOP\_ERR\_SOURCE\_LENGTH - Provided source is too long. Check source for missing null char. If source is greater than **CHOP\_TEMPLATE\_STRLEN\_SOURCE** contact ARG.

50002 - CHOP\_ERR\_TEMPLATE\_FULL - Template full of items. Contact ARG.

50003 - CHOP\_ERR\_NO\_END\_OF\_VAR - No end of variable detected during compile. Check source!

50004 - CHOP\_ERR\_NOT\_COMPILED - Attempted to render but template is not compiled. First compile template.

50005 - CHOP\_ERR\_DEST\_LENGTH - Destination buffer too small. 

50006 - CHOP\_ERR\_INTERNAL - Internal Error.




