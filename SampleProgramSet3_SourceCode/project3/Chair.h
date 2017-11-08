//Chair.h

#ifndef CHAIR_H
#define CHAIR_H

#include "SceneElement.h"
#include "ShaderIF.h"
#include "Block.h"
#include <GL/gl.h>

class Chair : public SceneElement
{
public:
	// As before: you will likely want to add parameters to the constructor
	Chair(ShaderIF* sIF, PhongMaterial& base, float blx, float bly, float blz, float lxz, float ly, int direction);
	virtual ~Chair();
	//the length of x is forced to be the same as the length of z
	bool handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY);
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	ShaderIF* shaderIF;
	float xmin;
	float xmax;
	float ymin;
	float ymax;
	float zmin;
	float zmax;
	//bool willRender;

	Block* seatBack;
	Block* seatBase;
	Block* frontRightLeg;
	Block* frontLeftLeg;
	Block* backRightLeg;
	Block* backLeftLeg;

	static GLuint indexList[3][4];
};

#endif
