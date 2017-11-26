/////////////////////////////////////////////////////////////////////
//
// This is the user's event handler. It is called by genieDoEvents()
// when the following conditions are true
//
//		The link is in an IDLE state, and
//		There is an event to handle
//
// The event can be either a REPORT_EVENT frame sent asynchronously
// from the display or a REPORT_OBJ frame sent by the display in
// response to a READ_OBJ (genie.ReadObject) request.
//


//COMPACT VERSION HERE, LONGHAND VERSION BELOW WHICH MAY MAKE MORE SENSE
void displayEventHandler(void)
{
	genieFrame Event;
	genie.DequeueEvent(&Event);

	//Event handlers for buttons pressed on Main Screen (Form0)
	if (genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_TRACKBAR, 0)) TempVolumeSP = genie.GetEventData(&Event);
	if (genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, 0)) StartPB++;
	if (genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, 1)) StopPB++;
	if (genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, 2)) AbortPB++;
	if (genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, 3)) PausePB++;
	if (genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, 4)) ProceedPB++;
	if (genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, 5)) ResetPB++;
	if (genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, 7)) ConfigurationPB++;
	if (genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, 9)) ManualModePB++;



}




