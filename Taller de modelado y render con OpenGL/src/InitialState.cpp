#include "InitialState.h"

InitialState::InitialState(StateMachineApp* app) : State(app){	
}

void InitialState::setup(){
	gui.setup();
	gui.add(ambient.setup("Ambient", ofColor(0), ofColor(0), ofColor(255)));
	gui.add(diffuse.setup("Diffuse", ofColor(255), ofColor(0), ofColor(255)));
	gui.add(specular.setup("Specular", ofColor(255), ofColor(0), ofColor(255)));
	gui.add(shininess.setup("Shininess", 128, 0.1, 128));	
	gui.add(hCells.setup("rows", 100, 4, 200));
	gui.add(vCells.setup("cols", 100, 4, 200));
	gui.add(R.setup("R", 300, 100, 500));
	gui.add(r.setup("r", 100, 10, 200));

	drawGui = true;

	torus = new Torus(hCells, vCells, R, r);

	lastR = R;
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
	
	if(lastR != R || lastr != r || lastHCells != hCells || lastVCells != vCells){
		delete torus;
		torus = new Torus(hCells, vCells, R, r);
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
	if(torus)
		torus->draw(ofPoint(ofGetWidth() / 2, ofGetHeight() / 2, -100), 
		this->ambient,
		this->diffuse, 
		this->specular, 
		shininess, 
		renderMode);
	glPopMatrix();


	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	if(drawGui)
		gui.draw();


	lastR = R;
	lastr = r;
	lastHCells = hCells;
	lastVCells = vCells;
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
}

void InitialState::out(){
}