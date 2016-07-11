#pragma once

#include <GL\glew.h>
#include <GL\freeglut.h>
#include "Vector3.h";
#include "Vector2.h";
#include "Drawable.h";
#include "Matrix3x3.h";
#include "Ray.h";
#include <vector>
#include <iostream>

using namespace std;

namespace Protoone
{

	class StereoCam : public Drawable
	{
	private:
		// Extern
		Math::Vector3 _projCenter;
		Math::Vector3 _rotation;
		
		// Intern
		Math::Vector2 _mainPoint;
		double _camConstant;
		double _yScale;
		double _zCross;
		double _distortion1;
		double _distortion2;
		float _visualScale;

		vector<Math::Ray> rays;

		// Model
		Math::Matrix3x3 _rotMatrix;

	public:
		StereoCam(float xCenter, float yCenter, float zCenter, 
				  float xRotation, float yRotation, float zRotation,
				  float xMain, float yMain,
				  double camConst, double yScale, double zCross, double dist1, double dist2,
				  float visualisationScaling);
		~StereoCam(void);

		void draw();
		void drawExtern(); // Draws lines visualising the extern camera coordinate system
		void drawIntern(); // Draws lines visualising the intern camera coordinate system
		void drawRays();

		Math::Vector3 getProjCenter() const
		{
			return _projCenter;
		}

		void addRay(Math::Ray ray);

		/*
		/	Returns the line on wich the object point has to lie to be projected on the given image point.
		*/
		Math::Ray getProjectionRay(double x, double y);

	};

}
