#include "CustomApp.h"

#include "InitialState.h"
#include "State2.h"
#include "State3.h"
#include "State4.h"
#include "State5.h"

void CustomApp::setupInternal(){
	ofSetFrameRate(60);

	//goToState(STATE5);
}

void CustomApp::updateInternal(){
}

void CustomApp::drawInternal(){
}

void CustomApp::exitInternal(){
}

int CustomApp::getStateCount(){
	return NUM_STATES;
}

State* CustomApp::createState(int id){
	switch (id)	{
		case INITIAL_STATE:		return new InitialState(this);
		case STATE2:			return new State2(this);
		case STATE3:			return new State3(this);
		case STATE4:			return new State4(this);
		case STATE5:			return new State5(this);
	}
	
	return NULL;
}

string CustomApp::getStateName(int id){
	return "";
}

bool CustomApp::isTransitionValid(State* from, State* to){
	return true;
}

void CustomApp::keyPressed(int key){
	StateMachineApp::keyPressed(key);
}

void CustomApp::keyReleased(int key){
	StateMachineApp::keyReleased(key);

	if(key >= '0' && key <= '9'){
		key -= '0';
		if(key < NUM_STATES){
			goToState(key);
		}
	}
}

void CustomApp::mouseMoved(int x, int y ){
	StateMachineApp::mouseMoved(x, y);
}

void CustomApp::mouseDragged(int x, int y, int button){
	StateMachineApp::mouseDragged(x, y, button);
}

void CustomApp::mousePressed(int x, int y, int button){
	StateMachineApp::mousePressed(x, y, button);
}

void CustomApp::mouseReleased(int x, int y, int button){
	StateMachineApp::mouseReleased(x, y, button);
}