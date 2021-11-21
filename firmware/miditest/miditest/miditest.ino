#include <MIDI.h>
#include "noteList.h"
#include "pitches.h"


// Simple midi test, based off the "simpleSynth" example for the teensy   Note, your midi keyborad needs to be transmitting on channel 4!


MIDI_CREATE_DEFAULT_INSTANCE();


   

static const unsigned sMaxNumNotes = 16;
MidiNoteList<sMaxNumNotes> midiNotes;



// -----------------------------------------------------------------------------

void handleNotesChanged(bool isFirstNote = false)
{
    
    //Serial.println("change");
    
    if (midiNotes.empty())
    {
       // handleGateChanged(false);
        //noTone(sAudioOutPin); // Remove to keep oscillator running during envelope release.
   
    }
    else
    {
        // Possible playing modes: 
        // Mono Low:  use midiNotes.getLow.. Mono High: use midiNotes.getHigh.. Mono Last: use midiNotes.getLast

        byte currentNote = 0;
        if (midiNotes.getLast(currentNote))
        {
            //tone(sAudioOutPin, sNotePitches[currentNote]);'
            Serial.println("note change");
            Serial.println(currentNote);

            if (isFirstNote)
            {
                //handleGateChanged(true);
                //Serial.println("gate on first");
            }
            else
            {
                //Serial.println("gate on multiple");
                //pulseGate(); // Retrigger envelopes. Remove for legato effect.
            }
        }
    }
}

// -----------------------------------------------------------------------------

void handleNoteOn(byte inChannel, byte inNote, byte inVelocity)
{
    const bool firstNote = midiNotes.empty();
    Serial.println("on");
    midiNotes.add(MidiNote(inNote, inVelocity));
    handleNotesChanged(firstNote);
    //Serial.println("on");
}

void handleNoteOff(byte inChannel, byte inNote, byte inVelocity)
{
    Serial.println("off");
    midiNotes.remove(inNote);
    handleNotesChanged();
    //Serial.println("off");
}

// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------

void setup()
{
    //pinMode(sGatePin,     OUTPUT);
    //pinMode(sAudioOutPin, OUTPUT);
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
    MIDI.begin(4);
    Serial.begin(9600);
    Serial.println("here");
}

void loop()
{
 
    MIDI.read();
}
