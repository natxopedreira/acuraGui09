//
//  barraDial.h
//  accuraGUI
//
//  Created by Natxo Pedreira gonzalez on 25/11/15.
//
//

#ifndef accuraGUI_barraDial_h
#define accuraGUI_barraDial_h

#include "ledGlow.h"

class barraDial {
   
public:
    
    // numero de ladrillos
    //--------------------------------------------------------------
    void setNumeroLadrillos(int d){
        numeroLadrillos = d;
    }
    
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
        int por = ofMap(p, 0, 1, 0, numeroLadrillos);
        potencia = por;
    }
    
    // cargamos las imagenes
    //--------------------------------------------------------------
    void setup(){
        pastilla.loadImage("ladrillo.png");
        pastillaOn.loadImage("ladrilloOn.png");
        pastillaGlow.loadImage("ladrilloGlow.png");
        
        potencia = 0;
        
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
        
    }
    
    //--------------------------------------------------------------
    void update(){
        for (int i = 0; i<numeroLadrillos; i++) {
            if(i < potencia){
                ledsBarra.at(i).enciendete();
            }else{
                ledsBarra.at(i).apagate();
            }
            ledsBarra.at(i).update();
        }
    }
    
    //--------------------------------------------------------------
    void draw(){
        ofPushMatrix();
        ofTranslate(origen.x, origen.y);
        ofScale(scale, scale*-1);
        
        for (int i = 0; i < numeroLadrillos; i++) {
            ofPushMatrix();
            ofTranslate(0, i*20);
            pastilla.draw(0,0);
            ledsBarra.at(i).draw();
            ofPopMatrix();
        }
        
        ofPopMatrix();
    }
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    

    ofImage pastilla, pastillaOn, pastillaGlow;
    
private:
    vector<ledGlow> ledsBarra;
    
    ofPoint origen;
    
    int numeroLadrillos, potencia;
    float scale;
    
    ofColor color;
    
};

#endif
