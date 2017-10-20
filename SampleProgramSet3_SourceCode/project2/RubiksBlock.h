// TEMPLATE_Subclass.h

#ifndef RUBIKSBLOCK_H
#define RUBIKSBLOCK_H

#include "ModelView.h"
#include "ShaderIF.h"
#include "Block.h"
class RubiksBlock : public ModelView
{
public:
	// As before: you will likely want to add parameters to the constructor
	RubiksBlock(ShaderIF* sIF, float cx, float cy, float cz, float length);
	RubiksBlock(ShaderIF* sIF, float cx, float cy, float cz, float length, int white, int red, int blue);//int white,red,and blue determine the directions of red white and blue
	virtual ~RubiksBlock();

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

	Block* top;
	Block* bottom;
	Block* right;
	Block* left;
	Block* front;
	Block* back;

	static GLuint indexList[3][4];
};

#endif
