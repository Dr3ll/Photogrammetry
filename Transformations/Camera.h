#pragma once

#include <GL\glew.h>
#include <GL\freeglut.h>
#include "Vector3.h";
#include <iostream>

namespace Protoone
{
	class Camera
	{
	private:
		Math::Vector3 _direction;
		Math::Vector3 _position;
		Math::Vector3 center;
		Math::Vector3 _lookAt;
		Math::Vector3 _orientation;
		float _ux;
		float _uy;
		float _uz;
		float _distance;

		float _theta, _phi;
		
		float r;

	public:
		Camera(float x, float y, float z);
		~Camera();

		void setPosition(const int x, const int y, const int z);
		Math::Vector3* getPosition();
		void setPosition(const Math::Vector3* position);
		void setOrientation(const double xAngle, const double yAngle, const double zAngle);
		void getOrientation(double& xAngle, double& yAngle, double& zAngle);
		void setParameters(float distance, float theta, float phi);

		void Look();
	};

}
