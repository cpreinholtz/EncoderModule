#ifndef CONTROL_H
#define CONTROL_H




class Control
{
    
private:

    //**************************************************************
    // members
    //**************************************************************
    //min and max val, inclusive
    static const int kMin = 0; 
    static const int kMax = 255;  

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
        
        float scaledDif = dif  / (float)(kMax - kMin);
        //Serial.println(scaledDif);

        float scaledFloat = scaledDif * (mScaleMax - mScaleMin);
        //Serial.println(scaledFloat);

        float shifted = scaledFloat + mScaleMin;
        //Serial.println(shifted);
        
        return shifted;
    }



};



#endif
