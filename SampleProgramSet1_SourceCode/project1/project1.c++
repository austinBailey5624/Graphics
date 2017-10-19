// project1.c++

#include "GLFWController.h"
#include "ModelView.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{

	std::ifstream file;
	if(argc == 1)
	{
		file.open("proj1TestDataSet1.txt");
	}
	else if(argc ==2)
	{
		file.open(argv[1]);
	}
	else
	{
		std::cout << "argc = " << argc <<"\n";
		std::cout << "arcv[1]" << argv[1] << "\n";
		std::cout << "Too many arguments\n";
		return 0;
	}
	int sizeOfArray = 0;
	int numOfCurves=0;
	float temp;
	while(file.good())
	{
		file >> temp;
		sizeOfArray++;
	}
	file.close();
	numOfCurves = sizeOfArray/11;
//	std::cout << "\nSize of Array:    " << sizeOfArray << "\n";
//	std::cout << "\nNumber of Curves: " << numOfCurves << "\n";
/*	if(sizeOfArray%11!=0)
	{
		std::cout << "warning, size is not a multiple of eleven\n";
		std::cout << "Only the first " << (numOfCurves*11) << " data points were used\n";
	}*/
	float curveAttributes[sizeOfArray];
	if(argc == 1)
	{
		file.open("proj1TestDataSet1.txt");
	}
	else
	{
		file.open(argv[1]);
	}
	GLFWController c(argv[0]);
	c.reportVersions(std::cout);
	ShaderIF* sIF = new ShaderIF("shaders/project1.vsh", "shaders/project1.fsh");
	double a0,a1,a2,a3,b0,b1,b2,b3,tmin,tmax, nPoints,t, deltaT;
	while(file.good())
	{
		numOfCurves++;
		file >> a0 >> a1 >> a2 >> a3 >> b0 >> b1 >> b2 >> b3 >> tmin >> tmax >> nPoints;
		vec2 curve[(int)nPoints];
		t = tmin;
		deltaT = (tmax-tmin)/(nPoints);
		for(int i=0; i<nPoints; i++)
		{
			curve[i][0] = a0 + a1*t + a2*t*t + a3*t*t*t;
			curve[i][1] = b0 + b1*t + b2*t*t + b3*t*t*t;
			t += deltaT;
		}
		c.addModel(new ModelView(sIF, curve, nPoints));
	}

	file.close();
	std::cout << "\n";

	double xyz[6]; // xyz limits, even though this is 2D
	c.getOverallMCBoundingBox(xyz);
	//std::cout << "Bounding Box: (" << xyz[0] << "," << xyz[1] << ") (" << xyz[2] << "," << xyz[3] << ") (" << xyz[4] << "," << xyz[5] << ")\n";//debugging

	// Tell class ModelView we initially want to see the whole scene:
	ModelView::setMCRegionOfInterest(xyz);
	glClearColor(.5,.5,.5,1);
	c.run();

	delete sIF;

	return 0;
}
