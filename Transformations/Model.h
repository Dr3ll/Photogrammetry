#pragma once

#include "Vector3.h";
#include "Drawable.h";
#include <functional>;

namespace Protoone
{
	class Model : public Drawable
	{
	private:
		Math::Vector3 _position;
		double _xAngle;
		double _yAngle;
		double _zAngle;
		std::function<void()> _content;

	public:
		Model() :
		  _position(0, 0, 0), _content([](){})
		{}
		Model(const std::function<void()> content, const Math::Vector3* position, const double xAngle, const double yAngle, const double zAngle);
		~Model();

		void setPosition(const int x, const int y, const int z);
		Math::Vector3* getPosition();
		void setPosition(const Math::Vector3* position);
		void setOrientation(const double xAngle, const double yAngle, const double zAngle);
		void getOrientation(double& xAngle, double& yAngle, double& zAngle);

		void draw();
	};
}

