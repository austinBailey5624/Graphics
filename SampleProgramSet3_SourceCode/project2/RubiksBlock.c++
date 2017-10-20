

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

RubiksBlock::RubiksBlock(ShaderIF* sIF, float cx, float cy, float cz, float length,int white, int red, int blue) : shaderIF(sIF)
{
	//1::top
	//2::bottom
	//3::right
	//4::left
	//5::front
	//6::back
	//only one length because all sides of the rubiks are same length

	float colorTop[3] = {1.0,1.0,1.0};
	float colorBottom[3] = {1.0,1.0,0};
	float colorRight[3] = {0,0,1.0};
	float colorLeft[3] = {0,1.0,0};
	float colorFront[3] = {1.0,0,0};
	float colorBack[3] = {1.0,0.5,0};

	xmin = cx;
	ymin = cy;
	zmin = cz;
	xmax = xmin + length;
	ymax = ymin + length;
	zmax = zmin + length;
	double offset = .05;//a fraction representing how much of the block gets cut off from the sides

	float w[3] = {1.0,1.0,1.0};
	float y[3] = {1.0,1.0,0};
	float b[3] = {0,0,1.0};
	float g[3] = {0,1.0,0};
	float r[3] = {1.0,0,0};
	float o[3] = {1.0,0.5,0};

	if(white==1)
	{
		colorTop[0] = w[0];
		colorTop[1] = w[1];
		colorTop[2] = w[2];
		colorBottom[3] = y[3];
	}
	else if(white==2)
	{
		colorBottom[0] = w[0];
		colorBottom[1] = w[1];
		colorBottom[2] = w[2];
//		colorBottom[3] = w[3];
		colorTop[0] = y[0];
		colorTop[1] = y[1];
		colorTop[2] = y[2];
//		colorTop[3] = y[3];
	}
	else if(white==3)
	{
		colorRight[3] = w[3];
		colorLeft[3] = y[3];
	}
	else if(white==4)
	{
		colorLeft[3] = w[3];
		colorRight[3] = y[3];
	}
	else if(white==5)
	{
		colorFront[3] = w[3];
		colorBack[3] = y[3];
	}
	else if(white==6)
	{
		colorBack[3] = w[3];
		colorFront[3] = y[3];
	}
	if(red==1)
	{
		colorTop[3] = r[3];
		colorBottom[3] = o[3];
	}
	else if(red==2)
	{
		colorBottom[3] = r[3];
		colorTop[3] = o[3];
	}
	else if(red==3)
	{
		colorRight[3] = r[3];
		colorLeft[3] = o[3];
	}
	else if(red==4)
	{
		colorLeft[3] = r[3];
		colorRight[3] = o[3];
	}
	else if(red==5)
	{
		colorFront[3] = r[3];
		colorBack[3] = o[3];
	}
	else if(red==6)
	{
	//	colorBack[3] = r[3];
	//	colorFront[3] = o[3];
		colorBack[0] = r[0];
		colorBack[1] = r[1];
		colorBack[2] = r[2];
		colorFront[0] = o[0];
		colorFront[1] = o[1];
		colorFront[2] = o[2];
	}
	if(blue==1)
	{
		colorTop[3] = b[3];
		colorBottom[3] = g[3];
	}
	else if(blue==2)
	{
		colorBottom[3] = b[3];
		colorTop[3] = g[3];
	}
	else if(blue==3)
	{
		colorRight[3] = b[3];
		colorLeft[3] = g[3];
	}
	else if(blue==4)
	{
	//	colorLeft[3] = b[3];
	//	colorRight[3] = g[3];
		colorLeft[0] = b[0];
		colorLeft[1] = b[1];
		colorLeft[2] = b[2];
		colorRight[0] = g[0];
		colorRight[1] = g[1];
		colorRight[2] = g[2];
	}
	else if(blue==5)
	{
		colorFront[3] = b[3];
		colorBack[3] = g[3];
	}
	else if(blue==6)
	{
		colorBack[3] = b[3];
		colorFront[3] = g[3];
	}
	double localxmin = xmin+offset*length;
	double localymin = ymin+offset*length;
	double localzmin = zmin+offset*length;
	double localxmax = xmax-offset*length;
	double localymax = ymax-offset*length;
	double localzmax = zmax-offset*length;


	top = new Block(sIF, localxmin, localymax, localzmin, localxmax-localxmin, ymax-localymax, localzmax-localzmin,colorTop[0],colorTop[1],colorTop[2]);

	bottom = new Block(sIF, localxmin, ymin, localzmin, localxmax-localxmin, localymin-ymin, localzmax-localzmin, colorBottom[0], colorBottom[1], colorBottom[2]);

	right = new Block(sIF, xmin,localymin,localzmin ,localxmin-xmin,localymax-localymin,localzmax-localzmin,colorRight[0],colorRight[1],colorRight[2]);

	left = new Block(sIF, localxmax, localymin,localzmin,xmax-localxmax,localymax-localymin,localzmax-localzmin,colorLeft[0],colorLeft[1],colorLeft[2]);

	front = new Block(sIF, localxmin, localymin, zmin, localxmax-localxmin, localymax-localymin, localzmin-zmin, colorFront[0], colorFront[1], colorFront[2]);

	back = new Block(sIF, localxmin, localymin,localzmax, localxmax-localxmin, localymax-localymin,zmax-localzmax,colorBack[0], colorBack[1], colorFront[2]);
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
