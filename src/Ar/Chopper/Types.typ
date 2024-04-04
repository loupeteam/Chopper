(*
 * File: Types.typ
 * Copyright (c) 2023 Loupe
 * https://loupe.team
 * 
 * This file is part of Chopper, licensed under the MIT License.
 * 
 *)

TYPE
	Chop_Status_Enum : 
		(
		CHOP_ERR_INVALID_INPUT := 50000,
		CHOP_ERR_INVALID_TEMPLATE_VALUES,
		CHOP_ERR_SOURCE_LENGTH,
		CHOP_ERR_TEMPLATE_FULL,
		CHOP_ERR_NO_END_OF_VAR, (*Check source vars are surrounded by '{{}}'*)
		CHOP_ERR_NOT_COMPILED, (*50005*)
		CHOP_ERR_DEST_LENGTH,
		CHOP_ERR_INTERNAL,
		CHOP_ERR_INVALID_FORMATTER := 51000 (*51XXX Invalid variable format XXX represents the index of the variable *)
		);
	Chop_Template_typ :Chop_Template_Static_typ;
	Chop_Template_Static_typ : 	STRUCT 
		generic : Chop_Template_Generic_typ;
		snippet : ARRAY[0..CHOP_TEMPLATE_MAI_VARIABLES]OF Chop_Template_Variable_typ;
		source : STRING[CHOP_TEMPLATE_STRLEN_SOURCE];
	END_STRUCT;
	Chop_Template_Generic_typ : 	STRUCT 
		maxSnippets : UDINT;
		snippet : REFERENCE TO Chop_Template_Variable_typ;
		maxSrcLen : UDINT;
		source : REFERENCE TO STRING[CHOP_TEMPLATE_STRLEN_SOURCE];
		iSnippet : UDINT;
		sourceLen : UDINT;
		compiled : BOOL;
		doublePrecision : BOOL;
		usePrintf : BOOL;
	END_STRUCT;
	Chop_Template_Variable_typ : 	STRUCT 
		pv : varVariable_typ;
		prefixStart : UDINT;
		prefixLen : UDINT;
		flags : STRING[CHOP_NUM_FLAG_LEN];
		hasVar : BOOL;
	END_STRUCT;
END_TYPE
