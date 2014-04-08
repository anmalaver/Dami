#include "SineSurface.h"

SineSurface::SineSurface(int w, int h, float amplitude, int periods, float phase, ofPoint size) : ParametricObject(w, h) {
	this->amplitude = amplitude;
	this->periods = periods;
	this->size = size;
	this->phase = phase;
}

SineSurface::~SineSurface(void){
}

ofPoint SineSurface::computePosition(ofPoint point){
	point = (point - ofPoint(0.5, 0.5)) * size;

	float distance = ofDist(point.x, point.y, 0, 0);
	float maxDistance = ofDist(0, 0, size.x / 2, size.y / 2);

	float height = distance / maxDistance * TWO_PI * periods;
	return ofPoint(point.x, point.y, amplitude * sin(height + phase));
}

ofPoint SineSurface::computeNormal(ofPoint point){
	return ofPoint(0, 0, 1);
}