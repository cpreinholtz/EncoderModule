
#include <Wire.h>
#include <Adafruit_MCP23X17.h>




Adafruit_MCP23X17 mcp;

#define CS_PIN 19

//#define DEFAULT_ADDR 0x

const int DEFAULT_ADDR = 0x40;

void initMcp(){

    
    //pinMode(19,INPUT_PULLUP);    
    //pinMode(18,INPUT_PULLUP);   
    
    //Wire.begin();             // join i2c bus (address optional for master)

    Serial.println(MCP23XXX_ADDR,HEX);
    // uncomment appropriate mcp.begin
    if (!mcp.begin_I2C()) {
        Serial.println("Error.");
        while (1);
    }

    int i;
    for( i = 0; i < 16; i++){
        mcp.pinMode(i,INPUT_PULLUP);        
    }
    
}



void getKnobs(){
    
    Serial.println("getting knobs");
    int i;
    for( i = 0; i < 2; i++){
        Serial.println(mcp.readGPIO(i), BIN);        
    }    
    
}
