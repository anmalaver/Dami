#include "StateMachineApp.h"
#include "State.h"

void StateMachineApp::setup(){
	int numStates = getStateCount();
	for(int i = 0; i < numStates; i++){
		State* newState = createState(i); 
		newState->setup();

		states.push_back(newState);
	}

	if(numStates > 0){
		currentState = states[0];
		currentState->in();
	}

	setupInternal();
}
void StateMachineApp::update(){
	updateInternal();

	if(currentState)
		currentState->update();	
}
void StateMachineApp:: draw(){
	drawInternal();

	if(currentState)
		currentState->draw();
}
void StateMachineApp::exit(){
	exitInternal();

	if(currentState)
		currentState->exit();

	for(int i = 0; i < states.size(); i++){
		delete states[i];
	}
}

void StateMachineApp::keyPressed(int key){
	if(currentState)
		currentState->keyPressed(key);
}

void StateMachineApp::keyReleased(int key){
	if(currentState)
		currentState->keyReleased(key);
}

void StateMachineApp::mouseMoved(int x, int y ){
	if(currentState)
		currentState->mouseMoved(x, y);
}

void StateMachineApp::mouseDragged(int x, int y, int button){
	if(currentState)
		currentState->mouseDragged(x, y, button);
}

void StateMachineApp::mousePressed(int x, int y, int button){
	if(currentState)
		currentState->mousePressed(x, y, button);
}

void StateMachineApp::mouseReleased(int x, int y, int button){
	if(currentState)
		currentState->mouseReleased(x, y, button);
}

void StateMachineApp::goToState(int id){
	if(id < states.size() && isTransitionValid(currentState, states[id])){
		currentState->out();
		currentState = states[id];
		currentState->in();
	}
}