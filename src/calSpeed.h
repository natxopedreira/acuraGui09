//
//  calSpeed.h
//  acuraGui09
//
//  Created by Natxo Pedreira gonzalez on 1/12/15.
//
//

#ifndef acuraGui09_calSpeed_h
#define acuraGui09_calSpeed_h

class calSpeed {
    float speed, speedDest;
    
public:
    
    calSpeed(){
        speed = 0.0;
        speedDest = 0.0;
    }
    
    void update(){
            if (speed < speedDest) {
                speed = speed +.5;
            }else if(speed > speedDest){
                speed = speed -.25;
            }
        

        
        //cout << "speed " << speed << " // speedDest " << speedDest << endl;
    }
    
    void setDesiredSpeed(float f){
        speedDest = f*100;
    }
    
    float getSpeed(){
        float f = ofMap(speed,0,100,0,1,true);
        return f;
    }
};

#endif
