//
//  esferaDial.h
//  accuraGUI
//
//  Created by Natxo Pedreira gonzalez on 25/11/15.
//
//

#ifndef accuraGUI_esferaDial_h
#define accuraGUI_esferaDial_h

#include "ledGlow.h"

#include "txtDisplay.h"
#include "ofxBlur.h"

class esferaDial {
public:
    
    //// setea el origen de la esfera
    //--------------------------------------------------------------
    void setOrigenEsfera(ofPoint p){
        origenEsfera = p;
    }
    
    //// setea el punto de rotacion de la imagen de la casilla
    //--------------------------------------------------------------
    void setImgPivotPoint(ofPoint p){
        imgPivotPoint = p;
    }
    
    //// setea el punto de origen de las lineas
    //--------------------------------------------------------------
    void setLineaOrPoint(ofPoint p){
        lineaOrPoint = p;
    }
    
    //// setea el punto final de las lineas
    //--------------------------------------------------------------
    void setLineaFinPoint(ofPoint p){
        lineaFinPoint = p;
    }
    
    //// setea la escala de la esfera
    //--------------------------------------------------------------
    void setScale(float f){
        esferaScale = f;
    }
    
    //// setea el numero de pastillas en una esfera
    //--------------------------------------------------------------
    void setNumPastillas(int n){
        numeroPastillasEsfera = n;
    }
    
    //// setea el numero de grados en la esfera
    //--------------------------------------------------------------
    void setGradosDial(int n){
        gradosDial = n;
    }
    
    //// setea el origen y fin de la linea
    //--------------------------------------------------------------
    void setLineaOrFin(int o, int f){
        lineaOr = o;
        lineaFin = f;
    }
    
    // pones el color a la pastilla
    //--------------------------------------------------------------
    void setPastillaColor(ofColor c){
        color = c;
    }
    
    //--------------------------------------------------------------
    void setFontScale(int c){
        fontScale = c;
    }
    
    //--------------------------------------------------------------
    void setBlur(bool c){
        enableBlur = c;
    }
    
    /// carga la imagen para la esfera
    //--------------------------------------------------------------
    void setup(){
        
        potencia = 0;
        
        if(numeroPastillasEsfera==0)numeroPastillasEsfera = 35;
        if(gradosDial==0)gradosDial = 320;
        
        fontScale = 1.1;
        
        lineaOr = 355;
        lineaFin = 100;
        
        lineaOrPoint.set(355,0);
        lineaFinPoint.set(100,18);
        
        rotationInicial = 87;
        desfaseLineasRotacion = 5.5;
        
        pastilla.loadImage("pastilla.png");
        pastilla.setAnchorPoint(imgPivotPoint.x, imgPivotPoint.y);
        
        pastillaOn.loadImage("pastillaOnBlanca.png");
        pastillaOn.setAnchorPoint(imgPivotPoint.x+3, imgPivotPoint.y+3);
        
        pastillaLuz.loadImage("pastillaLuzBlanca.png");
        pastillaLuz.setAnchorPoint(imgPivotPoint.x+3, imgPivotPoint.y+3);
        
        //color.setSaturation(color.getSaturation()+numeroPastillasEsfera);
        
        for (int i = 0; i<numeroPastillasEsfera; i++) {
            
            //int f = ((float)i / (float)numeroPastillasEsfera)*4;
            //color.setSaturation(color.getSaturation()+f);
            
            //int f = ((float)i / (float)numeroPastillasEsfera)*6;
            //color.setSaturation(color.getSaturation()-f);
            
            ledGlow led;
            led.pastillaLuz = &pastillaLuz;
            led.pastillaOn = &pastillaOn;
            led.colorPastilla = color;
            led.setup();
            
            ledsEsfera.push_back(led);
        }

        // texto
        speedText.setup(230);
        speedText.setColor(ofColor(130,255,222));
        
        if(enableBlur){
            // filtro blur
            blur.setup(320, 240, 6, .2, 2);
        
            // fbo para el blur del texto
            areaTexto.allocate(320,240);
            areaTexto.begin();
            ofClear(color.r,color.g,color.b);
            areaTexto.end();
        }
    }
    
    //--------------------------------------------------------------
    void setPotencia(int p){
        potencia = p;
    }
    //--------------------------------------------------------------
    void setPotenciaNorm(float p){
        int potNorm = ofMap(p, 0, 1, 0, numeroPastillasEsfera);
        potPercent =  ofMap(p, 0, 1, 0, 99);
        potencia = potNorm;
    }
    //--------------------------------------------------------------
    void update(){
        
        for (int i = 0; i<numeroPastillasEsfera; i++) {
            if(i < potencia){
                
                ledsEsfera.at(i).enciendete();
            }else{
                ledsEsfera.at(i).apagate();
            }
            
            ledsEsfera.at(i).update();
        }
        
        // texto con la velocidad
        speedText.setPotencia(potPercent);
        speedText.update();
        
        if(enableBlur){
            areaTexto.begin();
            ofClear(color.r,color.g,color.b);
            speedText.drawBlur();
            areaTexto.end();
        }
    }
    
    // dibuja la esfera
    //--------------------------------------------------------------
    void draw(ofPoint _origenEsfera){
        ofPushMatrix();
        
        // posicion origen de la esfera
        //ofTranslate(origenEsfera);
        ofTranslate(_origenEsfera);
        
        // escala pa la esfera
        ofScale(esferaScale, esferaScale);
        
        
        
        ofPushMatrix();
        ofTranslate(-155, -140);
        ofScale(fontScale, fontScale);
        speedText.draw();
        speedText.drawBlur();
        if(enableBlur){
            drawVelocidadTextBlur();
        }
        ofPopMatrix();
        
        
        
            
        float gradosStep = gradosDial/numeroPastillasEsfera;
        
        
        
        /// lineas dial
        
        ofPushStyle();
        ofSetColor(140, 140, 140);
        
        for (int j = 0; j < numeroPastillasEsfera; j++) {
            ofPushMatrix();
            // rotacion inicial de la esfera
            ofRotate(rotationInicial + desfaseLineasRotacion);
            
            ofRotate(j*gradosStep);
            
            
            if(j%2==0){
                ofRect(lineaOrPoint.x-40, lineaOrPoint.y+2, lineaFinPoint.x+80, lineaOrPoint.y+2);
            }else{
                ofRect(lineaOrPoint.x, lineaOrPoint.y+2, lineaFinPoint.x, lineaOrPoint.y+2);
            }
            
            ofPopMatrix();
        }
        ofPopStyle();
        
        
        
        // rotacion inicial de la esfera
        ofRotate(rotationInicial*-1);
        
        //cout << "numeroPastillasEsfera:: " << numeroPastillasEsfera << endl;
        //cout << "gradosDial:: " << gradosDial << endl;
        /// pastillas dial
        for (int i = 0; i < numeroPastillasEsfera; i++) {
            ofPushMatrix();
            ofRotate(i*(gradosStep));
            //cout << "i*(gradosStep):: " << i*(gradosStep) << endl;
            
            pastilla.draw(0,0);
            
            ledsEsfera.at(i).draw();
            ofPopMatrix();
        }
        
        
        
        
        
        ofPopMatrix();
        
        
    }
    
    // dibuja la esfera
    //--------------------------------------------------------------
    void drawSinTexto(ofPoint _origenEsfera){
        ofPushMatrix();
        
        // posicion origen de la esfera
        //ofTranslate(origenEsfera);
        ofTranslate(_origenEsfera);
        
        // escala pa la esfera
        ofScale(esferaScale, esferaScale);
        ofEnableAlphaBlending();
        
        float gradosStep = gradosDial/numeroPastillasEsfera;
        
        
        
        /// lineas dial
        
        ofPushStyle();
        ofSetColor(140, 140, 140);
        
        for (int j = 0; j < numeroPastillasEsfera; j++) {
            ofPushMatrix();
            // rotacion inicial de la esfera
            ofRotate(rotationInicial + desfaseLineasRotacion);
            
            ofRotate(j*gradosStep);
            
            
            if(j%2==0){
                ofRect(lineaOrPoint.x-40, lineaOrPoint.y+2, lineaFinPoint.x+80, lineaOrPoint.y+2);
            }else{
                ofRect(lineaOrPoint.x, lineaOrPoint.y+2, lineaFinPoint.x, lineaOrPoint.y+2);
            }
            
            ofPopMatrix();
        }
        ofPopStyle();
        
        
        
        // rotacion inicial de la esfera
        ofRotate(rotationInicial*-1);
        
        //cout << "numeroPastillasEsfera:: " << numeroPastillasEsfera << endl;
        //cout << "gradosDial:: " << gradosDial << endl;
        /// pastillas dial
        for (int i = 0; i < numeroPastillasEsfera; i++) {
            ofPushMatrix();
            ofRotate(i*(gradosStep));
            //cout << "i*(gradosStep):: " << i*(gradosStep) << endl;
            
            pastilla.draw(0,0);
            
            ledsEsfera.at(i).draw();
            ofPopMatrix();
        }
        
        
        
        
        
        ofPopMatrix();
        
        
    }
    
    
    //--------------------------------------------------------------
    void drawVelocidadTextBlur(){
        
        speedText.draw();
        
        speedText.drawWhite();
        
        blur.begin();
        ofClear(color.r,color.g,color.b);
        ofEnableAlphaBlending();
        areaTexto.draw(0, 0);
        ofDisableAlphaBlending();
        blur.end();
        
        ofEnableAlphaBlending();
        blur.draw();
        
    }
    
    //--------------------------------------------------------------
    int rotationInicial;
    float desfaseLineasRotacion,fontScale;
    
    txtDisplay speedText;

    //--------------------------------------------------------------
    //--------------------------------------------------------------
private:
    bool enableBlur;
    ofxBlur blur;
    
    ofFbo areaTexto;
    
    vector<ledGlow> ledsEsfera;
    
    ofImage pastilla, pastillaOn, pastillaLuz;
    
    ofPoint origenEsfera;
    ofPoint imgPivotPoint;
    ofPoint lineaOrPoint, lineaFinPoint;
    
    ofColor color;
    
    float esferaScale;
    
    
    int potPercent;
    int numeroPastillasEsfera;
    int gradosDial;
    int potencia;
    int lineaOr, lineaFin;
    
};

#endif
