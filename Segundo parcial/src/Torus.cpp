#include "Torus.h"

Torus::Torus(int w, int h, int R, int r) : ParametricObject(w, h) {
	this->R = R;
	this->r = r;
}


Torus::~Torus(void){
}

ofPoint Torus::computePosition(ofPoint point){
	float phi = point.x * 2.0 * PI, theta = point.y * 2.0 * PI;
	float R = getBigR(phi, theta/*, 6, 100, 0*/), r = getSmallR(phi, theta/*, 10, 20, 0*/);

	return ofPoint((R - r * cos(theta)) * cos(phi),
				   r * sin(theta),
				   (R - r * cos(theta)) * sin(phi));
}

ofPoint Torus::computeNormal(ofPoint point){
	float phi = point.x * 2.0 * PI, theta = point.y * 2.0 * PI;
	float R = getBigR(phi, theta/*, 6, 100, 0*/), r = getSmallR(phi, theta/*, 10, 20, 0*/);

	ofPoint dTheta = ofPoint(r * sin(theta) * cos(phi),
							 r * cos(theta),
							 r * sin(theta) * sin(phi));

	ofPoint dPhi = ofPoint(-R * sin(phi) + r * cos(theta) * sin(phi),
						   0,
						   R * cos(phi) - r * cos(phi) * cos(theta));

	ofPoint normal = dPhi.getCrossed(dTheta).getNormalized();
	return normal;
}

float Torus::getBigR(float phi, float theta, float periods, float waveMagnitude, float phase) {
	return R + waveMagnitude * sin(periods * phi + phase);
}

float Torus::getSmallR(float phi, float theta, float periods, float waveMagnitude, float phase) {
	return r + waveMagnitude * sin(periods * theta + phase);
}