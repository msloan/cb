#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	App = new CBApp();
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
	if (button == 2)
	{ 
		if (App->GetState() == CBApp::State::Recording)
		{
			App->PlayRecording();
		}
	}
	else
	{
		Event touchEvent;
		touchEvent.Type = Event::Type::TouchDown;
		touchEvent.Value.Touch.Id = button;
		touchEvent.Value.Touch.x = (float)x;
		touchEvent.Value.Touch.y = (float)y;

		App->PostEvent(touchEvent);
	}
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
