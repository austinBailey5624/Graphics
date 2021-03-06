// ModelView.c++ - a basic combined Model and View for OpenGL

#include <iostream>

#include "ModelView.h"
#include "Controller.h"
#include "ShaderIF.h"

double ModelView::mcRegionOfInterest[6] = { -1.0, 1.0, -1.0, 1.0, -1.0, 1.0 };
bool ModelView::aspectRatioPreservationEnabled = true;
vec3 ModelView::colors[6] = { {0,0,1},{0,1,0},{1,0,0},{1,1,0},{1,0,1},{0,1,1} };
int ModelView::id = 0;

// NOTE: You will likely want to modify the ModelView constructor to
//       take additional parameters.
/*
ModelView::ModelView(ShaderIF* sIF, vec2* coords) : shaderIF(sIF)
{
	// TODO: define and call method(s) to initialize your model and send data to GPU
	initModelGeometry(coords);
	m_numVerticies = 1;
}*/

ModelView::ModelView(ShaderIF* sIF, vec2* coords, int numVertices) : shaderIF(sIF)
{
/*
	for(int i=0; i<numVertices; i++)
	{
		std::cout << "coords[i]" << coords[i][0] << "," << coords[i][1]<<"\n";
	}*///debugging
	myId = id;
	id++;
	m_numVerticies = numVertices;
	//std::cout << "m_numVertices: " << m_numVerticies << "\n"; debugging
	initModelGeometry(coords);
}

ModelView::~ModelView()
{
	// TODO: delete the vertex array objects and buffers here
	if (vao[0] > 0)
	{
		glDeleteBuffers(1, vbo);
		glDeleteVertexArrays(1, vao);
		vao[0] = vbo[0] = 0;
	}
}

void ModelView::initModelGeometry(vec2* verticies)
{
	color[0] = colors[myId % 6][0];
	color[1] = colors[myId % 6][1];
	color[2] = colors[myId % 6][2];
	glGenVertexArrays(1, vao);
	glGenBuffers(1, vbo);

	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	int bytesinBuffer = m_numVerticies * sizeof(vec2);

	glBufferData(GL_ARRAY_BUFFER, bytesinBuffer, verticies, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("MC"), 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("MC"));


	xmin = verticies[0][0];
	xmax = verticies[0][0];
	ymin = verticies[0][1];
	ymax = verticies[0][1];

	for(int i = 0; i<m_numVerticies; i++)
	{
		if(verticies[i][0] < xmin)
		{
			xmin = verticies[i][0];
		//	std::cout << "xmin updated to: " << xmin <<"\n";
		}
		if(verticies[i][0] > xmax)
		{
			xmax = verticies[i][0];
		//	std::cout << "xmax updated to: " << xmax << "\n";
		}
		if(verticies[i][1] < ymin)
		{
			ymin = verticies[i][1];
		//	std::cout << "ymin updated to: " << ymin << "\n";
		}
		if(verticies[i][1] > ymax)
		{
			ymax = verticies[i][1];
		//	std::cout << "ymax updated to: " << ymax << "\n";
		}
	}
}

void ModelView::compute2DScaleTrans(float* scaleTransF) // CLASS METHOD
{
	// TODO: This code can be used as is, BUT be absolutely certain you
	//       understand everything about how it works.

	double xmin = mcRegionOfInterest[0];
	double xmax = mcRegionOfInterest[1];
	double ymin = mcRegionOfInterest[2];
	double ymax = mcRegionOfInterest[3];

	if (aspectRatioPreservationEnabled)
	{
		// preserve aspect ratio. Make "region of interest" wider or taller to
		// match the Controller's viewport aspect ratio.
		double vAR = Controller::getCurrentController()->getViewportAspectRatio();
		matchAspectRatio(xmin, xmax, ymin, ymax, vAR);
	}

    // We are only concerned with the xy extents for now, hence we will
    // ignore mcRegionOfInterest[4] and mcRegionOfInterest[5].
    // Map the overall limits to the -1..+1 range expected by the OpenGL engine:
	double scaleTrans[4];
	linearMap(xmin, xmax, -1.0, 1.0, scaleTrans[0], scaleTrans[1]);
	linearMap(ymin, ymax, -1.0, 1.0, scaleTrans[2], scaleTrans[3]);
	for (int i=0 ; i<4 ; i++)
		scaleTransF[i] = static_cast<float>(scaleTrans[i]);
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void ModelView::getMCBoundingBox(double* xyzLimits) const
{
	// TODO:
	// Put this ModelView instance's min and max x, y, and z extents
	// into xyzLimits[0..5]. (-1 .. +1 is OK for z direction for 2D models)
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = -1;
	xyzLimits[5] = 1;
}

bool ModelView::handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY)
{
	return true;
}

// linearMap determines the scale and translate parameters needed in
// order to map a value, f (fromMin <= f <= fromMax) to its corresponding
// value, t (toMin <= t <= toMax). Specifically: t = scale*f + trans.
void ModelView::linearMap(double fromMin, double fromMax, double toMin, double toMax,
					  double& scale, double& trans) // CLASS METHOD
{
	scale = (toMax - toMin) / (fromMax - fromMin);
	trans = toMin - scale*fromMin;
}

void ModelView::matchAspectRatio(double& xmin, double& xmax,
        double& ymin, double& ymax, double vAR)
{
	// TODO: This code can be used as is, BUT be absolutely certain you
	//       understand everything about how it works.

	double wHeight = ymax - ymin;
	double wWidth = xmax - xmin;
	double wAR = wHeight / wWidth;
	if (wAR > vAR)
	{
		// make window wider
		wWidth = wHeight / vAR;
		double xmid = 0.5 * (xmin + xmax);
		xmin = xmid - 0.5*wWidth;
		xmax = xmid + 0.5*wWidth;
	}
	else
	{
		// make window taller
		wHeight = wWidth * vAR;
		double ymid = 0.5 * (ymin + ymax);
		ymin = ymid - 0.5*wHeight;
		ymax = ymid + 0.5*wHeight;
	}
}

void ModelView::render() const
{
	// save the current GLSL program in use
	GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);

	// draw the triangles using our vertex and fragment shaders
	glUseProgram(shaderIF->getShaderPgmID());

	float scaleTrans[4];
	compute2DScaleTrans(scaleTrans);

	glUniform3fv(shaderIF->ppuLoc("color"),1, color);
	glUniform4fv(shaderIF->ppuLoc("scaleTrans"),1,scaleTrans);

	glBindVertexArray(vao[0]);
	glDrawArrays(GL_LINE_STRIP, 0, m_numVerticies);

	// restore the previous program
	glUseProgram(pgm);
}

void ModelView::setMCRegionOfInterest(double xyz[6])
{
	for (int i=0 ; i<6 ; i++)
		mcRegionOfInterest[i] = xyz[i];
}
