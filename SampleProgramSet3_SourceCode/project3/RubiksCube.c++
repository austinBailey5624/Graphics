// RubiksCube.c++

#include "RubiksCube.h"

RubiksCube::RubiksCube(ShaderIF* sIF, PhongMaterial& matl, float cx, float cy, float cz, float l, int which, bool modifiable) : SceneElement(sIF,matl)
{
	xmin = cx;
	ymin = cy;
	zmin = cz;
	xmax = xmin + l;
	ymax = ymin + l;
	zmax = zmin + l;

	length=l/3;

	//blocks[0][0][0] = new RubiksBlock(sIF,cx,cy,cz,l);
	if(which==0)//clear cube
	{
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				for(int k=0; k<3; k++)
				{
					blocks[i][j][k]= new RubiksBlock(sIF, matl, xmin+i*length,ymin+j*length,zmin+k*length,length,1,5);
				}
			}
		}
	}
	else if (which==1)
	{
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				for(int k=0; k<3; k++)
				{
					if((i+j+k)%2==0)
					{
						blocks[i][j][k] = new RubiksBlock(sIF,matl, xmin+i*length,ymin+j*length,zmin+k*length,length,1,5);
					}
					else
					{
						blocks[i][j][k] = new RubiksBlock(sIF,matl,xmin+i*length,ymin+j*length,zmin+k*length,length,2,6);
					}
				}
			}
		}
	}
	else if(which==2)
	{
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				for(int k=0; k<3; k++)
				{
					if( (i==1)&&(j==1) || (j==1)&&(k==1) || (k==1)&&(i==1))//if we're on a center
					{
						blocks[i][j][k] = new RubiksBlock(sIF,matl,xmin+i*length,ymin+j*length,zmin+k*length,length,1,3);
					}
					else
					{
						blocks[i][j][k] = new RubiksBlock(sIF,matl,xmin+i*length,ymin+j*length,zmin+k*length,length,5,3);
						//blocks[i][j][k] = new RubiksBlock(sIF,xmin+i*length,ymin+j*length,zmin+k*length,length,2,4,6);
					}
				}
			}
		}
	}
	else if (which == 3)//testing cases
	{
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				for(int k=0; k<3; k++)
				{
					if(i==0&&j==2&&k==1)
					{
						blocks[i][j][k] = new RubiksBlock(sIF,matl,xmin+i*length,ymin+j*length,zmin+k*length,length,1,4);
					}
					else
					{
						blocks[i][j][k] = new RubiksBlock(sIF,matl,xmin+i*length,ymin+j*length,zmin+k*length,length,1,3);
					}
				}
			}
		}
	}
}

RubiksCube::~RubiksCube()
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			for(int k=0; k<3; k++)
			{
				delete blocks[i][j][k];
			}
		}
	}
}

bool RubiksCube::handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY)
{
	if(anASCIIChar=='u')
	{
		rotate(1);
	}
//	return this->ModelView::handleCommand(anASCIIChar, ldsX, ldsY);
	return true;
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void RubiksCube::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

void RubiksCube::rotate(int direction)
{
	PhongMaterial error(.5,.5,.5,.5,.5,.5,.5,.5,.5,15,1);
	std::cout << "got here\n";
	if(direction == 1)
	{
		int j=2;
		int whitedirLookup[3][3];
		int reddirLookup[3][3];
		for(int i = 0; i<3; i++)
		{
			std::cout << "gothere1\n";
			for(int k = 0; k<3; k++)
			{
				whitedirLookup[i][j] = blocks[i][j][k]->getWhitedir();
				reddirLookup[i][j] = blocks[i][j][k]->getReddir();

			}
		}
		std::cout <<"gothere2\n";
		int i=0;
		int k=0;
		//blocks[0][2][0]->rotate(2,3);
		//blocks[0][2][0] = new RubiksBlock(shaderIF,matl,xmin+i*length,ymin+j*length,zmin+k*length,length,2,3);
		/*
		for(int i=0; i<3; i++)
		{
			for(int k=0; k<3; k++)
			{
				delete blocks[i][j][k];
				blocks[i][j][k] = new RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,1,3);//causes seg fault
			}
		}*/
		std::cout << "gothere3\n";
	}
}

int RubiksCube::dirAfterRotate(int direction, int olddir)
{
	if(direction==1)//rotate up
	{
		if(olddir==1)
		{
			return 1;
		}
		else if(olddir==2)
		{
			return 2;
		}
		else if(olddir==3)
		{
			return 6;
		}
		else if(olddir==4)
		{
			return 5;
		}
		else if(olddir==5)
		{
			return 3;
		}
		else if(olddir==6)
		{
			return 4;
		}
	}
	else if(direction==2)
	{
		if(olddir==1)
		{
			return 1;
		}
		else if(olddir==2)
		{
			return 2;
		}
		else if(olddir==3)
		{
			return 5;
		}
		else if(olddir==4)
		{
			return 6;
		}
		else if(olddir==5)
		{
			return 4;
		}
		else if(olddir==6)
		{
			return 3;
		}
	}
	else if(direction==3)
	{
		if(olddir==1)
		{
			return 5;
		}
		else if(olddir==2)
		{
			return 6;
		}
		else if(olddir==3)
		{
			return 3;
		}
		else if(olddir==4)
		{
			return 4;
		}
		else if(olddir==5)
		{
			return 2;
		}
		else if(olddir==6)
		{
			return 1;
		}
	}
	else if(direction==4)
	{
		if(olddir==1)
		{
			return 6;
		}
		else if(olddir==2)
		{
			return 5;
		}
		else if(olddir==3)
		{
			return 3;
		}
		else if(olddir==4)
		{
			return 4;
		}
		else if(olddir==5)
		{
			return 1;
		}
		else if(olddir==6)
		{
			return 2;
		}
	}
	else if(direction==5)
	{
		if(olddir==1)
		{
			return 4;
		}
		else if(olddir==2)
		{
			return 3;
		}
		else if(olddir==3)
		{
			return 1;
		}
		else if(olddir==4)
		{
			return 2;
		}
		else if(olddir==5)
		{
			return 5;
		}
		else if(olddir==6)
		{
			return 6;
		}
	}
	else if(direction==6)
	{
		if(olddir==1)
		{
			return 3;
		}
		else if(olddir==2)
		{
			return 4;
		}
		else if(olddir==3)
		{
			return 2;
		}
		else if(olddir==4)
		{
			return 1;
		}
		else if(olddir==5)
		{
			return 5;
		}
		else if(olddir==6)
		{
			return 6;
		}
	}
	return 0;
}

void RubiksCube::render()
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			for(int k=0; k<3; k++)
			{
				blocks[i][j][k]->render();
			}
		}
	}
	//blocks[0][0][0]->render();
}
