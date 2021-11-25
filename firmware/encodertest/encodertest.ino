//encoder test based on this resource:
// http://makeatronics.blogspot.com/2013/02/efficiently-reading-quadrature-with.html


#include "grey_counter.h"
#include "time.h"



const int gA= 3;
const int gB= 4;
GreyCounter gc;

Timer knobTimer(100);


void setup() {
    // all your normal setup code

    pinMode(gA,INPUT_PULLUP);
    pinMode(gB,INPUT_PULLUP);
    

    Serial.begin(9600);
    Serial.println("here");



    //gc.initCounter( (digitalRead(gA)<<1)  | digitalRead(gB) );
    gc.initCounter( digitalRead(gA), digitalRead(gB) );

}





void loop()
{


    if (knobTimer.pollAndReset()){
        //GreyState gs = gc.updateCounter(digitalRead(gA), digitalRead(gB));    
        gc.updateCounter( (digitalRead(gA)<<1)  | digitalRead(gB) );
    
        
        if (gc.getChanged()){
            Serial.println(gc.getCount());
        }       
    }
    

    
}
