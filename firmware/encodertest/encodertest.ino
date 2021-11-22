//encoder test based on this resource:
// http://makeatronics.blogspot.com/2013/02/efficiently-reading-quadrature-with.html


#include "grey_counter.h"




const int gA= 3;
const int gB= 4;
GreyCounter gc;




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

    
    //GreyState gs = gc.updateCounter(digitalRead(gA), digitalRead(gB));    
    GreyState gs = gc.updateCounter( (digitalRead(gA)<<1)  | digitalRead(gB) );

    
    if (gs.sChanged){
        Serial.println(gs.sCount);
    }    
    
}
