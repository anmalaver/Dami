#include "ofMain.h"
#include "CustomApp.h"

void main(){
	ofSetupOpenGL(1024, 768, OF_WINDOW);
	ofRunApp(new CustomApp());
}