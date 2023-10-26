
TYPE
	Chop_Status_Enum : 
		(
		CHOP_ERR_INVALID_INPUT := 50000,
		CHOP_ERR_SOURCE_LENGTH,
		CHOP_ERR_TEMPLATE_FULL,
		CHOP_ERR_NO_END_OF_VAR, (*Check source vars are surrounded by '{{}}'*)
		CHOP_ERR_NOT_COMPILED,
		CHOP_ERR_DEST_LENGTH, (*50005*)
		CHOP_ERR_INTERNAL
		);
	Chop_Template_typ : 	STRUCT 
		snippet : ARRAY[0..CHOP_TEMPLATE_MAI_VARIABLES]OF Chop_Template_Variable_typ;
		iSnippet : UINT;
		source : STRING[CHOP_TEMPLATE_STRLEN_SOURCE];
		compiled : BOOL;
	END_STRUCT;
	Chop_Template_Variable_typ : 	STRUCT 
		pv : varVariable_typ;
		prefixStart : UDINT;
		prefixLen : UDINT;
		flags : STRING[CHOP_NUM_FLAG_LEN];
		hasVar : BOOL;
	END_STRUCT;
END_TYPE
