#ifndef TIME_H
#define TIME_H

/*
float bpmToFreq(float bpm){
    float bps = bpm / 60.0;
    return bps;
}




class Timer{

public:

    Timer(unsigned long periodMicros){        
        setPeriodMicros(periodMicros);
        startTick();        
    }




    void setPeriodMicros(unsigned long periodMicros){
        mPeriodMicros =  periodMicros;        
    }

    
    void startTick(){
        mStartedMicros =  micros();        
    }

    bool epochDone(){
        unsigned long currentMicros = micros();
        if (currentMicros - mStartedMicros >mPeriodMicros ){

            if (currentMicros - mStartedMicros >mPeriodMicros*2 ){
                Serial.println("too slow");
                Serial.println(currentMicros - mStartedMicros);
            }
            return true;
        } else {
            return false;
        }
    }

    bool pollAndReset(){
        bool isDone = epochDone();
        if (isDone){
            startTick();
        }
        return isDone;
    }


    
    unsigned long mPeriodMicros;
    unsigned long mStartedMicros;

private:

};


*/


#endif
