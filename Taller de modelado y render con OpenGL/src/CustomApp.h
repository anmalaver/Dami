#pragma once

#include "ofMain.h"
#include "StateMachineApp.h"

class CustomApp : public StateMachineApp {
public:
	typedef enum{INITIAL_STATE, NUM_STATES} States;

	void setupInternal();
	void updateInternal();
	void drawInternal();
	void exitInternal();

	int getStateCount();
	State* createState(int id);
	string getStateName(int id);
	bool isTransitionValid(State* from, State* to);

	void keyPressed(int key);
	void keyReleased(int key);

	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);

	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);		
};
