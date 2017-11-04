

#include "RubiksBlock.h"



RubiksBlock::RubiksBlock(ShaderIF* sIF, PhongMaterial &base, float cx, float cy, float cz, float length, int whitedir, int reddir) : SceneElement(sIF,base)
{
	//only one length because all sides of the rubiks are same length

	xmin = cx;
	ymin = cy;
	zmin = cz;
	xmax = xmin + length;
	ymax = ymin + length;
	zmax = zmin + length;
	double offset = .05;//a fraction representing how much of the block gets cut off from the sides

	PhongMaterial white(1,1,1,1,1,1,1,1,1,15,1);
	PhongMaterial yellow(1,1,0,1,1,0,1,1,0,15,1);
	PhongMaterial blue(0,0,1,0,0,1,0,0,1,15,1);
	PhongMaterial green(0,1,0,0,1,0,0,1,0,15,1);
	PhongMaterial red(1,0,0,1,0,0,1,0,0,15,1);
	PhongMaterial orange(1,.5,0,1,.5,0,1,.5,0,15,1);



	float localxmin = xmin+offset*length;
 	float localymin = ymin+offset*length;
	float localzmin = zmin+offset*length;
	float localxmax = xmax-offset*length;
	float localymax = ymax-offset*length;
	float localzmax = zmax-offset*length;



//	top = new Block(sIF, base, xmin, ymin, zmin, length, length, length);

	top = new Block(sIF, white, localxmin, localymax, localzmin, localxmax-localxmin, ymax-localymax, localzmax-localzmin);

	bottom = new Block(sIF, yellow, localxmin, ymin, localzmin, localxmax-localxmin, localymin-ymin, localzmax-localzmin);

	right = new Block(sIF, blue, xmin,localymin,localzmin ,localxmin-xmin,localymax-localymin,localzmax-localzmin);;

	left = new Block(sIF, green,localxmax, localymin,localzmin,xmax-localxmax,localymax-localymin,localzmax-localzmin);

	front = new Block(sIF,red, localxmin, localymin, zmin, localxmax-localxmin, localymax-localymin, localzmin-zmin);

	back = new Block(sIF,orange, localxmin, localymin,localzmax, localxmax-localxmin, localymax-localymin,zmax-localzmax);
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
