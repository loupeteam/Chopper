
PROGRAM _INIT
	
	chopperInst.pDest := ADR(chopperOutput);
	chopperInst.maxDestLength := SIZEOF(chopperOutput);
	chopperInst.pSource := ADR(chopperSource);
	chopperInst.pTemplate := ADR(chopperTemplate);
	
	chopperSource := '{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}{{Chop5:currentTime}}';
	//	chopperSource := '{{Chop5:currentTimeDint}}{{Chop5:currentTimeDint}}{{Chop5:currentTimeDint}}{{Chop5:currentTimeDint}}{{Chop5:currentTimeDint}}{{Chop5:currentTimeDint}}{{Chop5:currentTimeDint}}{{Chop5:currentTimeDint}}{{Chop5:currentTimeDint}}{{Chop5:currentTimeDint}}{{Chop5:currentTimeDint}}{{Chop5:currentTimeDint}}{{Chop5:currentTimeDint}}';

	// compile
	//chopperInst();
	
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
		currentTimeDint := AsIOTimeStamp();
	END_WHILE
	
END_PROGRAM

PROGRAM _EXIT
	(* Insert code here *)
	 
END_PROGRAM

