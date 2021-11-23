
class Voice
{
    
private:
    //**************************************************************
    // members
    //**************************************************************
    bool mVel;
    byte mNote;
    unsigned long long mSetTime;
    
    void startVoice(){
        //todo, hit the oscilators and envelopes now   
    }
    
    void stopVoice(){
        //todo, hit the oscilators and envelopes now
    }

public:

    //**************************************************************
    // constructors
    //**************************************************************
    Voice(){
        clear();
        mSetTime = 0;
    }

    //**************************************************************
    // setters
    //**************************************************************
    void set(byte note, byte vel){
        mVel = vel;
        mNote = note;
        mSetTime = millis();
        if (vel >0){
            startVoice();
        } else {
            stopVoice();
        }        
    }

    void clear(){
        mVel = 0;
        stopVoice();
    }    
    
    //**************************************************************
    // getters
    //**************************************************************
    byte getVel(){
        return mVel;
    }    
    byte getNote(){
        return mNote;
    }    
    unsigned long long getTime(){
        return mSetTime;
    }  
};





class Voices
{
    
private:

    //**************************************************************
    // members
    //**************************************************************
    static const int kNumVoices = 3; 
    int mNextVoice;
    Voice mVoices [kNumVoices];

    
    
    //**************************************************************
    // arbitration
    //**************************************************************
    void pickNext(){
        int i;    
        unsigned long long lowestTime = millis();        
        for (i=0; i<kNumVoices ; i++){

            //pick the first one not in use by default, returns immidiatly
            if (mVoices[i].getVel() <= 0 ){
                mNextVoice = i;
                return;
            }

            //otherwise pick the one that started the earlist
            if (mVoices[i].getTime() <= lowestTime ){
                mNextVoice = i;
                lowestTime = mVoices[i].getTime();
            }
            
        }  
    }




public:


    //**************************************************************
    // constructors
    //**************************************************************
    Voices(){
        clear();        
    }

    
    //**************************************************************
    // setters
    //**************************************************************
    void set(byte note, byte vel){

        if (vel <= 0 ){
            Serial.println("unset caught");
            Serial.println(note);
            
            unset(note);
        } else {

            //check if the note is already being played, only really an issue if using sequencer or multiple keyboards for some reason
            int i;                 
            for (i=0; i<kNumVoices ; i++){           
                if (mVoices[i].getVel() > 0  and mVoices[i].getNote() == note) {
                    Serial.println("repeat");
                    return;
                }
            }
            
            mVoices[mNextVoice].set(note,vel);
            pickNext(); 
        }    
    }

    void unset(byte note){
        int i;
        for (i=0; i<kNumVoices ; i++){
            if (mVoices[i].getNote() == note){
                mVoices[i].clear();
                //Serial.println("clearing");
                //Serial.println(i);
                pickNext();
            }
        }
    }

    void clear(){
        mNextVoice = 0;
        int i;
        for (i=0; i<kNumVoices ; i++){
            mVoices[i].clear();
        }
    }

    //**************************************************************
    // getters
    //**************************************************************
    int getNumVoices(){
        return kNumVoices;
    }

    void dbg(){
        Serial.println("voicelist");
        int i;
        for (i = 0 ; i<kNumVoices; i++){
            if (mVoices[i].getVel() <= 0 ) {
                Serial.print("X");
            } else {
               Serial.print(mVoices[i].getNote()); 
            }            
            Serial.print("\t");
        }
        Serial.println("");
    }
    

};
