#include "State2.h"

State2::State2(StateMachineApp* app) : State(app){	
}

void State2::setup(){
	gui.setup();
	gui.add(ambient.setup("Ambient", ofFloatColor(0), ofFloatColor(0), ofFloatColor(1)));
	gui.add(diffuse.setup("Diffuse", ofFloatColor(1, 0.5, 0), ofFloatColor(0), ofFloatColor(1)));
	gui.add(specular.setup("Specular", ofFloatColor(1, 1, 0), ofFloatColor(0), ofFloatColor(1)));
	gui.add(shininess.setup("Shininess", 128, 0.1, 128));	
	gui.add(hCells.setup("rows", 50, 4, 100));
	gui.add(vCells.setup("cols", 50, 4, 100));
	gui.add(amplitude.setup("amplitude", 60, 10, 200));
	gui.add(periods.setup("periods", 2, 1, 20));

	drawGui = true;

	sineSurface = new SineSurface(hCells, vCells, 100, 5, 0, ofPoint(ofGetWidth() * 1.5, ofGetHeight() * 1.5));	
	
	xRot = yRot = 0;

	lastTimeSample = 0;

	phase = 0;

	showHelp = false;

	renderMode = ParametricObject::WIREFRAME;
}

void State2::update(){
}

void State2::draw(){
	ofBackgroundGradient(ofColor(64), ofColor(0), OF_GRADIENT_BAR);

	ofEnableBlendMode(OF_BLENDMODE_ADD);

	if(lastTimeSample == 0){
		lastTimeSample = ofGetElapsedTimeMillis();
		return;
	}
	
	float deltaT = (ofGetElapsedTimeMillis() - lastTimeSample) / 1000.0;
	float phaseSpeed = TWO_PI;
	lastTimeSample = ofGetElapsedTimeMillis();


	delete sineSurface;
	sineSurface = new SineSurface(hCells, vCells, amplitude, periods, phase += phaseSpeed * deltaT, ofPoint(ofGetWidth() * 1.5, ofGetHeight() * 1.5));


	glEnable(GL_DEPTH_TEST);

	GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat position[] = {ofGetWidth() / 2, ofGetHeight() / 2, 1000, 1.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);	

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	glPushMatrix();
	//glTranslatef(0, 0, -400);
	glTranslatef(ofGetWidth() / 2, ofGetHeight() / 2, 0.0);
	glRotatef(xRot, 1, 0, 0);
	glRotatef(yRot, 0, 1, 0);
	glTranslatef(-ofGetWidth() / 2, -ofGetHeight() / 2, 0.0);
	if(sineSurface)
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		sineSurface->draw(ofPoint(ofGetWidth() / 2, ofGetHeight() / 2, -100), 
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

	ofEnableBlendMode(OF_BLENDMODE_ALPHA);

	if(drawGui)
		gui.draw();

	if(showHelp){
		ofSetColor(0, 0, 0, 200);
		ofRect(0, 0, ofGetWidth(), ofGetHeight());		

		ofSetColor(255);
		ofPoint start(20, ofGetHeight() - 160);
		ofDrawBitmapString("Tips:", start.x, start.y += 20);
		ofDrawBitmapString("-Superficie parametrica sinusoidal. (ParametricObject)", start.x, start.y += 20);
		ofDrawBitmapString("-Solo cambia Z mapeando la distancia de cada punto al centro de la superficie a una onda seno.", start.x, start.y += 20);
		ofDrawBitmapString("-Se usan los mismos controles del segundo taller.", start.x, start.y += 20);
		ofDrawBitmapString("-Se usan los mismos controles del segundo taller.", start.x, start.y += 20);
		ofDrawBitmapString("-Usar esta linea al inicio del metodo draw: ofEnableBlendMode(OF_BLENDMODE_ADD);", start.x, start.y += 20);
		ofDrawBitmapString("Puntaje: 2", start.x, start.y += 20);
	}
}

string State2::getStateName(){
	return "State2";
}

void State2::keyPressed(int key){
}

void State2::keyReleased(int key){
	if(key == ' ')
		drawGui = !drawGui;

	if(key == 'l' || key == 'L')
		renderMode = ParametricObject::WIREFRAME;

	if(key == 'p')
		renderMode = ParametricObject::POINTS;

	if(key == 'h' || key == 'H')
		showHelp = !showHelp;
}

void State2::mouseMoved(int x, int y ){
}

void State2::mousePressed(int x, int y, int button){
	xRot = y / (float)ofGetHeight() * 360;
	yRot = x / (float)ofGetWidth() * 360;
}

void State2::mouseReleased(int x, int y, int button){
}

void State2::mouseDragged(int x, int y, int button){
	xRot = y / (float)ofGetHeight() * 360;
	yRot = x / (float)ofGetWidth() * 360;
}

void State2::in(){
	showHelp = false;
}

void State2::out(){
}