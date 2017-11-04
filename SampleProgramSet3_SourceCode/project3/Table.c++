//Table.c++

#include "Table.h"

typedef float vec3[3];

Table::Table(ShaderIF* sIF, PhongMaterial& base, float blx, float bly, float blz, float lx, float ly, float lz) : SceneElement(sIF,matl)
{
	xmin = blx;
	ymin = bly;
	zmin = blz;
	xmax = xmin + lx;
	ymax = ymin + ly;
	zmax = zmin + lz;


	double legwidth=.1;//a fraction representing the leg witdth as a portion of the tables width
	double legheight=.8;//a fraction representing the leg height as a portion of the tables height
	double deltax = xmax - xmin;
	double deltay = ymax - ymin;
	double deltaz = zmax - zmin;
	double localymin = ymin + (legheight)*ly;
	double localylength = (1-legheight)*ly;

	top = new Block(sIF,base,xmin,localymin,zmin,lx,localylength,lz);
	double localxlength = legwidth*lx;
	localylength = legheight*ly;
	double localzlength = legwidth*lz;
	frontRightLeg = new Block(sIF,base,xmin,ymin,zmin,localxlength,localylength,localzlength);
	double localxmin = xmax-legwidth*lx;

	frontLeftLeg = new Block(sIF,base,localxmin,ymin,zmin,localxlength,localylength,localzlength);
	double localzmin = zmax - legwidth*lz;
	backRightLeg = new Block(sIF,base,xmin,ymin,localzmin,localxlength,localylength,localzlength);
	backLeftLeg = new Block(sIF,base,localxmin,ymin,localzmin,localxlength,localylength,localzlength);
}

Table::~Table()
{
	delete top;
	delete frontRightLeg;
	delete frontLeftLeg;
	delete backRightLeg;
	delete backLeftLeg;
}

void Table::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

bool Table::handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY)
{
	// Block does not look for events; just hand off to inherited handleCommand.
	return this->ModelView::handleCommand(anASCIIChar, ldsX, ldsY);
}

void Table::render()
{
	top->render();
	frontRightLeg->render();
	frontLeftLeg->render();
	backRightLeg->render();
	backLeftLeg->render();
}
