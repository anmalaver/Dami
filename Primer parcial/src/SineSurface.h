#pragma once

#include "ParametricObject.h"

class SineSurface : public ParametricObject {
public:
	SineSurface(int w, int h, float amplitude, int periods, float phase, ofPoint size);
	~SineSurface(void);

	ofPoint computePosition(ofPoint point);
	ofPoint computeNormal(ofPoint point);

protected:
	float	amplitude;
	float	phase;
	int		periods;
	ofPoint size;
};

