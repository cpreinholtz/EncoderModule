
#include <Wire.h>
#include <Adafruit_MCP23X17.h>

#include "grey_counter.h"

const int DEFAULT_ADDR = 0x20;
const int kNumReems = 4;
const int kReemAddr[kNumReems] = { 0, 6 , 4, 5};

const int LED_PIN = 13;

//const int kReemAddr[kNumReems] = { 0, 1 ,2, 4, 3,  7, 5};


//const int kReemAddr[8] = { 0, 1 ,2, 4, 3, 6, 7, 5};

Adafruit_MCP23X17 mcp[kNumReems];

//GreyCounter gGreyCounters[CtrlLast];
GreyCounter gGreyCounters[kNumReems *8];


void initMcp(){
    

    
    //Start and set all mcp pins to pullups
    int i,j;           
    for( j = 0; j < kNumReems; j++){
        if (!mcp[j].begin_I2C(DEFAULT_ADDR+kReemAddr[j] )) {
            Serial.println("Error.");
            Serial.println(j);
            Serial.println(DEFAULT_ADDR+kReemAddr[j]);
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
    pinMode(LED_PIN, OUTPUT);
    
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

                if (tCtrlIndex < CtrlLast){
                    gControls[tCtrlIndex].setTick(tTick);
                }
                

                Serial.println("knob Change");
                Serial.println(tCtrlIndex);
                //Serial.println(tTick);

                //analogWrite(LED_PIN, map(tTick,0,);

                

                if (tCtrlIndex < CtrlLast){
                    long val = gControls[tCtrlIndex].getVal();
                    
                    Serial.println(val);                  
                    Serial.println(gControls[tCtrlIndex].getScaled());                    
                        
                    analogWrite(LED_PIN, map(val, 0, 40, 0, 255));
                    
                }

                applyAllVoices();
            }            
        }            
    }
    
}
