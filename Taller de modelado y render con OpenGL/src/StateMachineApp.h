#pragma once

#include "ofMain.h"

class State;
class StateMachineApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void exit();

	virtual void setupInternal() = 0;
	virtual void updateInternal() = 0;
	virtual void drawInternal() = 0;
	virtual void exitInternal() = 0;

	virtual void keyPressed(int key);
	virtual void keyReleased(int key);

	virtual void mouseMoved(int x, int y );
	virtual void mouseDragged(int x, int y, int button);
	virtual void mousePressed(int x, int y, int button);
	virtual void mouseReleased(int x, int y, int button);

	virtual int getStateCount() = 0;
	virtual State* createState(int id) = 0;
	virtual string getStateName(int id) = 0;
	virtual bool isTransitionValid(State* from, State* to) = 0;

	virtual void goToState(int id);

protected:
	vector<State*> states;
	State* currentState;
};