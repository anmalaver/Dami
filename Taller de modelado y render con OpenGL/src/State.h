#pragma once

#include "ofMain.h"
#include "StateMachineApp.h"

class State{
public:	
	State(StateMachineApp* app);
	
	virtual void setup() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

	virtual void exit(){}

	virtual void keyPressed(int key){}
	virtual void keyReleased(int key){}

	virtual void mouseMoved(int x, int y ){}
	virtual void mouseReleased(int x, int y, int button){}
	virtual void mousePressed(int x, int y, int button){}
	virtual void mouseDragged(int x, int y, int button){}
	
	virtual string getStateName() = 0;
	virtual void in() = 0;
	virtual void out() = 0;

protected:
	StateMachineApp* app;
};