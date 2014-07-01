#include "ofiOSApp.h"

//--------------------------------------------------------------
void ofiOSApp::setup(){	
    App = new CBApp();
    App->Initialize();
}

//--------------------------------------------------------------
void ofiOSApp::update(){
    App->Update((float)ofGetLastFrameTime());
}

//--------------------------------------------------------------
void ofiOSApp::draw(){
	App->Draw();
}

//--------------------------------------------------------------
void ofiOSApp::exit(){

}

//--------------------------------------------------------------
void ofiOSApp::touchDown(ofTouchEventArgs & touch){

    Event touchEvent;
    touchEvent.Type = Event::TouchDown;
    touchEvent.Value.Touch.Id = touch.id;
    touchEvent.Value.Touch.x = (float)touch.x / ofGetWidth();
    touchEvent.Value.Touch.y = (float)touch.y / ofGetHeight();
    touchEvent.Value.Touch.Pressure = touch.majoraxis;


    App->PostEvent(touchEvent);
}

//--------------------------------------------------------------
void ofiOSApp::touchMoved(ofTouchEventArgs & touch){

	Event touchMoveEvent;
	touchMoveEvent.Type = Event::Type::TouchMove;
	touchMoveEvent.Value.Touch.Id = touch.id;
	touchMoveEvent.Value.Touch.x = (float)touch.x / ofGetWidth();
	touchMoveEvent.Value.Touch.y = (float)touch.y / ofGetHeight();
	touchMoveEvent.Value.Touch.Pressure = touch.majoraxis;

	App->PostEvent(touchMoveEvent);
}

//--------------------------------------------------------------
void ofiOSApp::touchUp(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofiOSApp::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofiOSApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void ofiOSApp::lostFocus(){

}

//--------------------------------------------------------------
void ofiOSApp::gotFocus(){

}

//--------------------------------------------------------------
void ofiOSApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void ofiOSApp::deviceOrientationChanged(int newOrientation){

}
