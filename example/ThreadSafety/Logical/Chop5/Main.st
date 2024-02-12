
PROGRAM _INIT
	
	// Chop5 continuously chops (ChopRender) so it can be interrupted by Chop1
	
	chopperInst.pDest := ADR(chopperOutput);
	chopperInst.maxDestLength := SIZEOF(chopperOutput);
	chopperInst.pSource := ADR(chopperSource);
	chopperInst.pTemplate := ADR(chopperTemplate);
	
	chopperSource := '{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}';
	
END_PROGRAM

PROGRAM _CYCLIC

	startTime := AsIOTimeStamp();
	diffTime := 0;
	
	WHILE (diffTime < 180000) DO
		IF NOT stop THEN
			chopperInst();
		END_IF
		diffTime := AsIOTimeStamp() - startTime;
		currentTime := AsIOTimeStamp() + 1358673E100;
	END_WHILE
	
END_PROGRAM

PROGRAM _EXIT
	(* Insert code here *)
	 
END_PROGRAM

