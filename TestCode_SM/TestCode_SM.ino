/*
 Name:		TestCode_SM.ino
 Created:	11/24/2017 3:15:18 PM
 Author:	PC0123
*/

// the setup function runs once when you press reset or power the board
#include <SPI.h>
#include <genieArduino.h>


Genie genie;

//**********State Names//
#define INITIALIZE 0
#define IDLE 1
#define LOAD_SETTINGS 2
#define STARTUP 3
#define CONNECT_VEH 4
#define CAPTURE_FLOW_PRESS 5
#define RUN 6
#define DONE 7
#define CAPTURE_FLOW_PRESS2 8  //Could this be the same as #4?
#define RESET 9
#define ABORT 10
//#define UPDATE_DISPLAY 11
#define FAULT 12

//**********Global Variables//
bool Fault = FALSE;
int FaultMsg = 0;
int CurrentState = 0, PrevState = 0, FaultedState = 0, TempState = 0;
int AbortPB = 0, ResetPB = 0, ClearPB = 0, StartPB = 0, PausePB = 0, StopPB = 0, ProceedPB = 0, ConfigurationPB = 0, ManualModePB = 0;
double StateStartTime = 0;
unsigned long currentTime = 0, previousdebugtime = 0;

int TempVolumeSP = 0;
int VolumeSP = 0;

int previousCaptureTime = 0, previousFlowTime = 0;
const int captureInterval1 = 200;

int FlowIn = 5, FlowOut = 5;
int PressIn = 250, PressOut = 245;

int StatusMessage = 0;


//**********PIN Configuration Constants//
const byte pin_ResetDisplay = 23;
const int pin_PoutSS = 45;
const int pin_PinSS = 46;



//**********Constants//
int k_10sTimeOut = 10000;  //Generic timeout timer for 10 seconds


void setup() {
	//**********Setup for display communication
	Serial.begin(14400);
	Serial3.begin(200000);
	genie.Begin(Serial3);
	genie.AttachEventHandler(displayEventHandler);
	pinMode(pin_ResetDisplay, OUTPUT);
	digitalWrite(pin_ResetDisplay, LOW);
	delay(100);
	digitalWrite(pin_ResetDisplay, HIGH);
	delay(3500);	//Allow time for display to reset.
	
	//**********Initial state
	CurrentState = INITIALIZE;	//Always set state to Initialize when power up or on reset of controller.  THis will then force a Reset.
	
	//**********Make sure the display PB counters are zero before starting!
	AbortPB = 0, ResetPB = 0, ClearPB = 0, StartPB = 0, PausePB = 0, StopPB = 0, ProceedPB = 0, ConfigurationPB = 0, ManualModePB = 0;

	//**********Setup for SPI Communication
	SPI.begin();
	SPI.setBitOrder(MSBFIRST);
	SPI.setClockDivider(SPI_CLOCK_DIV4);
	pinMode(pin_PoutSS, OUTPUT);
	digitalWrite(pin_PoutSS, HIGH);
	digitalWrite(pin_PinSS, HIGH);


}

// the loop function runs over and over again until power down or reset
void loop() {

	currentTime = millis();
	//Debug Serial Print Code - Only excecutes every 2 seconds
	if ((currentTime - previousdebugtime) >= 1000) {
		Serial.println(millis());
		Serial.print("Reset PB Counter:");
		Serial.println(ResetPB);
		Serial.print("Current State:");
		Serial.println(CurrentState);
		Serial.print("Previous State:");
		Serial.println(PrevState);
		Serial.print("Pressure In:");
		Serial.println(PressIn);
		//Serial.print("Setpoint:");
		//Serial.println(TempVolumeSP);
		previousdebugtime += 1000;
	}


	genie.DoEvents();	//Update inputs from display
	PressOut = getAnalogData(pin_PoutSS);
	PressIn = getAnalogData(pin_PinSS);

	DisplayUpdate();


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
		state_Startup();
		break;
	case CONNECT_VEH:
		state_ConnectVeh();
		break;
	case CAPTURE_FLOW_PRESS:
		state_CaptureFlowPress();
		break;
	case RUN:
		state_Run();
		break;
	case DONE:
		state_Done;
		break;
	case CAPTURE_FLOW_PRESS2:
		state_CaptureFlowPress2();
		break;
	case RESET:
		state_Reset();
		break;
	case ABORT:
		state_Abort;
		break;
	/*case UPDATE_DISPLAY:
		break;*/
	case FAULT:
		state_Fault;
		break;
	
	}

	TempState = CurrentState;	//Capture state for this loop to determine if it changes
	
}


