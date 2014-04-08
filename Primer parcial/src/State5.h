#pragma once

#include "State.h"
#include "Torus.h"

class State5 : public State {
public:	
	State5(StateMachineApp* app);
	
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

	ofPoint toTorusSpace(ofPoint point, float R, float r);

	float							phase;

	long							lastTimeSample;

	bool							showHelp;

	ofPoint							mousePos;

	vector<ofPoint>					positions;
	vector<ofPoint>					velocities;

	float							xRot, zRot;

	Torus							*torus;
};