#include "TransformationsState.h"

TransformationsState::TransformationsState(StateMachineApp* app) : State(app){	
}

void TransformationsState::setup(){
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

	torus = new Torus(20, 20, 200, 80);
	
	xRot = yRot = 0;

	renderMode = ParametricObject::SOLID;

	lastTimeSample = 0;

	rot = 0;
	secondRot = 0;
}

void TransformationsState::update(){
}

void TransformationsState::draw(){
	if(lastTimeSample == 0){
		lastTimeSample = ofGetElapsedTimeMillis();
		return;
	}

	ofBackgroundGradient(ofColor(64), ofColor(0), OF_GRADIENT_BAR);
	
	glEnable(GL_DEPTH_TEST);

	float delta = (ofGetElapsedTimeMillis() - lastTimeSample) / 1000.0;
	rot += 180 * delta;
	secondRot += 90 * delta;
	lastTimeSample = ofGetElapsedTimeMillis();
	
	glEnable(GL_NORMALIZE);

	GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
	//GLfloat position[] = {ofGetWidth() / 2, ofGetHeight() / 2, 1000, 0.0};
	GLfloat position[] = {0, 0, 1, 1};

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
		glTranslatef(0, 0, -1000);
		glPushMatrix();
			glTranslatef(ofGetWidth() / 2, ofGetHeight() / 2, 0.0);
			glPushMatrix();
				glRotatef(rot, 0, 1, 0);
				glRotatef(90, 1, 0, 0);

				ofFloatColor initial(1, 0, 0, 1), final(1, 1, 0, 1);
				ofFloatColor current = initial.getLerped(final, sin(2 * rot / 360.0));
				torus->draw(ofPoint(), this->ambient, current, this->specular, shininess, renderMode);
			glPopMatrix();
						
			for(int i = 0; i < 8; i++){
				glPushMatrix();
					glRotatef(360 / 8.0 * i + secondRot, 0, 0, 1);
					glTranslatef(500, 0, 0);
					glRotatef(90, 1, 0, 0);
					glScalef(0.3, 0.3, 0.3);
					
					torus->draw(ofPoint(), this->ambient, this->diffuse, this->specular, shininess, renderMode);

					for(int j = 0; j < 5; j++){
						glTranslatef(600, 0, 0);
						glRotatef(30, 0, 1, 0);						
						glScalef(0.5, 0.5, 0.5);
						torus->draw(ofPoint(), this->ambient, this->diffuse, this->specular, shininess, renderMode);
					}
				glPopMatrix();
			}			
		glPopMatrix();
	glPopMatrix();

	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	if(drawGui)
		gui.draw();	
}

string TransformationsState::getStateName(){
	return "TransformationsState";
}

void TransformationsState::keyPressed(int key){
}

void TransformationsState::keyReleased(int key){
	if(key == ' ')
		drawGui = !drawGui;

	if(key == 'l' || key == 'L')
		renderMode = ParametricObject::WIREFRAME;

	if(key == 's')
		renderMode = ParametricObject::SOLID;

	if(key == 'p')
		renderMode = ParametricObject::POINTS;
}

void TransformationsState::mouseMoved(int x, int y ){
}

void TransformationsState::mousePressed(int x, int y, int button){
	xRot = y / (float)ofGetHeight() * 360;
	yRot = x / (float)ofGetWidth() * 360;
}

void TransformationsState::mouseReleased(int x, int y, int button){
}

void TransformationsState::mouseDragged(int x, int y, int button){
	xRot = y / (float)ofGetHeight() * 360;
	yRot = x / (float)ofGetWidth() * 360;
}

void TransformationsState::in(){
}

void TransformationsState::out(){
}