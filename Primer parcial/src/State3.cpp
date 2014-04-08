#include "State3.h"

State3::State3(StateMachineApp* app) : State(app){	
}

void State3::setup(){
	lastTimeSample = 0;
	phase = 0;

	showHelp = false;
}

void State3::update(){
}

void State3::drawEllipse(int steps, ofPoint position, float xRadius, float yRadius, float amplitude, float phase, int periods) {
	float angle = 0, angleInc = TWO_PI / steps;
	glBegin(GL_LINE_LOOP);
		for(int i = 0; i < steps; i++, angle += angleInc){
			float sineWave = amplitude * sin(angle / TWO_PI * (TWO_PI * periods) + phase);
			glVertex3f(xRadius * cos(angle) + position.x + sineWave, yRadius * sin(angle) + position.y + sineWave, position.z);
		}
	glEnd();
}

void State3::draw(){
	ofBackgroundGradient(ofColor(64), ofColor(0), OF_GRADIENT_BAR);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	if(lastTimeSample == 0){
		lastTimeSample = ofGetElapsedTimeMillis();
		return;
	}
	
	float deltaT = (ofGetElapsedTimeMillis() - lastTimeSample) / 1000.0;
	float phaseSpeed = PI / 2;
	phase += phaseSpeed * deltaT;
	lastTimeSample = ofGetElapsedTimeMillis();


	float phaseScale = ofDist(mousePos.x, mousePos.y, ofGetWidth() / 2, ofGetHeight() / 2) / ofDist(0, 0, ofGetWidth() / 2, ofGetHeight() / 2);
	int radius = 10, numEllipses = 30;
	ofFloatColor initial(1, 0, 0), final(0.5, 1, 0);
	for(int i = 0; i < numEllipses; i++, radius += 10) {
		float step = i / (float)(numEllipses - 1);

		ofSetColor(initial.getLerped(final, step));
		drawEllipse(200, ofPoint(ofGetWidth() / 2, ofGetHeight() / 2), radius * 1.5, radius, ofLerp(10, 100, step) * phaseScale, phase, 4);
	}	

	ofSetColor(255);

	if(showHelp){
		ofSetColor(0, 0, 0, 200);
		ofRect(0, 0, ofGetWidth(), ofGetHeight());		

		ofSetColor(255);
		ofPoint start(20, ofGetHeight() - 160);
		ofDrawBitmapString("Tips:", start.x, start.y += 20);
		ofDrawBitmapString("-30 elipses concéntricas pintadas como lineas con las ecuaciones parametricas de la elipse", start.x, start.y += 20);
		ofDrawBitmapString("-Su color cambia de rojo a verde de adentro hacia afuera", start.x, start.y += 20);
		ofDrawBitmapString("-Su radio es modificado por una onda seno de 4 periodos y de amplitud variable de acuerdo con la", start.x, start.y += 20);
		ofDrawBitmapString(" distancia del mouse al centro de la pantalla", start.x, start.y += 20);
		ofDrawBitmapString("-La fase de la onda seno que modifica los radios aumenta a razon de PI/2 por segundo", start.x, start.y += 20);
		ofDrawBitmapString("Puntaje: 2", start.x, start.y += 20);
	}
}

string State3::getStateName(){
	return "State3";
}

void State3::keyPressed(int key){
}

void State3::keyReleased(int key){
	if(key == 'h' || key == 'H')
		showHelp = !showHelp;
}

void State3::mouseMoved(int x, int y ){
	mousePos = ofPoint(x, y);
}

void State3::mousePressed(int x, int y, int button){	
}

void State3::mouseReleased(int x, int y, int button){
}

void State3::mouseDragged(int x, int y, int button){	
}

void State3::in(){
	showHelp = false;
}

void State3::out(){
}