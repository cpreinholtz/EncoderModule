#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>



// GUItool: begin automatically generated code






//dry
AudioAmplifier           gAmpDry;         //xy=1921.6666717529297,833.3333129882812
AudioConnection patchFxDry (gVoiceMixer, 0, gAmpDry , 0);
AudioConnection patchFxDryL (gAmpDry, 0, gMixerFxL , 0);
AudioConnection patchFxDryR (gAmpDry, 0, gMixerFxR , 0);


//delay
AudioMixer4              gMixerDelayFb;   //xy=254.666748046875,765.3333740234375
AudioEffectDelay         gDelay;         //xy=417.666748046875,769.3333740234375
AudioAmplifier           gAmpDelay;         //xy=1921.6666717529297,833.3333129882812
AudioConnection patchFxDelayDry (gVoiceMixer, 0, gMixerDelayFb , 0);
AudioConnection patchFxDelayFb2 (gMixerDelayFb, 0, gDelay , 0);
AudioConnection patchFxDelayFb (gDelay, 0, gMixerDelayFb , 1);
AudioConnection patchFxDelay (gDelay, 0, gAmpDelay , 0);
AudioConnection patchFxDelayL (gAmpDelay, 0, gMixerFxL , 1);
AudioConnection patchFxDelayR (gAmpDelay, 0, gMixerFxR , 1);


//Reverb
AudioMixer4              gMixerDelayFf;   //xy=254.666748046875,765.3333740234375
AudioEffectFreeverbStereo gFreeverb;     //xy=871.666748046875,590.3333740234375
AudioAmplifier           gAmpReverbL;         //xy=1921.6666717529297,833.3333129882812
AudioAmplifier           gAmpReverbR;         //xy=1921.6666717529297,833.3333129882812
AudioConnection patchFxRvbDry (gVoiceMixer, 0, gMixerDelayFf , 0);
AudioConnection patchFxRvbDly (gAmpDelay, 0, gMixerDelayFf , 1);

AudioConnection patchFxRvbIn (gMixerDelayFf, 0, gFreeverb , 0);
AudioConnection patchFxRvbAmpL (gFreeverb, 0, gAmpReverbL , 0);
AudioConnection patchFxRvbAmpR (gFreeverb, 1, gAmpReverbR , 0);
AudioConnection patchFxRvbL (gAmpReverbL, 0, gMixerFxL , 2);
AudioConnection patchFxRvbR (gAmpReverbR, 0, gMixerFxR , 2);




//bitcrusher
AudioEffectBitcrusher    gBitcrush;    //xy=849.666748046875,903.3333740234375
AudioAmplifier           gAmpBitcrush;         //xy=1921.6666717529297,833.3333129882812
AudioConnection patchFxBcIn (gMixerDelayFf, 0, gBitcrush , 0);
AudioConnection patchFxBc (gBitcrush, 0, gAmpBitcrush , 0);
AudioConnection patchFxBcL (gAmpBitcrush, 0, gMixerFxL , 3);
AudioConnection patchFxBcR (gAmpBitcrush, 0, gMixerFxR , 3);



// GUItool: end automatically generated code





void setFxScalers(){

    gControls[DryMix].setScaler(0.0, 0.5);
    gControls[DryPan].setScaler(0.0, 1.0);

    gControls[DelayMix].setScaler(0.0, 0.5);
    gControls[DelayPan].setScaler(0.0, 1.0);
    gControls[DelayFeedBack].setScaler(0.0, .9);
    gControls[DelayRate].setScaler(500.0, 100.0); //this is in ms , I want faster rate to the right

    gControls[ReverbMix].setScaler(0.0, 0.5);
    gControls[ReverbPan].setScaler(0.0, 1.0);    
    gControls[ReverbDamping].setScaler(1.0, 0.01);
    gControls[ReverbRoomSize].setScaler(0.0, 1.0);

    gControls[BitcrushMix].setScaler(0.0, 0.5);
    gControls[BitcrushPan].setScaler(0.0, 1.0);
    gControls[BitcrushBits].setScaler(15.0, 2.0); //sample bits, reverse polarity
    gControls[BitcrushSampleRate].setScaler(16000, 100);  //in Hz, reverse polarity

}




void setFxDefaults(){

    gControls[DryMix].setValPercent(1.0);
    gControls[DryPan].setValPercent(0.5);

    gControls[DelayMix].setValPercent(0.0);
    gControls[DelayPan].setValPercent(0.4);
    gControls[DelayFeedBack].setValPercent(0.3);
    gControls[DelayRate].setValPercent(0.7);

    gControls[ReverbMix].setValPercent(0.0);
    gControls[ReverbPan].setValPercent(0.2);
    gControls[ReverbRoomSize].setValPercent(0.5);
    gControls[ReverbDamping].setValPercent(0.5);

    gControls[BitcrushMix].setValPercent(0);
    gControls[BitcrushPan].setValPercent(0.7);
    gControls[BitcrushBits].setValPercent(.5);
    gControls[BitcrushSampleRate].setValPercent(0.5);

    //other defaults

    gMixerDelayFb.gain(0,1.0);
    gMixerDelayFb.gain(1,0.0);  //set in contol functions
    gMixerDelayFb.gain(2,0.0);
    gMixerDelayFb.gain(3,0.0);


    gMixerDelayFf.gain(0,1.0);
    gMixerDelayFf.gain(1,1.0);
    gMixerDelayFf.gain(2,0.0);
    gMixerDelayFf.gain(3,0.0);


    gDelay.disable(1);
    gDelay.disable(2);
    gDelay.disable(3);
    gDelay.disable(4);
    gDelay.disable(5);
    gDelay.disable(6);
    gDelay.disable(7);
    
}

void applyAllFx(){

    setDryMix(gControls[DryMix].getScaled());
    setDryPan(gControls[DryPan].getScaled());

    setDelayMix(gControls[DelayMix].getScaled());
    setDelayPan(gControls[DelayPan].getScaled());
    setDelayFeedback(gControls[DelayFeedBack].getScaled());
    setDelayRate(gControls[DelayRate].getScaled());

    setReverbMix(gControls[ReverbMix].getScaled());
    setReverbPan(gControls[ReverbPan].getScaled());
    setReverbRoomSize(gControls[ReverbRoomSize].getScaled());
    setReverbDamping(gControls[ReverbDamping].getScaled());

    setBitcrushMix(gControls[BitcrushMix].getScaled());
    setBitcrushPan(gControls[BitcrushPan].getScaled());
    setBitcrushBits(gControls[BitcrushBits].getScaled());
    setBitcrushSampleRate(gControls[BitcrushSampleRate].getScaled());


    
}


//Dry
void setDryMix(float val){
    gAmpDry.gain(val);
}

void setDryPan(float val){
    gMixerFxL.gain(0,1.0-val);
    gMixerFxR.gain(0,val);
}



//Delay
void setDelayMix(float val){
    gAmpDelay.gain(val);
}

void setDelayPan(float val){
    gMixerFxL.gain(1,1.0-val);
    gMixerFxR.gain(1,val);
}

void setDelayFeedback(float val){
    gMixerDelayFb.gain(1,val);
}

//inMs !!~!!!
void setDelayRate(float val){
    gDelay.delay(0,val);
}




//Reverb
void setReverbMix(float val){
    gAmpReverbR.gain(val);
    gAmpReverbL.gain(val);
}

void setReverbPan(float val){
    gMixerFxL.gain(2,1.0-val);
    gMixerFxR.gain(2,val);
}

void setReverbRoomSize(float val){
    gFreeverb.roomsize(val);
}

void setReverbDamping(float val){
    gFreeverb.damping(val);
}


//Reverb
void setBitcrushMix(float val){
    gAmpBitcrush.gain(val);
}

void setBitcrushPan(float val){
    gMixerFxL.gain(3,1.0-val);
    gMixerFxR.gain(3,val);
}

//frequency 1 to 44100
void setBitcrushSampleRate(float val){
    gBitcrush.sampleRate(val);
}

void setBitcrushBits(float val){
    gBitcrush.bits( (int) val);
}
