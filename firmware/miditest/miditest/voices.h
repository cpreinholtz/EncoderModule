#ifndef VOICES_H
#define VOICES_H

/*
 * 
 #include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
*/

#include "time.h"

class Voice
{
    

    



public:    

    //**************************************************************
    // members (Audio)
    //**************************************************************



// GUItool: begin automatically generated code


//Wave modifiers
AudioSynthWaveform       mLfoWave;      //xy=483.74998474121094,213.75001287460327
AudioAmplifier           mAmpShape;           //xy=639.7500839233398,261.75000190734863
AudioAmplifier           mAmpFreq;           //xy=650.7499923706055,162.75001049041748

//Oscilators
AudioSynthWaveformModulated mWave0;         //xy=874.0000953674316,161.99999713897705
AudioSynthWaveformModulated mWave1; //xy=875.5,203.75
AudioSynthWaveformModulated mWave2; //xy=875.5,248.75
AudioSynthWaveformModulated mWave3; //xy=880.5,293.75
AudioMixer4              mMixerOSC; //xy=1033.2500305175781,229.75000381469727
AudioEffectEnvelope      mEnvOsc;      //xy=1189.7500038146973,227.75001430511475

//filter Modifiers
AudioSynthWaveformDc     mDc;            //xy=913.0001220703125,521.7500219345093
AudioEffectEnvelope      mEnvFilter; //xy=1055.7500305175781,510.75002098083496
AudioSynthWaveform       mLfoFilter; //xy=1055.7500038146973,574.750018119812
AudioMixer4              mMixerFilter;         //xy=1239.0000190734863,540.7500095367432
AudioFilterStateVariable mFilter;        //xy=1338.7500038146973,382.7500514984131









/* this bad syntax
AudioConnection          patchCord1(mLfoWave, mAmpFreq);
AudioConnection          patchCord2(mLfoWave, mAmpShape);
AudioConnection          patchCord3(mAmpShape, 0, mWave0, 1);
AudioConnection          patchCord4(mAmpShape, 0, mWave1, 1);
AudioConnection          patchCord5(mAmpShape, 0, mWave2, 1);
AudioConnection          patchCord6(mAmpShape, 0, mWave3, 1);
AudioConnection          patchCord7(mAmpFreq, 0, mWave0, 0);
AudioConnection          patchCord8(mAmpFreq, 0, mWave1, 0);
AudioConnection          patchCord9(mAmpFreq, 0, mWave2, 0);
AudioConnection          patchCord10(mAmpFreq, 0, mWave3, 0);
AudioConnection          patchCord11(mWave0, 0, mMixerOSC, 0);
AudioConnection          patchCord12(mWave1, 0, mMixerOSC, 1);
AudioConnection          patchCord13(mWave2, 0, mMixerOSC, 2);
AudioConnection          patchCord14(mWave3, 0, mMixerOSC, 3);
AudioConnection          patchCord15(mDc, mEnvFilter);
AudioConnection          patchCord16(mMixerOSC, mEnvOsc);
AudioConnection          patchCord17(mEnvFilter, 0, mMixerFilter, 0);
AudioConnection          patchCord18(mLfoFilter, 0, mMixerFilter, 1);
AudioConnection          patchCord19(mEnvOsc, 0, mFilter, 0);
AudioConnection          patchCord20(mMixerFilter, 0, mFilter, 1);
*/


// this is correct
AudioConnection          patchCord1;
AudioConnection          patchCord2;
AudioConnection          patchCord3;
AudioConnection          patchCord4;
AudioConnection          patchCord5;
AudioConnection          patchCord6;
AudioConnection          patchCord7;
AudioConnection          patchCord8;
AudioConnection          patchCord9;
AudioConnection          patchCord10;
AudioConnection          patchCord11;
AudioConnection          patchCord12;
AudioConnection          patchCord13;
AudioConnection          patchCord14;
AudioConnection          patchCord15;
AudioConnection          patchCord16;
AudioConnection          patchCord17;
AudioConnection          patchCord18;
AudioConnection          patchCord19;
AudioConnection          patchCord20;


// GUItool: end automatically generated code

    //**************************************************************
    // constructors
    //**************************************************************
    Voice():
        patchCord1(mLfoWave, mAmpFreq),
        patchCord2(mLfoWave, mAmpShape),
        patchCord3(mAmpShape, 0, mWave0, 1),
        patchCord4(mAmpShape, 0, mWave1, 1),
        patchCord5(mAmpShape, 0, mWave2, 1),
        patchCord6(mAmpShape, 0, mWave3, 1),
        patchCord7(mAmpFreq, 0, mWave0, 0),
        patchCord8(mAmpFreq, 0, mWave1, 0),
        patchCord9(mAmpFreq, 0, mWave2, 0),
        patchCord10(mAmpFreq, 0, mWave3, 0),
        patchCord11(mWave0, 0, mMixerOSC, 0),
        patchCord12(mWave1, 0, mMixerOSC, 1),
        patchCord13(mWave2, 0, mMixerOSC, 2),
        patchCord14(mWave3, 0, mMixerOSC, 3),
        patchCord15(mDc, mEnvFilter),
        patchCord16(mMixerOSC, mEnvOsc),
        patchCord17(mEnvFilter, 0, mMixerFilter, 0),
        patchCord18(mLfoFilter, 0, mMixerFilter, 1),
        patchCord19(mEnvOsc, 0, mFilter, 0),
        patchCord20(mMixerFilter, 0, mFilter, 1)
    {
        clear();
        mSetTime = 0;
        mOffTime = 0;
    }


    void initLfoWave(){
        mLfoWave.begin(1.0, 100, WAVEFORM_SINE); //level freq, wave
        mAmpShape.gain(0.0);
        mAmpFreq.gain(0.0);
    }

    void initOsc(){        
        mWave0.begin(1.0, 100, WAVEFORM_SAWTOOTH); //level freq, wave
        mWave1.begin(1.0, 100, WAVEFORM_PULSE); //level freq, wave
        mWave2.begin(1.0, 100, WAVEFORM_TRIANGLE_VARIABLE); //level freq, wave
        mWave3.begin(1.0, 50, WAVEFORM_SINE); //level freq, wave
        mMixerOSC.gain(0, 0.5);
        mMixerOSC.gain(1, 1.0);
        mMixerOSC.gain(2, 0.2);
        mMixerOSC.gain(3, 1.0);
        mEnvOsc.delay(0);
        mEnvOsc.hold(0);
        mEnvOsc.attack(100);
        mEnvOsc.decay(300);
        mEnvOsc.sustain(0.7);
        mEnvOsc.release(1000);
    }

    void initFilter(){        
        mDc.amplitude(1.0);
        mMixerFilter.gain(0, 0.0);
        mMixerFilter.gain(1, 0.0);
        mMixerFilter.gain(2, 0.0);
        mMixerFilter.gain(3, 0.0);
        mLfoFilter.begin(1.0, 100, WAVEFORM_SINE); //level freq, wave
        mEnvFilter.delay(0);
        mEnvFilter.hold(0);
        mEnvFilter.attack(200);
        mEnvFilter.decay(100);
        mEnvFilter.sustain(0.4);
        mEnvFilter.release(100);

        mFilter.frequency(8000);
        mFilter.resonance(0);
        mFilter.octaveControl(2);
    }

    void initAudio(){        
        initFilter();
        initOsc();
        initLfoWave();
    }

    
    



    //**************************************************************
    // setters
    //**************************************************************
    void set(byte note, byte vel, int bend){
        mVel = vel;
        mNote = note;
        mSetTime = millis();
        if (vel >0){
            updateVoiceFrequency(bend);
            mEnvOsc.noteOn();
            mEnvFilter.noteOn();
        } else {
            clear();
        }        
    }
    
    void updateVoiceFrequency(int bend){
        //todo, hit the oscilators and envelopes now
        float freq = getBendedFrequency(bend);
        mWave0.frequency(freq);
        mWave1.frequency(freq);
        mWave2.frequency(freq);
        mWave3.frequency(freq/2.0); 
        //Serial.println("freq");   
        //Serial.println(freq); 
    }

    void clear(){
        if (mVel > 0 ){
            mVel = 0;
            mOffTime = millis();
            mEnvOsc.noteOff();
            mEnvFilter.noteOff();
        }

    }    
    
    //**************************************************************
    // getters
    //**************************************************************
    byte getVel(){
        return mVel;
    }    
    byte getNote(){
        return mNote;
    }    
    unsigned long long getTime(){
        return mSetTime;
    }  
    unsigned long long getOffTime(){
        return mOffTime;
    }  



private:
    //**************************************************************
    // members
    //**************************************************************
    bool mVel;
    byte mNote;
    static const int nWaves = 4;


    
    unsigned long long mSetTime;
    unsigned long long mOffTime;

    
    static const int kA = 440; // a is 440 hz...
    static const int kFullBend = 8191;
    static const int kBendHalfSteps = 2.0;
    static constexpr float kBbendScaler = ((float) kBendHalfSteps) / ( 12.0 * ((float)kFullBend) ) ;

    //get note frequency * bendMultiplier
    float getBendedFrequency(int bend){    
        //actual bend is 2^ ((bendHalfSteps /12.0) * (bend/fullBend))
        //therefore if half steps is 12 (one octave) and bend is max or min, your pitch will be multiplied by 2^-1 or 2^1 (0.5 or 2)            
        float bendMultiplier = pow(2, (float) bend * kBbendScaler );
        return ( getNoteFrequency() * bendMultiplier);        
    }
    
    //get note frequency (before bending)
    float getNoteFrequency(){        
        return ( ((float)kA) / 32.0) * ( pow(2,(((float)mNote - 9.0) / 12.0)) )  ;
    }

    





    
};





class Voices
{
    
private:

    //**************************************************************
    // members
    //**************************************************************
    static const int kNumVoices = 4; 
    int mNextVoice;
    int mBend;


    
    
    //**************************************************************
    // arbitration
    //**************************************************************
    void pickNext(byte note){
        int i;    
        unsigned long long lowestTime = millis();   
        unsigned long long lowestOffTime = lowestTime; 
        bool foundOff = false;
        
        for (i=0; i<kNumVoices ; i++){


            if (mVoices[i].getNote() == note){
                mNextVoice = i;
                return;
                
            //pick the lowest off time of the off notesby default
            } else if (mVoices[i].getVel() <= 0 ){
                foundOff = true;
                if (mVoices[i].getOffTime() < lowestOffTime){
                    lowestOffTime = mVoices[i].getOffTime();
                    mNextVoice = i;
                }

            //if all are in use pick the lowest on time
            } else {
                if (foundOff == false and mVoices[i].getTime() < lowestTime){
                    lowestTime = mVoices[i].getTime();
                    mNextVoice = i;
                }                
            }
            
            
        }  
    }




public:

    Voice mVoices [kNumVoices];

    //**************************************************************
    // constructors
    //**************************************************************
    Voices(){
        mBend =0;
        mNextVoice = 0;
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].clear();
        }      
    }

    
    //**************************************************************
    // setters
    //**************************************************************
    void set(byte note, byte vel){

        if (vel <= 0 ){
            unset(note);
        } else {

            //check if the note is already being played, only really an issue if using sequencer or multiple keyboards for some reason
            int i;                 
            for (i=0; i<kNumVoices ; i++){           
                if (mVoices[i].getVel() > 0  and mVoices[i].getNote() == note) {
                    //Serial.println("repeat");
                    return;
                }
            }
            
            pickNext(note); 
            mVoices[mNextVoice].set(note,vel,mBend);
            
        }    
    }

    void updateBend(int bend){
        int i;
        for (i=0; i<kNumVoices ; i++){           
            mVoices[i].updateVoiceFrequency(bend);
        }
    }

    void unset(byte note){
        int i;
        for (i=0; i<kNumVoices ; i++){
            if (mVoices[i].getNote() == note){
                mVoices[i].clear();
            }
        }
    }



    void initAudio(){        
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].initAudio();
        }
    }


    //**************************************************************
    // getters
    //**************************************************************
    int getNumVoices(){
        return kNumVoices;
    }

    void dbg(){
        /*
        Serial.println("voicelist");
        int i;
        for (i = 0 ; i<kNumVoices; i++){
            if (mVoices[i].getVel() <= 0 ) {
                Serial.print("X");
            } else {
               Serial.print(mVoices[i].getNote()); 
            }            
            Serial.print("\t");
        }
        Serial.println("");
        */
    }



    //**************************************************************
    // audio
    //**************************************************************

    
    ///////////////////////////////////////////////////////////
    //WaveMixes
    ///////////////////////////////////////////////////////////
    void setWave0Mix(float mix){
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].mMixerOSC.gain(0, mix);
        }
    }    
    void setWave1Mix(float mix){
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].mMixerOSC.gain(1, mix);
        }
    }    
    void setWave2Mix(float mix){
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].mMixerOSC.gain(2, mix);
        }
    }
    void setWave3Mix(float mix){
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].mMixerOSC.gain(3, mix);
        }
    }

    ///////////////////////////////////////////////////////////
    //VCA OSC ENV
    ///////////////////////////////////////////////////////////
    void setEnvAttack(float val){
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].mEnvOsc.attack(val);
        }
    }    
    void setEnvDecay(float val){
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].mEnvOsc.decay(val);
        }
    }        
    void setEnvSustain(float val){
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].mEnvOsc.sustain(val);
        }
    }    

    void setEnvRelease(float val){
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].mEnvOsc.release(val);
        }
    }    

    ///////////////////////////////////////////////////////////
    //LFO wave
    ///////////////////////////////////////////////////////////
    void setLfoRate(float val){
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].mLfoWave.frequency(bpmToFreq(val));
        }
    }    

    void setLfoShapeMix(float val){
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].mAmpShape.gain(val);
        }
    }    

    void setLfoFreqMix(float val){
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].mAmpFreq.gain(val);
        }
    }    

    ///////////////////////////////////////////////////////////
    //filter
    ///////////////////////////////////////////////////////////
    void setFilterCutoff(float freq){
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].mFilter.frequency(freq);
        }
    }

    void setFilterRes(float val){
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].mFilter.resonance(val);
        }
    }


    ///////////////////////////////////////////////////////////
    //filter Env
    ///////////////////////////////////////////////////////////
    void setFilterEnvAmmount(float val){
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].mMixerFilter.gain(0, val);
        }
    }
    void setFilterEnvAttack(float val){
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].mEnvFilter.attack(val);
        }
    }    
    void setFilterEnvDecay(float val){
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].mEnvFilter.decay(val);
        }
    }        
    void setFilterEnvSustain(float val){
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].mEnvFilter.sustain(val);
        }
    }
    void setFilterEnvRelease(float val){
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].mEnvFilter.release(val);
        }
    }    

    ///////////////////////////////////////////////////////////
    //filter LFO
    ///////////////////////////////////////////////////////////
    void setFilterLfoAmmount(float val){
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].mMixerFilter.gain(1, val);
        }
    }
    void setFilterLfoRate(float val){
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].mLfoFilter.frequency(bpmToFreq(val));
        }
    }

    
};









#endif
