#include <inttypes.h>


struct GreyState
{
    bool sChanged;
    long sCount;
};




//This class keeps track of the motion of a rotary encoder
//when updating, the class returns the state structure that tells the current tick count and weather or not anything has changed since the last update
//the update function is meant to be called frequently (>100Hz ish) whenever the encoder pins are polled

//encoder counter updates based on this resource:
//http://makeatronics.blogspot.com/2013/02/efficiently-reading-quadrature-with.html

class GreyCounter
{
private:
    GreyState mState;
    uint8_t mShiftReg;

    //this is the basis of counter updates,  it uses the laststate<<2 | currentstate
    //See Doc/quadratureTable.png for full table breakdown
    const int8_t kLookupTable[16] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};




public:

    //**************************************************************
    //Update current state
    //**************************************************************
    //thisVal is a 2 bit binary : 000000ab  where b is the least significant bit
    GreyState updateCounter(uint8_t thisVal){
        //mask low 2 bits
        thisVal = thisVal & 0b11;
        
        //shift into shiftreg
        mShiftReg = (mShiftReg << 2) | (thisVal);

        //use lookup to get dif
        int8_t dif = kLookupTable[mShiftReg & 0b00001111];  
        mState.sChanged = dif !=0;        
        mState.sCount = mState.sCount + dif;
        return mState;
    }

    

    //A and b given seperatly in this overloaded implimentation, concatenate A and B and feed to the original update function
    GreyState updateCounter(uint8_t a, uint8_t b){
        //thisVal is a 2 bit binary : 000000ab  where b is the least significant bit
        uint8_t thisVal = ((a&0b1) << 1) |  (b & 0b1);                
        return GreyCounter::updateCounter(thisVal);
    }



    //**************************************************************
    // Getters
    //**************************************************************
    bool getChanged(){
        return mState.sChanged;        
    }
    
    long getCount(){
        return mState.sCount;        
    }
    


    //**************************************************************
    // Consturctors
    //**************************************************************
    GreyCounter(){ 
        mShiftReg = 0; //This alone will not ensure an initial count of 0 because the shiftreg is not representative of the actual encoder state
        mState.sChanged = false;    
        mState.sCount = 0;   
    }


    //Used to ensure the starting count is truly 0 by setting the shiftreg properly
    //A and b given seperatly in this overloaded implimentation, concatenate A and B and feed to the original init function
    void initCounter(uint8_t a, uint8_t b){
        //thisVal is a 2 bit binary : 000000ab  where b is the least significant bit
        uint8_t thisVal = ((a&0b1) << 1) |  (b & 0b1);       
        initCounter(thisVal);        
    }

    //Used to ensure the starting count is truly 0 by setting the shiftreg properly
    //thisVal is a 2 bit binary : 000000ab  where b is the least significant bit
    void initCounter(uint8_t thisVal){
        //mask low 2 bits
        thisVal = thisVal & 0b11;        
        //shift into shiftreg
        mShiftReg = (mShiftReg << 2) | (thisVal);
        mState.sChanged = false;    
        mState.sCount = 0;   
    }

    


};// end class definition
