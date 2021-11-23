#include <MIDI.h>
#include "noteList.h"
#include "voices.h"

Voices gVoices;
Notes gNotes;

// Simple midi test, based off the "simpleSynth" example for the teensy   Note, your midi keyborad needs to be transmitting on channel 4!


MIDI_CREATE_DEFAULT_INSTANCE();



void updateNotes(){
    int i;
    for (i=0; i<gVoices.getNumVoices(); i++){
        Note tNote = gNotes.get(i);
        gVoices.set(tNote.mNote, tNote.mVel);
    }    
}
  

// -----------------------------------------------------------------------------

void handleNoteOn(byte ch, byte note, byte vel){
    Serial.println("on");
    gNotes.noteOn(note, vel);
    updateNotes();
}

void handleNoteOff(byte ch, byte note, byte vel){
    Serial.println("off");
    gNotes.noteOff(note);
    updateNotes();
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
