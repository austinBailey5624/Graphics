// Block.h

#ifndef BLOCK_H
#define BLOCK_H

#include <GL/gl.h>
#include "SceneElement.h"
#include "ShaderIF.h"

class Block : public SceneElement
{
public:
//	TEMPLATE_Subclass(ShaderIF* sIF, PhongMaterial& matl);
//	virtual ~TEMPLATE_Subclass();
	Block(ShaderIF* sIF, PhongMaterial& matl, float cx, float cy, float cz, float lx, float ly, float lz);//rgb removed since included in
	//PhongMaterial
	virtual ~Block();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	bool handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY);
	void render();
private:
	GLuint vao[1];
	GLuint vbo[1];
	GLuint ebo[3];

	float xmin;
	float xmax;
	float ymin;
	float ymax;
	float zmin;
	float zmax;

	static GLuint indexList[3][4];

	void defineBlock();
	void renderBlock();
};

#endif
