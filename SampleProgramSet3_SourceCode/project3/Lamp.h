// Lamp.h

#ifndef Lamp_H
#define Lamp_H

#include "SceneElement.h"
#include "ShaderIF.h"
#include "Block.h"
#include <GL/gl.h>

class Lamp : public SceneElement
{
public:
	Lamp(ShaderIF* sIF,PhongMaterial& matl, float blx, float bly, float blz, float lxz, float ly);
	virtual ~Lamp();
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	float xmin;
	float xmax;
	float ymin;
	float ymax;
	float zmin;
	float zmax;

	Block* base;
	Block* stand;
	Block* shade;

};

#endif
