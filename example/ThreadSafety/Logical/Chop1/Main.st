
PROGRAM _INIT
	
	chopperInst.pDest := ADR(chopperOutput);
	chopperInst.maxDestLength := SIZEOF(chopperOutput);
	chopperInst.pSource := ADR(chopperSource);
	chopperInst.pTemplate := ADR(chopperTemplate);
	
	chopperSource := '{{Chop1:value}}';
	//chopperSource := '{"field":"{{Chop1:valueDint}}"}';

	
	iMax := 1;
	value := 123456789123456789.876543210;
	valueDint := 123456;
	
	// compile
	//chopperInst();
	 
END_PROGRAM

PROGRAM _CYCLIC

	FOR i:=0 TO iMax DO
		IF (i MOD 2) = 0 THEN
			value := value + 1;
			valueDint := valueDint + 1;
		ELSE
			value := value - 1;
			valueDint := valueDint - 1;
		END_IF
			
		IF interrupt THEN
			chopperInst();
		END_IF

	END_FOR
	
END_PROGRAM

PROGRAM _EXIT
	(* Insert code here *)
	 
END_PROGRAM

