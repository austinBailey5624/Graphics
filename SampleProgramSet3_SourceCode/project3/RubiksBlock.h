// TEMPLATE_Subclass.h

#ifndef RUBIKSBLOCK_H
#define RUBIKSBLOCK_H

#include "SceneElement.h"
#include "ShaderIF.h"
#include "Block.h"
#include "PhongMaterial.h"
class RubiksBlock : public SceneElement
{
public:
	RubiksBlock(ShaderIF* sIF, PhongMaterial& base, float cx, float cy, float cz, float length, int white, int red);
	//int white and red determine the direction of the cube

	virtual ~RubiksBlock();

	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	ShaderIF* shaderIF;
	float xmin;
	float xmax;
	float ymin;
	float ymax;
	float zmin;
	float zmax;

	Block* top;
	Block* bottom;
	Block* right;
	Block* left;
	Block* front;
	Block* back;

	static PhongMaterial white;
	static PhongMaterial yellow;
	static PhongMaterial blue;
	static PhongMaterial green;
	static PhongMaterial red;
	static PhongMaterial orange;

};

#endif
