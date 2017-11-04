// RubiksCube.h

#ifndef RUBIKSCUBE_H
#define RUBIKSCUBE_H

#include "SceneElement.h"
#include "ShaderIF.h"
#include "RubiksBlock.h"
#include <GL/gl.h>

class RubiksCube : public SceneElement
{
public:
	// As before: you will likely want to add parameters to the constructor
	RubiksCube(ShaderIF* sIF,PhongMaterial& matl, float xmin,float ymin,float zmin, float l, int which);
	virtual ~RubiksCube();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	RubiksBlock* blocks[3][3][3];
	ShaderIF* shaderIF;
	float xmin;
	float xmax;
	float ymin;
	float ymax;
	float zmin;
	float zmax;

};

#endif
