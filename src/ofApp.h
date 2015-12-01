#pragma once

#include "ofMain.h"
#include "guiScreen.h"
#include "ofxOsc.h"
#include "pistaSettings.h"
#include "calSpeed.h"

/// interaction devices
#include "ofxThinkgear.h"
#include "ofxLeapMotion.h"
#include "RazorAHRS.h"

#define PLAYER_NUM 0

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    
    void setScreeSpheresData(float attention, float meditation, float power, float connection, float speedBar);
    
    // iniciamos las comunicaciones OSC
    void initOsc();
    void readOsc();
    
    // hace que la velocidad sea progresiva
    calSpeed calculaVelocidad;
    
    // gui
    guiScreen pantalla;
    
    // envia data por osc
    ofxOscSender enviarOsc;
    
    // recibe datos por osc
    ofxOscReceiver recibirOsc;
    
    bool conectado;
    
    // numero de vueltas que llevo
    int laps;
    
    // que index de player ha ganado
    int playerWinner;
    
    // esta la pista habilitada?
    int trackEnabled;
    
    // cual es el estado del juego
    int estadoJuego;
    
    // cuenta atras
    int countdown;
    
    // tiempo desde el ultimo mensaje
    long tiempoDesdeMsg;
    
    // ajustes de velocidad en la pista
    pistaSettings ajustesPista;
    
    // interaction device
    string interactionDevice;
    
    /// DEVICE LEAP
    ofxLeapMotion leap;
    vector <Hand> hands;
    
    /// DEVICE ACCELEROMETER
    bool imuConectado;
    static long tiempoDesdeUltimoMensaje;
    RazorAHRS *razor;
    static float yaw, pitch, roll, offYaw, offPitch, offRoll, rYaw, rPitch, rRoll;
    static void on_error(const string &msg);
    static void on_data(const float data[]);
    
    
    /// DEVICE MINDWAVE
    float poorSignal;
    float attention;
    float meditation;
    float blink;
    
    ofxThinkgear mindWave;
    ofxThinkgearEventArgs mindWaveArgs;
    
    //
    void onThinkgearPoorSignal(ofxThinkgearEventArgs & args);
    void onThinkgearAttention(ofxThinkgearEventArgs & args);
    void onThinkgearMeditation(ofxThinkgearEventArgs & args);
    void onThinkgearBlinkStrength(ofxThinkgearEventArgs & args);
};
