#include "InitialState.h"
#include "Poco/Base64Decoder.h"
#include "Poco/Base64Encoder.h"
#include "Poco\StreamCopier.h"
#include "..\resource.h"
#include <winbase.h>

InitialState::InitialState(StateMachineApp* app) : State(app){	
}

void InitialState::encodeFile(string fileName){
	if(ofFile::doesFileExist(fileName)){
		ofFile file;
		file.open(fileName, ofFile::ReadOnly);
		ofBuffer buf = file.readToBuffer();

		ostringstream ostr;
		Poco::Base64Encoder encoder(ostr);
		encoder << buf.getText();
		encoder.close();

		string outputStr = ostr.str();
		string output = ofFilePath::getBaseName(fileName) + (ofToLower(ofFilePath::getFileExt(fileName)) == "vert" ? ".v" : ".f");
		ofstream str;
		str.open(output, ios_base::out | ios_base::trunc);
		str << outputStr;		
		str.close();
	}
}

string InitialState::decode(int shaderResourceID){
	HRSRC h = FindResourceW(NULL, MAKEINTRESOURCE(shaderResourceID), L"SHADER");
	HGLOBAL hRes = LoadResource(NULL, h);
	char* resData = (char*)LockResource(hRes);
	int size = SizeofResource(NULL, h);
	char* newData = new char[size + 1];
	memset(newData, 0, size + 1);
	memcpy(newData, resData, size + 1);
	string s(newData);
	delete []newData;

	ostringstream ostr;
	istringstream istr(s);

	Poco::Base64Decoder decoder(istr);
	Poco::StreamCopier::copyStream(decoder, ostr);

	return ostr.str();
}

void InitialState::setup(){
	ofSetFrameRate(60);

	vector<string> text;

	gui[0].setup();
	gui[0].add(rWeight.setup("rWeight", 1/3.0, 0, 1));
	gui[0].add(gWeight.setup("gWeight", 1/3.0, 0, 1));
	gui[0].add(bWeight.setup("bWeight", 1/3.0, 0, 1));
	gui[0].add(power.setup("power", 1, 0, 5));
	text.push_back("Tip: Promedio ponderado con pesos dados elevado a una potencia.");
	text.push_back("Aconsejo hacerlo para que practiquen.");
	text.push_back("Puntaje: 1 punto.");
	texts[0] = text;

	gui[1].setup();
	gui[1].add(runningAverageFactor.setup("factor", 0.93, 0, 1));
	text.clear();
	text.push_back("Tip: El fbo resultado del frame anterior entra como parametro y se mezcla");
	text.push_back("con el frame actual de la camara linealmente de acuerdo con un factor");
	text.push_back("Puntaje: 1.5 puntos.");
	texts[1] = text;

	gui[2].setup();
	gui[2].add(motionDiffThreshold.setup("Motion diff distance", 0.3, 0, 1));
	text.clear();
	text.push_back("Tip: Se resalta cada fragmento  con un color anaranjado de acuerdo con su distancia");
	text.push_back("en el espacio de color al pixel del frame anterior. Se acumula de acuerdo con el");
	text.push_back("frame anterior de forma similar al anterior ejercicio.");	
	text.push_back("Puntaje: 1.5 puntos.");
	texts[2] = text;

	gui[3].setup();
	gui[3].add(cellSize.setup("cellSize", 20, 1, 100));
	gui[3].add(radius.setup("radius", 8, 1, 50));
	text.clear();
	text.push_back("Tip: Se asigna el color del centro de circulos de radio cellSize a circulos construidos en espacios");
	text.push_back("circulares del mismo tamano con radio dado. Se agrega un borde azul de 1.5 pixeles");
	text.push_back("Puntaje: 2 puntos.");
	texts[3] = text;

	gui[4].setup();
	gui[4].add(scale.setup("scale", 0.03, 0.0001, 1));
	text.clear();
	text.push_back("Tip: Se pintan miniaturas de la imagen completa en secciones de tamaño escalado por un factor");
	text.push_back("El color de cada miniatura se asigna de acuerdo a un color de la posición original");
	text.push_back("Puntaje: 2 puntos.");
	texts[4] = text;

	cam.initGrabber(960, 720, true);
	fboCam.allocate(cam.getWidth(), cam.getHeight(), GL_RGB);
	
	shaderGrayscale.setupShaderFromSource(GL_VERTEX_SHADER, decode(IDR_SHADER_GRAYSCALEV));
	shaderGrayscale.setupShaderFromSource(GL_FRAGMENT_SHADER, decode(IDR_SHADER_GRAYSCALEF));
	shaderGrayscale.linkProgram();
	fboGrayscale.allocate(ofGetWidth(), ofGetHeight(), GL_RGB32F);
	
	fboRunningAverage.allocate(ofGetWidth(), ofGetHeight(), GL_RGB32F);
	shaderRunningAverage.setupShaderFromSource(GL_VERTEX_SHADER, decode(IDR_SHADER_RUNNINGV));
	shaderRunningAverage.setupShaderFromSource(GL_FRAGMENT_SHADER, decode(IDR_SHADER_RUNNINGF));
	shaderRunningAverage.linkProgram();
	fboLast.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);

	shaderMotionDiff.setupShaderFromSource(GL_VERTEX_SHADER, decode(IDR_SHADER_MOTIONV));
	shaderMotionDiff.setupShaderFromSource(GL_FRAGMENT_SHADER, decode(IDR_SHADER_MOTIONF));
	shaderMotionDiff.linkProgram();
	fboMotionDiff.allocate(ofGetWidth(), ofGetHeight());
	fboLastCam.allocate(960, 720);

	shaderCartoonizer.setupShaderFromSource(GL_VERTEX_SHADER, decode(IDR_SHADER_CARTOONIZERV));
	shaderCartoonizer.setupShaderFromSource(GL_FRAGMENT_SHADER, decode(IDR_SHADER_CARTOONIZERF));
	shaderCartoonizer.linkProgram();
	fboCartoonizer.allocate(ofGetWidth(), ofGetHeight());

	shaderMosaic.setupShaderFromSource(GL_VERTEX_SHADER, decode(IDR_SHADER_MOSAICV));
	shaderMosaic.setupShaderFromSource(GL_FRAGMENT_SHADER, decode(IDR_SHADERMOSAICF));
	shaderMosaic.linkProgram();
	fboMosaic.allocate(ofGetWidth(), ofGetHeight());

	/*video1.loadMovie("Malcolm_Precomp.mov");
	video1.setLoopState(OF_LOOP_NONE);
	video1.play();
	video1.update();
	video1.stop();

	video2.loadMovie("Vanessa_Cinemagraph_6.mov");
	video2.setLoopState(OF_LOOP_NONE);
	video2.play();
	video2.update();
	video2.stop();
	showVideo = 0;*/

	drawGui = true;

	exerciseIndex = 0;
}

void InitialState::update(){
}

void InitialState::draw(){
	cam.update();

	if(cam.isFrameNew()){
		fboCam.begin();
			cam.draw(0, 0);
		fboCam.end();
	}

	ofBackgroundGradient(ofColor(64), ofColor(0), OF_GRADIENT_BAR);
	
	if(exerciseIndex == 0){
		fboGrayscale.begin();
			shaderGrayscale.begin();
				shaderGrayscale.setUniformTexture("tex", cam.getTextureReference(), 0);
				shaderGrayscale.setUniform1f("rWeight", rWeight);
				shaderGrayscale.setUniform1f("gWeight", gWeight);
				shaderGrayscale.setUniform1f("bWeight", bWeight);
				shaderGrayscale.setUniform1f("power", power);			

				ofRect(0, 0, fboGrayscale.getWidth(), fboGrayscale.getHeight());
			shaderGrayscale.end();
		fboGrayscale.end();

		fboGrayscale.draw(0, 0);
	} else if(exerciseIndex == 1){
		fboRunningAverage.begin();
			shaderRunningAverage.begin();
				shaderRunningAverage.setUniformTexture("tex", cam.getTextureReference(), 0);
				shaderRunningAverage.setUniformTexture("lastTex", fboLast.getTextureReference(), 1);
				shaderRunningAverage.setUniform1f("factor", runningAverageFactor);

				ofRect(0, 0, fboRunningAverage.getWidth(), fboRunningAverage.getHeight());
			shaderGrayscale.end();
		fboRunningAverage.end();

		fboRunningAverage.draw(0, 0);

		fboLast.begin();
			fboRunningAverage.draw(0, 0, fboLast.getWidth(), fboLast.getHeight());
		fboLast.end();
	} else if(exerciseIndex == 2){
		fboMotionDiff.begin();
			shaderMotionDiff.begin();
				shaderMotionDiff.setUniformTexture("tex", fboCam.getTextureReference(), 0);
				shaderMotionDiff.setUniformTexture("lastTex", fboLastCam.getTextureReference(), 1);
				shaderMotionDiff.setUniformTexture("lastOutput", fboLast.getTextureReference(), 2);
				shaderMotionDiff.setUniform1f("factor", motionDiffThreshold);

				static float colorPhase = 0;
				shaderMotionDiff.setUniform1f("colorPhase", colorPhase += 0.01);
				

				ofRect(0, 0, fboMotionDiff.getWidth(), fboMotionDiff.getHeight());
			shaderGrayscale.end();
		fboMotionDiff.end();

		fboMotionDiff.draw(0, 0);

		fboLast.begin();
			fboMotionDiff.draw(0, 0, fboLast.getWidth(), fboLast.getHeight());
		fboLast.end();

		fboLastCam.begin();
			cam.draw(0, 0, fboLastCam.getWidth(), fboLastCam.getHeight());
		fboLastCam.end();
	} else if(exerciseIndex == 3){
		fboCartoonizer.begin();
			shaderCartoonizer.begin();
				shaderCartoonizer.setUniformTexture("tex", cam.getTextureReference(), 0);
				shaderCartoonizer.setUniform1i("cellSize", cellSize);
				shaderCartoonizer.setUniform1i("radius", radius);				
				
				ofRect(0, 0, fboCartoonizer.getWidth(), fboCartoonizer.getHeight());
			shaderGrayscale.end();
		fboCartoonizer.end();

		fboCartoonizer.draw(0, 0);
	} else if(exerciseIndex == 4){
		fboMosaic.begin();
			shaderMosaic.begin();
				shaderMosaic.setUniformTexture("tex", cam.getTextureReference(), 0);
				shaderMosaic.setUniform1f("scale", scale);				
				shaderMosaic.setUniform2f("size", cam.getWidth(), cam.getHeight());				
				
				ofRect(0, 0, fboMosaic.getWidth(), fboMosaic.getHeight());
			shaderMosaic.end();
		fboMosaic.end();

		fboMosaic.draw(0, 0);
	}

	
	
	/*if(showVideo == 1){
		int frame = ofLerp(0, video1.getTotalNumFrames(), ofGetMouseX() / (float)ofGetWidth());
		video1.setFrame(frame);
		video1.play();
		video1.update();
		video1.stop();
		video1.draw(ofGetWidth(), 0, -ofGetWidth(), ofGetHeight());
		ofDrawBitmapString("Frame: " + ofToString(frame), 20, ofGetHeight() - 40);
	} else if(showVideo == 2){
		int frame = ofLerp(0, video2.getTotalNumFrames(), ofGetMouseX() / (float)ofGetWidth());
		video2.setFrame(frame);
		video2.play();
		video2.update();
		video2.stop();
		video2.draw(ofGetWidth(), 0, -ofGetWidth(), ofGetHeight());
		ofDrawBitmapString("Frame: " + ofToString(frame), 20, ofGetHeight() - 40);
	}*/

	if(drawGui)
		gui[exerciseIndex].draw();

	int y = ofGetHeight() - 20;
	for(int i = texts[exerciseIndex].size() - 1; i >= 0; i--, y -= 20){
		ofDrawBitmapString(texts[exerciseIndex][i], 20, y);
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

	if(key == 358)
		++exerciseIndex %= NUM_EXERCISES;
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