//
//  crono.h
//  accuraGUI
//
//  Created by Natxo Pedreira gonzalez on 28/11/15.
//
//

#ifndef accuraGUI_crono_h
#define accuraGUI_crono_h

class crono {
public:
    //--------------------------------------------------------------
    void setup(int fontSize){
        fuente.loadFont("DIN Condensed Bold.ttf", fontSize, true, true, true);
        fuente.setLetterSpacing(.82);
        
        actual = 0;
        anterior = 0;
        
        potencia = 50;
        
        cambiando = false;
        
        alpha = 0;
        
        actualStr = "00";
        anteriorStr = "00";
        
        running = false;
        
        tiempoActual = 0;
    }
    
    //--------------------------------------------------------------
    void update(){
        if(actual != potencia && potencia >=0){
            anterior = actual;
            actual = potencia;
            cambiando = true;
            alpha = 200;
            alphaNew = 200;
            
            
        }else{
            
            if(alpha>150){
                alpha -=5;
                //cout << alpha << endl;
            }
            
            if(alphaNew<230){
                alphaNew +=2;
            }
            
        }
        
        
        
        if(running){
            
            tiempoActual = ofGetElapsedTimeMillis()-tiempoStart;
        }
            int seconds = (int) (tiempoActual / 1000) % 60 ;
            int centesimas = (int) (tiempoActual % 1000) ;
            int minutes = (int) ((tiempoActual / (1000*60)) % 60);
            int hours   = (int) ((tiempoActual / (1000*60*60)) % 24);
        
            string secsString = ofToString(seconds);
            if(secsString.size()<2) secsString = "0"+secsString;
        
            string minutesString = "";
            if(minutes<10){
            
                minutesString = "0"+ofToString(minutes);
            
            }else{
            
                minutesString = ofToString(minutes);
            
            }
        
            string hoursString = ofToString(centesimas);
        if (hoursString.size()<2) {
            hoursString = "00"+hoursString;
        }
        
            actualStr =  minutesString + "::" + secsString + "::" +hoursString;
       
        
       

        
    }
    //--------------------------------------------------------------
    void draw(){
        
        ofPushStyle();
        // anterior
        ofSetColor(colorTxt.r,colorTxt.g,colorTxt.b,alpha);
        
        fuente.drawStringAsShapes(anteriorStr, 10, 230);
        
        
        ofPopStyle();
        
    }
    //--------------------------------------------------------------
    void drawWhite(){
        
        ofPushStyle();
        
        //float largo = fuente.stringWidth(actualStr);
        // nueva
        ofSetColor(colorTxt.r,colorTxt.g,colorTxt.b, 200);
        fuente.drawStringAsShapes(actualStr, 10, 230);
        
        
        ofPopStyle();
        
    }
    
    //--------------------------------------------------------------
    void drawBlur(){
        
        ofPushStyle();
        
        // nueva
        ofSetColor(colorTxt.r,colorTxt.g,colorTxt.b, alphaNew);
        fuente.drawStringAsShapes(actualStr, 10, 230);
        
        ofPopStyle();
        
    }
    
    
    //--------------------------------------------------------------
    void setLap(int _potencia){
        potencia = _potencia;
    }
    
    //--------------------------------------------------------------
    void setColor(ofColor _c){
        colorTxt = _c;
    }
    //--------------------------------------------------------------
    ofColor getColor(){
        return colorTxt;
    }
    
    //--------------------------------------------------------------
    void startTime(){
        tiempoStart = ofGetElapsedTimeMillis();
        running = true;
    }
    
    void stopTimer(){
        tiempoFinish = ofGetElapsedTimeMillis();
        running = false;
    }
    
private:
    long tiempoActual;
    long tiempoStart;
    long tiempoFinish;
    bool running;
    
    ofColor colorTxt;
    ofTrueTypeFont fuente;
    int actual, anterior;
    string actualStr, anteriorStr;
    int potencia;
    int alpha,alphaNew;
    bool cambiando;
    
    
};

#endif
