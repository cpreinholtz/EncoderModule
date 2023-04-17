#ifndef CONTROL_H
#define CONTROL_H
#include <EEPROM.h>


extern const int kCtrlLast;
class Control
{
    
private:

    //**************************************************************
    // members
    //**************************************************************
    //min and max val, inclusive.  do not change these of else you need to fix these locations:: 
    //lfoRate value check in "applyAllVoices" and the led brightness mapping in mcp get knobs
    static const int kMin = 0; 
    static const int kMax = 40;  
    static const int kControlTotal=64; //contral values and keys
    //min and max val, inclusive
    float mScaleMin; 
    float mScaleMax;

    //number of encoder ticks
    long mTick;
    
    //current control value
    long mVal;
    long mModulator;


public:
    static const int kControlMax=61; //control values 0 to 61
    static const int kKey0=kControlMax+1;//key0=62
    static const int kKey1=kControlMax+2;//key1=63
    //**************************************************************
    // constructors
    //**************************************************************
    Control(){
        Control(0);
    }
    
    Control(int setVal){
        Control(setVal, 0.0, 1.0);        
    }

    Control(int setVal, float scaleMin, float scaleMax){
        mVal =setVal;
        mTick = 0;
        mModulator = 0;
        setScaler(scaleMin, scaleMax);
    }

    
    //**************************************************************
    // setters
    //**************************************************************

    //use val (relative from last tick) then update val
    void setTick(long nextTick){
        //get the dif of the ticks, this is the number of spots the encoder has moved since last update
        long tickDif = nextTick - mTick;
        long desiredVal = mVal + tickDif;
        setVal(desiredVal);
        mTick = nextTick;
    }

    //use val (absolute) leave tick alone
    void setVal(long desiredVal){
        if (desiredVal < kMin){
            mVal = kMin;
        } else if(desiredVal > kMax){
            mVal = kMax;
        } else {
            mVal = desiredVal;
        }
    }

    //use val (percentage 0 to 1) leave tick alone
    void setValPercent(float desiredValPercent){
        long desiredVal = kMin + (long) (desiredValPercent * (float) (kMax - kMin) );
        setVal(desiredVal);
    }

    void setScaler(float scaleMin, float scaleMax){
        mScaleMin = scaleMin;
        mScaleMax = scaleMax;
        //Serial.println("setting Scaler");
        //Serial.println(mScaleMin);
        //Serial.println(mScaleMax);
    }


    void modulateVal(float modulator){
        mModulator = modulator;
    }
    

    //**************************************************************
    // getters
    //**************************************************************

    long getModulatedVal(){
        if (mVal+mModulator > kMax){
            return kMax;
        } else if( mVal+mModulator < kMin){
            return kMin;
        }else {
            return mVal+mModulator;
        }
    }

    long getVal(){
        return mVal;
    }



    float getScaled(){

        //Serial.println("scaling");
        //Serial.println(mScaleMin);
        //Serial.println(mScaleMax);
        
        
        float dif =(float)(getModulatedVal() - kMin);
        //Serial.println(dif);
        
        float scaledDif = dif  / ( (float) kMax - (float) kMin );
        //Serial.println(scaledDif);

        float scaledFloat = scaledDif * (mScaleMax - mScaleMin);
        //Serial.println(scaledFloat);

        float shifted = scaledFloat + mScaleMin;
        //Serial.println(shifted);
        
        return shifted;
    }





    int calcAddr(int patchIndex, int controlIndex){
        if (controlIndex > kControlMax) return 5000;
        else return patchIndex*kControlTotal+controlIndex;
    }
    
    byte readEeprom(int addr){
        if (addr < 1024) {
            return EEPROM.read(addr);        
        } else { 
            return 0;
        }
    }
    void writeEeprom(int addr, byte val){
        if (addr < 1024) {
            EEPROM.write(addr, val);        
        } 
    }

    void saveControl(int patchIndex, int controlIndex){
        //ADDR , Data
        int addr = calcAddr(patchIndex, controlIndex);
        if (addr < 1024){
            writeEeprom(addr, byte(getVal()));
        }
    }

    void loadControl(int patchIndex, int controlIndex){
        //ADDR , Data
        int addr = calcAddr(patchIndex, controlIndex);
        if (addr < 1024) {
            setVal(long(readEeprom(addr)));        
        }
    }
    

    //lets make this protected
    bool readKeys(int patchIndex){
        if( readEeprom(calcAddr(patchIndex, kKey0)) == 42 and readEeprom(calcAddr(patchIndex, kKey1)) == 69 ){
            return true;
        } else {
            return false;
        }
    }  
    
    void writeKeys(int patchIndex){
        writeEeprom(calcAddr(patchIndex, kKey0), 42);
        writeEeprom(calcAddr(patchIndex, kKey1), 69);        
    }
    


    


};



#endif
