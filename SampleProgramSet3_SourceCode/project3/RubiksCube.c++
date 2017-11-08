// RubiksCube.c++

#include "RubiksCube.h"

RubiksCube::RubiksCube(ShaderIF* sIF, PhongMaterial& matl, float cx, float cy, float cz, float l, int which, bool modifiable) : SceneElement(sIF,matl)
{
	shaderIF = sIF;
	m_modifiable = modifiable;
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
					blocks[i][j][k]= new RubiksBlock(sIF, matl, xmin+i*length,ymin+j*length,zmin+k*length,length,1,3);
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
	if(!m_modifiable)
	{
		return this->ModelView::handleCommand(anASCIIChar, ldsX, ldsY);
	}
	if(anASCIIChar=='u')
	{
		rotate(1);//rotate top clockwise
	}
	else if(anASCIIChar=='U')
	{
		//to model counterclockwise rotation,
		//rotate clockwise 3 times
		rotate(1);
		rotate(1);
		rotate(1);
	}
	else if(anASCIIChar=='d')//rotate bottom clockwise
	{
		rotate(2);
	}
	else if(anASCIIChar=='D')
	{
		rotate(2);
		rotate(2);
		rotate(2);
	}
	else if(anASCIIChar=='f')//rotate front clockwise
	{
		rotate(3);
	}
	else if(anASCIIChar=='F')
	{
		rotate(3);
		rotate(3);
		rotate(3);
	}
	else if(anASCIIChar=='b')//rotate back clockwise
	{
		rotate(4);
	}
	else if(anASCIIChar=='B')//rotate back clockwise
	{
		rotate(4);
		rotate(4);
		rotate(4);
	}
	else if(anASCIIChar=='r')//rotate right clockwise{
	{
		rotate(5);
	}
	else if(anASCIIChar=='R')
	{
		rotate(5);
		rotate(5);
		rotate(5);
	}
	else if(anASCIIChar=='l')
	{
		rotate(6);
	}
	else if(anASCIIChar=='L')
	{
		rotate(6);
		rotate(6);
		rotate(6);
	}
	else if(anASCIIChar=='s')
	{
		srand(time(NULL));
		int temp;
		for(int i=0; i<5; i++)
		{
			temp=rand()%5+1;
			rotate(temp);
			if(temp==1)
			{
				std::cout << "up\n";
			}
			else if(temp==2)
			{
				std::cout << "down\n";
			}
			else if(temp==3)
			{
				std::cout << "front\n";
			}
			else if(temp==4)
			{
				std::cout << "back\n";
			}
			else if(temp==5)
			{
				std::cout << "right\n";
			}
			else if(temp==6)
			{
				std::cout << "left\n";
			}
		}
	}
	else if(anASCIIChar=='S')
	{
		solve();
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
	if(direction == 1)
	{
		int j=2;
		int whitedirLookup[3][3];
		int reddirLookup[3][3];
		for(int i = 0; i<3; i++)
		{
			for(int k = 0; k<3; k++)
			{
				whitedirLookup[i][k] = blocks[i][j][k]->getWhitedir();
				reddirLookup[i][k] = blocks[i][j][k]->getReddir();

			}
		}
		for(int i=0; i<3; i++)
		{
			for(int k=0; k<3; k++)
			{
				delete blocks[i][j][k];
				if(i==0&&k==0)
				{
					blocks[i][j][k] = new RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length, dirAfterRotate(direction,whitedirLookup[0][2]), dirAfterRotate(direction,reddirLookup[0][2]));
				}
				else if(i==0&&k==1)
				{
//					std::cout << "got here\n";

				//	blocks[i][j][k] = new RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,1,3);
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length, dirAfterRotate(direction,whitedirLookup[1][2]), dirAfterRotate(direction,reddirLookup[1][2]));
				}
				else if(i==0&&k==2)
				{
	//				std::cout << "got her4e\n";

					blocks[i][j][k] = new 					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length, dirAfterRotate(direction,whitedirLookup[2][2]), dirAfterRotate(direction,reddirLookup[2][2]));
				}
				else if(i==1&&k==0)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length, dirAfterRotate(direction,whitedirLookup[0][1]), dirAfterRotate(direction,reddirLookup[0][1]));
				}
				else if(i==1&&k==1)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length, dirAfterRotate(direction,whitedirLookup[1][1]), dirAfterRotate(direction,reddirLookup[1][1]));
				}
				else if(i==1&&k==2)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length, dirAfterRotate(direction,whitedirLookup[2][1]), dirAfterRotate(direction,reddirLookup[2][1]));
				}
				else if(i==2&&k==0)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length, dirAfterRotate(direction,whitedirLookup[0][0]), dirAfterRotate(direction,reddirLookup[0][0]));
				}
				else if(i==2&&k==1)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length, dirAfterRotate(direction,whitedirLookup[1][0]), dirAfterRotate(direction,reddirLookup[1][0]));
				}
				else if(i==2&&k==2)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length, dirAfterRotate(direction,whitedirLookup[2][0]), dirAfterRotate(direction,reddirLookup[2][0]));
				}
				else//error case
				{
					std::cout << "error on block i= "<< i << "j= " << j << "k= " << k << "\n";
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length, dirAfterRotate(direction,0), dirAfterRotate(direction,0));
				}
			}
		}
		return;
	}
	else if(direction==2)
	{
		int j=0;
		int whitedirLookup[3][3];
		int reddirLookup[3][3];
		for(int i = 0; i<3; i++)
		{
			for(int k = 0; k<3; k++)
			{
				whitedirLookup[i][k] = blocks[i][j][k]->getWhitedir();
				reddirLookup[i][k] = blocks[i][j][k]->getReddir();
			}
		}
		for(int i=0; i<3; i++)
		{
			for(int k=0; k<3; k++)
			{
				delete blocks[i][j][k];
				if(i==0&&k==0)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[2][0]),
					dirAfterRotate(direction,reddirLookup[2][0]));
				}
				else if(i==0&&k==1)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[1][0]),
					dirAfterRotate(direction,reddirLookup[1][0]));
				}
				else if(i==0&&k==2)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[0][0]),
					dirAfterRotate(direction,reddirLookup[0][0]));
				}
				else if(i==1&&k==0)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[2][1]),
					dirAfterRotate(direction,reddirLookup[2][1]));
				}
				else if(i==1&&k==1)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[1][1]),
					dirAfterRotate(direction,reddirLookup[1][1]));
				}
				else if(i==1&&k==2)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[0][1]),
					dirAfterRotate(direction,reddirLookup[0][1]));
				}
				else if(i==2&&k==0)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[2][2]),
					dirAfterRotate(direction,reddirLookup[2][2]));
				}
				else if(i==2&&k==1)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[1][2]),
					dirAfterRotate(direction,reddirLookup[1][2]));
				}
				else if(i==2&&k==2)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[0][2]),
					dirAfterRotate(direction,reddirLookup[0][2]));
				}
				else//error case
				{
					std::cout << "error on block i= "<< i << "j= " << j << "k= " << k << "\n";
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length, dirAfterRotate(direction,0), dirAfterRotate(direction,0));
				}
			}
		}
		return;
	}
	else if(direction==3)
	{
		//std::cout <<"got here-1\n";
		int k=0;
		int whitedirLookup[3][3];
		int reddirLookup[3][3];
		for(int i = 0; i<3; i++)
		{
			//std::cout << "gothere-2\n";
			for(int j = 0; j<3; j++)
			{
				whitedirLookup[i][j] = blocks[i][j][k]->getWhitedir();
				reddirLookup[i][j] = blocks[i][j][k]->getReddir();

			}
		}
		//std::cout<<"got here0\n";
		for(int i = 0; i<3; i++)
		{
			for(int j = 0; j<3; j++)
			{
				delete blocks[i][j][k];
				if(i==0&&j==0)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[0][2]),
					dirAfterRotate(direction,reddirLookup[0][2]));
					//std::cout<<"gothere00\n";
				}
				else if(i==0&&j==1)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[1][2]),
					dirAfterRotate(direction,reddirLookup[1][2]));
				}
				else if(i==0&&j==2)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[2][2]),
					dirAfterRotate(direction,reddirLookup[2][2]));
				}
				else if(i==1&&j==0)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[0][1]),
					dirAfterRotate(direction,reddirLookup[0][1]));
				}
				else if(i==1&&j==1)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[1][1]),
					dirAfterRotate(direction,reddirLookup[1][1]));
				}
				else if(i==1&&j==2)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[2][1]),
					dirAfterRotate(direction,reddirLookup[2][1]));
				}
				else if(i==2&&j==0)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[0][0]),
					dirAfterRotate(direction,reddirLookup[0][0]));
				}
				else if(i==2&&j==1)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[1][0]),
					dirAfterRotate(direction,reddirLookup[1][0]));
				}
				else if(i==2&&j==2)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[2][0]),
					dirAfterRotate(direction,reddirLookup[2][0]));
				}
				else//error case
				{
					std::cout << "error on block i= "<< i << "j= " << j << "k= " << k << "\n";
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length, dirAfterRotate(direction,0), dirAfterRotate(direction,0));
				}
			}
		}
		return;
	}
	else if(direction==4)
	{
		int k=2;
		int whitedirLookup[3][3];
		int reddirLookup[3][3];
		for(int i = 0; i<3; i++)
		{
			//std::cout << "gothere-2\n";
			for(int j = 0; j<3; j++)
			{
				whitedirLookup[i][j] = blocks[i][j][k]->getWhitedir();
				reddirLookup[i][j] = blocks[i][j][k]->getReddir();

			}
		}
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				/*
				delete blocks[i][j][k];
				if(i==0&&j==0)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[0][2]),
					dirAfterRotate(direction,reddirLookup[2][0]));
				}*/
				delete blocks[i][j][k];
				if(i==0&&j==0)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[0][2]),
					dirAfterRotate(direction,reddirLookup[0][2]));
					//std::cout<<"gothere00\n";
				}
				else if(i==0&&j==1)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[1][2]),
					dirAfterRotate(direction,reddirLookup[1][2]));
				}
				else if(i==0&&j==2)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[2][2]),
					dirAfterRotate(direction,reddirLookup[2][2]));
				}
				else if(i==1&&j==0)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[0][1]),
					dirAfterRotate(direction,reddirLookup[0][1]));
				}
				else if(i==1&&j==1)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[1][1]),
					dirAfterRotate(direction,reddirLookup[1][1]));
				}
				else if(i==1&&j==2)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[2][1]),
					dirAfterRotate(direction,reddirLookup[2][1]));
				}
				else if(i==2&&j==0)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[0][0]),
					dirAfterRotate(direction,reddirLookup[0][0]));
				}
				else if(i==2&&j==1)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[1][0]),
					dirAfterRotate(direction,reddirLookup[1][0]));
				}
				else if(i==2&&j==2)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[2][0]),
					dirAfterRotate(direction,reddirLookup[2][0]));
				}
				else//error case
				{
					std::cout << "error on block i= "<< i << "j= " << j << "k= " << k << "\n";
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length, dirAfterRotate(direction,0), dirAfterRotate(direction,0));
				}
			}
		}
		return;
	}
	else if(direction==5)//rotate right clockwise
	{
		int i=0;
		int whitedirLookup[3][3];
		int reddirLookup[3][3];
		for(int j = 0; j<3; j++)
		{
			//std::cout << "gothere-2\n";
			for(int k = 0; k<3; k++)
			{
				whitedirLookup[j][k] = blocks[i][j][k]->getWhitedir();
				reddirLookup[j][k] = blocks[i][j][k]->getReddir();
			}
		}
		for(int j=0; j<3; j++)
		{
			for(int k=0; k<3; k++)
			{
				delete blocks[i][j][k];
				if(j==0&&k==0)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[0][2]),
					dirAfterRotate(direction,reddirLookup[0][2]));
				}
				else if(j==0&&k==1)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[1][2]),
					dirAfterRotate(direction,reddirLookup[1][2]));
				}
				else if(j==0&&k==2)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[2][2]),
					dirAfterRotate(direction,reddirLookup[2][2]));
				}
				else if(j==1&&k==0)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[0][1]),
					dirAfterRotate(direction,reddirLookup[0][1]));
				}
				else if(j==1&&k==1)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[1][1]),
					dirAfterRotate(direction,reddirLookup[1][1]));
				}
				else if(j==1&&k==2)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[2][1]),
					dirAfterRotate(direction,reddirLookup[2][1]));
				}
				else if(j==2&&k==0)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[0][0]),
					dirAfterRotate(direction,reddirLookup[0][0]));
				}
				else if(j==2&&k==1)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[1][0]),
					dirAfterRotate(direction,reddirLookup[1][0]));
				}
				else if(j==2&&k==2)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[2][0]),
					dirAfterRotate(direction,reddirLookup[2][0]));
				}
				else//error case
				{
					std::cout << "error on block i= "<< i << "j= " << j << "k= " << k << "\n";
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length, dirAfterRotate(direction,0), dirAfterRotate(direction,0));
				}
			}
		}
		return;
	}
	else if(direction==6)
	{
		int i=2;
		int whitedirLookup[3][3];
		int reddirLookup[3][3];
		for(int j = 0; j<3; j++)
		{
			//std::cout << "gothere-2\n";
			for(int k = 0; k<3; k++)
			{
				whitedirLookup[j][k] = blocks[i][j][k]->getWhitedir();
				reddirLookup[j][k] = blocks[i][j][k]->getReddir();
			}
		}
		for(int j=0; j<3; j++)
		{
			for(int k=0; k<3; k++)
			{
				delete blocks[i][j][k];
				if(j==0&&k==0)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[0][2]),
					dirAfterRotate(direction,reddirLookup[0][2]));
				}
				else if(j==0&&k==1)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[1][2]),
					dirAfterRotate(direction,reddirLookup[1][2]));
				}
				else if(j==0&&k==2)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[2][2]),
					dirAfterRotate(direction,reddirLookup[2][2]));
				}
				else if(j==1&&k==0)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[0][1]),
					dirAfterRotate(direction,reddirLookup[0][1]));
				}
				else if(j==1&&k==1)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[1][1]),
					dirAfterRotate(direction,reddirLookup[1][1]));
				}
				else if(j==1&&k==2)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[2][1]),
					dirAfterRotate(direction,reddirLookup[2][1]));
				}
				else if(j==2&&k==0)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[0][0]),
					dirAfterRotate(direction,reddirLookup[0][0]));
				}
				else if(j==2&&k==1)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[1][0]),
					dirAfterRotate(direction,reddirLookup[1][0]));
				}
				else if(j==2&&k==2)
				{
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,
					dirAfterRotate(direction,whitedirLookup[2][0]),
					dirAfterRotate(direction,reddirLookup[2][0]));
				}
				else//error case
				{
					std::cout << "error on block i= "<< i << "j= " << j << "k= " << k << "\n";
					blocks[i][j][k] = new
					RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length, dirAfterRotate(direction,0), dirAfterRotate(direction,0));
				}
			}
		}
	}
}

void RubiksCube::solve()
{
	PhongMaterial error(.5,.5,.5,.5,.5,.5,.5,.5,.5,15,1);
	for(int i=0;i<3;i++)
	{
		for(int j=0; j<3; j++)
		{
			for(int k=0; k<3; k++)
			{
				delete blocks[i][j][k];
				blocks[i][j][k] = new
				RubiksBlock(shaderIF,error,xmin+i*length,ymin+j*length,zmin+k*length,length,1,3);
			}
		}
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
