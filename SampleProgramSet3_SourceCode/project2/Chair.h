//Chair.h

#ifndef CHAIR_H
#define CHAIR_H

#include "ModelView.h"
#include "ShaderIF.h"
#include "Table.h"
#include "Block.h"
#include <GL/gl.h>

class Chair : public ModelView
{
public:
	// As before: you will likely want to add parameters to the constructor
	Chair(ShaderIF* sIF, float blx, float bly, float blz, float lx, float ly, float lz, float r, float g, float b);
	virtual ~TEMPLATE_Subclass();

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
	Table* seatBase;

	static GLuint indexList[3][4];
};

#endif
