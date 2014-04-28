#include "InitialState.h"

InitialState::InitialState(StateMachineApp* app) : State(app){	
}

void InitialState::setup(){
	gui.setup();
	gui.add(useCam.setup("Usar camara", true));
	gui.add(useShader.setup("Usar shader", true));	

	shader.load("Negative.vert", "Negative.frag");	

	cam.initGrabber(960, 720, true);
	fbo.allocate(cam.getWidth(), cam.getHeight(), GL_RGB);

	video.loadMovie("video.mov");
	video.setLoopState(OF_LOOP_NORMAL);
	video.play();

	drawGui = false;
}

void InitialState::update(){
}

void InitialState::draw(){
	if(useCam) {
		cam.update();
		if(fbo.getWidth() != cam.getWidth() || fbo.getHeight() != cam.getHeight()){
			fbo.allocate(cam.getWidth(), cam.getHeight(), GL_RGB);
		}
	} else {
		video.update();
		if(fbo.getWidth() != video.getWidth() || fbo.getHeight() != video.getHeight()){
			fbo.allocate(video.getWidth(), video.getHeight(), GL_RGB);
		}
	}
	
	
	if(useShader){
		fbo.begin();	//Habilitar fbo para pintar en él la salida del shader
			shader.begin();	//Habilitar shader para transformar la textura
				shader.setUniformTexture("heightMap", useCam ? cam.getTextureReference() : video.getTextureReference(), 0);	//Pasar como parámetro la textura a transformar			
			
				//Pintar rectángulo que define los fragmentos que serán afectados
				//Se usa el tamaño del FBO
				ofRect(0, 0, fbo.getWidth(), fbo.getHeight());
			shader.end();
		fbo.end();

		fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
	} else {
		if(useCam)
			cam.draw(0, 0, ofGetWidth(), ofGetHeight());
		else
			video.draw(0, 0, ofGetWidth(), ofGetHeight());
	}

	if(drawGui)
		gui.draw();
}

string InitialState::getStateName(){
	return "InitialState";
}

void InitialState::keyPressed(int key){
}

void InitialState::keyReleased(int key){
	if(key == ' ')
		drawGui = !drawGui;
}

void InitialState::mouseMoved(int x, int y ){
}

void InitialState::mousePressed(int x, int y, int button){
}

void InitialState::mouseReleased(int x, int y, int button){
}

void InitialState::mouseDragged(int x, int y, int button){
}

void InitialState::in(){
}

void InitialState::out(){
}