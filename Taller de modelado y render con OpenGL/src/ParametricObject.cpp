#include "ParametricObject.h"


ParametricObject::ParametricObject(int w, int h) {
	this->w = w;
	this->h = h;
}

ParametricObject::~ParametricObject() {
}

void ParametricObject::generateGrid() {
	points.clear();
	normals.clear();

	//Generate vertices
	float hInc = 1.0 / (w - 1), vInc = 1.0 / (h - 1);
	ofPoint current;
	for(int i = 0; i < h; i++, current.y += vInc) {
		current.x = 0;
		for(int j = 0; j < w; j++, current.x += hInc) {
			points.push_back(computePosition(current));
			normals.push_back(computeNormal(current));
		}
	}

	//Generate triangles
	for(int i = 0; i < h - 1; i++) {
		for(int j = 0; j < w - 1; j++) {
			triangles.push_back(INDEX(i, j, w));
			triangles.push_back(INDEX(i + 1, j, w));
			triangles.push_back(INDEX(i + 1, j + 1, w));

			triangles.push_back(INDEX(i, j, w));
			triangles.push_back(INDEX(i + 1, j + 1, w));
			triangles.push_back(INDEX(i, j + 1, w));
		}
	}
}

void ParametricObject::draw(ofPoint position, ofFloatColor ambient, ofFloatColor diffuse, ofFloatColor specular, float shininess, RenderMode renderMode){
	if(points.size() == 0 || normals.size() == 0 || triangles.size() == 0)
		generateGrid();

	glMaterialfv(GL_FRONT, GL_AMBIENT, &ambient.r);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &diffuse.r);
	glMaterialfv(GL_FRONT, GL_SPECULAR, &specular.r);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	glTranslatef(position.x, position.y, position.z);

	if(renderMode == WIREFRAME)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBegin(renderMode == POINTS ? GL_POINTS : GL_TRIANGLES);
		for(int i = 0; i < triangles.size(); i += 3) {
			for(int j = 0; j < 3; j++) {
				glNormal3fv(&normals[triangles[i + j]].x);
				glVertex3fv(&points[triangles[i + j]].x);
			}		
		}
	glEnd();

	if(renderMode == WIREFRAME)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}