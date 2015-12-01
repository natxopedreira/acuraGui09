//
//  txtCountDown.h
//  accuraGUI
//
//  Created by Natxo Pedreira gonzalez on 28/11/15.
//
//

#ifndef accuraGUI_txtCountDown_h
#define accuraGUI_txtCountDown_h

class txtCountDown {
public:
    //--------------------------------------------------------------
    void setup(int fontSize){
        fuente.loadFont("DIN Alternate Bold.ttf", fontSize, true, true, true);
        fuente.setLetterSpacing(.82);
        
        actual = 0;
        anterior = 0;
        
        potencia = 5;
        
        cambiando = false;
        
        alpha = 0;
        
        actualStr = "0";
        anteriorStr = "0";
        
        lastRead = ofGetElapsedTimeMillis();
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
            
            if(alpha>0){
                alpha -=5;
                //cout << alpha << endl;
            }
            
            if(alphaNew<255){
                alphaNew +=2;
            }
            
        }
        
        
        actualStr = ofToString(actual);
        anteriorStr = ofToString(anterior);
    }
    //--------------------------------------------------------------
    void draw(){
        
        ofPushStyle();
        // anterior
        ofSetColor(104,105,107,alpha);
        fuente.drawStringAsShapes(anteriorStr, 0, 530);
        
        ofPopStyle();
        
    }
    //--------------------------------------------------------------
    void drawWhite(){
        
        ofPushStyle();
        
        //float largo = fuente.stringWidth(actualStr);
        // nueva
        ofSetColor(colorTxt.r,colorTxt.g,colorTxt.b, 200);
        fuente.drawStringAsShapes(actualStr, 0, 530);
        
        
        ofPopStyle();
        
    }
    
    //--------------------------------------------------------------
    void drawBlur(){
        
        ofPushStyle();
        
        // nueva
        ofSetColor(colorTxt.r,colorTxt.g,colorTxt.b, alphaNew);
        fuente.drawStringAsShapes(actualStr, 0, 530);
        
        ofPopStyle();
        
    }
    
    
    //--------------------------------------------------------------
    void setCountDownNumber(int _potencia){
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
    
private:
    ofColor colorTxt;
    ofTrueTypeFont fuente;
    int actual, anterior;
    string actualStr, anteriorStr;
    int potencia;
    int alpha,alphaNew;
    bool cambiando;
    long lastRead;
    
};

#endif
