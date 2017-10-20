//Chair.h

#ifndef CHAIR_H
#define CHAIR_H

#include "ModelView.h"
#include "ShaderIF.h"
#include "Block.h"
#include "Cylinder.h"
#include <GL/gl.h>

class Chair : public ModelView
{
public:
	// As before: you will likely want to add parameters to the constructor
	Chair(ShaderIF* sIF, float blx, float bly, float blz, float lxz, float ly, float r, float g, float b, int direction);
	virtual ~Chair();
	//the length of x is forced to be the same as the length of z



	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	ShaderIF* shaderIF;
	float kd[3];
	float xmin;
	float xmax;
	float ymin;
	float ymax;
	float zmin;
	float zmax;

	Block* seatBack;
	Block* seatBase;
	Cylinder* frontRightLeg;
	Cylinder* frontLeftLeg;
	Cylinder* backRightLeg;
	Cylinder* backLeftLeg;

	static GLuint indexList[3][4];
};

#endif
