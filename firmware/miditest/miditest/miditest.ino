#include <MIDI.h>
#include "noteList.h"



// Simple midi test, based off the "simpleSynth" example for the teensy   Note, your midi keyborad needs to be transmitting on channel 4!


MIDI_CREATE_DEFAULT_INSTANCE();


  

// -----------------------------------------------------------------------------

void handleNoteOn(byte inChannel, byte inNote, byte inVelocity)
{
    Serial.println("on");
}

void handleNoteOff(byte inChannel, byte inNote, byte inVelocity)
{
    Serial.println("off");
}

// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------

void setup()
{
    //pinMode(sGatePin,     OUTPUT);
    //pinMode(sAudioOutPin, OUTPUT);
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
    MIDI.begin(4); //channel
    Serial.begin(9600);
    Serial.println("here");
}

void loop()
{
 
    MIDI.read();
}
