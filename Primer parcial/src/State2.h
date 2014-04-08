#pragma once

#include "State.h"

#include "SineSurface.h"

#include "ofxGui.h"
#include "ofxPanel.h"

class State2 : public State {
public:	
	State2(StateMachineApp* app);
	
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


	ofxPanel						gui;
	ofxFloatColorSlider				ambient, diffuse, specular;
	ofxIntSlider					hCells, vCells;		
	ofxFloatSlider					amplitude, shininess;
	ofxIntSlider					periods;

	bool							drawGui;

	SineSurface						*sineSurface;

	float							phase;

	float							xRot, yRot;
	ParametricObject::RenderMode	renderMode;

	long							lastTimeSample;

	bool							showHelp;
};