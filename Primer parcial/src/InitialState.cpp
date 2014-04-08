#include "InitialState.h"

InitialState::InitialState(StateMachineApp* app) : State(app){	
}

void InitialState::setup(){
	gui.setup();
	gui.add(ambient.setup("Ambient", ofFloatColor(0), ofFloatColor(0), ofFloatColor(1)));
	gui.add(diffuse.setup("Diffuse", ofFloatColor(1, 0.5, 0), ofFloatColor(0), ofFloatColor(1)));
	gui.add(specular.setup("Specular", ofFloatColor(1, 1, 0), ofFloatColor(0), ofFloatColor(1)));
	gui.add(shininess.setup("Shininess", 10, 0.1, 128));	
	gui.add(hCells.setup("rows", 100, 4, 200));
	gui.add(vCells.setup("cols", 100, 4, 200));
	gui.add(r.setup("r", 30, 10, 50));

	drawGui = true;

	romanSurface = new RomanSurface(hCells, vCells, r);

	lastr = r;
	lastHCells = hCells;
	lastVCells = vCells;

	xRot = yRot = 0;

	renderMode = ParametricObject::SOLID;
}

void InitialState::update(){
}

void InitialState::draw(){
	ofBackgroundGradient(ofColor(64), ofColor(0), OF_GRADIENT_BAR);
	
	if(lastr != r || lastHCells != hCells || lastVCells != vCells){
		delete romanSurface;
		romanSurface = new RomanSurface(hCells, vCells, r);
	}


	glEnable(GL_DEPTH_TEST);

	GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat position[] = {ofGetWidth() / 2, ofGetHeight() / 2, 1000, 1.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);	

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	glPushMatrix();
	glTranslatef(0, 0, -400);
	glTranslatef(ofGetWidth() / 2, ofGetHeight() / 2, 0.0);
	glRotatef(xRot, 1, 0, 0);
	glRotatef(yRot, 0, 1, 0);
	glTranslatef(-ofGetWidth() / 2, -ofGetHeight() / 2, 0.0);
	if(romanSurface)
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
		romanSurface->draw(ofPoint(ofGetWidth() / 2, ofGetHeight() / 2, -100), this->ambient, this->diffuse, this->specular, shininess, renderMode);
	glPopMatrix();


	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	if(drawGui)
		gui.draw();

	lastr = r;
	lastHCells = hCells;
	lastVCells = vCells;

	if(showHelp){
		ofSetColor(0, 0, 0, 200);
		ofRect(0, 0, ofGetWidth(), ofGetHeight());		

		ofSetColor(255);
		ofPoint start(20, ofGetHeight() - 120);
		ofDrawBitmapString("Tips:", start.x, start.y += 20);
		ofDrawBitmapString("-Superficie romana (implementada como un ParametricObject)", start.x, start.y += 20);
		ofDrawBitmapString("-El comportamiento es el mismo que el del taller del toroide", start.x, start.y += 20);
		ofDrawBitmapString("-Se debe ver identico. Ojo con las normales...", start.x, start.y += 20);
		ofDrawBitmapString("Puntaje: 3", start.x, start.y += 20);
	}
}

string InitialState::getStateName(){
	return "InitialState";
}

void InitialState::keyPressed(int key){
}

void InitialState::keyReleased(int key){
	if(key == ' ')
		drawGui = !drawGui;

	if(key == 'l' || key == 'L')
		renderMode = ParametricObject::WIREFRAME;

	if(key == 's')
		renderMode = ParametricObject::SOLID;

	if(key == 'p')
		renderMode = ParametricObject::POINTS;

	if(key == 'h' || key == 'H')
		showHelp = !showHelp;
}

void InitialState::mouseMoved(int x, int y ){
}

void InitialState::mousePressed(int x, int y, int button){
	xRot = y / (float)ofGetHeight() * 360;
	yRot = x / (float)ofGetWidth() * 360;
}

void InitialState::mouseReleased(int x, int y, int button){
}

void InitialState::mouseDragged(int x, int y, int button){
	xRot = y / (float)ofGetHeight() * 360;
	yRot = x / (float)ofGetWidth() * 360;
}

void InitialState::in(){
	showHelp = false;
}

void InitialState::out(){
}