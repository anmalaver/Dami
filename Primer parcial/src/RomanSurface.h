#pragma once

#include "ParametricObject.h"

class RomanSurface : public ParametricObject {
public:
	RomanSurface(int w, int h, float r);
	~RomanSurface(void);

	ofPoint computePosition(ofPoint point);
	ofPoint computeNormal(ofPoint point);

protected:
	float r;
};

