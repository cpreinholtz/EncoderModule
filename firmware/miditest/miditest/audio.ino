

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



void initAudio(){

    audioShield.enable();
    //audioShield.inputSelect(myInput);
    audioShield.volume(0.5);
    
    int i;
    
    for ( i=0; i<gVoices.getNumVoices(); i++){
        gVoiceMixer.gain(i,0.5);
    }    
    for ( i=gVoices.getNumVoices(); i<4; i++){
        gVoiceMixer.gain(i,0.0);
    }

    gVoices.initAudio();
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
  

// -----------------------------------------------------------------------------

void handleNoteOn(byte ch, byte note, byte vel){
    Serial.println("on");
    if (vel <= 0){
        Serial.println("Velocity 0!!!!!!!!!!!!!!");
        gNotes.noteOff(note);
        gVoices.unset(note);
    } else {
        gNotes.noteOn(note, vel);
        updateNotes();//this contains voices.set
    }
    
}

void handleNoteOff(byte ch, byte note, byte vel){
    //Serial.println("off");
    gNotes.noteOff(note);
    gVoices.unset(note);
    //updateNotes();
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
// -----------------------------------------------------------------------------
