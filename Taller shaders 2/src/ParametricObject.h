#pragma once

#include <ofMain.h>

#define INDEX(row, col, w) ((row) * w + col)

class ParametricObject {
public:
	ParametricObject(int w, int h);
	~ParametricObject();

	typedef enum{POINTS, WIREFRAME, SOLID} RenderMode;

	virtual ofPoint computePosition(ofPoint point) = 0;
	virtual ofPoint computeNormal(ofPoint point) = 0;

	void draw(ofPoint position, ofFloatColor ambient, ofFloatColor diffuse, ofFloatColor specular, float shininess, RenderMode renderMode);

protected:
	void						generateGrid();

	int					w, h;
	vector<ofPoint>		points;
	vector<ofPoint>		normals;
	vector<int>			triangles;
};