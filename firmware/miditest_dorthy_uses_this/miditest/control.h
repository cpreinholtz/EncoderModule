#ifndef CONTROL_H
#define CONTROL_H
#include <EEPROM.h>



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
    static const int kControlMax=64;
    //min and max val, inclusive
    float mScaleMin; 
    float mScaleMax;

    //number of encoder ticks
    long mTick;
    
    //current control value
    long mVal;


public:


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
    

    //**************************************************************
    // getters
    //**************************************************************

    long getVal(){
        return mVal;
    }





    float getScaled(){

        //Serial.println("scaling");
        //Serial.println(mScaleMin);
        //Serial.println(mScaleMax);
        
        
        float dif =(float)(mVal - kMin);
        //Serial.println(dif);
        
        float scaledDif = dif  / ( (float) kMax - (float) kMin );
        //Serial.println(scaledDif);

        float scaledFloat = scaledDif * (mScaleMax - mScaleMin);
        //Serial.println(scaledFloat);

        float shifted = scaledFloat + mScaleMin;
        //Serial.println(shifted);
        
        return shifted;
    }

    void saveControl(int patchIndex, int controlIndex){
        //ADDR , Data
        int addr = patchIndex*kControlMax+controlIndex;
        if (addr < 1024){
            byte val = byte(getVal());
            //Serial.print("addr: ");Serial.print(addr); Serial.print(" \t val : "); Serial.println(val);
            EEPROM.write(addr, val);      
        }
    }

    void loadControl(int patchIndex, int controlIndex){
        //ADDR , Data
        int addr = patchIndex*kControlMax+controlIndex;
        if (addr < 1024) {
            setVal(long(EEPROM.read(addr)));        
        }
    }

};



#endif
