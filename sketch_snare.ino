/* 
e-coustic drumkit

built by: Rich Durante
*/

int SNARE[4] = {50,1000,26,0};		// {threshold, sensitivity, note, hitVelocity}

/*
int HIHAT[5] = {50,0,37,39,0};		// channel 32 contains sound for pressing pedal down
int HHPED[4] = {400,0,30,0};
int KICK[4] = {100,0,24,0};
int SETTING[4] = {4,500,100,1};     // {scantime,snare/rim,pedalVelocity,masktime}
*/

#include <MIDI.h>					// includes MIDI library
MIDI_CREATE_DEFAULT_INSTANCE();		// created and binds the MIDI interface to the default serial port

boolean snareFlag = false;			// set once outside loop *do for all drums*
// boolean pedalFlag = false;


void setup() {
  MIDI.begin(10);					// begin MIDI listen on channel 10
}

void loop() {
  int snareValue = analogRead(A0);  // reading snare drum head shot 
  
  /*
  int hhValue = analogRead(A1);
  int hhPedal = analogRead(A2);
  int kickValue = analogRead(A3);
  */
    
  if (snareValue >= SNARE[0]) {						// checks if snare reading is above minimum threshold velocity *requires tuning*
    SNARE[3] = map(snareValue,50,700,0,127);		// remaps values of snare velocity to appropriate MIDI decimal velocities
    MIDI.sendNoteOn(SNARE[2], SNARE[3], 10);		// {note, velocity, midi_channel} snare drum
    MIDI.sendNoteOn(SNARE[2], 0, 10);				// ending note *try without one day*
    snareFlag = true;
  }
 
  /*
  if (hhValue > HIHAT[0] && hhPedal > HHPED[0]) {
    hhValue = map(hhValue,0,500,0,127);
    MIDI.sendNoteOn(HIHAT[2],hhValue, 10); // hi hat closed note
    MIDI.sendNoteOn(HIHAT[2], 0, 10);
    // hhFlag = true;
  }
  else
    hhValue = map(hhvalue,0,500,0,127);
    MIDI.sendNoteOn(HIHAT[3],hhValue, 10); // hi hat open note
    MIDI.sendNoteOn(HIHAT[3],0, 10);

  if (kickValue > KICK[0])  {
    kickValue = map(kickValue, 0,1000,0,127); // kick drum
    MIDI.sendNoteOn(KICK[2],kickValue,10);
    MIDI.sendNoteOn(KICK[2],0,10);

  }
*/
/*
******************************** FLAG SECTION *****************************************************
*/
 if (snareValue >= SNARE[0] && snareFlag == true) {
    snareFlag = false;
	SNARE[3] = 0x00;   
	delay(10);
}
}
