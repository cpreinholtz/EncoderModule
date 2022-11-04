#include <chord_maker.h>

#include <arpegio.h>
#include <midi_clk.h>


//limitations
//turning on arp while playing a note would be bad, should not really be possible currently
//
//


AudioOutputI2S      audioOutput;        // audio shield: headphones & line-out
AudioControlSGTL5000 audioShield;




//mix all voices
AudioMixer4              gVoiceMixer;         //xy=900,337
AudioConnection patchVoices0 (gVoices.mVoices[0].mFilter, 0, gVoiceMixer , 0);
AudioConnection patchVoices1 (gVoices.mVoices[1].mFilter, 0, gVoiceMixer , 1);
AudioConnection patchVoices2 (gVoices.mVoices[2].mFilter, 0, gVoiceMixer , 2);
AudioConnection patchVoices3 (gVoices.mVoices[3].mFilter, 0, gVoiceMixer , 3);



//Efects out
AudioMixer4              gMixerFxL;       //xy=1095.666748046875,564.3333740234375
AudioMixer4              gMixerFxR;       //xy=1287.666748046875,777.3333740234375


//output to Dacs
//AudioOutputAnalogStereo  dacs1;          //xy=688.75,520.75
//AudioConnection patchOut0 (gMixerFxL, 0, dacs1 , 0);
//AudioConnection patchOut1 (gMixerFxR, 0, dacs1 , 1);

AudioConnection patchOut0 (gMixerFxL, 0, audioOutput , 0);
AudioConnection patchOut1 (gMixerFxR, 0, audioOutput , 1);

// -----------------------------------------------------------------------------
bool chordMode;
bool dummyMode;
bool splitMode;
bool arpMode;
byte splitKey;
extern const int LED_PIN;
ChordMaker chordMaker;
Arpegio arp;
byte arpDiv;


void initAudio(){

    audioShield.enable();
    //audioShield.inputSelect(myInput);
    audioShield.volume(1.0);
    
    int i;
    
    for ( i=0; i<gVoices.getNumVoices(); i++){
        gVoiceMixer.gain(i,0.5);
    }    
    for ( i=gVoices.getNumVoices(); i<4; i++){
        gVoiceMixer.gain(i,0.0);
    }

    gVoices.initAudio();
    chordMode = false;
    arpMode=false;
    dummyMode = false;
    splitMode = false;
    splitKey = 0;
    Serial.println("Audio init");
}


void serviceAudio(){
    if (arp.service()==true){
        if (arp.getGateStatus()==true) {
            gNotes.noteOn(arp.get().mNote, arp.get().mVel);
            updateNotes();
        } else {
            gNotes.noteOff(arp.get().mNote);
            gVoices.unset(arp.get().mNote);
        }
    }
}

// -----------------------------------------------------------------------------


void dbgNotes(){
    Serial.println("");
    gNotes.dbg(); 
    gVoices.dbg();
}

void updateNotes(){
    int i;
    //Serial.println("updating");
    for (i=0; i<gVoices.getNumVoices(); i++){
        Note tNote = gNotes.get(i);
        //Serial.println(i);
        //Serial.println(tNote.mNote);
        //Serial.println(tNote.mVel);
        if (tNote.mVel > 0 ){
            gVoices.set(tNote.mNote, tNote.mVel);
        } else {
            break;
        }
    }
    dbgNotes();
}
  




void toggleSettings(byte note){
    switch(note%12){
        case 0: 
            chordMode = !chordMode;
            digitalWrite(LED_PIN,chordMode);
            break;
        case 2:
            dummyMode = !dummyMode;
            digitalWrite(LED_PIN,dummyMode);
            break;
        case 4:
            splitMode = !splitMode;
            digitalWrite(LED_PIN,splitMode);
            break;
        case 9:
            arpMode = !arpMode;
            if (arpMode == true){
                arp.start();
            } else {
                arp.stop();
                if(arp.getGateStatus() ==true){
                    gNotes.noteOff(arp.get().mNote);
                    gVoices.unset(arp.get().mNote);
                }
            }
            digitalWrite(LED_PIN,arpMode);
            break;
        default:
            Serial.println("bad toggle signal");
            break;            
    }
}


void defaultNoteOn(byte note, byte vel){
    chordMaker.setRoot(note);
    //check for dummys
    if ( dummyMode ==true and chordMaker.getValid() ==false) return; //do nothing!!! prevent dummy from playing bad note

    if (arpMode == false){
        gNotes.noteOn(note, vel);
         //check if we want to make this a chord
        if (chordMode==true and chordMaker.getValid() ==true and (splitMode==false or (splitMode==true and note<splitKey)) ){
            gNotes.noteOn(chordMaker.getTriadMiddle(), vel);
            gNotes.noteOn(chordMaker.getTriadLast(), vel);
        }
        updateNotes();//this contains voices.set
    //arpMode==true
    } else {        
        //is a valid chord
        if (chordMode==true and chordMaker.getValid() ==true and (splitMode==false or (splitMode==true and note<splitKey)) ){
            arp.noteOn(chordMaker.getTriadLast(), vel);
            arp.noteOn(chordMaker.getTriadMiddle(), vel);
            arp.noteOn(note, vel);            
        } else {
            //not a valid chord, but not a dummy
            gNotes.noteOn(note, vel);  
            updateNotes();//this contains voices.set
        }
    }

    
   
    
}


void defaultNoteOff(byte note){

    chordMaker.setRoot(note);
    //check for dummys
    //if ( dummyMode ==true and chordMaker.getValid() ==false) return; //do nothing!!! prevent dummy from playing bad note
    if (arpMode == false){
        //else valid chord, or dummy mode disabled
        gNotes.noteOff(note);
        gVoices.unset(note);
        //check if we wanted to make this a chord
        if (chordMode==true and chordMaker.getValid() ==true and (splitMode==false or (splitMode==true and note<splitKey)) ){
            gNotes.noteOff(chordMaker.getTriadMiddle()); 
            gVoices.unset(chordMaker.getTriadMiddle());
            gNotes.noteOff(chordMaker.getTriadLast());
            gVoices.unset(chordMaker.getTriadLast());
        }
    } else {
        if (chordMode==true and chordMaker.getValid() ==true and (splitMode==false or (splitMode==true and note<splitKey)) ){
            //gVoices.unset(arp.get().mNote);
            gNotes.noteOff(arp.get().mNote);
            gVoices.unset(arp.get().mNote);
            arp.noteOff(chordMaker.getTriadLast());
            arp.noteOff(chordMaker.getTriadMiddle());
            arp.noteOff(note);            
        } else {
            gNotes.noteOff(note);
            gVoices.unset(note);
        }
    }
}

void handleNoteOn(byte ch, byte note, byte vel){
    Serial.println("on");
    if (vel <= 0){
        Serial.println("Velocity 0!!!!!!!!!!!!!!");
        handleNoteOff(ch, note, vel);
    } else {
        switch(ch) {
            case 15://used for toggling settings
                toggleSettings(note);
                break;
            case 14://for seting key
                chordMaker.setKey(note);
                break;
            case 13://for setting split
                splitKey = note;
                break;
            case 12:
                arpDiv = note%12;
                arp.setDiv(arpDiv);
                break;
            default:
                defaultNoteOn(note, vel);
                break;
        }            
    }
    
}

void handleNoteOff(byte ch, byte note, byte vel){
    //Serial.println("off");
    switch(ch) {
        case 15://used for toggling settings
            //toggleSettings(note);
            break;
        case 14://for seting key
            //chordMaker.setKey(note);
            break;
        case 13://for setting split
            //splitKey = note;
            break;
        case 12:
            break;
        default:
            defaultNoteOff(note);
            break;
                    
    }
}


void handleControlChange(byte ch, byte cc, byte val){
    //Serial.println(ch);
    //Serial.println(cc);  
    //Serial.println(val);
    setCc(ch,cc,val);
}

void handlePitchBend(byte ch, int bend){
    //Serial.println(ch);
    //Serial.println(bend);  
    gVoices.updateBend(bend);
}

MidiClk clk;
void handleClock(){
    clk.tickIn();
    arp.setBpm(clk.getQuarterNoteBpm()); //24 midi clks in a quarter note
    //Serial.println("clkin");
    //Serial.println(clk.getQuarterNoteBpm()); //TODO REMOVE ME
    //Serial.println();
}

void handleAfterTouchPoly(byte ch, byte note, byte preassure){
    //TODO
    if (arpMode ==true and chordMaker.getRoot()==note ){
        arp.setDiv(map(preassure, 1,255,arpDiv,64));        
    }
}

// -----------------------------------------------------------------------------
