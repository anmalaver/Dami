#pragma once

#include "State.h"

#include "Torus.h"

#include "ofxGui.h"
#include "ofxPanel.h"

class InitialState : public State {
public:	
	InitialState(StateMachineApp* app);
	
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

	void onDrawHeightMapChanged();

	ofxPanel				gui;
	ofxFloatColorSlider		ambient, diffuse, specular;
	ofxToggle				useCam, useShader;
	ofxIntSlider			periods;
	
	bool					drawGui;	

	float					phase;

	ofShader				shader;

	ofFbo					fbo;

	ofVideoGrabber			cam;
	ofVideoPlayer			video;
	ofImage					image;
};