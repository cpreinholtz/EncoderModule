
#include "control.h"


enum tCtrlList {
    VoiceWave0Mix,
    VoiceWave1Mix,
    VoiceWave2Mix,
    VoiceWave3Mix,

    VoiceEnvAttack,
    VoiceEnvDecay,
    VoiceEnvSustain,
    VoiceEnvRelease,

    VoiceLfoShapeMix,
    VoiceLfoFreqMix,
    VoiceLfoRate,
    
    VoiceFilterCutoff,
    VoiceFilterRes,

    VoiceFilterEnvAmmount,
    VoiceFilterEnvAttack,
    VoiceFilterEnvDecay,
    VoiceFilterEnvSustain,
    VoiceFilterEnvRelease,
    
    VoiceFilterLfoAmmount,
    VoiceFilterLfoRate,


    CtrlLast //always keep this at the bottom!
};

Control gControls[CtrlLast];


void setScalers(){

    gControls[VoiceWave0Mix].setScaler(0.0, 1.0);
    gControls[VoiceWave1Mix].setScaler(0.0, 1.0);
    gControls[VoiceWave2Mix].setScaler(0.0, 1.0);
    gControls[VoiceWave3Mix].setScaler(0.0, 1.0);

    gControls[VoiceEnvAttack].setScaler(5.0, 2000.0);
    gControls[VoiceEnvDecay].setScaler(5.0, 2000.0);
    gControls[VoiceEnvSustain].setScaler(0.0, 1.0);
    gControls[VoiceEnvRelease].setScaler(5.0, 2000.0);


    gControls[VoiceLfoShapeMix].setScaler(0.0, 1.0);
    gControls[VoiceLfoFreqMix].setScaler(0.0, 1.0);
    gControls[VoiceLfoRate].setScaler(6.0, 180.0);

    
    gControls[VoiceFilterCutoff].setScaler(100.0, 8000.0);
    gControls[VoiceFilterRes].setScaler(0.0, 0.7);

    gControls[VoiceFilterEnvAmmount].setScaler(100.0, 8000.0);
    gControls[VoiceFilterEnvAttack].setScaler(5.0, 2000.0);
    gControls[VoiceFilterEnvDecay].setScaler(5.0, 2000.0);
    gControls[VoiceFilterEnvSustain].setScaler(0.0, 1.0);
    gControls[VoiceFilterEnvRelease].setScaler(5.0, 2000.0); 
    
    gControls[VoiceFilterLfoAmmount].setScaler(0.0, 1.0);
    gControls[VoiceFilterLfoRate].setScaler(6.0, 180.0); 


}

void setDefaults(){

    gControls[VoiceWave0Mix].setVal(250);
    gControls[VoiceWave1Mix].setVal(50);
    gControls[VoiceWave2Mix].setVal(100);
    gControls[VoiceWave3Mix].setVal(200);
    

    gControls[VoiceEnvAttack].setVal(40);
    gControls[VoiceEnvDecay].setVal(50);
    gControls[VoiceEnvSustain].setVal(200);
    gControls[VoiceEnvRelease].setVal(100);


    gControls[VoiceLfoShapeMix].setVal(0);
    gControls[VoiceLfoFreqMix].setVal(0);
    gControls[VoiceLfoRate].setVal(20);

    
    gControls[VoiceFilterCutoff].setVal(200);
    gControls[VoiceFilterRes].setVal(15);

    gControls[VoiceFilterEnvAmmount].setVal(0);
    gControls[VoiceFilterEnvAttack].setVal(0);
    gControls[VoiceFilterEnvDecay].setVal(0);
    gControls[VoiceFilterEnvSustain].setVal(0);
    gControls[VoiceFilterEnvRelease].setVal(0);     
    
    gControls[VoiceFilterLfoAmmount].setVal(0);
    gControls[VoiceFilterLfoRate].setVal(20); 

}

void appllyAll(){

    gVoices.setWave0Mix(gControls[VoiceWave0Mix].getScaled());
    gVoices.setWave1Mix(gControls[VoiceWave1Mix].getScaled());
    gVoices.setWave2Mix(gControls[VoiceWave2Mix].getScaled());
    gVoices.setWave3Mix(gControls[VoiceWave3Mix].getScaled());    

    gVoices.setEnvAttack(gControls[VoiceEnvAttack].getScaled());
    gVoices.setEnvDecay(gControls[VoiceEnvDecay].getScaled());
    gVoices.setEnvSustain(gControls[VoiceEnvSustain].getScaled());
    gVoices.setEnvRelease(gControls[VoiceEnvRelease].getScaled());

    gVoices.setLfoShapeMix(gControls[VoiceLfoShapeMix].getScaled());
    gVoices.setLfoFreqMix(gControls[VoiceLfoFreqMix].getScaled());
    gVoices.setLfoRate(gControls[VoiceLfoRate].getScaled());

    
    gVoices.setFilterCutoff(gControls[VoiceFilterCutoff].getScaled());
    gVoices.setFilterRes(gControls[VoiceFilterRes].getScaled());

    gVoices.setFilterEnvAmmount(gControls[VoiceFilterEnvAmmount].getScaled());
    gVoices.setFilterEnvAttack(gControls[VoiceFilterEnvAttack].getScaled());
    gVoices.setFilterEnvDecay(gControls[VoiceFilterEnvDecay].getScaled());
    gVoices.setFilterEnvSustain(gControls[VoiceFilterEnvSustain].getScaled());
    gVoices.setFilterEnvRelease(gControls[VoiceFilterEnvRelease].getScaled());
    
    
    gVoices.setFilterLfoAmmount(gControls[VoiceFilterLfoAmmount].getScaled());
    gVoices.setFilterLfoRate(gControls[VoiceFilterLfoRate].getScaled());

}




void initControl(){
    setScalers();
}









const int kCcModWheel = 1;

void setCc(byte ch, byte cc, byte val){
    switch (cc){
        case kCcModWheel:         
            
            //gControls[VoiceLfoFreqMix].setVal(val); 
            //gVoices.setLfoFreqMix(gControls[VoiceLfoFreqMix].getScaled());
            
            gControls[VoiceFilterCutoff].setVal(val + val);            
            gVoices.setFilterCutoff(gControls[VoiceFilterCutoff].getScaled());
            
            break;
    }
}
