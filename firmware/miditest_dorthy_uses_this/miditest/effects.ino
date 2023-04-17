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
//AudioEffectFreeverbStereo gFreeverb;     //xy=871.666748046875,590.3333740234375
AudioEffectFlange        flange1;        //xy=1167,1198.5
AudioAmplifier           gAmpReverbL;         //xy=1921.6666717529297,833.3333129882812
AudioAmplifier           gAmpReverbR;         //xy=1921.6666717529297,833.3333129882812
AudioConnection patchFxRvbDry (gVoiceMixer, 0, gMixerDelayFf , 0);
AudioConnection patchFxRvbDly (gAmpDelay, 0, gMixerDelayFf , 1);



//AudioConnection patchFxRvbIn (gMixerDelayFf, 0, gFreeverb , 0);
//AudioConnection patchFxRvbAmpL (gFreeverb, 0, gAmpReverbL , 0);
//AudioConnection patchFxRvbAmpR (gFreeverb, 1, gAmpReverbR , 0);

AudioConnection patchFxRvbIn (gMixerDelayFf, 0, flange1 , 0);
AudioConnection patchFxRvbAmpL (flange1, 0, gAmpReverbL , 0);
AudioConnection patchFxRvbAmpR (flange1, 0, gAmpReverbR , 0);

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





// Number of samples in each delay line
#define FLANGE_DELAY_LENGTH (6*AUDIO_BLOCK_SAMPLES)
// Allocate the delay lines for left and right channels
short flange_delayline[FLANGE_DELAY_LENGTH];


int s_idx = FLANGE_DELAY_LENGTH/4;
int s_depth = FLANGE_DELAY_LENGTH/4;
double s_freq = .5;

void setDelayScaler(){
    if (clkDivMode==true){
        gControls[DelayRate].setScaler(32.0, 1.0); //this is in clk periods *8 , I want faster rate to the right
    } else {
        gControls[DelayRate].setScaler(500.0, 100.0); //this is in ms , I want faster rate to the right
    }
}
void setFxScalers(){

    gControls[DryMix].setScaler(0.0, 0.5);
    gControls[DryPan].setScaler(0.0, 1.0);

    gControls[DelayMix].setScaler(0.0, 0.5);
    gControls[DelayPan].setScaler(0.0, 1.0);
    gControls[DelayFeedBack].setScaler(0.0, .9);
    setDelayScaler();

    gControls[ReverbMix].setScaler(0.0, 0.5);
    gControls[ReverbPan].setScaler(0.0, 1.0);    
    //gControls[ReverbDamping].setScaler(1.0, 0.01);
    //gControls[ReverbRoomSize].setScaler(0.0, 0.75);

    gControls[ReverbDamping].setScaler(0.1, (float) FLANGE_DELAY_LENGTH/4.0); //flange depth
    gControls[ReverbRoomSize].setScaler(0.5, 4.0); //flange freq

    gControls[BitcrushMix].setScaler(0.0, 0.5);
    gControls[BitcrushPan].setScaler(0.0, 1.0);
    gControls[BitcrushBits].setScaler(15.0, 2.0); //sample bits, reverse polarity
    gControls[BitcrushSampleRate].setScaler(16000, 100);  //in Hz, reverse polarity
    
    gControls[FxLfoAmmount].setScaler(0, 1.0);
    
     flange1.begin(flange_delayline,FLANGE_DELAY_LENGTH,s_idx,s_depth,s_freq);
    //flange1.voices(FLANGE_DELAY_PASSTHRU,0,0);

    
}

void setFxDefaults(){
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

    
    gControls[DryMix].setValPercent(1.0);
    //gControls[DryPan].setValPercent(0.5);

    gControls[DelayMix].setValPercent(0.0);
    //gControls[DelayPan].setValPercent(0.4);
    gControls[DelayFeedBack].setValPercent(0.3);
    gControls[DelayRate].setValPercent(0.7);

    gControls[ReverbMix].setValPercent(0.0);
    //gControls[ReverbPan].setValPercent(0.2);
    gControls[ReverbRoomSize].setValPercent(0.5);
    gControls[ReverbDamping].setValPercent(0.5);

    gControls[BitcrushMix].setValPercent(0);
    //gControls[BitcrushPan].setValPercent(0.7);
    gControls[BitcrushBits].setValPercent(.5);
    gControls[BitcrushSampleRate].setValPercent(0.5);

    //I find that for "ballanced" inputs, center pan means a loss of volume... pan all slightly
    gControls[DryPan].setValPercent(0.45);
    gControls[DelayPan].setValPercent(0.4);
    gControls[ReverbPan].setValPercent(0.6);
    gControls[BitcrushPan].setValPercent(0.55);

    gControls[FxLfoAmmount].setValPercent(0.8);
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
    //setReverbRoomSize(gControls[ReverbRoomSize].getScaled());
    //setReverbDamping(gControls[ReverbDamping].getScaled());    
    setFlange(gControls[ReverbDamping].getScaled(),gControls[ReverbRoomSize].getScaled());


    
    setBitcrushMix(gControls[BitcrushMix].getScaled());
    setBitcrushPan(gControls[BitcrushPan].getScaled());
    setBitcrushBits(gControls[BitcrushBits].getScaled());
    setBitcrushSampleRate(gControls[BitcrushSampleRate].getScaled());

    setFxLfoAmmount(gControls[FxLfoAmmount].getScaled());

    

    
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


//FX LFO
float gFxLfoAmmount;
const int kDelayLookup = 16;
const float kDelayMult = 1000/kDelayLookup*2; //for each delay, get through half of the lookup table (*2)
const float delayLookup[kDelayLookup] = {.1,.2,.3,.4,.5,.6,.7,.8,.9,.8,.7,.6,.5,.4,.3,.2};
#include <timer.h>
Timer gDelayPan(1000);


//inMs !!~!!!
void setDelayRate(float val){
    //convert to clk divs to millis
    if (clkDivMode){
        val = bpmToMillis(arp.getBpm()) * round(val)/16;
    }
    gDelay.delay(0,val);//delay rate (not pan)
    val = val * 1000/8; //convert to micros, then make 1/4 period
    if (val < 10000) val = 10000;//cap at n ms
    gDelayPan.setPeriodMicros(val);//period por panning delay
}

void serviceEffects(){
    static int pan = 0;
    if ( gDelayPan.pollAndReset()){
        pan = pan + 1;
        if (pan >= kDelayLookup) pan = 0;
        setDelayPan((delayLookup[pan]-0.5)*gFxLfoAmmount+0.5);
    }
}

void setFxLfoAmmount(float val){
    gFxLfoAmmount=val;
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

/*void setReverbRoomSize(float val){
    gFreeverb.roomsize(val);
    
}

void setReverbDamping(float val){
    gFreeverb.damping(val);
}*/

void setFlange(float depth, float dly){


    static float lastDepth =-1.0;
    static float lastDly =-1.0;

    if (depth!= lastDepth or dly !=lastDly ){
        lastDepth = depth;
        lastDly = dly;

        //gFreeverb.roomsize(val);
        flange1.voices(s_idx, (int) depth, dly);
        Serial.println("flange gepth and dly");
        Serial.println((int) depth);
        Serial.println(dly);
    }
    


    //flange1.voices(s_idx,s_depth,s_freq);
    
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
