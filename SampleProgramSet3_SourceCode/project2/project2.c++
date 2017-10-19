// project2.c++: Starter for EECS 672 Project 2

#include "GLFWController.h"
#include "TEMPLATE_Subclass.h"
#include <math.h>
#include "Block.h"
#include "Table.h"
#include "RubiksBlock.h"
void set3DViewingInformation(double xyz[6])
{
	ModelView::setMCRegionOfInterest(xyz);

	// double maxDelta = xyz[1] - xyz[0];
	// double delta = xyz[3] - xyz[2];
	// if (delta > maxDelta)
	// 	maxDelta = delta;
	// delta = xyz[5] - xyz[4];
	// if (delta > maxDelta)
	// 	maxDelta = delta;

	double delta = fmax(fmax(xyz[1] - xyz[0],xyz[3]-xyz[2]),xyz[5]-xyz[4]);
	// (ii) Determine the center of the created scene:
	// double xmid = 0.5 * (xyz[0] + xyz[1]);
	// double ymid = 0.5 * (xyz[2] + xyz[3]);
	// double zmid = 0.5 * (xyz[4] + xyz[5]);
	cryph::AffVector direction(1,1.5,1.25);
	direction.normalize();


	//cryph::AffPoint center(0.5 * (xyz[0] + xyz[1]),0.5 * (xyz[2] + xyz[3]),0.5 * (xyz[4] + xyz[5]));
	cryph::AffPoint center(6,1.5,5);

	//cryph::AffPoint eye(0.5 * (xyz[0] + xyz[1]),0.5 * (xyz[2] + xyz[3]),0.5 * (xyz[4] + xyz[5]));
	cryph::AffPoint eye = center + 1.95*delta*direction;
	//cryph::AffVector up = cryph::AffVector::zu;
	cryph::AffVector up(0,1,0);
	// Set values for eye-center-up to produce a reasonable off-axis
	// view of your scene, then:

	// Notify the ModelView of our MC->EC viewing requests:
	ModelView::setEyeCenterUp(eye, center, up);

	double ecZpp = -((2*delta)-(delta/2));
	double ecZmin = ecZpp - delta;
	double ecZmax = ecZpp + (delta/2);

	// Set values for ecZpp, ecZmin, ecZmax that make sense in the context of
	// the EC system established above, then:

	ModelView::setProjection(PERSPECTIVE);
	ModelView::setProjectionPlaneZ(ecZpp);
	ModelView::setECZminZmax(ecZmin, ecZmax);
}

int main(int argc, char* argv[])
{
	GLFWController c("GameTable", MVC_USE_DEPTH_BIT);
	c.reportVersions(std::cout);

	ShaderIF* sIF = new ShaderIF("shaders/basic.vsh", "shaders/phong.fsh");

//	c.addModel(new Block(sIF, 4, 0, 4, 4, 3, 2,.2,.2,.2));
	c.addModel(new Table(sIF, 4, 0, 4, 4, 3, 2,.7,.3,.3));
	c.addModel(new RubiksBlock(sIF,5.5,3.1,4.5,1));

	// create your scene, adding things to the Controller....

	glClearColor(0.5,0.5,0.5, 1.0);

	double xyz[6];
	c.getOverallMCBoundingBox(xyz);
	set3DViewingInformation(xyz);

	c.run();

	delete sIF;

	return 0;
}
