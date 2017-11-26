void DisplayUpdate() {
	//This is the code that actually performs updates to the display objects
	


	
	genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x01, FlowIn);  //Flow In
	genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x00, FlowOut);  //Flow Out
	genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x03, PressIn);  //Pressure In
	genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x02, PressOut);  //Pressure Out
	genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x05, 0);  //Tank Pressure SP

	genie.WriteObject(GENIE_OBJ_STRINGS, 0x00, CurrentState);
	
	//genie.WriteObject(GENIE_OBJ_STRINGS, 0x02, StatusMessage);



}
