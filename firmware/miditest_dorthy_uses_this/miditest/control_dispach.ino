
#include "control.h"




enum tCtrlList {
    //reem , row    
    // 0,0
    VoiceWave0Mix,
    VoiceWave1Mix,
    VoiceWave2Mix,
    VoiceWave3Mix,
    // 0,1
    VoiceEnvAttack,
    VoiceEnvDecay,
    VoiceEnvSustain,
    VoiceEnvRelease,
    
    //1,0
    VoiceLfoShapeMix,    
    VoiceLfoRate,
    DryMix,
    VoiceAllMix,    
    //1,1
    VoiceFilterCutoff,
    VoiceFilterRes,    
    VoiceFilterLfoAmmount,
    VoiceFilterLfoRate,   
     
    //2,0
    VoiceFilterEnvAttack,
    VoiceFilterEnvDecay,
    VoiceFilterEnvSustain,
    VoiceFilterEnvAmmount,
    //2,1    
    DelayMix,
    GlideSteps,
    DelayFeedBack,
    DelayRate,
    
    //3,0    
    ReverbMix,
    FrequencyDrift,    
    ReverbDamping,
    ReverbRoomSize,
    //3,1
    BitcrushMix,
    BitcrushPan,
    BitcrushBits,
    BitcrushSampleRate,

    //relics of the past
    VoiceFilterEnvRelease,
    DryPan,
    DelayPan,
    ReverbPan,
    CtrlLast //always keep this at the bottom!
};

Control gControls[CtrlLast]; //Never exceed control.kControlMax!!!

void modulateFrequency(float preassure){
    gControls[FrequencyDrift].modulateVal(preassure);
}

void setScalersVoices(){

    

    gControls[VoiceWave0Mix].setScaler(0.0, 0.5);
    gControls[VoiceWave1Mix].setScaler(0.0, .5);
    gControls[VoiceWave2Mix].setScaler(0.0, .5);
    gControls[VoiceWave3Mix].setScaler(0.0, .5);

    gControls[VoiceEnvAttack].setScaler(5.0, 2000.0);
    gControls[VoiceEnvDecay].setScaler(5.0, 2000.0);
    gControls[VoiceEnvSustain].setScaler(0.0, 1.0);
    gControls[VoiceEnvRelease].setScaler(5.0, 2000.0);
    
    gControls[GlideSteps].setScaler(1.0, 9.0);//true max steps is 2^scaler so really 2^9 = 512 steps,,, * 20ms = ~ 10 sec
    gControls[FrequencyDrift].setScaler(0.0, 1.0);

    gControls[VoiceLfoShapeMix].setScaler(0.0, 1.0);
    //gControls[VoiceLfoFreqMix].setScaler(0.0, .001);
    gControls[VoiceLfoRate].setScaler(0.0, 60*6);
    gControls[VoiceAllMix].setScaler(0.1, 0.5);

    
    gControls[VoiceFilterCutoff].setScaler(100.0, 4000.0);
    gControls[VoiceFilterRes].setScaler(0.0, 4.9);
    gControls[VoiceFilterLfoAmmount].setScaler(0.0, 0.5);
    gControls[VoiceFilterLfoRate].setScaler(6.0, 60*36); 
    

    gControls[VoiceFilterEnvAttack].setScaler(5.0, 2000.0);
    gControls[VoiceFilterEnvDecay].setScaler(5.0, 2000.0);
    gControls[VoiceFilterEnvSustain].setScaler(0.0, 1.0);
    gControls[VoiceFilterEnvRelease].setScaler(5.0, 2000.0); 
    
    gControls[VoiceFilterEnvAmmount].setScaler(0.0, 0.5);



}

void applyAllVoices(){

    gVoices.setWave0Mix(gControls[VoiceWave0Mix].getScaled());
    gVoices.setWave1Mix(gControls[VoiceWave1Mix].getScaled());
    gVoices.setWave2Mix(gControls[VoiceWave2Mix].getScaled());
    gVoices.setWave3Mix(gControls[VoiceWave3Mix].getScaled());    

    gVoices.setEnvAttack(gControls[VoiceEnvAttack].getScaled());
    gVoices.setEnvDecay(gControls[VoiceEnvDecay].getScaled());
    gVoices.setEnvSustain(gControls[VoiceEnvSustain].getScaled());
    gVoices.setEnvRelease(gControls[VoiceEnvRelease].getScaled());
    gVoices.setGlide(gControls[GlideSteps].getScaled());
    gVoices.setNoiseMultiplier(gControls[FrequencyDrift].getScaled());


    gVoices.setLfoShapeMix(gControls[VoiceLfoShapeMix].getScaled());
    gVoices.setLfoRate(gControls[VoiceLfoRate].getScaled());    

    
    float t = gControls[VoiceAllMix].getScaled();
    gVoiceMixer.gain(0,t);
    gVoiceMixer.gain(1,t);
    gVoiceMixer.gain(2,t);
    gVoiceMixer.gain(3,t);
    
    gVoices.setFilterCutoff(gControls[VoiceFilterCutoff].getScaled());
    gVoices.setFilterRes(gControls[VoiceFilterRes].getScaled());

    gVoices.setFilterEnvAmmount(gControls[VoiceFilterEnvAmmount].getScaled());
    gVoices.setFilterEnvAttack(gControls[VoiceFilterEnvAttack].getScaled());
    gVoices.setFilterEnvDecay(gControls[VoiceFilterEnvDecay].getScaled());
    gVoices.setFilterEnvSustain(gControls[VoiceFilterEnvSustain].getScaled());
    gVoices.setFilterEnvRelease(gControls[VoiceFilterEnvRelease].getScaled());
    
    
    gVoices.setFilterLfoAmmount(gControls[VoiceFilterLfoAmmount].getScaled());
    gVoices.setFilterLfoRate(gControls[VoiceFilterLfoRate].getScaled());

    applyAllFx();

}


//void applyAll(){
    //applyAllVoices();
    //applyAllFx();  //already in voices
//}

void initControl(){
    //this sets the max / min for each control value
    setScalersVoices();    
    setFxScalers();
    //this used to set default control values (
    //setDefaultsVoices();
    //setFxDefaults();
    //applyAllVoices();

    //now defaults are loaded from EEPROM
    loadPatch(0); //includes apply all voices()
    
    
}


void loadPatch(int patch){
    if (patch < 16){
        for (int i = 0; i < CtrlLast; i++){
            gControls[i].loadControl(patch,i);
        }
    }
    applyAllVoices();
}

void savePatch(int patch){
    if (patch < 16){
        for (int i = 0; i < CtrlLast; i++){
            gControls[i].saveControl(patch,i);
        }
    }
}








const int kCcModWheel = 1;

void setCc(byte ch, byte cc, byte val){
    switch (cc){
        case kCcModWheel:         
            
            //gControls[VoiceLfoFreqMix].setVal(val); 
            //gVoices.setLfoFreqMix(gControls[VoiceLfoFreqMix].getScaled());
            
            gControls[VoiceFilterCutoff].setValPercent((float)val / 128.0);            
            gVoices.setFilterCutoff(gControls[VoiceFilterCutoff].getScaled());
            
            break;
    }
}
