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

//Table.c++

#include "Table.h"

typedef float vec3[3];

Table::Table(ShaderIF* sIF, float blx, float bly, float blz, float lx, float ly, float lz) : shaderIF(sIF)
{
	xmin = blx;
	ymin = bly;
	zmin = blz;
	xmax = xmin + lx;
	ymax = ymin + ly;
	zmax = zmin + lz;
	kd[0] = .3;
	kd[1] = .28;
	kd[2] = .26;

	//The Affpoints without prefixes are for the entire table
	/*
	cryph::AffPoint lbf(xmin, ymin, zmax);//left bottom front
	cryph::AffPoint ltf(xmin, ymax, zmax);//Left Top Front
	cryph::AffPoint rbf(xmax,ymin,zmax);//right bottom front
	cryph::AffPoint rtf(xmax,ymax,zmax); //Right Top front
	cryph::AffPoint rbb(xmax,ymin,zmin);// right back bottom
	cryph::AffPoint rtb(xmax,ymax,zmin); //Right Top Back
	cryph::AffPoint lbb(xmin,ymin,zmin);//left bottom back
	cryph::AffPoint ltb(xmin,ymax,zmin); //Left Top Back

	//These Affpoints are especially for the shelf, or top part of the table

	cryph::AffPoint shelflbf(xmin,(ymin+.8*(ymax-ymin)),zmax);//left Bottom Front
	cryph::AffPoint shelfrbf(xmax, ymin + .8*(ymax-ymin),zmax);//right bottom front
	cryph::AffPoint shelfrbb(xmin, ymin + .8*(ymax-ymin), zmin);//right bottom back
	cryph::AffPoint shelflbb(xmin, ymin + .8*(ymax-ymin),zmin);//left bottom back

	//These AffPoints are for the front Left Leg of the table
	cryph::AffPoint flrbf(xmin+.1*(xmax-xmin),ymin,zmax);
	cryph::AffPoint flrtf(xmin+.1*(xmax-xmin),ymin+.8*(ymax-ymin),zmax);
	cryph::AffPoint flrbb(xmin+.1*(xmax-xmin),ymin,zmax-.1*(zmax-zmin));
	cryph::AffPoint flrtb(xmin+.1*(xmax-xmin),ymin+.8*(ymax-ymin),zmax-.1*(zmax-zmin));
	cryph::AffPoint fllbb(xmin,ymin,zmax-.1*(zmax-zmin));
	cryph::AffPoint flltb(xmin,ymin+.8*(ymax-ymin),zmax-.1*(zmax-zmin));

	top = new Block(sIF, shelflbf, ltf, shelfrbf, rtf, shelfrbb, rtb, shelflbb, ltb);
	frontLeftLeg = new Block(sIF, lbf, shelflbf, flrbf,flrtf,flrbb,flrtb,fllbb,flltb);
*/
	double legwidth=.1;//a fraction representing the leg witdth as a portion of the tables width
	double legheight=.8;//a fraction representing the leg height as a portion of the tables height
	double deltax = xmax - xmin;
	double deltay = ymax - ymin;
	double deltaz = zmax - zmin;
	double localymin = ymin + (legheight)*ly;
	double localylength = (1-legheight)*ly;

	top = new Block(sIF,xmin,localymin,zmin,lx,localylength,lz);
	double localxlength = legwidth*lx;
	localylength = legheight*ly;
	double localzlength = legwidth*lz;
	frontRightLeg = new Block(sIF,xmin,ymin,zmin,localxlength,localylength,localzlength);
	double localxmin = xmax-legwidth*lx;

	frontLeftLeg = new Block(sIF,localxmin,ymin,zmin,localxlength,localylength,localzlength);
	double localzmin = zmax - legwidth*lz;
	backRightLeg = new Block(sIF,xmin,ymin,localzmin,localxlength,localylength,localzlength);
	backLeftLeg = new Block(sIF,localxmin,ymin,localzmin,localxlength,localylength,localzlength);
	//top = new Block(sIF,xmin,ymin+legheight*(deltay),zmin,deltax,deltay,deltaz);
//	frontLeftLeg = new Block(sIF, xmin,ymin,zmax-legwidth*(deltaz),xmin+legwidth*deltax,ymin+legheight*deltay,zmax);

	//defineTable();
}

Table::~Table()
{
	delete top;
	delete frontRightLeg;
	delete frontLeftLeg;
	delete backRightLeg;
	delete backLeftLeg;
}

void Table::defineTable()
{

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
