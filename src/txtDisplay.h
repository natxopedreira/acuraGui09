//
//  txtDisplay.h
//  accuraGUI
//
//  Created by Natxo Pedreira gonzalez on 26/11/15.
//
//

#ifndef accuraGUI_txtDisplay_h
#define accuraGUI_txtDisplay_h

class txtDisplay {
public:
    //--------------------------------------------------------------
    void setup(int fontSize){
        fuente.loadFont("DIN Alternate Bold.ttf", fontSize, true, true, true);
        fuente.setLetterSpacing(.82);
        
        actual = 0;
        anterior = 0;

        potencia = 50;

        cambiando = false;
        
        alpha = 0;
        
        actualStr = "00";
        anteriorStr = "00";
        
        
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
        if(actual<10) actualStr = "0"+actualStr;
        
        anteriorStr = ofToString(anterior);
        if(anterior<10) anteriorStr = "0"+anteriorStr;
        
    }
    //--------------------------------------------------------------
    void draw(){

        ofPushStyle();
        // anterior
        ofSetColor(104,105,107,alpha);
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
    void setPotencia(int _potencia){
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
    
    
};

#endif
