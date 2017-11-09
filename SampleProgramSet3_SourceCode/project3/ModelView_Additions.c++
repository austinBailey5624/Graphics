// Extracted from: ModelView.c++ - an Abstract Base Class for a combined Model and View for OpenGL

#include "ModelView.h"

void ModelView::addToGlobalPan(double dxInLDS, double dyInLDS, double dzInLDS)
{
	// TODO: Delete or comment out the following std::cout statement when
	//       everything else is done here.
	//std::cout << "In project 3, you will implement ModelView::addToPan in ModelView_Additions.c++\n";
	// TODO: 1. Use last_ecXmin, et al. with dxInLDS, et al. to translate the LDS
	//          pan vector to an EC pan vector.
	double dxInEC = (dxInLDS/2)*(last_ecXmax-last_ecXmin);
	double dyInEC = (dyInLDS/2)*(last_ecYmax-last_ecYmin);

	cryph::AffVector panVec(dxInEC,dyInEC,dzInLDS);
	cryph::Matrix4x4 translationMatrix = cryph::Matrix4x4::translation(panVec);

	//       2. UPDATE dynamic_view
	dynamic_view = translationMatrix * dynamic_view;

}

void ModelView::addToGlobalRotationDegrees(double rx, double ry, double rz)
{

	cryph::Matrix4x4 xRot = cryph::Matrix4x4::xRotationDegrees(rx);
	cryph::Matrix4x4 yRot = cryph::Matrix4x4::yRotationDegrees(ry);
	cryph::Matrix4x4 zRot = cryph::Matrix4x4::zRotationDegrees(rz);
	dynamic_view = xRot*yRot*zRot*dynamic_view;

}

void ModelView::getMatrices(cryph::Matrix4x4& mc_ec, cryph::Matrix4x4& ec_lds)
{
	cryph::Matrix4x4 M_ECu = cryph::Matrix4x4::lookAt(ModelView::eye,
			ModelView::center, ModelView::up);


	cryph::AffVector distEyeCenterVec(0,0,ModelView::distEyeCenter);
	cryph::Matrix4x4 moveToCenter = cryph::Matrix4x4::translation(distEyeCenterVec);
	cryph::Matrix4x4 moveBack = cryph::Matrix4x4::translation(-distEyeCenterVec);

	mc_ec = moveBack*dynamic_view*moveToCenter*M_ECu;
	double deltaMcs[3];
	double* xyz = ModelView::mcRegionOfInterest;
	double max;

	deltaMcs[0] = xyz[1] - xyz[0];
	deltaMcs[1] = xyz[3] - xyz[2];
	deltaMcs[2] = xyz[5] - xyz[4];
	max = deltaMcs[0];
	for(int i = 1; i<3; i++)
	{
		if(deltaMcs[i] > max)
		{
			max = deltaMcs[i];
		}
	}

	double circumscribingSphereRadius = max/2; // Don't use 0.0; compute it!!!
	last_ecXmin = -circumscribingSphereRadius*dynamic_zoomScale;
	last_ecXmax = circumscribingSphereRadius*dynamic_zoomScale;
	last_ecYmin = -circumscribingSphereRadius*dynamic_zoomScale;
	last_ecYmax = circumscribingSphereRadius*dynamic_zoomScale;

	double viewPortAspectRatio = Controller::getCurrentController()->getViewportAspectRatio();
	ModelView::matchAspectRatio(last_ecXmin,last_ecXmax,last_ecYmin,last_ecYmax,viewPortAspectRatio);

	if (ModelView::projType == ORTHOGONAL)
		ec_lds = cryph::Matrix4x4::orthogonal(last_ecXmin, last_ecXmax, last_ecYmin, last_ecYmax,
				ModelView::ecZmin, ModelView::ecZmax);
	else if (ModelView::projType == PERSPECTIVE)
		ec_lds = cryph::Matrix4x4::perspective(ModelView::ecZpp,
				last_ecXmin, last_ecXmax, last_ecYmin, last_ecYmax, ModelView::ecZmin, ModelView::ecZmax);
	else // Must be OBLIQUE
		ec_lds = cryph::Matrix4x4::oblique(ModelView::ecZpp,
				last_ecXmin, last_ecXmax, last_ecYmin, last_ecYmax, ModelView::ecZmin, ModelView::ecZmax,
				ModelView::obliqueProjectionDir);

}

void ModelView::scaleGlobalZoom(double multiplier)
{
	dynamic_zoomScale *= multiplier;
	// TODO: Project 3: Use dynamic_zoomScale in ModelView::getMatrices
}
