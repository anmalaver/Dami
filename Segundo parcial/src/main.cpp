#include "ofMain.h"
#include "CustomApp.h"

void main(){
	ofSetupOpenGL(960, 720, OF_WINDOW);
	ofRunApp(new CustomApp());
}