// RubiksCube.c++

#include "RubiksCube.h"

RubiksCube::RubiksCube(ShaderIF* sIF, PhongMaterial& matl, float cx, float cy, float cz, float l, int which) : SceneElement(sIF,matl)
{
	xmin = cx;
	ymin = cy;
	zmin = cz;
	xmax = xmin + l;
	ymax = ymin + l;
	zmax = zmin + l;

	float length=l/3;

	//blocks[0][0][0] = new RubiksBlock(sIF,cx,cy,cz,l);
	if(which==0)
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
