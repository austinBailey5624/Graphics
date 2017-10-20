// Chair.c++

#include "Chair.h"

Chair::Chair(ShaderIF* sIF, float blx, float bly, float blz, float lxz, float ly, float r, float g, float b, int direction) : shaderIF(sIF)
{
	//direction lookup:
	//0: seat back is on zmax
	//1: seat back is on zmin
	//2: seat back is on xmax
	//3: seat back is on xmin

	// DON'T FORGET TO SET INSTANCE VARIABLE "kd", PERHAPS USING
	// SOME CONSTRUCTOR PARAMETERS
	xmin = blx;
	ymin = bly;
	zmin = blz;
	xmax = xmin + lxz;
	ymax = ymin + ly;
	zmax = zmin + lxz;

	double seatheight = .2;//the height of the seat as a percentage of the total height;
	double seatwidth = .2;//the width of the seat expressed as a percentage of total lxz
	double seatbackheight = .4;//the height of the seatBack as a percentage of total height;
	double legheight = .4;//the height of the legs as a percentage of the total height;
	double legRadius = .05;//the length of the radius of the leg expressed as a percentage of total lxz

	seatBase = new Block(sIF,xmin,ymin+legheight*ly,zmin,lxz,ly*seatheight,lxz,r,g,b);


	cryph::AffPoint frontRightLegTop(xmin+legRadius*lxz,ymin+legheight*ly,zmax-legRadius*lxz);
	cryph::AffPoint frontRightLegBottom(xmin+legRadius*lxz,ymin,zmax-legRadius*lxz);
	frontRightLeg = new Cylinder(sIF, legRadius*lxz, frontRightLegTop, frontRightLegBottom,100,r,g,b);

	cryph::AffPoint frontLeftLegTop(xmax-legRadius*lxz,ymin+legheight*ly,zmax-legRadius*lxz);
	cryph::AffPoint frontLeftLegBottom(xmax-legRadius*lxz,ymin,zmax-legRadius*lxz);
	frontLeftLeg = new Cylinder(sIF, legRadius*lxz,frontLeftLegTop, frontLeftLegBottom,100,r,g,b);

	cryph::AffPoint backRightLegTop(xmin+legRadius*lxz,ymin+legheight*ly,zmin+legRadius*lxz);
	cryph::AffPoint backRightLegBottom(xmin+legRadius*lxz,ymin,zmin+legRadius*lxz);
	backRightLeg = new Cylinder(sIF, legRadius*lxz, backRightLegTop, backRightLegBottom,100,r,g,b);

	cryph::AffPoint backLeftLegTop(xmax-legRadius*lxz,ymin+legheight*ly,zmin+legRadius*lxz);
	cryph::AffPoint backLeftLegBottom(xmax-legRadius*lxz,ymin,zmin+legRadius*lxz);
	backLeftLeg = new Cylinder(sIF, legRadius*lxz, backLeftLegTop, backLeftLegBottom,100,r,g,b);

	if(direction == 0)//seatback on zmax axis
	{
		seatBack = new Block(sIF,xmin, ymin + (seatheight+legheight)*ly, zmax-seatwidth*lxz,lxz,seatbackheight*ly,seatwidth*lxz,r,g,b);
	}
	else if(direction ==1)//seatback on zmin axis
	{
		seatBack = new Block(sIF, xmin, ymin + (seatheight+legheight)*ly,zmin,lxz,seatbackheight*ly, seatwidth*lxz,r,g,b);
	}
	else if(direction ==2)//seatback on xmax axis
	{
		seatBack = new Block(sIF,xmax-seatwidth*lxz,ymin + (seatheight+legheight)*ly,zmin,seatwidth*lxz,seatbackheight*ly,lxz,r,g,b);
	}
	else//seatback on xmin axis
	{
		seatBack = new Block(sIF,xmin, ymin + (seatheight+legheight)*ly, zmin, seatwidth*lxz, seatbackheight*ly, lxz,r,g,b);
	}


}

Chair::~Chair()
{
	delete seatBase;
	delete frontRightLeg;
	delete frontLeftLeg;
	delete backRightLeg;
	delete backLeftLeg;
	delete seatBack;
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Chair::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

void Chair::render()
{
	seatBase->render();
	frontRightLeg->render();
	frontLeftLeg->render();
	backRightLeg->render();
	backLeftLeg->render();
	seatBack->render();
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
}
