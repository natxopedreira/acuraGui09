//
//  ledGlow.h
//  accuraGUI
//
//  Created by Natxo Pedreira gonzalez on 25/11/15.
//
//

#ifndef accuraGUI_ledGlow_h
#define accuraGUI_ledGlow_h

#include "ofMain.h"

class ledGlow {
    
public:
    
    //--------------------------------------------------------------
    void setup(){
        encendido = true;
        p = 0;
    }
    
    //--------------------------------------------------------------
    void update(){
        if (encendido) {
            if(p<10)p++;
        }else{
            if(p>0)p--;
        }
    }
    
    //--------------------------------------------------------------
    void apagate(){
        encendido = false;
    }
    
    //--------------------------------------------------------------
    void enciendete(){
        encendido = true;
    }
    
    //--------------------------------------------------------------
    void draw(){

            ofPushStyle();
            int alpha = ofMap(p, 4, 10, 0, 255);
            int luz = ofMap(p, 0, 3, 0, 255);
            ofSetColor(colorPastilla.r,colorPastilla.g,colorPastilla.b,luz);
            pastillaLuz->draw(0,0);
            ofSetColor(colorPastilla.r,colorPastilla.g,colorPastilla.b,alpha);
            pastillaOn->draw(0,0);
            
            ofPopStyle();

    }
    
    //--------------------------------------------------------------
    ofColor colorPastilla;
    
    bool encendido;
    int p;
    
    ofImage * pastillaOn;
    ofImage *  pastillaLuz;
};

#endif
