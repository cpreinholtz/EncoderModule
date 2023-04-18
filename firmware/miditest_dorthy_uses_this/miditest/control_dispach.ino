
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
    FxLfoAmmount,
    BitcrushBits,
    BitcrushSampleRate,


    //relics of the past
    VoiceFilterEnvRelease,
    DryPan,
    DelayPan,
    ReverbPan,
    BitcrushPan,
    CtrlLast //always keep this at the bottom!
};

//default destinations
int gModWheelDestination = VoiceFilterCutoff;
int gAftertouchDestination = FrequencyDrift;

Control gControls[CtrlLast]; //Never exceed control.kControlMax!!!


void setLfoScaler(){
    if (clkDivMode==true){
        gControls[VoiceLfoRate].setScaler(33.0, 1.0); //this is in clk periods *8 , I want faster rate to the right
        gControls[VoiceFilterLfoRate].setScaler(33.0, 1.0); //this is in clk periods *8 , I want faster rate to the right
    } else {
        gControls[VoiceLfoRate].setScaler(0.0, 60*6);
        gControls[VoiceFilterLfoRate].setScaler(0.0, 60*36);
    }
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
    gControls[FrequencyDrift].setScaler(1.0, 4.0);

    gControls[VoiceLfoShapeMix].setScaler(0.0, 1.0);
    //gControls[VoiceLfoFreqMix].setScaler(0.0, .001);
    //gControls[VoiceLfoRate].setScaler(0.0, 60*6);
    gControls[VoiceAllMix].setScaler(0.1, 0.5);

    
    gControls[VoiceFilterCutoff].setScaler(100.0, 4000.0);
    gControls[VoiceFilterRes].setScaler(0.0, 4.9);
    gControls[VoiceFilterLfoAmmount].setScaler(0.0, 0.5);
    //gControls[VoiceFilterLfoRate].setScaler(0.0, 60*36); 
    setLfoScaler();

    gControls[VoiceFilterEnvAttack].setScaler(5.0, 2000.0);
    gControls[VoiceFilterEnvDecay].setScaler(5.0, 2000.0);
    gControls[VoiceFilterEnvSustain].setScaler(0.0, 1.0);
    gControls[VoiceFilterEnvRelease].setScaler(5.0, 2000.0); 
    
    gControls[VoiceFilterEnvAmmount].setScaler(0.0, 0.5);

  

}

//these SHOULD be overwritten in patch loading
void setDefaultsVoices(){

    gControls[VoiceWave0Mix].setValPercent(.95);
    gControls[VoiceWave1Mix].setValPercent(.24);
    gControls[VoiceWave2Mix].setValPercent(.5);
    gControls[VoiceWave3Mix].setValPercent(.9);


    gControls[VoiceEnvAttack].setValPercent(.2);
    gControls[VoiceEnvDecay].setValPercent(.25);
    gControls[VoiceEnvSustain].setValPercent(.7);
    gControls[VoiceEnvRelease].setValPercent(.49);
    gControls[GlideSteps].setValPercent(0);

    gControls[VoiceLfoShapeMix].setValPercent(0);
    gControls[VoiceLfoRate].setValPercent(.1);
    gControls[VoiceAllMix].setValPercent(.6);

    gControls[VoiceFilterCutoff].setValPercent(.7);
    gControls[VoiceFilterRes].setValPercent(.1);
    gControls[VoiceFilterLfoAmmount].setValPercent(.99);
    gControls[VoiceFilterLfoRate].setValPercent(0);


    gControls[VoiceFilterEnvAttack].setValPercent(.2);
    gControls[VoiceFilterEnvDecay].setValPercent(.2);
    gControls[VoiceFilterEnvSustain].setValPercent(.5);
    gControls[VoiceFilterEnvRelease].setValPercent(0);

    gControls[VoiceFilterEnvAmmount].setValPercent(0);
}

void setLfoRates(){
    gVoices.setFilterLfoRate(gControls[VoiceFilterLfoRate].getScaled());
    gVoices.setLfoRate(gControls[VoiceLfoRate].getScaled());
    setDelayRate(gControls[DelayRate].getScaled());

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
    
    //this used to set default control values (most are overwritten if loading patch completes successfully)
    setDefaultsVoices();
    setFxDefaults();    
    applyAllVoices();
    
    //uncomment this when you make changes to patch saving and loading in order to fix the patch stuff
    //for (int i=0; i < 16; i++){ loadPatch(i); savePatch(i); }
    
    //now defaults are loaded from EEPROM
    loadPatch(0); //includes apply all voices()
    

    

    applyAllVoices();
    
    
}


////////////////////////////////////////////////////////////
//patch saving and loading
////////////////////////////////////////////////////////////
void loadPatch(int patch){
    if (patch < 16 and gControls[0].readKeys(patch) == true) {        
        for (int i = 0; i < CtrlLast; i++){
            gControls[i].loadControl(patch,i);
        }
        
        int addr = gControls[0].calcAddr(patch, CtrlLast);
        byte ctrl = gControls[0].readEeprom(addr+1);        
        if (ctrl & (1 << 0)) chordMode = true; else chordMode = false;
        if (ctrl & (1 << 1)) dummyMode = true; else dummyMode = false;
        if (ctrl & (1 << 2)) arpMode = true; else arpMode = false;
        if (ctrl & (1 << 3)) splitMode = true; else splitMode = false;        
        if (ctrl & (1 << 4)) glideFromClosest = true; else glideFromClosest = false;
        if (ctrl & (1 << 5)) clkDivMode = true; else clkDivMode = false;
        
        setModWheelDestination(gControls[0].readEeprom(addr+2));
        setAftertouchDestination(gControls[0].readEeprom(addr+3));
        splitKey = gControls[0].readEeprom(addr+4);
        
        applyAllVoices();
    } else if (patch < 16 and gControls[0].readKeys(patch) == false ){
        Serial.println("error reading key");
    }
}

void savePatch(int patch){
    if (patch < 16){
        for (int i = 0; i < CtrlLast; i++){
            gControls[i].saveControl(patch,i);
        }
        
        byte ctrl = 0;
        if (chordMode) ctrl = ctrl | (1 << 0);
        if (dummyMode) ctrl = ctrl | (1 << 1);
        if (arpMode) ctrl = ctrl | (1 << 2);
        if (splitMode) ctrl = ctrl | (1 << 3);
        if (glideFromClosest) ctrl = ctrl | (1 << 4);
        if (clkDivMode) ctrl = ctrl | (1 << 5);
        
        int addr = gControls[0].calcAddr(patch, CtrlLast);
        gControls[0].writeEeprom(addr+1, ctrl);
        gControls[0].writeEeprom(addr+2, gModWheelDestination);
        gControls[0].writeEeprom(addr+3, gAftertouchDestination);
        gControls[0].writeEeprom(addr+4, splitKey);
        gControls[0].writeKeys(patch);
    }    
}





////////////////////////////////////////////////////////////
//mod wheel and after touch
////////////////////////////////////////////////////////////



void setModWheelDestination(int ctrlIndex){
    if (ctrlIndex < CtrlLast) gModWheelDestination = ctrlIndex;
}

void setAftertouchDestination(int ctrlIndex){
    if (ctrlIndex < CtrlLast) gAftertouchDestination = ctrlIndex;
}

const int kCcModWheel = 1;

void setCc(byte ch, byte cc, byte val){
    switch (cc){
        case kCcModWheel:         
            
            //gControls[VoiceLfoFreqMix].setVal(val); 
            //gVoices.setLfoFreqMix(gControls[VoiceLfoFreqMix].getScaled());
            
            //gControls[VoiceFilterCutoff].setValPercent((float)val / 128.0);            
            //gVoices.setFilterCutoff(gControls[VoiceFilterCutoff].getScaled());
            
            gControls[gModWheelDestination].setValPercent((float)val / 128.0);
            applyAllVoices();
            break;
    }
}

void setAftertouch(int preassure){
    gControls[gAftertouchDestination].modulateVal(preassure/4);
    applyAllVoices();
}
