// RubiksCube.h

#ifndef RUBIKSCUBE_H
#define RUBIKSCUBE_H

#include "SceneElement.h"
#include "ShaderIF.h"
#include "RubiksBlock.h"
#include <GL/gl.h>
//following three are for shuffle
#include <cstdio> /** NULL */
#include <cstdlib> /** srand(), rand() */
#include <ctime> /** time() */

class RubiksCube : public SceneElement
{
public:
	// As before: you will likely want to add parameters to the constructor
	RubiksCube(ShaderIF* sIF,PhongMaterial& matl, float xmin,float ymin,float zmin, float l, int which, bool modifiable);
	virtual ~RubiksCube();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	bool handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY);
	void render();
private:
	RubiksBlock* blocks[3][3][3];
	void rotate(int direction);
	void solve();
	int dirAfterRotate(int direction, int olddir);
	ShaderIF* shaderIF;
	float xmin;
	float xmax;
	float ymin;
	float ymax;
	float zmin;
	float zmax;
	float length;
	bool m_modifiable;
};

#endif
