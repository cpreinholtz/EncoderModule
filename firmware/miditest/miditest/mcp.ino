
#include <Wire.h>
#include <Adafruit_MCP23X17.h>

#include "grey_counter.h"

const int DEFAULT_ADDR = 0x20;
const int kNumReems = 2;

Adafruit_MCP23X17 mcp[kNumReems];

GreyCounter gGreyCounters[CtrlLast];



void initMcp(){

    //Start and set to pullups
    int i,j;   
    for( j = 0; j < kNumReems; j++){
        if (!mcp[j].begin_I2C(DEFAULT_ADDR+j)) {
            Serial.println("Error.");
             Serial.println(j);
            while (1);
        }        
        for( i = 0; i < 16; i++){
            mcp[j].pinMode(i,INPUT_PULLUP);        
        }
    }
    
    initAllKnobs();
        //gc.initCounter( digitalRead(gA), digitalRead(gB) );
}




void initAllKnobs(){
    
    //read all knobs
    int i,j;
    uint16_t tState[kNumReems];    
    for( j = 0; j < kNumReems; j++){        
        tState[j] = (((uint16_t) mcp[j].readGPIO(1)) <<8) | (uint16_t) mcp[j].readGPIO(0) ;        
    }


    //update greycounters
    for( j = 0; j < kNumReems; j++){
                
        for( i = 0; i < 8; i++){                         
            uint8_t a = tState[j] & 0x01;
            tState[j] = tState[j] >>1;
            uint8_t b = tState[j] & 0x01;
            tState[j] = tState[j] >>1;

            int tCtrlIndex = j*8+i;

            gGreyCounters[tCtrlIndex].initCounter(a,b);
         
        }            
    }
    
}








void getKnobs(){
    
    //read all knobs
    int i,j;
    uint16_t tState[kNumReems];    
    for( j = 0; j < kNumReems; j++){        
        tState[j] = (((uint16_t) mcp[j].readGPIO(1)) <<8) | (uint16_t) mcp[j].readGPIO(0) ;        
    }


    //update greycounters
    for( j = 0; j < kNumReems; j++){
                
        for( i = 0; i < 8; i++){                         
            uint8_t a = tState[j] & 0x01;
            tState[j] = tState[j] >>1;
            uint8_t b = tState[j] & 0x01;
            tState[j] = tState[j] >>1;

            int tCtrlIndex = j*8+i;

            gGreyCounters[tCtrlIndex].updateCounter(a,b);
            if (gGreyCounters[tCtrlIndex].getChanged( )) {
                

                long tTick = gGreyCounters[tCtrlIndex].getCount();                
                gControls[tCtrlIndex].setTick(tTick);

                Serial.println("knob Change");
                Serial.println(tCtrlIndex);
                Serial.println(tTick);
                Serial.println(gControls[tCtrlIndex].getVal());
                Serial.println(gControls[tCtrlIndex].getScaled());

                appllyAll();
            }            
        }            
    }
    
}
