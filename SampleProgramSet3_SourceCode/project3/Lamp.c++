// Lamp.c++

#include "Lamp.h"

Lamp::Lamp(ShaderIF* sIF, PhongMaterial& matl, float blx, float bly, float blz, float lxz, float ly) : SceneElement(sIF, matl)
{
	PhongMaterial White(1,1,1,1,1,1,1,1,1,15,1);
	xmin = blx;
	ymin = bly;
	zmin = blz;
	xmax = xmin + lxz;
	ymax = ymin + ly;
	zmax = zmin + lxz;
	double shadeHeight = .4;
	double standHeight = .5;
	double standWidth = .1;
	double baseHeight = .1;
	base = new Block(sIF,matl,blx,bly,blz,lxz,ly*baseHeight,lxz);
	stand = new Block(sIF,matl,xmin+.4*lxz,ymin+ly*baseHeight,zmin+.4*lxz,lxz*standWidth,standHeight*ly,lxz*standWidth);
	shade = new Block(sIF,White,xmin,ymin+.6*ly,zmin,lxz,.4*ly,lxz);

}

Lamp::~Lamp()
{
	delete base;
	delete stand;
	delete shade;
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Lamp::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

void Lamp::render()
{
	base->render();
	stand->render();
	shade->render();
}
