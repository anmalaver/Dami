#include "CustomApp.h"
#include "InitialState.h"
#include "TransformationsState.h"

void CustomApp::setupInternal(){
	ofSetFrameRate(60);
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
		case INITIAL_STATE:
			return new InitialState(this);
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