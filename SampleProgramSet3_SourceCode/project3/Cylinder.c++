// TEMPLATE_Subclass.c++

#include "Cylinder.h"

Cylinder::Cylinder(ShaderIF* sIF,PhongMaterial& matl, float radius, const cryph::AffPoint& topCenter, cryph::AffPoint& bottomCenter, int numPoints) : SceneElement(sIF,matl)
{
	numCircumferencePoints = numPoints;
	if(numCircumferencePoints<15)
	{
		numCircumferencePoints = 15;
	}
	else if(numCircumferencePoints>200)
	{
		numCircumferencePoints = 200;
	}

//	kd[0] = checkFloat(r);
//	kd[1] = checkFloat(g);
//	kd[2] = checkFloat(b);

//	kd[0] = r;
//	kd[1] = g;
//	kd[2] = b;

	xmin = topCenter.x - radius;
	xmax = topCenter.x + radius;
	ymin = bottomCenter.y;
	ymax = topCenter.y;
	zmin = topCenter.z - radius;
	zmax = topCenter.z + radius;

	direction = topCenter-bottomCenter;
	direction.normalize();

	typedef float vec3[3];
	int nPoints = 2 * numCircumferencePoints;
	vec3* coords = new vec3[nPoints+1];
	vec3* normals = new vec3[nPoints+1];
	double theta = 0.0;
	double pi = 3.1415926;
	double dtheta = 2.0*pi/numCircumferencePoints+1;

	cryph::AffVector dirCross = cryph::AffVector(direction.dx -1, direction.dy, direction.dz +1).cross(direction);

	cryph::AffPoint bottom = bottomCenter + radius*dirCross;
	cryph::AffPoint top = topCenter + radius * dirCross;

	for(int i = 0; i<= numCircumferencePoints; i++)
	{
		int j = 2*i;
		double dx = cos(theta);
		double dz = sin(theta);

		normals[j][0] = dx;
		normals[j][1] = 0.0;
		normals[j][2] = dz;
		normals[j+1][0] = dx;
		normals[j+1][1] = 0.0;
		normals[j+1][2] = dz;

		coords[j][0] = bottom.x + radius*dx;
		coords[j][1] = bottom.y;
		coords[j][2] = bottom.z + radius*dz;
		coords[j+1][0] = top.x + radius*dx;
		coords[j+1][1] = top.y;
		coords[j+1][2] = top.z + radius*dz;
		theta += dtheta;
	}

	glGenBuffers(2, vbo);
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, nPoints * sizeof(vec3), coords, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(sIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(sIF->pvaLoc("mcPosition"));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, nPoints * sizeof(vec3), normals, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(sIF->pvaLoc("mcNormal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(sIF->pvaLoc("mcNormal"));
}

Cylinder::~Cylinder()
{
	glDeleteBuffers(2,vbo);
	glDeleteVertexArrays(1,vao);
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Cylinder::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

float checkFloat(float f)
{
	if(f>1.0)
	{
		return 1.0;
	}
	if(f<0.0)
	{
		return 0.0;
	}
	return f;
}

//Note: Cylinder::render copied almost directly from
//MandM.Cylinder::render
void Cylinder::render()
{
	typedef float vec3[3];
	GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);
	glUseProgram(shaderIF->getShaderPgmID());

	establishMaterial();
	establishView();
	establishLightingEnvironment();

	cryph::Matrix4x4 mc_ec, ec_lds;
	getMatrices(mc_ec, ec_lds);
	float mat[16];
	glUniformMatrix4fv(shaderIF->ppuLoc("mc_ec"), 1, false, mc_ec.extractColMajor(mat));
	glUniformMatrix4fv(shaderIF->ppuLoc("ec_lds"), 1, false, ec_lds.extractColMajor(mat));

//	glUniform3fv(shaderIF->ppuLoc("kd"), 1, kd);
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 2*(numCircumferencePoints));

	glUseProgram(pgm);
}
