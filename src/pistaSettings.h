//
//  pistaSettings.h
//  acuraGui09
//
//  Created by Natxo Pedreira gonzalez on 30/11/15.
//
//

#ifndef acuraGui09_pistaSettings_h
#define acuraGui09_pistaSettings_h

#include "ofxDatGui.h"
#include "ofxXmlSettings.h"

class pistaSettings {
    ofxDatGui* gui;
    
    int velocidadMax;
    int velocidadMin;
    int interactionIndex;
    int leapMax;
    int talloMax;
    int talloMin;
    
    string estadoJuego;
    
    vector<string> optsJuego;
    vector<string> intModes;
    
    ofxXmlSettings settings;
    
public:
    //--------------------------------------------------------------
    void setup(){
        if(settings.loadFile("settings.xml")){
            velocidadMax = settings.getValue("properties:velocidadMax",255);
            velocidadMin = settings.getValue("properties:velocidadMin",0);
            interactionIndex = settings.getValue("properties:modo_interaccion",0);
            leapMax = settings.getValue("properties:leapMax",0);
            talloMax = settings.getValue("properties:talloMax",0);
            talloMin = settings.getValue("properties:talloMin",0);
        }
        
        
        gui = new ofxDatGui(100, 100);
        gui->addFRM();
        gui->addBreak();
        
        // velocidad Maxima
        gui->addSlider("max speed", 0, 255, velocidadMax);
        gui->getSlider("max speed")->setPrecision(0);
        
        // velocida dMinima
        gui->addSlider("min speed", 0, 255, velocidadMin);
        gui->getSlider("min speed")->setPrecision(0);
        
        // simular Velocidad
        gui->addSlider("speed",velocidadMin, velocidadMax, 0);
        gui->getSlider("speed")->setPrecision(0);
        
        gui->addBreak();
        
        // si queremos o no enviar la data del gui
        gui->addToggle("enviar data");
        
        gui->addToggle("pista conectada",false);
        gui->addToggle("pista activada",false);
        
        optsJuego = {"GAME NEWGAME", "GAME COUNTDOWN", "GAME RUNNING", "GAME FINISHED"};
        
        gui->addBreak();
        
        gui->addTextInput("estado del juego", "game status");
        
        intModes = {"INTERACTION MINDWAVE", "INTERACTION LEAP MOTION", "INTERACTION ACCELEROMETER"};
        gui->addDropdown("modo interaccion", intModes);
        gui->getDropdown("modo interaccion")->select(interactionIndex);
        
        gui->addBreak();
        
        ////// mindwave
        gui->addToggle("attention + meditation",false);
        gui->addBreak();
        
        // leap motion
        gui->addSlider("leap distance max", 0, 500, leapMax);
        gui->getSlider("leap distance max")->setPrecision(0);
        
        // accelerometer
        gui->addSlider("tallo max", -180, 180, talloMax);
        gui->getSlider("tallo max")->setPrecision(0);
        
        gui->addSlider("tallo min", -180, 180, talloMin);
        gui->getSlider("tallo min")->setPrecision(0);
        
        
        gui->addBreak();
        gui->addMatrix("laps", 10, true);
        
        gui->addBreak();
        
        gui->addButton("save data");
        
        gui->addBreak();
        
        gui->addHeader(":: ajustes para la pista ::");
        
        gui->addFooter();
        
        //
        gui->onSliderEvent(this, &pistaSettings::onSliderEvent);
        gui->onButtonEvent(this, &pistaSettings::onButtonEvent);
        gui->onDropdownEvent(this, &pistaSettings::onDropdownEvent);
        gui->onMatrixEvent(this, &pistaSettings::onMatrixEvent);
        
    }
    
    //--------------------------------------------------------------
    void onMatrixEvent(ofxDatGuiMatrixEvent e)
    {
        //cout << "onMatrixEvent " << e.child << " : " << e.enabled << endl;
        //cout << "onMatrixEvent " << e.target->getLabel() << " : " << e.target->getSelected().size() << endl;
    }

    
    //--------------------------------------------------------------
    void onSliderEvent(ofxDatGuiSliderEvent e){
        
        if (e.target->is("max speed")){
            velocidadMax = e.target->getValue();
            settings.setValue("properties:velocidadMax", (int)velocidadMax);
        }
        
        if (e.target->is("min speed")){
            velocidadMin = e.target->getValue();
            settings.setValue("properties:velocidadMin", (int)velocidadMin);
        }
        
        if(e.target->is("leap distance max")){
            leapMax = e.target->getValue();
            settings.setValue("properties:leapMax", (int)leapMax);
        }
        
        if(e.target->is("tallo max")){
            talloMax = e.target->getValue();
            cout << talloMax << endl;
            settings.setValue("properties:talloMax", (int)talloMax);
        }
        
        if(e.target->is("tallo min")){
            talloMin = e.target->getValue();
            settings.setValue("properties:talloMin", (int)talloMin);
        }
    }
    
    //--------------------------------------------------------------
    void onButtonEvent(ofxDatGuiButtonEvent e){
        if (e.target->is("save data")) settings.saveFile();
    }
    
    //--------------------------------------------------------------
    void onDropdownEvent(ofxDatGuiDropdownEvent e)
    {
        if (e.target->is("modo interaccion")){
            settings.setValue("properties:modo_interaccion", e.child);
        }
        
        //cout << "onDropdownEvent: " << e.target->getLabel() << " Selected" << endl;
    }
    
    //--------------------------------------------------------------
    int getVelocidadMaxima(){
        return velocidadMax;
    }
    
    //--------------------------------------------------------------
    int getVelocidadMinima(){
        return velocidadMin;
    }
    
    //--------------------------------------------------------------
    bool getSendData(){
        return gui->getButton("enviar data")->getEnabled();
    }
    
    //--------------------------------------------------------------
    float getSpeedNorm(){
        return gui->getSlider("speed")->getScale();
    }
    
    //--------------------------------------------------------------
    int getLeapMax(){
        return leapMax;
    }
    
    //--------------------------------------------------------------
    int getTalloMax(){
        return talloMax;
    }
    
    //--------------------------------------------------------------
    int getTalloMin(){
        return talloMin;
    }
    
    //--------------------------------------------------------------
    string getInteractionMode(){
        //
        return gui->getDropdown("modo interaccion")->getLabel();
    }
    
    //--------------------------------------------------------------
    bool getAttentionPlusMeditation(){
        return gui->getButton("attention + meditation")->getEnabled();
    }
    
    // SETTERS
    //--------------------------------------------------------------
    void setLaps(int b){
        gui->getMatrix("laps")->getChildAt(b)->setSelected(true);
    }
    //--------------------------------------------------------------
    void setGameStatus(int b){
        //
        
        gui->getTextInput("estado del juego")->setText(optsJuego.at(b));
    }
    //--------------------------------------------------------------
    void setPistaConectada(bool b){
        gui->getButton("pista conectada")->setEnabled(b);
    }
    //--------------------------------------------------------------
    void setPistaActivada(bool b){
        gui->getButton("pista activada")->setEnabled(b);
    }
};
#endif
