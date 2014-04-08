#include "RomanSurface.h"

RomanSurface::RomanSurface(int w, int h, float r) : ParametricObject(w, h) {
	this->r = r;
}

RomanSurface::~RomanSurface(void){
}

ofPoint RomanSurface::computePosition(ofPoint point){
	float phi = point.x * TWO_PI, theta = point.y * HALF_PI;
	
	return ofPoint(r * r * cos(theta) * sin(theta) * sin(phi),
				   r * r * cos(theta) * sin(theta) * cos(phi),
				   r * r * cos(theta) * cos(theta) * cos(phi) * sin(phi));
}

ofPoint RomanSurface::computeNormal(ofPoint point){
	float phi = point.x * TWO_PI, theta = point.y * HALF_PI;	

	ofPoint dTheta = ofPoint(r * r * cos(2 * theta) * sin(phi),
							 r * r * cos(2 * theta) * cos(phi),
							 -2 * r * r * sin(theta) * cos(theta) * sin(phi) * cos(phi));

	ofPoint dPhi = ofPoint(r * r * sin(theta) * cos(theta) * cos(phi),
						   -r * r * sin(theta) * cos(theta) * sin(phi),
						   r * r * cos(theta) * cos(theta) * cos(2 * phi));

	ofPoint normal = dPhi.getCrossed(dTheta).getNormalized();
	return normal;
}