#include "State5.h"

State5::State5(StateMachineApp* app) : State(app){	
}

void State5::setup(){
	lastTimeSample = 0;
	phase = 0;

	showHelp = false;

	for(int i = 0; i < 4000; i++){
		positions.push_back(ofPoint(ofRandom(0, 1), ofRandom(0, 1)));

		float speed = ofRandom(0.2, 0.5);
		velocities.push_back(ofPoint(speed / 5.0, speed));
	}

	xRot = zRot = 0;

	torus = new Torus(50, 50, 300, 100);
}

void State5::update(){	
}

ofPoint State5::toTorusSpace(ofPoint point, float R, float r){
	float phi = point.x * 2.0 * PI, theta = point.y * 2.0 * PI;	
	return ofPoint((R - r * cos(theta)) * cos(phi),
				   r * sin(theta),
				   (R - r * cos(theta)) * sin(phi));
}

void State5::draw(){
	ofBackground(0);

	if(lastTimeSample == 0){
		lastTimeSample = ofGetElapsedTimeMillis();
		return;
	}
	
	ofEnableBlendMode(OF_BLENDMODE_ADD);

	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	float deltaT = (ofGetElapsedTimeMillis() - lastTimeSample) / 1000.0;
	float xSpeed = 30, zSpeed = 20;
	xRot += xSpeed * deltaT;
	zRot += zSpeed * deltaT;
	lastTimeSample = ofGetElapsedTimeMillis();

	glPushMatrix();
		glTranslatef(ofGetWidth() / 2, ofGetHeight() / 2, 0.0);
		glRotatef(xRot, 1, 0, 0);
		glRotatef(zRot, 0, 0, 1);
		glTranslatef(-ofGetWidth() / 2, -ofGetHeight() / 2, 0.0);
	
		for(int i = 0; i < positions.size(); i++){
			ofPoint current = positions[i];
			current += velocities[i] * deltaT;

			if(current.x > 1)	current.x -= 1;
			if(current.x < 0)	current.x += 1;

			if(current.y > 1)	current.y -= 1;
			if(current.y < 0)	current.y += 1;

			positions[i] = current;

			float dist = ofDist(current.x, current.y, 0.5, 0.5);

			ofFloatColor initial(1, 0.5, 1, 0.3), final(0, 1, 1, 0.3);
			ofSetColor(initial.getLerped(final, dist));

			ofPoint torusPosition = torus->computePosition(current) + ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);		

			glPointSize(5 + dist * 10);
			glBegin(GL_POINTS);
				glVertex3f(torusPosition.x, torusPosition.y, torusPosition.z);
			glEnd();
		}


		ofSetColor(100, 100, 100, 50);	
		torus->draw(ofPoint(ofGetWidth() / 2, ofGetHeight() / 2), ofFloatColor(0), ofFloatColor(1, 0, 0), ofFloatColor(1), 50, ParametricObject::WIREFRAME);
	glPopMatrix();

	glPointSize(1);
	ofSetColor(255);
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);

	if(showHelp){
		ofSetColor(0, 0, 0, 200);
		ofRect(0, 0, ofGetWidth(), ofGetHeight());		

		ofSetColor(255);
		ofPoint start(20, ofGetHeight() - 240);
		ofDrawBitmapString("Tips:", start.x, start.y += 20);
		ofDrawBitmapString("-4000 particulas moviendose en el espacio del toroide pintadas como GL_POINTS", start.x, start.y += 20);
		ofDrawBitmapString("-Tambien se esta pintando un toroide gris con lineas grises...", start.x, start.y += 20);
		ofDrawBitmapString("-Todo el espacio se rota independientemente en X y Y", start.x, start.y += 20);
		ofDrawBitmapString("-El color y la transpacencia de las particulas se basa en su distancia al", start.x, start.y += 20);
		ofDrawBitmapString(" centro (En el espacio [0,1]x[0,1]) y se mapea entre azul y morado", start.x, start.y += 20);
		ofDrawBitmapString("-Su radio (modificado usando glPointSize) igualmente en su distancia al centro", start.x, start.y += 20);
		ofDrawBitmapString("-No se puede usar glPointSize dentro de bloques glBegin() - glEnd()", start.x, start.y += 20);
		ofDrawBitmapString("-Usar suavizado de puntos y lineas como figura en el segundo taller", start.x, start.y += 20);
		ofDrawBitmapString("-Usar esta linea al inicio del metodo draw: ofEnableBlendMode(OF_BLENDMODE_ADD);", start.x, start.y += 20);
		ofDrawBitmapString("Puntaje: 4", start.x, start.y += 20);
	}
}

string State5::getStateName(){
	return "State5";
}

void State5::keyPressed(int key){
}

void State5::keyReleased(int key){
	if(key == 'h' || key == 'H')
		showHelp = !showHelp;
}

void State5::mouseMoved(int x, int y ){
	mousePos = ofPoint(x, y);
}

void State5::mousePressed(int x, int y, int button){	
}

void State5::mouseReleased(int x, int y, int button){
}

void State5::mouseDragged(int x, int y, int button){	
}

void State5::in(){
	showHelp = false;
}

void State5::out(){
}