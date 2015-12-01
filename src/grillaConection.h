//
//  grillaConection.h
//  accuraGUI
//
//  Created by Natxo Pedreira gonzalez on 27/11/15.
//
//

#ifndef accuraGUI_grillaConection_h
#define accuraGUI_grillaConection_h

#include "ledGlow.h"
#include "txtDisplay.h"
#include "ofxBlur.h"

class grillaConection {
    
public:
    
    
    // escala para dibujar
    //--------------------------------------------------------------
    void setScale(float d){
        scale = d;
    }
    
    // origen de la barra
    //--------------------------------------------------------------
    void setOrigen(ofPoint d){
        origen = d;
    }
    
    // color para las casillas
    //--------------------------------------------------------------
    void setColor(ofColor d){
        color = d;
    }
    
    // ajusta la potencia
    //--------------------------------------------------------------
    void setPotencia(float p){
        potencia = p;
    }
    //--------------------------------------------------------------
    void setBlur(bool c){
        enableBlur = c;
    }
    
    // cargamos las imagenes
    //--------------------------------------------------------------
    void setup(){
        pastilla.loadImage("ladrillo.png");
        pastillaOn.loadImage("ladrilloOn.png");
        pastillaGlow.loadImage("ladrilloGlow.png");
        
        potencia = 0;
        
        numeroLadrillos = 45;
        
        for (int i = 0; i < numeroLadrillos; i++) {
            
            //int f = ((float)i / (float)numeroLadrillos)*6;
            //color.setSaturation(color.getSaturation()-f);
            
            ledGlow led;
            led.pastillaLuz = &pastillaGlow;
            led.pastillaOn = &pastillaOn;
            led.colorPastilla = color;
            
            led.setup();
            
            ledsBarra.push_back(led);
        }
        
        // texto
        speedText.setup(230);
        speedText.setColor(ofColor(255,255,255));
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
    void update(){
        
        int potmap = ofMap(potencia, 0, 1, 0, numeroLadrillos);
        int potPercent = ofMap(potencia, 0, 1, 0, 100);
        
        for (int i = 0; i<numeroLadrillos; i++) {
            
            if(i < potmap){
                ledsBarra.at(i).enciendete();
            }else{
                ledsBarra.at(i).apagate();
            }
            ledsBarra.at(i).update();
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
    
    //--------------------------------------------------------------
    void draw(){
        ofPushMatrix();
        ofTranslate(origen.x, origen.y);
        
        ofPushMatrix();
        ofTranslate(325, -262);
        ofScale(.19, .19);
        speedText.draw();
        speedText.drawBlur();
        
        if(enableBlur){
            drawVelocidadTextBlur();
        }
        ofPopMatrix();
        
        
        ofScale(scale, scale*-1);
        
        //numeroLadrillos = 14+12+10+8+6;
        
        for (int i = 0; i < numeroLadrillos; i++) {
            
            ofPushMatrix();
            
            if(i>0 && i<=12){
                ofTranslate(0, i*20 );
                
            }else if (i>12 && i<=23){
                ofTranslate(80, ((i-14)*20) + 20);
                
            }else if (i>23 && i<=32){
                ofTranslate(160, ((i-14)*20) - 200);
                
            }else if (i>32 && i<=39){
                ofTranslate(240, ((i-14)*20) - 380);
                
            }else if (i>39 && i<=44){
                ofTranslate(320, ((i-14)*20) - 520);
            }else if (i>45){
                ofTranslate(100, i*20);
            }
            
            pastilla.draw(0,0);
            ledsBarra.at(i).draw();
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
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    txtDisplay speedText;
    
    ofImage pastilla, pastillaOn, pastillaGlow;
    
private:
    bool enableBlur;
    ofxBlur blur;
    ofFbo areaTexto;
    vector<ledGlow> ledsBarra;
    
    ofPoint origen;
    
    int potPercent;
    int numeroLadrillos;
    float scale;
    float potencia;
    ofColor color;
    
};


#endif
