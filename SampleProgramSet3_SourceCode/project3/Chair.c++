// Chair.c++

#include "Chair.h"

Chair::Chair(ShaderIF* sIF, PhongMaterial& base, float blx, float bly, float blz, float lxz, float ly, int direction) : SceneElement(sIF,matl)
{
	//direction lookup:
	//0: seat back is on zmax
	//1: seat back is on zmin
	//2: seat back is on xmax
	//3: seat back is on xmin
//	willRender=true;

	xmin = blx;
	ymin = bly;
	zmin = blz;
	xmax = xmin + lxz;
	ymax = ymin + ly;
	zmax = zmin + lxz;

	double seatheight = .15;//the height of the seat as a percentage of the total height;
	double seatwidth = .2;//the width of the seat expressed as a percentage of total lxz
	double seatbackheight = .45;//the height of the seatBack as a percentage of total height;
	double legheight = .4;//the height of the legs as a percentage of the total height;
	double legWidth = .2;//the length of the radius of the leg expressed as a percentage of total lxz

	seatBase = new Block(sIF,base,xmin,ymin+legheight*ly,zmin,lxz,ly*seatheight,lxz);
	//I thought the cylinder legs looked silly so I changed them to blocks
	frontRightLeg = new Block(sIF,base, xmax-lxz*legWidth,ymin,zmax-lxz*legWidth,legWidth*lxz,(ymax-ymin)*legheight,legWidth*lxz);

	frontLeftLeg = new Block(sIF,base, xmin, ymin, zmax-lxz*legWidth,legWidth*lxz,(ymax-ymin)*legheight,legWidth*lxz);
	backRightLeg = new Block(sIF,base, xmax-lxz*legWidth,ymin,zmin,legWidth*lxz,(ymax-ymin)*legheight,legWidth*lxz);

	backLeftLeg = new Block(sIF,base, xmin, ymin, zmin, legWidth*lxz,(ymax-ymin)*legheight,legWidth*lxz);

	if(direction == 0)//seatback on zmax axis
	{
		seatBack = new Block(sIF,base,xmin, ymin + (seatheight+legheight)*ly, zmax-seatwidth*lxz,lxz,seatbackheight*ly,seatwidth*lxz);
	}
	else if(direction ==1)//seatback on zmin axis
	{
		seatBack = new Block(sIF,base, xmin, ymin + (seatheight+legheight)*ly,zmin,lxz,seatbackheight*ly, seatwidth*lxz);
	}
	else if(direction ==2)//seatback on xmax axis
	{
		seatBack = new Block(sIF,base,xmax-seatwidth*lxz,ymin + (seatheight+legheight)*ly,zmin,seatwidth*lxz,seatbackheight*ly,lxz);
	}
	else//seatback on xmin axis
	{
		seatBack = new Block(sIF,base,xmin, ymin + (seatheight+legheight)*ly, zmin, seatwidth*lxz, seatbackheight*ly, lxz);
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

bool Chair::handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY)
{
	if(anASCIIChar=='q')
	{
	//	willRender=!willRender;
	}
	return this->ModelView::handleCommand(anASCIIChar, ldsX, ldsY);
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
//	if(willRender)
//	{
		seatBase->render();
		frontRightLeg->render();
		frontLeftLeg->render();
		backRightLeg->render();
		backLeftLeg->render();
		seatBack->render();
//	}
}
