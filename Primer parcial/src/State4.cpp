#include "State4.h"

State4::State4(StateMachineApp* app) : State(app){	
}

void State4::setup(){
	lastTimeSample = 0;
	phase = 0;

	showHelp = false;
}

void State4::update(){
}

void State4::drawEllipse(int steps, ofPoint position, float xRadius, float yRadius, float amplitude, float phase, int periods) {
	float angle = 0, angleInc = TWO_PI / steps;
	glBegin(GL_LINE_LOOP);
		for(int i = 0; i < steps; i++, angle += angleInc){
			float sineWave = amplitude * sin(angle / TWO_PI * (TWO_PI * periods) + phase);
			glVertex3f(xRadius * cos(angle) + position.x + sineWave, yRadius * sin(angle) + position.y + sineWave, position.z);
		}
	glEnd();
}

void State4::draw(){
	ofBackground(0);

	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	if(lastTimeSample == 0){
		lastTimeSample = ofGetElapsedTimeMillis();
		return;
	}
	
	float deltaT = (ofGetElapsedTimeMillis() - lastTimeSample) / 1000.0;
	float phaseSpeed = PI / 2;
	phase += phaseSpeed * deltaT;
	lastTimeSample = ofGetElapsedTimeMillis();

	ofFloatColor initial(0, 1, 0), final(1, 1, 0);
	float amplitude = 100;
	for(int y = 0; y < ofGetHeight(); y += 10){
		for(int x = 0; x < ofGetWidth(); x += 10){
			float height = amplitude * sin(x / (float)ofGetWidth() * 2 * TWO_PI + phase) * cos(y / (float)ofGetHeight() * 2 * TWO_PI + phase);
			float mappedHeight = ofMap(height, -amplitude, amplitude, 0, 1, true);
						
			glPointSize(10 * mappedHeight);
			glBegin(GL_POINTS);
				ofSetColor(initial.getLerped(final, mappedHeight));				
				glVertex3f(x, y, height + 100);
			glEnd();
		}
	}	

	glPointSize(1);
	ofSetColor(255);

	if(showHelp){
		ofSetColor(0, 0, 0, 200);
		ofRect(0, 0, ofGetWidth(), ofGetHeight());		

		ofSetColor(255);
		ofPoint start(20, ofGetHeight() - 180);
		ofDrawBitmapString("Tips:", start.x, start.y += 20);
		ofDrawBitmapString("-Puntos pintados cada 10 pixeles vertical y horizontalmente con GL_POINTS", start.x, start.y += 20);
		ofDrawBitmapString("-Su profundidad esta dada por una ecuacion basada en sin(x)cos(y) con fase que se incrementa a razon de PI/2 por segundo", start.x, start.y += 20);
		ofDrawBitmapString("-Su color se basa en la profundidad y se mapea entre verde y amarillo", start.x, start.y += 20);
		ofDrawBitmapString("-Su radio (modificado usando glPointSize) se basa en la profundidad", start.x, start.y += 20);
		ofDrawBitmapString("-No se puede usar glPointSize dentro de bloques glBegin() - glEnd()", start.x, start.y += 20);
		ofDrawBitmapString("-Usar suavizado de puntos como figura en el segundo taller", start.x, start.y += 20);
		ofDrawBitmapString("Puntaje: 3", start.x, start.y += 20);
	}
}

string State4::getStateName(){
	return "State4";
}

void State4::keyPressed(int key){
}

void State4::keyReleased(int key){
	if(key == 'h' || key == 'H')
		showHelp = !showHelp;
}

void State4::mouseMoved(int x, int y ){
	mousePos = ofPoint(x, y);
}

void State4::mousePressed(int x, int y, int button){	
}

void State4::mouseReleased(int x, int y, int button){
}

void State4::mouseDragged(int x, int y, int button){	
}

void State4::in(){
	showHelp = false;
}

void State4::out(){
}