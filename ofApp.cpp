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
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	Event touchEvent;
	touchEvent.Type = Event::Type::TouchDown;
	touchEvent.Value.Touch.Id = button;
	touchEvent.Value.Touch.x = (float)x / ofGetWidth(),
	touchEvent.Value.Touch.y = (float)y / ofGetHeight();

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
