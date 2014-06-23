#include "ofiOSApp.h"

//--------------------------------------------------------------
void ofiOSApp::setup(){	
    App = new CBApp();
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
    if (touch.x < 20.f && touch.y < 20.f)
    {
        if (App->GetState() == CBApp::Recording)
        {
            App->PlayRecording();
        }
    }
    
    Event touchEvent;
    touchEvent.Type = Event::TouchDown;
    touchEvent.Value.Touch.Id = touch.id;
    touchEvent.Value.Touch.x = (float)touch.x;
    touchEvent.Value.Touch.y = (float)touch.y;
    

    App->PostEvent(touchEvent);
}

//--------------------------------------------------------------
void ofiOSApp::touchMoved(ofTouchEventArgs & touch){

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
