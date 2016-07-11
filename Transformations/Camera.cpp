#include "Camera.h"
#include <math.h>

namespace Protoone
{
	Camera::Camera(float x, float y, float z) : _position(x, y, z), _lookAt(0, 0, 0), _direction(0, 0, 1), r(1), _theta(-1.6), _phi(4.6), center(x,y,z)
	{
		_ux = 0.0;
		_uy = 1.0;
		_uz = 0.0;
	}

	Camera::~Camera(void)
	{
	}

	void Camera::Look()
	{
		float x = _distance * sin(_theta) * cos(_phi);
		float y = _distance * cos(_theta);
		float z = _distance * sin(_theta) * sin(_phi);
 
		float bla = center[0];
		float blub = center[1];
		float blip = center[2];

		_position[0] = center[0] + x;
		_position[1] = center[1] + y;
		_position[2] = center[2] + z;
		_direction[0] = -x;
		_direction[1] = -y;
		_direction[2] = -z;


		gluLookAt(_position[0], _position[1], _position[2],
				  center.X(), center.Y(), center.Z(),
				  0, 1, 0);
	}

	void Camera::setPosition(const int x, const int y, const int z)
	{
		//center.X() = (float)x;
		//center.Y() = (float)y;
		//center.Z() = (float)z;
		_lookAt.X() = _position.X() + _direction.X();
		_lookAt.Y() = _position.Y() + _direction.Y();
		_lookAt.Z() = _position.Z() + _direction.Z();
	}

	Math::Vector3* Camera::getPosition()
	{
		return &_position;
	}

	void Camera::setPosition(const Math::Vector3* position)
	{
		//center.mimik(*position);
	}

	void Camera::setOrientation(const double xAngle, const double yAngle, const double zAngle)
	{
		_orientation[0] = xAngle;
		_orientation[1] = yAngle;
		_orientation[2] = zAngle;
	}

	void Camera::getOrientation(double& xAngle, double& yAngle, double& zAngle)
	{
		//xAngle = _xAngle;
		//yAngle = _yAngle;
		//zAngle = _zAngle;
	}

	void Camera::setParameters(float distance, float theta, float phi)
	{
		_theta = theta;
		_phi = phi;
		_distance = distance;

		//std::cout << phi << "\n";
	}
}