#include <MIDI.h>
#include "noteList.h"
#include "voices.h"
#include "Audio.h"



Voices gVoices;
Notes gNotes;

//mix all voices
AudioMixer4              gVoiceMixer;         //xy=900,337
AudioConnection patchVoices0 (gVoices.mVoices[0].mFilter, 0, gVoiceMixer , 0);
AudioConnection patchVoices1 (gVoices.mVoices[1].mFilter, 0, gVoiceMixer , 1);
AudioConnection patchVoices2 (gVoices.mVoices[2].mFilter, 0, gVoiceMixer , 2);

//output to Dacs
AudioOutputAnalogStereo  dacs1;          //xy=688.75,520.75
AudioConnection patchOut0 (gVoiceMixer, 0, dacs1 , 0);
AudioConnection patchOut1 (gVoiceMixer, 0, dacs1 , 1);


void initAudio(){
    int i;
    for ( i=0; i<gVoices.getNumVoices(); i++){
        gVoiceMixer.gain(i,1.0);
    }    
    for ( i=gVoices.getNumVoices(); i<4; i++){
        gVoiceMixer.gain(i,0.0);
    }

    gVoices.initAudio();
}
    


// Simple midi test, based off the "simpleSynth" example for the teensy   Note, your midi keyborad needs to be transmitting on channel 4!
MIDI_CREATE_DEFAULT_INSTANCE();






void dbgNotes(){
    Serial.println("");
    gNotes.dbg(); 
    gVoices.dbg();
}

void updateNotes(){
    int i;
    Serial.println("updating");
    for (i=0; i<gVoices.getNumVoices(); i++){
        Note tNote = gNotes.get(i);
        Serial.println(i);
        Serial.println(tNote.mNote);
        Serial.println(tNote.mVel);
        if (tNote.mVel >0 ){
            gVoices.set(tNote.mNote, tNote.mVel);
        }
        delay(10);
    }
    dbgNotes();
}
  

// -----------------------------------------------------------------------------

void handleNoteOn(byte ch, byte note, byte vel){
    Serial.println("on");
    gNotes.noteOn(note, vel);
    if (vel <= 0){
        gVoices.unset(note);
    }    
    updateNotes();
}

void handleNoteOff(byte ch, byte note, byte vel){
    Serial.println("off");
    gNotes.noteOff(note);
    gVoices.unset(note);
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
