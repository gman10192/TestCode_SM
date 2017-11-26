
//STATE Functions

//**********INITALIZE
void state_Initialize(void) {
	genie.WriteObject(GENIE_OBJ_STRINGS, 2, 23);  //resert required
	if (AbortPB > 0) {	//Monitor for Abort button press.
		AbortPB = 0;
		CurrentState = ABORT;
		PrevState = INITIALIZE;
		return;
	}
	else if (ResetPB > 0) {
		ResetPB = 0;
		CurrentState = RESET;
		PrevState = INITIALIZE;
		return;
	}
	return;
}

//**********RESET
void state_Reset(void) {

	if (AbortPB > 0) {
		AbortPB = 0;
		CurrentState = ABORT;
		PrevState = RESET;
		return;
	}
	if (PrevState == INITIALIZE) {
		CurrentState = CAPTURE_FLOW_PRESS;
		PrevState = RESET;
	}
	return;
}

//**********CAPTURE FLOW AND PRESSURE
void state_CaptureFlowPress(void) {
	//flowPulse(inputpint, pulsestocapture)
	//Insert code here to capture the pressure and flow variables,
	//for now code just picks a number, wait a while, then changes it to be ok.
	FlowOut++;
	//PressIn = getAnalogData(pin_PoutSS);
	if (PrevState == RESET) {
		if (FlowOut >= 500) {
			CurrentState = IDLE;
			PrevState = CAPTURE_FLOW_PRESS;
		}
		else if (PressIn <= 10) {
			CurrentState = IDLE;
			PrevState = CAPTURE_FLOW_PRESS;
		}
	}
	return;
}

//**********IDLE
void state_Idle(void) {
	genie.WriteObject(GENIE_OBJ_STRINGS, 2, 24);  //system idle
	if (AbortPB > 0) {
		AbortPB = 0;
		CurrentState = ABORT;
		PrevState = IDLE;
		return;
	}
	else if (StartPB > 0) {
		StartPB = 0;
		CurrentState = STARTUP;
		PrevState = IDLE;
		return;
	}
	return;
}

//**********LOAD SETTINGS
void state_LoadSettings(void) {
	//Read settings from EEPROM and save to structure variables.
	//Not currently used, values hard coded.
	
	if (AbortPB > 0) {
		AbortPB = 0;
		CurrentState = ABORT;
		PrevState = LOAD_SETTINGS;
		return;
	}

	CurrentState = STARTUP;
	PrevState = LOAD_SETTINGS;
	return;
}

//**********STARTUP
void state_Startup(void) {
	if (AbortPB > 0) {
		AbortPB = 0;
		CurrentState = ABORT;
		PrevState = STARTUP;
		return;
	}
	genie.WriteObject(GENIE_OBJ_STRINGS, 2, 1);  //Enter desired exchange volume then press Resume.
	if (TempVolumeSP > 0) {
		if (ProceedPB > 0) {
			ProceedPB = 0;
			VolumeSP = TempVolumeSP;
			PrevState = STARTUP;
			CurrentState = CONNECT_VEH;
		}
	}
	return;
}

//**********CONNECT VEHICLE
void state_ConnectVeh(void) {
	if (AbortPB > 0) {
		AbortPB = 0;
		CurrentState = ABORT;
		PrevState = CONNECT_VEH;
		return;
	}
	genie.WriteObject(GENIE_OBJ_STRINGS, 2, 3);  //Connect and start vehicle, the press Resume.
	if (ProceedPB > 0) {
		ProceedPB = 0;
		PrevState = CONNECT_VEH;
		CurrentState = CAPTURE_FLOW_PRESS2;
	}
	return;
}

//**********CAPTURE FLOW AND PRESSURE 2
void state_CaptureFlowPress2(void) {

	genie.WriteObject(GENIE_OBJ_STRINGS, 2, 4);  //waiting for flow and pressure to stablize
	FlowIn++;
	if (PrevState == CONNECT_VEH) {
		if (FlowIn >= 500) {
			CurrentState = RUN;
			PrevState = CAPTURE_FLOW_PRESS2;
		}
		
	}
	return;
}

//**********RUN
void state_Run(void) {
	// 1)capture flow data (timer based, and done within this function not buy the capture ones)
	// 2)update PID
	// 3)update tank pressure
	// 4) determine volume
	if (PrevState == CAPTURE_FLOW_PRESS2) {
		CurrentState = DONE;
		PrevState = RUN;
	}
	return;
}

//**********DONE
void state_Done(void) {
	//Activate bypass CV
	
	genie.WriteObject(GENIE_OBJ_STRINGS, 2, 9); //Stop and disconnect vehicle, then press reset.
	if (ResetPB > 0) {
		ResetPB = 0;
		CurrentState = RESET;
		PrevState = DONE;
	}
	return;
}




//**********FAULT
void state_Fault(void) {

	return;
}

//**********ABORT
void state_Abort(void) {
	CurrentState = ABORT;
	if (ResetPB > 0) {
		
		ResetPB = 0;

	}
	return;
}

