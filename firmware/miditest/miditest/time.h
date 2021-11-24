#ifndef TIME_H
#define TIME_H


float bpmToFreq(float bpm){
    float bps = 60.0*bpm;
    return 1/bps;
}


#endif

