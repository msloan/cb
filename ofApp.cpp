#include "ofApp.h" 
#include "Event.h"

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
	CBApp::State state = App->GetState();
	switch (key)
	{
		case '0':

			App->SetPosition(0.0f);
			break;
		case '1':

			App->SetPosition(5.0f);
			break;
		case '2':

			App->SetPosition(10.0f);
			break;
		case '3':

			App->SetPosition(100.0f);
			break;

		case 'p':
			switch (state)
			{
				case CBApp::Playing:
				case CBApp::Recording:

					App->Pause();
					break;

				case CBApp::Paused:

					App->Play();
					break;
			}
			break;

		case 'r':
			App->Record();
			break;

		case 'l':
			App->SaveLayer();
			break;
	}
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

int id = 0;
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

	Event touchMoveEvent;
	touchMoveEvent.Type = Event::Type::TouchMove;
	touchMoveEvent.Value.Touch.Id = id++;
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
void ofApp::mouseReleased(int x, int y, int button)
{
	Event touchEvent;
	touchEvent.Type = Event::Type::TouchUp;
	touchEvent.Value.Touch.Id = button;
	touchEvent.Value.Touch.x = (float)x / ofGetWidth(),
	touchEvent.Value.Touch.y = (float)y / ofGetHeight();
	touchEvent.Value.Touch.Pressure = 15.f;

	App->PostEvent(touchEvent);

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
