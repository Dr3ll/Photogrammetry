#include "StereoCam.h"

namespace Protoone
{

	StereoCam::StereoCam(float xCenter, float yCenter, float zCenter, 
						 float omega, float phi, float kappa,
						 float xMain, float yMain,
					 	 double camConst, double yScale, double zCross, double dist1, double dist2,
						 float visualisationScaling) :
			_projCenter(xCenter, yCenter, zCenter),
			_rotation(omega, phi, kappa),
			_mainPoint(xMain, yMain),
			_camConstant(camConst),
			_yScale(yScale),
			_zCross(zCross),
			_distortion1(dist1),
			_distortion2(dist2),
			_rotMatrix(cos(phi)*cos(kappa), cos(omega)*sin(kappa) + sin(omega)*sin(phi)*cos(kappa), sin(omega)*sin(kappa) - cos(omega)*sin(phi)*cos(kappa),
					   -cos(omega)*sin(kappa), -sin(omega)*sin(phi)*sin(kappa) + cos(omega)*cos(kappa), cos(omega)*sin(phi)*sin(kappa) + sin(omega)*cos(kappa),
					   sin(phi), -sin(omega)*cos(phi), cos(omega)*cos(phi)),
			_visualScale(visualisationScaling)
	{

		//_projCenter[2] += -50;
	}


	StereoCam::~StereoCam(void)
	{
	}

	void StereoCam::draw()
	{
		drawExtern();
		//drawIntern();
		//drawRays();
	}

	void StereoCam::drawExtern()
	{
		float scale = 100.0f;

		glDisable(GL_LIGHTING);

		glPushMatrix();
		glTranslatef(_visualScale * _projCenter.X(), _visualScale * _projCenter.Y(), _visualScale * _projCenter.Z());
		glRotatef(_rotation.X(), 1, 0, 0);
		glRotatef(_rotation.Y(), 0, 1, 0);
		glRotatef(_rotation.Z(), 0, 0, 1);

		// X-axis
		glBegin(GL_LINE_STRIP);
			glColor3f(1, 0, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(scale, 0, 0);
		glEnd();
		// Y-axis
		glBegin(GL_LINE_STRIP);
			glColor3f(0, 1, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, scale, 0);
		glEnd();
		// Z-axis
		glBegin(GL_LINE_STRIP);
			glColor3f(0, 0, 1);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, scale);
		glEnd();

		glPopMatrix();

		glEnable(GL_LIGHTING);
	}

	void StereoCam::drawRays()
	{
		glDisable(GL_LIGHTING);

		glColor4f(1, 1, 1, .5f);
		for(int i(0); i<rays.size(); ++i)
		{
				rays[i].draw(_visualScale);
		}

		glEnable(GL_LIGHTING);
	}

	void StereoCam::drawIntern()
	{
		float scale = 100000000.0f;

		glDisable(GL_LIGHTING);


		glColor4f(1, 1, 1, .5f);
		for(int x(0); x<656; ++x)
		{
			Math::Ray ray = getProjectionRay(x,0);

			ray.draw();

			ray = getProjectionRay(x,491);

			ray.draw();
		}

		glColor4f(1, 0, 0, .5f);
		for(int y(0); y<491; ++y)
		{
			Math::Ray ray = getProjectionRay(0,y);

			glBegin(GL_LINE_STRIP);
				glVertex3f(ray._base.X(), ray._base.Y(), ray._base.Z());
				glVertex3f(ray._dir.X(), ray._dir.Y(), ray._dir.Z() * scale);
			glEnd();

			ray = getProjectionRay(656,y);

			glBegin(GL_LINE_STRIP);
				glVertex3f(ray._base.X(), ray._base.Y(), ray._base.Z());
				glVertex3f(ray._dir.X(), ray._dir.Y(), ray._dir.Z() * scale);
			glEnd();
		}


		glEnable(GL_LIGHTING);
	}

	Math::Ray StereoCam::getProjectionRay(double x, double y)
	{
		Math::Ray ray(_projCenter.X(), _projCenter.Y(), _projCenter.Z(), 
			_rotMatrix.r11() * x + _rotMatrix.r12() * y + _rotMatrix.r13() * _camConstant,
			_rotMatrix.r21() * x + _rotMatrix.r22() * y + _rotMatrix.r23() * _camConstant,
			_rotMatrix.r31() * x + _rotMatrix.r32() * y + _rotMatrix.r33() * _camConstant);

		rays.push_back(ray);

		return ray;
	}

	void StereoCam::addRay(Math::Ray ray)
	{
		rays.push_back(ray);
	}

}