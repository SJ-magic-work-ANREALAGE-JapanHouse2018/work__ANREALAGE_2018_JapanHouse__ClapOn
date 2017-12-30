/************************************************************
************************************************************/
#include "ofApp.h"


/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp()
: Osc_ClapDetector("127.0.0.1", 12350, 12349)
, b_ClapMessage(false)
, id_Clap(0)
{
}

/******************************
******************************/
ofApp::~ofApp()
{
}
	
/******************************
******************************/
void ofApp::exit()
{
}

//--------------------------------------------------------------
void ofApp::setup(){
	/********************
	********************/
	srand((unsigned) time(NULL));
	
	/********************
	********************/
	ofSetWindowTitle("ANREALAGE:ClapOn");
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofSetWindowShape(WIDTH, HEIGHT);
	ofSetEscapeQuitsApp(false);
	
	ofEnableAlphaBlending();
	// ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	// ofEnableSmoothing();
	
	/********************
	********************/
	for(int i = 0; i < NUM_CLAPSOUNDS; i++){
		char buf[BUF_SIZE];
		sprintf(buf, "sound_%d.mp3", i);
		sound[i].loadSound(buf);
		
		if(!sound[i].isLoaded()) { ERROR_MSG(); std::exit(1); }
		
		sound[i].setVolume(1.0);
		sound[i].setLoop(false);
		sound[i].setMultiPlay( true );
		// sound[i].setSpeed( 1.0 );
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	/********************
	********************/
	ofSoundUpdate();
	
	/********************
	********************/
	while(Osc_ClapDetector.OscReceive.hasWaitingMessages()){
		ofxOscMessage m_receive;
		Osc_ClapDetector.OscReceive.getNextMessage(&m_receive);
		
		if(m_receive.getAddress() == "/DetectClap"){
			m_receive.getArgAsInt32(0); // 読み捨て
			
			b_ClapMessage = true;
		}
	}
	
	/********************
	********************/
	if(b_ClapMessage){
		id_Clap = Dice_index(NUM_CLAPSOUNDS);
		
		sound[id_Clap].play();
		
		b_ClapMessage = false;
	}
}

/******************************
******************************/
int ofApp::Dice_index(int NUM)
{
	return (int)( ((double)rand() / ((double)RAND_MAX + 1)) * (NUM) );
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
		case ' ':
			b_ClapMessage = true;
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
