//
//  guiScreen.cpp
//  accuraGUI
//
//  Created by Natxo Pedreira gonzalez on 28/11/15.
//
//

#include "guiScreen.h"

//--------------------------------------------------------------
void guiScreen::startCrono(){
    cronometro.startTime();
}

//--------------------------------------------------------------
void guiScreen::stopCrono(){
    cronometro.stopTimer();
}


//--------------------------------------------------------------
void guiScreen::setLapCounter(int c){
    laps = c;
}

//--------------------------------------------------------------
void guiScreen::setAtencionTxt(string f){
    esferaAtencionTxt = f;
}

//--------------------------------------------------------------
void guiScreen::setMeditacionTxt(string f){
    esferaMeditacionTxt = f;
}

//--------------------------------------------------------------
void guiScreen::setBarraConectionTxt(string f){
    barraConectionTxt = f;
}



//--------------------------------------------------------------
void guiScreen::setVelocidadPower(float f){
    velocidadEsferaPower = f;
}

//--------------------------------------------------------------
void guiScreen::setMeditacionPower(float f){
    meditacionEsferaPower = f;
}

//--------------------------------------------------------------
void guiScreen::setAtencionPower(float f){
    atencionEsferaPower = f;
}

//--------------------------------------------------------------
void guiScreen::setBarraPower(float f){
    powerBarra = f;
}

//--------------------------------------------------------------
void guiScreen::setConectionPower(float f){
    conectionBarraPower = f;
}

//--------------------------------------------------------------
void guiScreen::newGame(){
    //estadoJuego = NEWGAME;
    winner = false;
    //cronometro.startTime();
}

//--------------------------------------------------------------
void guiScreen::finishGame(){
    estadoJuego = FINISHED;
}

void guiScreen::setGameStatus(gameStatus g){
    estadoJuego = g;
}
gameStatus guiScreen::getGameStatus(){
    return estadoJuego;
}

int guiScreen::getnumLaps(){
    return cuentaVueltas.getLap();
}
//--------------------------------------------------------------
void guiScreen::setup(){
    
    winner = false;
    
    setupEsferas();
    
    cronometro.setup(108);
    cronometro.setColor(ofColor(106,106,106));
    
    
    backgroundImage.load("pantalla.png");
    banda.load("barra.png");
    fondoGris.load("fondoGris.png");
    
    fuenteMediana.load("HelveticaNeue-CondensedBold.ttf", 20, true, true, true);
    fuentePorciento.load("HelveticaNeue-CondensedBold.ttf", 83, true, true, true);
    
    fuenteWinner.load("HelveticaNeue-CondensedBold.ttf", 120, true, true, true);
    
    estadoJuego = NEWGAME;
    
    countDown.setup();
}

//--------------------------------------------------------------
void guiScreen::update(){
    
    if (estadoJuego == RUNNING || estadoJuego == NEWGAME) {
        // indicador de velocidad
        esferaVelocidad.setPotenciaNorm(velocidadEsferaPower);
        
    }else{
        // indicador de velocidad
        esferaVelocidad.setPotenciaNorm(0);
        
    }
    
    // indicador de meditacion
    esferaMeditacion.setPotenciaNorm(meditacionEsferaPower);
    
    // indicador de atencion
    esferaAtencion.setPotenciaNorm(atencionEsferaPower);
    
    // barra de power
    barraPower.setPotencia(powerBarra);
    
    // barra de conection
    barraConnection.setPotencia(conectionBarraPower);
    
    //
    esferaVelocidad.update();
    esferaMeditacion.update();
    esferaAtencion.update();
    barraPower.update();
    barraConnection.update();
    
    // cuentavueltas
    cuentaVueltas.setLap(laps);
    cuentaVueltas.update();
    
    //
    cronometro.update();
    
    //
    countDown.update();
}

//--------------------------------------------------------------
void guiScreen::draw(){
    
    //backgroundImage.draw(0, 0);
    
    ofSetColor(140, 140, 140);
    
    /////////////////////////
    ////// lineas ///////////
    /////////////////////////
    ofRect(1100, 540, 1920, 2);
    ofRect(1570, 540, 2, 500);
    ofRect(1630, 540, 2, -500);
    
    ofSetColor(255,255, 255, 255);
    
    
    //// barra con mind icono
    ofPushMatrix();
    ofTranslate(125, 1080);
    ofRotate(-90);
    banda.draw(0, 0);
    ofPopMatrix();
    
    
    /////////////////////////
    // cuentavueltas //
    /////////////////////////
    
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    
    ofPushMatrix();
    ofTranslate(190, 380);
    ofRotate(-90);
    cuentaVueltas.draw();
    cuentaVueltas.drawBlur();
    
    ofDisableBlendMode();
    ofSetColor(130,255,222,200);
    ofScale(1.4,1.4);
    fuenteMediana.drawStringAsShapes("LAP NUMBER", 70, 30);
    ofSetColor(255,255,255,255);
    ofPopMatrix();
    
    
    /////////////////////////
    // cronometro //
    /////////////////////////
    ofPushMatrix();
    
    ofTranslate(1550, 515);
    ofRotate(-90);
    //cronometro.draw();
    cronometro.drawBlur();
    ofPopMatrix();
    
    
    /////////////////////////
    // esfera de velocidad //
    /////////////////////////
    ofPushMatrix();
    ofTranslate(845, 540);
    ofRotate(-90);
    
    
    if (estadoJuego == RUNNING || estadoJuego == NEWGAME) {
        esferaVelocidad.draw(ofPoint(0,0));
        
        ofPushStyle();
        ofSetColor(140, 140, 140);
        fuentePorciento.drawStringAsShapes("%",-44, 240);
        ofPopStyle();
        
    }else{
        esferaVelocidad.drawSinTexto(ofPoint(0,0));
        
        if (estadoJuego == FINISHED) {
            // se acabo el juego pinta si ganaste o perdise

            fuenteWinner.drawString("YOU", -120, -50);
            fuenteWinner.drawString("LOSE", -150, 100);
            
            
        }else if (estadoJuego == COUNTDOWN){
            // pintas la cuenta atras
            countDown.draw();
        }
    }
    
    
    //esferaVelocidad.draw(ofPoint(0,0));
    

    
    ofPopMatrix();
    
    ////////////////////////
    // esfera de atencion //
    ////////////////////////
    ofPushMatrix();
    ofTranslate(1455, 697);
    ofRotate(-90);
    esferaAtencion.draw(ofPoint(0,0));
    
    ofSetColor(130,255,222);
    fuenteMediana.drawStringAsShapes(esferaAtencionTxt, -62, -115);
    ofSetColor(255,255, 255);
    ofPopMatrix();
    
    //////////////////////////
    // esfera de meditacion //
    //////////////////////////
    ofPushMatrix();
    ofTranslate(1720, 697);
    ofRotate(-90);
    esferaMeditacion.draw(ofPoint(0,0));
    
    ofSetColor(130,255,222);
    fuenteMediana.drawStringAsShapes(esferaMeditacionTxt, -68, -115);
    ofSetColor(255,255, 255);
    ofPopMatrix();
    
    ////////////////////
    // barra de power //
    ////////////////////
    ofPushMatrix();
    ofTranslate(1005, 937);
    ofRotate(-90);
    barraPower.draw();
    ofPopMatrix();
    
    /////////////////////////
    // barra de connection //
    /////////////////////////
    ofPushMatrix();
    ofTranslate(1580, 510);
    ofRotate(-90);
    barraConnection.draw();
    
    ofSetColor(130,255,222);
    fuenteMediana.drawStringAsShapes(barraConectionTxt, 88, -240);
    ofSetColor(255,255, 255);
    ofPopMatrix();
    
    
    /////////////////////////////
    // mini % para las esferas //
    /////////////////////////////
    ofPushMatrix();
    ofTranslate(1510, 710);
    ofRotate(-90);
    ofScale(1.1,1.1);
    fuenteMediana.drawStringAsShapes("%", 0, 0);
    fuenteMediana.drawStringAsShapes("%", 492, -100);
    fuenteMediana.drawStringAsShapes("%", 0, 240);
    ofPopMatrix();
    
    
    //////////////////////////////////////
    // imagen con los bordes sombreados //
    //////////////////////////////////////
    ofPushStyle();
    
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    fondoGris.draw(0, 0);
    ofDisableBlendMode();
    
    ofPopStyle();
}

//--------------------------------------------------------------
void guiScreen::setupEsferas(){
    
    // cuenta vueltas
    cuentaVueltas.setup(440);
    cuentaVueltas.setColor(ofColor(128, 128, 128));
    
    // barra vertical
    barraPower.setNumeroLadrillos(24);
    barraPower.setScale(1.01);
    barraPower.setOrigen(ofPoint(20, 800));
    barraPower.setColor(ofColor(130,255,222));
    barraPower.setup();
    
    // barra de conexion
    barraConnection.setScale(1.01);
    barraConnection.setOrigen(ofPoint(0, 0));
    barraConnection.setColor(ofColor(130,255,222));
    barraConnection.setup();
    
    
    // donde ponemos la esfera
    esferaVelocidad.setOrigenEsfera(ofPoint(ofGetWidth()/2, ofGetHeight()/2));
    esferaMeditacion.setOrigenEsfera(ofPoint(ofGetWidth()/2, ofGetHeight()/2));
    esferaAtencion.setOrigenEsfera(ofPoint(ofGetWidth()/2, ofGetHeight()/2));
    
    
    // punto de rotacion para la imagen de las casillas
    esferaVelocidad.setImgPivotPoint(ofPoint(435, 18));
    esferaMeditacion.setImgPivotPoint(ofPoint(435, 18));
    esferaAtencion.setImgPivotPoint(ofPoint(435, 18));
    
    // la escala a la que dibujamos la esfera
    esferaVelocidad.setScale(0.9);
    esferaMeditacion.setScale(0.2053);
    esferaAtencion.setScale(0.2053);
    esferaVelocidad.setNumPastillas(50);
    
    
    // colores para las esferas
    esferaVelocidad.setPastillaColor(ofColor(130,255,222));
    esferaMeditacion.setPastillaColor(ofColor(130,255,222));
    esferaAtencion.setPastillaColor(ofColor(130,255,222));
    
    // cargamos las imagenes
    esferaVelocidad.setup();
    esferaMeditacion.setup();
    esferaAtencion.setup();
    
    
    // customice esferas pequeñas atencion y meditacion
    esferaAtencion.setNumPastillas(34);
    esferaAtencion.setGradosDial(310);
    esferaAtencion.rotationInicial = 60;
    esferaAtencion.desfaseLineasRotacion = 60;
    esferaAtencion.speedText.setColor(ofColor(255,255,255));
    esferaAtencion.setFontScale(1.0);
    
    esferaMeditacion.setNumPastillas(34);
    esferaMeditacion.setGradosDial(310);
    esferaMeditacion.rotationInicial = 60;
    esferaMeditacion.desfaseLineasRotacion = 60;
    esferaMeditacion.speedText.setColor(ofColor(255,255,255));
    esferaMeditacion.setFontScale(1.0);
}