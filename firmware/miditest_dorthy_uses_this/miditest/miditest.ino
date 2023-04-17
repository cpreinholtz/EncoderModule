#define ARDUINO_TARGET 1


#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


#include <MIDI.h>
#include <notes.h>
#include "voices.h"






Voices gVoices;
Notes gNotes;
//Timer knobTimer(1000);

Timer knobTimer(5000);
//GreyCounter gc;

// Simple midi test, based off the "simpleSynth" example for the teensy   Note, your midi keyborad needs to be transmitting on channel 4!
MIDI_CREATE_DEFAULT_INSTANCE();


// -----------------------------------------------------------------------------

void setup()
{
    AudioMemory(600);
    //pinMode(sGatePin,     OUTPUT);
    //pinMode(sAudioOutPin, OUTPUT);

    //https://github.com/FortySevenEffects/arduino_midi_library/wiki/Using-Callbacks
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);    
    MIDI.setHandleControlChange(handleControlChange);
    MIDI.setHandlePitchBend(handlePitchBend);
    MIDI.setHandleClock(handleClock);
    
    //MIDI.setHandleAfterTouchPoly(handleAfterTouchPoly);
    MIDI.setHandleAfterTouchChannel(handleAfterTouch);
    
    MIDI.setHandleStart(handleStart);
    MIDI.setHandleContinue(handleContinue);
    MIDI.setHandleStop(handleStop);
    
    MIDI.begin(MIDI_CHANNEL_OMNI); //channel
    Serial.begin(115200);
    Serial.println("here");
    

    
    initAudio();
    initControl();
    initMcp();


    
}


void loop()
{ 

    MIDI.read();

    if (knobTimer.pollAndReset()){
        getKnobs();
    }
    serviceAudio();
    serviceEffects();
}
