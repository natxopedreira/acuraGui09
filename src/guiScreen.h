//
//  guiScreen.h
//  accuraGUI
//
//  Created by Natxo Pedreira gonzalez on 27/11/15.
//
//

#ifndef accuraGUI_guiScreen_h
#define accuraGUI_guiScreen_h

#include "esferaDial.h"
#include "barraDial.h"
#include "grillaConection.h"
#include "lapCounter.h"
#include "crono.h"
#include "cuentaAtras.h"

enum gameStatus{
    NEWGAME,
    COUNTDOWN,
    RUNNING,
    FINISHED
};

class guiScreen {
    
private:
    crono cronometro;
    lapCounter cuentaVueltas;
    
    barraDial barraPower;
    
    ofImage backgroundImage;
    ofImage fondoGris;
    ofImage banda;
    
    ofTrueTypeFont fuenteMediana, fuentePorciento, fuenteWinner;
    
    float velocidadEsferaPower;
    float meditacionEsferaPower;
    float atencionEsferaPower;
    float powerBarra;
    float conectionBarraPower;
    
    int laps;
    
    string esferaAtencionTxt;
    string esferaMeditacionTxt;
    string barraConectionTxt;
    
    gameStatus estadoJuego;
    
    string resultado;
    
    bool winner;
    
public:
    
    cuentaAtras countDown;
    
    esferaDial esferaVelocidad, esferaMeditacion, esferaAtencion;
    
    grillaConection barraConnection;
    
    //--------------------------------------------------------------
    void setup();
    
    //--------------------------------------------------------------
    void update();
    
    //--------------------------------------------------------------
    void draw();
    
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    gameStatus getGameStatus();
    
    int getnumLaps();
    //--------------------------------------------------------------
    void setGameStatus(gameStatus g);
    
    //--------------------------------------------------------------
    void setupEsferas();
    
    //--------------------------------------------------------------
    void newGame();
    
    //--------------------------------------------------------------
    void finishGame();
    
    //--------------------------------------------------------------
    void startCrono();
    
    //--------------------------------------------------------------
    void stopCrono();
    
    //--------------------------------------------------------------
    void setLapCounter(int c);
    
    //--------------------------------------------------------------
    void setAtencionTxt(string f);
    
    //--------------------------------------------------------------
    void setMeditacionTxt(string f);
    
    //--------------------------------------------------------------
    void setBarraConectionTxt(string f);
    
    //--------------------------------------------------------------
    void setVelocidadPower(float f);
    
    //--------------------------------------------------------------
    void setMeditacionPower(float f);
    
    //--------------------------------------------------------------
    void setAtencionPower(float f);
    
    //--------------------------------------------------------------
    void setBarraPower(float f);
    
    //--------------------------------------------------------------
    void setConectionPower(float f);
    
};
#endif
