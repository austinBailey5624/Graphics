// Cylinder.h
//NOTE: based on Cylinder from MandM
#ifndef CYLINDER_H
#define CYLINDER_H

#include "SceneElement.h"
#include "ShaderIF.h"

class Cylinder : public SceneElement
{
public:

	Cylinder(ShaderIF* sIF, PhongMaterial& matl, float radius, const cryph::AffPoint& topCenter, cryph::AffPoint& bottomCenter, int numPoints);
	~Cylinder();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
	float checkFloat(float f);

	float xmin;
	float xmax;
	float ymin;
	float ymax;
	float zmin;
	float zmax;
	int numCircumferencePoints;
	cryph::AffVector direction;
private:
	ShaderIF* shaderIF;
	GLuint vao[1];
	GLuint vbo[2];
//	float kd[3];
};

#endif
