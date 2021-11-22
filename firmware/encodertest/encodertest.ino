//encoder test based on this resource:
// http://makeatronics.blogspot.com/2013/02/efficiently-reading-quadrature-with.html


//set this to 0 for interupt usage 1 for polling
#define USE_POLLING 0

volatile long enc_count = 0; 



void encoder_isr() {
    static int8_t lookup_table[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
    static uint8_t enc_val = 0;
    
    enc_val = enc_val << 2;
    
    //for this to work, the encoder needs to be on pins 3 and 4
    //PIND is an easy way to read input pins on the arduino, returning the value of pins 0 - 7.  
    //we mask and shiftright to get only pins 3 and 4
    enc_val = enc_val | ((PIND & 0b11000) >> 3);
 
    enc_count = enc_count + lookup_table[enc_val & 0b1111];
    Serial.print("interupt result: ");
    Serial.println(enc_count);

    
}



void encoder_poll(uint8_t thisVal) {
    static int8_t lookup_table[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
    //this really acts as a 
    static uint8_t enc_val = 0;

    //check for change ( this isnt even really necisarry honestly
    
    //if (thisVal != enc_val & 0b11){
    
        
        //shift the last value to the left, add on this val
        enc_val = (enc_val << 2) | (thisVal & 0b011);
        
        //lookup wheather we want +1 -1 +0 based on the last and previous readings
        enc_count = enc_count + lookup_table[enc_val & 0b00001111];
        Serial.print("polling result: ");
        Serial.println(enc_count);

    //}
}




void setup() {
    // all your normal setup code

    pinMode(3,INPUT_PULLUP);
    pinMode(4,INPUT_PULLUP);
    
#if not USE_POLLING
    attachInterrupt(3,encoder_isr,CHANGE);
    attachInterrupt(4,encoder_isr,CHANGE);
#endif

    Serial.begin(9600);
    Serial.println("here");
    
}





void loop()
{
    
#if USE_POLLING

    //for this to work, the encoder needs to be on pins 3 and 4
    //PIND is an easy way to read input pins on the arduino, returning the value of pins 0 - 7.  
    //we mask and shiftright to get only pins 3 and 4
    uint8_t thisVal = ((PIND & 0b11000) >> 3); 
    encoder_poll( thisVal);

    delay(1);
#endif




    
}
