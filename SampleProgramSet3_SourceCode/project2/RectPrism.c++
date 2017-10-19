// TEMPLATE_Subclass.c++
/*
#include "TEMPLATE_Subclass.h"

TEMPLATE_Subclass::TEMPLATE_Subclass(ShaderIF* sIF) : shaderIF(sIF)
{
	// DON'T FORGET TO SET INSTANCE VARIABLE "kd", PERHAPS USING
	// SOME CONSTRUCTOR PARAMETERS
}

TEMPLATE_Subclass::~TEMPLATE_Subclass()
{
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void TEMPLATE_Subclass::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = -1000.0; // xmin  Give real values!
	xyzLimits[1] = 1000.0;  // xmax         |
	xyzLimits[2] = -1234.5; // ymin         |
	xyzLimits[3] = -1011.2; // ymax         |
	xyzLimits[4] = -3000.0; // zmin         |
	xyzLimits[5] = -2000.0; // zmax        \_/
}

void TEMPLATE_Subclass::render()
{
	// 1. Save current and establish new current shader program
	// ...

	// 2. Establish "mc_ec" and "ec_lds" matrices
	// ...

	// 3. Set GLSL's "kd" variable using this object's "kd" instance variable
	// ...

	// 4. Establish any other attributes and make one or more calls to
	//    glDrawArrays and/or glDrawElements
	// ...

	// 5. Reestablish previous shader program
	// ...
}*/

#include "RectPrism.h"

typedef float vec3[3];

GLunit RectPrism::indexList[3][4] =
{
	{1,7,3,5},
	{6,0,4,2},
	{6,7,0,1}
}

RectPrism::RectPrism(ShaderIF* sIF, float blx, float bly, float blz, float urx, float ury, float urz, float theta): shaderIF(sIF)
{
	xmin = blx;
	ymin = bly;
	zmin = blz;
	xmax = urx;
	ymax = ury;
	zmax = urz;
	this.theta = theta;
}
