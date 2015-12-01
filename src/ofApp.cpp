#include "ofApp.h"

float ofApp::yaw;
float ofApp::pitch;
float ofApp::roll;

float ofApp::offYaw;
float ofApp::offPitch;
float ofApp::offRoll;

float ofApp::rYaw;
float ofApp::rPitch;
float ofApp::rRoll;

// tiempo desde el ultimo mensaje
long ofApp::tiempoDesdeUltimoMensaje;

//--------------------------------------------------------------
void ofApp::setup(){
    //
    ofBackground(128, 128, 128);
    
    estadoJuego=laps=playerWinner=trackEnabled=countdown=0;
    
    // quitamos el blur al texto de conecion
    pantalla.barraConnection.setBlur(false);
    
    // blur para las esferas
    pantalla.esferaVelocidad.setBlur(true);
    pantalla.esferaMeditacion.setBlur(false);
    pantalla.esferaAtencion.setBlur(false);
    
    // textos para mostrar
    pantalla.setMeditacionTxt("MEDITATION");
    pantalla.setAtencionTxt("ATENTION");
    pantalla.setBarraConectionTxt("CONECTION QUALITY");
    
    // inicamos el skin
    pantalla.setup();
    
    // comunicaciones osc
    initOsc();
    
    // iniciamos el gui con los settings
    ajustesPista.setup();
    
    ///////////////////////////////////
    /////// INTERACTION DEVICE ////////
    ///////////////////////////////////
    
    //// **************************** ////
    ////// ***** LEAP MOTION ***** //////
    
    poorSignal = 200;
    attention = meditation = 0;
    
    if (ajustesPista.getInteractionMode() == "INTERACTION MINDWAVE"){
        mindWave.setup("/dev/tty.MindWaveMobile-DevA", 57600, TG_COMMS_DRIVER);
        mindWave.addEventListener(this);
    }
    
    //// ************************ ////
    ////// ***** MINDWAVE ***** //////
    
    if (ajustesPista.getInteractionMode() == "INTERACTION LEAP MOTION"){
        /// leap motion
        leap.open();
        
        pantalla.setMeditacionTxt("POSITION Z");
        pantalla.setAtencionTxt("POSITION X");
        pantalla.setBarraConectionTxt("LEAP HANDS");
    }
    
    //// ****************************** ////
    ////// ***** ACCELEROMETER ***** //////
    imuConectado = false;
    string serial_port_name = "/dev/tty.RNBT-72A4-RNI-SPP";
    
    if (ajustesPista.getInteractionMode() == "INTERACTION ACCELEROMETER") {
        
        // offset para el IMU
        offYaw = 0;
        offPitch = 0;
        offRoll = 0;
        
        pantalla.setMeditacionTxt("IMU PITCH");
        pantalla.setAtencionTxt("  IMU YAW");
        pantalla.setBarraConectionTxt("IMU CONNECTION");
        
        try{
            
            razor = new RazorAHRS(serial_port_name, on_data, on_error, RazorAHRS::YAW_PITCH_ROLL);
            imuConectado = true;
        }
        catch(runtime_error &e){
            cout << "  " << (string("Could not create tracker: ") + string(e.what())) << endl;
            return 0;
        }
        
        
    }
}

//--------------------------------------------------------------
void ofApp::update(){

    float finalSpeed = 0.0;
    
    //interaction device
    if (interactionDevice != ajustesPista.getInteractionMode()) {
        interactionDevice = ajustesPista.getInteractionMode();
    }
    
    
    //// ************************ ////
    ////// ***** MINDWAVE ***** //////
    
    if (interactionDevice == "INTERACTION MINDWAVE") {
        // estamos usando el mindwaves
        mindWave.update();
        
        // si la conexion esta ook
        if(poorSignal == 1){
            
            // mira si quieres usar un valor solo o los dos juntos
            if(ajustesPista.getAttentionPlusMeditation()){
                float v = (attention+meditation)*.5;
                calculaVelocidad.setDesiredSpeed(v);
            }else{
                calculaVelocidad.setDesiredSpeed(attention);
            }
            
        }else{
            calculaVelocidad.setDesiredSpeed(0);
        }
        
        // actualiza el calculo de velocidad
        calculaVelocidad.update();
        
        // setea el valor que envias a las esferas de velocidad por el calculo de velocidad
        finalSpeed = calculaVelocidad.getSpeed();
    }
    
    
    
    //// **************************** ////
    ////// ***** LEAP MOTION ***** //////
    
    if (interactionDevice == "INTERACTION LEAP MOTION") {
        // usamos el leap
        
        hands = leap.getLeapHands();
        leap.markFrameAsOld();
        
        //
        if(hands.size() > 0){
            int posX = hands.at(0).palmPosition().x;
            int posY = hands.at(0).palmPosition().y;
            int posZ = hands.at(0).palmPosition().z;
            
            finalSpeed = ofMap(posY, 20, ajustesPista.getLeapMax(), 0, 1, true);
            
            attention = ofMap(posX, -100, 100, 0, 1, true);
            meditation = ofMap(posZ, -100, 100, 0, 1, true);
            
            poorSignal = 1;
        }else{
            poorSignal = 0;
        }
    }
    
    
    
    
    //// ****************************** ////
    ////// ***** ACCELEROMETER ***** //////
    
    if (interactionDevice == "INTERACTION ACCELEROMETER") {
        
        if (imuConectado) {
            poorSignal = 1;
            
            finalSpeed = ofMap(pitch, ajustesPista.getTalloMin(), ajustesPista.getTalloMax(), 0, 1, true);
            
            attention = ofMap(roll, -180, 180, 0, 1, true);
            meditation = ofMap(yaw, -180, 180, 0, 1, true);
            
            
        }else{
            poorSignal = 0;
        }
        
        
    }
    

    
    
    
    //// ****************************** ////
    //// ****************************** ////
    //// ****************************** ////
    //// ****************************** ////
    //// ****************************** ////
    
    
    
    // panel de debug enviar data
    if (ajustesPista.getSendData()) {
        finalSpeed = ajustesPista.getSpeedNorm();
    }
    
    
    
    // mandamos los datos para las esferas
    setScreeSpheresData(attention, meditation, finalSpeed, poorSignal, finalSpeed);
    

    // leemos los datos de osc del arduino si los hay
    // estadoJuego
    // laps
    // playerWinner
    // trackEnabled
    // countdown
    
    readOsc();
    
    // actualizamos el estado en el gui
    ajustesPista.setPistaActivada(trackEnabled);
    
    // comprobamos el estado del juego si es distinto del actual lo cambiamos
    if (pantalla.getGameStatus() != estadoJuego) {
        pantalla.setGameStatus((gameStatus)estadoJuego);
        
        // mira si quiere iniciar la partida, solo lo decimos una vez
        if (pantalla.getGameStatus() == NEWGAME) {
            pantalla.newGame();
        }
        
        // mira si quiere acabar la partida, solo lo decimos una vez
        if (pantalla.getGameStatus() == FINISHED) {
            pantalla.finishGame();
        }
        
        ajustesPista.setGameStatus(pantalla.getGameStatus());
    }
    
    
    if (pantalla.getGameStatus() == COUNTDOWN) {
        // cuenta atras
        pantalla.countDown.setData(countdown);
        
    }else if (pantalla.getGameStatus() == RUNNING) {
        // cuentavueltas
        if (pantalla.getnumLaps() != laps) {
            pantalla.setLapCounter(laps);
            ajustesPista.setLaps(laps);
        }
    }
    
    // update el skin
    pantalla.update();
    
    // miramos cuanto hace desde el ultimo mensaje de la pista para ver si esta o no conectada
    if (ofGetElapsedTimeMillis()-tiempoDesdeMsg > 1000) {
        conectado = false;
        ajustesPista.setPistaConectada(false);
    }
    
    
    if (ofGetElapsedTimeMillis()-tiempoDesdeUltimoMensaje > 10000) {
        
        imuConectado = false;
        poorSignal = 0;
        tiempoDesdeUltimoMensaje = ofGetElapsedTimeMillis();
        
        if(interactionDevice == "INTERACTION ACCELEROMETER" && !ajustesPista.getSendData()){
            
            
            
            try{
                if(razor != NULL) delete razor;
                
                string serial_port_name = "/dev/tty.RNBT-72A4-RNI-SPP";
                
                razor = new RazorAHRS(serial_port_name, on_data, on_error, RazorAHRS::YAW_PITCH_ROLL);
            }
            catch(runtime_error &e)
            {
                cout << "  " << (string("Could not create tracker: ") + string(e.what())) << endl;
                return 0;
            }
        
        }

    }
}

//// MINDWAVES CALLBACK
//--------------------------------------------------------------
void ofApp::onThinkgearPoorSignal(ofxThinkgearEventArgs & args){
    int f = (int) args.poorSignal;
    poorSignal = ofMap(f, 200, 0, 0, 1, true);
}
//--------------------------------------------------------------
void ofApp::onThinkgearAttention(ofxThinkgearEventArgs & args){
    int a = (int) args.attention;
    attention = ofMap(a, 0, 100, 0, 1, true);
}
//--------------------------------------------------------------
void ofApp::onThinkgearMeditation(ofxThinkgearEventArgs & args){
    int m = (int) args.meditation;
    meditation = ofMap(m, 0, 100, 0, 1, true);
}
//--------------------------------------------------------------
void ofApp::onThinkgearBlinkStrength(ofxThinkgearEventArgs & args){
    int b = (int) args.blinkStrength;
    
    blink = ofMap(b, 0, 255, 0, 1, true);
}

//// RAZOR 9DOF CALLBACK
//--------------------------------------------------------------
void ofApp::on_error(const string &msg)
{
    cout << "  " << "ERROR: " << msg << endl;
    
    // NOTE: make a copy of the message if you want to save it or send it to another thread. Do not
    // save or pass the reference itself, it will not be valid after this function returns!
}
void ofApp::on_data(const float data[])
{
    
    rYaw = data[0];
    rPitch = data[1];
    rRoll = data[2];
    
    yaw = ofWrap(rYaw - offYaw, -180, 180);
    pitch = ofWrap(rPitch - offPitch, -180, 180);
    roll = ofWrap(rRoll - offRoll, -180, 180);
    
    tiempoDesdeUltimoMensaje = ofGetElapsedTimeMillis();
}


//--------------------------------------------------------------
void ofApp::setScreeSpheresData(float attention, float meditation, float power, float connection, float speedBar){
    // nivel de atencion
    pantalla.setAtencionPower(attention);
    
    // nivel de power // si es solo atencion o solo meditacion o ambos
    pantalla.setBarraPower(power);
    
    // calidad de la conexion
    pantalla.setConectionPower(connection);
    
    // nivel de meditacion
    pantalla.setMeditacionPower(meditation);
    
    // nivel de velocidad = power
    pantalla.setVelocidadPower(speedBar);
}
//--------------------------------------------------------------
void ofApp::draw(){
    pantalla.draw();
}

//--------------------------------------------------------------
void ofApp::initOsc(){
    enviarOsc.setup("192.168.0.252", 10000);
    recibirOsc.setup(12000);
    
    conectado = false;
    tiempoDesdeMsg = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void ofApp::readOsc(){
    while(recibirOsc.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        recibirOsc.getNextMessage(&m);
        
        tiempoDesdeMsg = ofGetElapsedTimeMillis();
        

        
        if(m.getAddress() == "/gameStatus"){
            estadoJuego = m.getArgAsInt32(0);
        }
        
        if(m.getAddress() == "/vueltas"){
            laps = m.getArgAsInt32(PLAYER_NUM);
        }
        
        if(m.getAddress() == "/winner"){
            playerWinner = m.getArgAsInt32(0);
        }
        
        if(m.getAddress() == "/trackEnabled"){
            trackEnabled = m.getArgAsInt32(0);
        }
        
        if(m.getAddress() == "/countdown"){
            countdown = m.getArgAsInt32(0);
        }
        conectado = true;
        ajustesPista.setPistaConectada(true);
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '3') {
        estadoJuego = 3;
    }
    if (key == '2') {
        estadoJuego = 2;
    }
    if (key == '1') {
        estadoJuego = 1;
    }
    if (key == '0') {
        estadoJuego = 0;
    }
    /*
     if (key == 's') {
     pantalla.startCrono();
     }
     
     if (key == 'f') {
     pantalla.stopCrono();
     }
     
     if (key == 'n') {
     pantalla.newGame();
     }
     
     if (key == 'e') {
     pantalla.finishGame();
     }
     
     
     if (key == '5') {
     pantalla.countDown.setData(5);
     }
     if (key == '4') {
     pantalla.countDown.setData(4);
     }
     if (key == '3') {
     estadoJuego = 3;
     }
     if (key == '2') {
     estadoJuego = 2;
     }
     if (key == '1') {
     estadoJuego = 1;
     }
     if (key == '0') {
     estadoJuego = 0;
     }*/
}