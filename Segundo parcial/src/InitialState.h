#pragma once

#include "State.h"

#include "Torus.h"

#include "ofxGui.h"
#include "ofxPanel.h"

#define NUM_EXERCISES	5

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

	void encodeFile(string fileName);
	string decode(int shaderResourceID);

	void in();
	void out();	

	bool					drawGui;
	ofxPanel				gui[NUM_EXERCISES];

	//Grayscale
	ofxFloatSlider			rWeight, gWeight, bWeight, power;
	ofShader				shaderGrayscale;
	ofFbo					fboGrayscale;

	//Running average
	ofxFloatSlider			runningAverageFactor;
	ofShader				shaderRunningAverage;
	ofFbo					fboRunningAverage, fboLast;

	//Motion diff
	ofxFloatSlider			motionDiffThreshold;
	ofShader				shaderMotionDiff;	
	ofFbo					fboMotionDiff, fboLastCam;

	//Cartoonizer
	ofxIntSlider			cellSize, radius;
	ofShader				shaderCartoonizer;
	ofFbo					fboCartoonizer;

	//Mosaic
	ofxFloatSlider			scale;
	ofShader				shaderMosaic;
	ofFbo					fboMosaic;

	ofVideoGrabber			cam;
	ofFbo					fboCam;

	int						exerciseIndex;
	int						showVideo;
	ofVideoPlayer			video1, video2;

	vector<string>			texts[NUM_EXERCISES];
};