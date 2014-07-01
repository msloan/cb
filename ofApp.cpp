#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	App = new CBApp();
	App->Initialize();
}

//--------------------------------------------------------------
void ofApp::update(){
	App->Update((float)ofGetLastFrameTime());
}

//--------------------------------------------------------------
void ofApp::draw(){
	App->Draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

	Event touchMoveEvent;
	touchMoveEvent.Type = Event::Type::TouchMove;
	touchMoveEvent.Value.Touch.Id = button;
	touchMoveEvent.Value.Touch.x = (float)x / ofGetWidth();
	touchMoveEvent.Value.Touch.y = (float)y / ofGetHeight();
	touchMoveEvent.Value.Touch.Pressure = 15.f;

	App->PostEvent(touchMoveEvent);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	Event touchEvent;
	touchEvent.Type = Event::Type::TouchDown;
	touchEvent.Value.Touch.Id = button;
	touchEvent.Value.Touch.x = (float)x / ofGetWidth(),
	touchEvent.Value.Touch.y = (float)y / ofGetHeight();
	touchEvent.Value.Touch.Pressure = 15.f;

	App->PostEvent(touchEvent);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
