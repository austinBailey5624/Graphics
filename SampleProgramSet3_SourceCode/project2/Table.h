#ifndef TABLE_H
#define TABLE_H

#include "ModelView.h"
#include "ShaderIF.h"
#include "Block.h"
#include <GL/gl.h>

class Table : public ModelView
{
public:
	Table(ShaderIF* sIF, float blx, float bly, float blz, float lx, float ly, float lz,float r, float g, float b);
	~Table();
	bool handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY);
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
	void defineTable();
private:
	ShaderIF* shaderIF;
	GLuint vao[5];
	GLuint vbo[5];
	GLuint ebo[3];
	float kd[3]; //colors
	float xmin;
	float xmax;
	float ymin;
	float ymax;
	float zmin;
	float zmax;
	Block* top;
	Block* frontLeftLeg;
	Block* frontRightLeg;
	Block* backLeftLeg;
	Block* backRightLeg;

	static GLuint indexList[3][4];
};
#endif
