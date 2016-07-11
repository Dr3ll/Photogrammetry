#include "Model.h"
#include "Vector.h";
#include <GL\glew.h>
#include <GL\freeglut.h>

namespace Protoone
{

	Model::Model(const std::function<void()> content, const Math::Vector3* position, const double xAngle, const double yAngle, const double zAngle)
		: _position(*position), Drawable()
	{
		_content = content;

		_xAngle = xAngle;
		_yAngle = yAngle;
		_zAngle = zAngle;
	}

	Model::~Model()
	{
	}

	void Model::setPosition(const int x, const int y, const int z)
	{
		_position.X() = (float)x;
		_position.Y() = (float)y;
		_position.Z() = (float)z;
	}

	Math::Vector3* Model::getPosition()
	{
		return &_position;
	}

	void Model::setPosition(const Math::Vector3* position)
	{
		_position.mimik(*position);
	}

	void Model::setOrientation(const double xAngle, const double yAngle, const double zAngle)
	{
		_xAngle = xAngle;
		_yAngle = yAngle;
		_zAngle = zAngle;
	}

	void Model::getOrientation(double& xAngle, double& yAngle, double& zAngle)
	{
		xAngle = _xAngle;
		yAngle = _yAngle;
		zAngle = _zAngle;
	}

	void Model::draw()
	{
		glPushMatrix();
		//glRotatef(_xAngle, 1.0f, 0.0f, 0.0f);
		//glRotatef(_yAngle, 0.0f, 1.0f, 0.0f);
		//glRotatef(_zAngle, 0.0f, 0.0f, 1.0f);
		glTranslatef((_position)[0], (_position)[1], (_position)[2]);

		_content();

		glPopMatrix();
	}

}
