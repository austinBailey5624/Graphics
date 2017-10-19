// TEMPLATE_Subclass.h
/*
#ifndef TEMPLATE_SUBCLASS_H
#define TEMPLATE_SUBCLASS_H

#include "ModelView.h"
#include "ShaderIF.h"

class TEMPLATE_Subclass : public ModelView
{
public:
	// As before: you will likely want to add parameters to the constructor
	TEMPLATE_Subclass(ShaderIF* sIF);
	virtual ~TEMPLATE_Subclass();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	ShaderIF* shaderIF;
	float kd[3];
};

#endif
*/
//RectPrism.h
#ifndef RECTPRISM_H
#define RECTPRISM_H

#include <GL/gl.h>

#include "ModelView.h"
#include "ShaderIF.h"

class RectPrism : public ModelView
{
	public:
		RectPrism(ShaderIF* sIF, float blx, float bly, float blz, float urx, float ury, float urz, float theta);//bl means bottom left corner, ur upper right corner, theta is rotation about z axis
		void getMCBoundingBox(double* xyzLimitsF) const;
		void render();
	private:
		ShaderIF* ShaderIF;
		GLunit vao[1];
		GLunit vbo[1];
		Glunit ebo[3];
		float kd[3];
		float xmin;
		float xmax;
		float ymin;
		float ymax;
		float zmin;
		float zmax;
		float theta;

		Block* top;
		Block* bottom;
		Block* left;
		Block* right;
		Block* front;
		Block* back;

		static GLunit indexList[3][4];
};
#endif
