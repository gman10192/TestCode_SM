/*
 Name:		TestCode_SM.ino
 Created:	11/24/2017 3:15:18 PM
 Author:	PC0123
*/

// the setup function runs once when you press reset or power the board
#include <genieArduino.h>

Genie genie;

//State Names//
#define INITIALIZE 0
#define IDLE 1
#define LOAD_SETTINGS 2
#define STARTUP 3
#define CAPTURE_FLOW_PRESS 4
#define RUN 5
#define DONE 6
#define CAPTURE_FLOW_PRESS2 7  //Could this be the same as #4?
#define RESET 8
#define ABORT 9
#define UPDATE_DISPLAY 10
#define FAULT 20

//Global Variables//
bool Fault = FALSE;
int FaultMsg = 0;
int CurrentState = 0, PrevState = 0, FaultedState = 0;
int AbortPB = 0, ResetPB = 0, ClearPB = 0, StartPB = 0, PausePB = 0, StopPB = 0, ProceedPB = 0, ConfigurationPB = 0, ManualModePB = 0;

//PIN Configuration Constants//
const byte pin_ResetDisplay = 23;


void setup() {
	//Setup for display communication
	Serial2.begin(14400);
	genie.Begin(Serial2);
	genie.AttachEventHandler(displayEventHandler);
	pinMode(pin_ResetDisplay, OUTPUT);
	digitalWrite(pin_ResetDisplay, LOW);
	delay(100);
	digitalWrite(pin_ResetDisplay, HIGH);
	delay(5000);	//Allow time for display to reset.
	genie.WriteStr(0, GENIE_VERSION);
	genie.WriteContrast(15);


	//wait for serial connection to attached PC (serial port 0)
	while (!Serial) {
		;
	}
	Serial.println("Serial Connection Active");
		
	CurrentState = INITIALIZE;	//Always set state to Initialize when power up or on reset of controller.  THis will then force a Reset.
}

// the loop function runs over and over again until power down or reset
void loop() {
	
	genie.DoEvents();	//Update inputs from display
	genie.WriteObject(GENIE_OBJ_STRINGS, 0, CurrentState);

	switch (CurrentState) {
	case INITIALIZE:
		state_Initialize();
		break;
	case IDLE:
		state_Idle();
		break;
	case LOAD_SETTINGS:
		state_LoadSettings();
		break;
	case STARTUP:

		break;
	case CAPTURE_FLOW_PRESS:

		break;
	case RUN:

		break;
	case DONE:
		break;
	case CAPTURE_FLOW_PRESS2:
		break;
	case RESET:
		break;
	case ABORT:
		break;
	case UPDATE_DISPLAY:
		break;
	case FAULT:
		break;
	default:
		PrevState = CurrentState;
		CurrentState = 0;
	}

}
