#pragma once

#include "State.h"

class State3 : public State {
public:	
	State3(StateMachineApp* app);
	
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);

	void mouseMoved(int x, int y );
	void mouseReleased(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseDragged(int x, int y, int button);
		
protected:
	string getStateName();
	void in();
	void out();	

	void drawEllipse(int steps, ofPoint position, float xRadius, float yRadius, float amplitude, float phase, int periods);

	float							phase;

	long							lastTimeSample;

	bool							showHelp;

	ofPoint							mousePos;
};