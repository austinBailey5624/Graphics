

#include "RubiksBlock.h"



RubiksBlock::RubiksBlock(ShaderIF* sIF, PhongMaterial &base, float cx, float cy, float cz, float length, int whitedir, int reddir) : SceneElement(sIF,base)
{
	//only one length because all sides of the rubiks are same length
	m_whitedir = whitedir;
	m_reddir = reddir;
	xmin = cx;
	ymin = cy;
	zmin = cz;
	xmax = xmin + length;
	ymax = ymin + length;
	zmax = zmin + length;
	double offset = .05;//a fraction representing how much of the block gets cut off from the sides

	float b = .25;//brightness
	PhongMaterial white(b,b,b,b,b,b,b,b,b,15,1);
	PhongMaterial yellow(b,b,0,b,b,0,b,b,0,15,1);
	PhongMaterial blue(0,0,b,0,0,b,0,0,b,15,1);
	PhongMaterial green(0,b,0,0,b,0,0,b,0,15,1);
	PhongMaterial red(b,0,0,b,0,0,b,0,0,15,1);
	PhongMaterial orange(b,b*.5,0,b,b*.5,0,b,b*.5,0,15,1);
	PhongMaterial error(.5,.5,.5,.5,.5,.5,.5,.5,.5,15,1);


	float localxmin = xmin+offset*length;
 	float localymin = ymin+offset*length;
	float localzmin = zmin+offset*length;
	float localxmax = xmax-offset*length;
	float localymax = ymax-offset*length;
	float localzmax = zmax-offset*length;



	PhongMaterial topMat = white;
	PhongMaterial botMat = yellow;
	PhongMaterial rigMat = blue;
	PhongMaterial lefMat = green;
	PhongMaterial froMat = red;
	PhongMaterial bacMat = orange;

	if(whitedir==1)
	{
		topMat = white;
		botMat = yellow;
		if(reddir==3)
		{
			froMat = red;
			bacMat = orange;
			rigMat = blue;
			lefMat = green;
		}
		else if(reddir==4)
		{
			froMat = orange;
			bacMat = red;
			rigMat = green;
			lefMat = blue;
		}
		else if(reddir==5)
		{
			froMat = green;
			bacMat = blue;
			rigMat = red;
			lefMat = orange;
		}
		else if(reddir==6)
		{
			froMat = blue;
			bacMat = green;
			rigMat = orange;
			lefMat = red;
		}
		else//errorCase
		{
			froMat = error;
			bacMat = error;
			rigMat = error;
			lefMat = error;
		}
	}
	else if(whitedir==2)
	{
		topMat = yellow;
		botMat = white;
		if(reddir==3)
		{
			froMat = red;
			bacMat = orange;
			rigMat = green;
			lefMat = blue;
		}
		else if(reddir==4)
		{
			froMat = orange;
			bacMat = red;
			rigMat = blue;
			lefMat = green;
		}
		else if(reddir==5)
		{
			froMat = green;
			bacMat = blue;
			rigMat = orange;
			lefMat = red;
		}
		else if(reddir==6)
		{
			froMat = blue;
			bacMat = green;
			rigMat = red;
			lefMat = orange;
		}
		else
		{
			froMat = error;
			bacMat = error;
			rigMat = error;
			lefMat = error;
		}
	}
	else if(whitedir==3)
	{
		froMat = white;
		bacMat = yellow;
		if(reddir==1)
		{
			topMat = red;
			botMat = orange;
			lefMat = blue;
			rigMat = green;
		}
		else if(reddir == 2)
		{
			topMat = orange;
			botMat = red;
			lefMat = green;
			rigMat = blue;
		}
		else if(reddir == 5)
		{
			topMat = blue;
			botMat = green;
			lefMat = orange;
			rigMat = blue;
		}
		else if(reddir == 6)
		{
			topMat = green;
			botMat = blue;
			lefMat = red;
			rigMat = orange;
		}
		else
		{
			topMat = error;
			botMat = error;
			rigMat = error;
			lefMat = error;
		}
	}
	else if(whitedir == 4)
	{
		froMat = yellow;
		bacMat = white;
		if(reddir==1)
		{
			topMat = red;
			botMat = orange;
			lefMat = green;
			rigMat = blue;
		}
		else if(reddir == 2)
		{
			topMat = orange;
			botMat = red;
			lefMat = blue;
			rigMat = green;
		}
		else if(reddir == 5)
		{
			topMat = green;
			botMat = blue;
			lefMat = orange;
			rigMat = blue;
		}
		else if(reddir == 6)
		{
			topMat = blue;
			botMat = green;
			lefMat = red;
			rigMat = orange;
		}
		else
		{
			topMat = error;
			botMat = error;
			rigMat = error;
			lefMat = error;
		}
	}
	else if(whitedir == 5)
	{
		rigMat = white;
		lefMat = yellow;
		if(reddir == 1)
		{
			topMat = red;
			botMat = orange;
			froMat = blue;
			bacMat = green;
		}
		else if(reddir == 2)
		{
			topMat = orange;
			botMat = red;
			froMat = green;
			bacMat = blue;
		}
		else if(reddir == 3)
		{
			froMat = red;
			bacMat = orange;
			topMat = green;
			botMat = blue;
		}
		else if(reddir == 4)
		{
			froMat = orange;
			bacMat = red;
			topMat = blue;
			botMat = green;
		}
		else
		{
			froMat = error;
			bacMat = error;
			topMat = error;
			botMat = error;
		}
	}
	else if(whitedir == 6)
	{
		rigMat = yellow;
		lefMat = white;
		if(reddir == 1)
		{
			topMat = red;
			botMat = orange;
			froMat = green;
			bacMat = blue;
		}
		else if(reddir == 2)
		{
			topMat = orange;
			botMat = red;
			froMat = blue;
			bacMat = green;
		}
		else if(reddir == 3)
		{
			froMat = red;
			bacMat = orange;
			topMat = blue;
			botMat = green;
		}
		else if(reddir == 4)
		{
			froMat = orange;
			bacMat = red;
			topMat = green;
			botMat = blue;
		}
		else
		{
			froMat = error;
			bacMat = error;
			topMat = error;
			botMat = error;
		}
	}
	else
	{
		topMat = error;
		botMat = error;
		froMat = error;
		bacMat = error;
		rigMat = error;
		lefMat = error;
	}


//	top = new Block(sIF, base, xmin, ymin, zmin, length, length, length);

	top = new Block(sIF, topMat, localxmin, localymax, localzmin, localxmax-localxmin, ymax-localymax, localzmax-localzmin);

	bottom = new Block(sIF, botMat, localxmin, ymin, localzmin, localxmax-localxmin, localymin-ymin, localzmax-localzmin);

	right = new Block(sIF, rigMat, xmin,localymin,localzmin ,localxmin-xmin,localymax-localymin,localzmax-localzmin);;

	left = new Block(sIF, lefMat,localxmax, localymin,localzmin,xmax-localxmax,localymax-localymin,localzmax-localzmin);

	front = new Block(sIF, froMat, localxmin, localymin, zmin, localxmax-localxmin, localymax-localymin, localzmin-zmin);

	back = new Block(sIF,bacMat, localxmin, localymin,localzmax, localxmax-localxmin, localymax-localymin,zmax-localzmax);
}

void RubiksBlock::rotate(int whitedir, int reddir)
{
	PhongMaterial white(1,1,1,1,1,1,1,1,1,15,1);
	PhongMaterial yellow(1,1,0,1,1,0,1,1,0,15,1);
	PhongMaterial blue(0,0,1,0,0,1,0,0,1,15,1);
	PhongMaterial green(0,1,0,0,1,0,0,1,0,15,1);
	PhongMaterial red(1,0,0,1,0,0,1,0,0,15,1);
	PhongMaterial orange(1,.5,0,1,.5,0,1,.5,0,15,1);
	PhongMaterial error(.5,.5,.5,.5,.5,.5,.5,.5,.5,15,1);

	PhongMaterial topMat = white;
	PhongMaterial botMat = yellow;
	PhongMaterial rigMat = blue;
	PhongMaterial lefMat = green;
	PhongMaterial froMat = red;
	PhongMaterial bacMat = orange;

	if(whitedir==1)
	{
		topMat = white;
		botMat = yellow;
		if(reddir==3)
		{
			froMat = red;
			bacMat = orange;
			rigMat = blue;
			lefMat = green;
		}
		else if(reddir==4)
		{
			froMat = orange;
			bacMat = red;
			rigMat = green;
			lefMat = blue;
		}
		else if(reddir==5)
		{
			froMat = green;
			bacMat = blue;
			rigMat = red;
			lefMat = orange;
		}
		else if(reddir==6)
		{
			froMat = blue;
			bacMat = green;
			rigMat = orange;
			lefMat = red;
		}
		else//errorCase
		{
			froMat = error;
			bacMat = error;
			rigMat = error;
			lefMat = error;
		}
	}
	else if(whitedir==2)
	{
		topMat = yellow;
		botMat = white;
		if(reddir==3)
		{
			froMat = red;
			bacMat = orange;
			rigMat = green;
			lefMat = blue;
		}
		else if(reddir==4)
		{
			froMat = orange;
			bacMat = red;
			rigMat = blue;
			lefMat = green;
		}
		else if(reddir==5)
		{
			froMat = green;
			bacMat = blue;
			rigMat = orange;
			lefMat = red;
		}
		else if(reddir==6)
		{
			froMat = blue;
			bacMat = green;
			rigMat = red;
			lefMat = orange;
		}
		else
		{
			froMat = error;
			bacMat = error;
			rigMat = error;
			lefMat = error;
		}
	}
	else if(whitedir==3)
	{
		froMat = white;
		bacMat = yellow;
		if(reddir==1)
		{
			topMat = red;
			botMat = orange;
			lefMat = blue;
			rigMat = green;
		}
		else if(reddir == 2)
		{
			topMat = orange;
			botMat = red;
			lefMat = green;
			rigMat = blue;
		}
		else if(reddir == 5)
		{
			topMat = blue;
			botMat = green;
			lefMat = orange;
			rigMat = blue;
		}
		else if(reddir == 6)
		{
			topMat = green;
			botMat = blue;
			lefMat = red;
			rigMat = orange;
		}
		else
		{
			topMat = error;
			botMat = error;
			rigMat = error;
			lefMat = error;
		}
	}
	else if(whitedir == 4)
	{
		froMat = yellow;
		bacMat = white;
		if(reddir==1)
		{
			topMat = red;
			botMat = orange;
			lefMat = green;
			rigMat = blue;
		}
		else if(reddir == 2)
		{
			topMat = orange;
			botMat = red;
			lefMat = blue;
			rigMat = green;
		}
		else if(reddir == 5)
		{
			topMat = green;
			botMat = blue;
			lefMat = orange;
			rigMat = blue;
		}
		else if(reddir == 6)
		{
			topMat = blue;
			botMat = green;
			lefMat = red;
			rigMat = orange;
		}
		else
		{
			topMat = error;
			botMat = error;
			rigMat = error;
			lefMat = error;
		}
	}
	else if(whitedir == 5)
	{
		rigMat = white;
		lefMat = yellow;
		if(reddir == 1)
		{
			topMat = red;
			botMat = orange;
			froMat = blue;
			bacMat = green;
		}
		else if(reddir == 2)
		{
			topMat = orange;
			botMat = red;
			froMat = green;
			bacMat = blue;
		}
		else if(reddir == 3)
		{
			froMat = red;
			bacMat = orange;
			topMat = green;
			botMat = blue;
		}
		else if(reddir == 4)
		{
			froMat = orange;
			bacMat = red;
			topMat = blue;
			botMat = green;
		}
		else
		{
			froMat = error;
			bacMat = error;
			topMat = error;
			botMat = error;
		}
	}
	else if(whitedir == 6)
	{
		rigMat = yellow;
		lefMat = white;
		if(reddir == 1)
		{
			topMat = red;
			botMat = orange;
			froMat = green;
			bacMat = blue;
		}
		else if(reddir == 2)
		{
			topMat = orange;
			botMat = red;
			froMat = blue;
			bacMat = green;
		}
		else if(reddir == 3)
		{
			froMat = red;
			bacMat = orange;
			topMat = blue;
			botMat = green;
		}
		else if(reddir == 4)
		{
			froMat = orange;
			bacMat = red;
			topMat = green;
			botMat = blue;
		}
		else
		{
			froMat = error;
			bacMat = error;
			topMat = error;
			botMat = error;
		}
	}
	else
	{
		topMat = error;
		botMat = error;
		froMat = error;
		bacMat = error;
		rigMat = error;
		lefMat = error;
	}
//	top->matl = topMat;
//	bottom->matl = botMat;
//	right->matl = rigMat;
//	left->matl = lefMat;
//	front->matl = froMat;
//	back->matl=bacMat;
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

int RubiksBlock::getWhitedir()
{
	return m_whitedir;
}

int RubiksBlock::getReddir()
{
	return m_reddir;
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
