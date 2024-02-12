
PROGRAM _INIT
	
	// Chop1 exists to interrupt the chop calls happening in Chop5
	// Use the watch window to set "interrupt" to TRUE to test this case
	// This tests thread-safety of ChopRender
	
	chopperInst.pDest := ADR(chopperOutput);
	chopperInst.maxDestLength := SIZEOF(chopperOutput);
	chopperInst.pSource := ADR(chopperSource);
	chopperInst.pTemplate := ADR(chopperTemplate);
	
	chopperSource := '{{Chop1:value}}';

	iMax := 0;
	value := 123456789123456789.876543210;
	interrupt := FALSE;	// avoid instant faults during testing
	 
END_PROGRAM

PROGRAM _CYCLIC

	FOR i:=0 TO iMax DO
			
		IF interrupt THEN
			chopperInst();
		END_IF

	END_FOR
	
END_PROGRAM

PROGRAM _EXIT
	
	
	 
END_PROGRAM

