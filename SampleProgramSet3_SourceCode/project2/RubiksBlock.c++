

#include "RubiksBlock.h"

RubiksBlock::RubiksBlock(ShaderIF* sIF, float cx, float cy, float cz, float length) : shaderIF(sIF)
{
	//only one length because all sides of the rubiks are same length

	xmin = cx;
	ymin = cy;
	zmin = cz;
	xmax = xmin + length;
	ymax = ymin + length;
	zmax = zmin + length;
	double offset = .05;//a fraction representing how much of the block gets cut off from the sides

	float colorTop[3] = {1.0,1.0,1.0};
	float colorBottom[3] = {1.0,1.0,0};
	float colorRight[3] = {0,0,1.0};
	float colorLeft[3] = {0,1.0,0};
	float colorFront[3] = {1.0,0,0};
	float colorBack[3] = {1.0,0.5,0};
	double localxmin = xmin+offset*length;
	double localymin = ymin+offset*length;
	double localzmin = zmin+offset*length;
	double localxmax = xmax-offset*length;
	double localymax = ymax-offset*length;
	double localzmax = zmax-offset*length;



	//bottom = new Block(sIF, xmin, ymin, zmin, length, length, length, colorBottom[0], colorBottom[1], colorBottom[2]);

	top = new Block(sIF, localxmin, localymax, localzmin, localxmax-localxmin, ymax-localymax, localzmax-localzmin,colorTop[0],colorTop[1],colorTop[2]);

	bottom = new Block(sIF, localxmin, ymin, localzmin, localxmax-localxmin, localymin-ymin, localzmax-localzmin, colorBottom[0], colorBottom[1], colorBottom[2]);

	right = new Block(sIF, xmin,localymin,localzmin ,localxmin-xmin,localymax-localymin,localzmax-localzmin,colorRight[0],colorRight[1],colorRight[2]);

	left = new Block(sIF, localxmax, localymin,localzmin,xmax-localxmax,localymax-localymin,localzmax-localzmin,colorLeft[0],colorLeft[1],colorLeft[2]);

	front = new Block(sIF, localxmin, localymin, zmin, localxmax-localxmin, localymax-localymin, localzmin-zmin, colorFront[0], colorFront[1], colorFront[2]);

	back = new Block(sIF, localxmin, localymin,localzmax, localxmax-localxmin, localymax-localymin,zmax-localzmax,colorBack[0], colorBack[1], colorFront[2]);
	//bottom = new Block(sIF,localxmin,ymin,localzmin,localxmax,localymin,localzmax,colorBottom[0], colorBottom[1], colorBottom[2]);


}

RubiksBlock::~RubiksBlock()
{
	delete top;
	delete bottom;
	delete right;
	delete left;
	delete front;
	delete back;
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void RubiksBlock::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

void RubiksBlock::render()
{
	top->render();
	bottom->render();
	right->render();
	left->render();
	front->render();
	back->render();
}
