#pragma once

#include "Vector3.h";

namespace Math
{
	class Plane
	{
	private:
		// Plane in coordinate form a1*x1 + a2*x2 + a3*x3 - b = 0
		float _a1;
		float _a2;
		float _a3;
		float _b;
		bool _isVoid;	// Reflects whether a plane is initialised; true == uninitialised

	public:
		Plane(float a1, float a2, float a3, float b) 
			: _a1(a1), _a2(a2), _a3(a3), _b(b) 
		{
			_isVoid = false;
		}

		Plane(void)
			:  _a1(0.0f), _a2(0.0f), _a3(0.0f), _b(0.0f) 
		{
			_isVoid = true;
		}

		~Plane(void);

		void Initialise(float a1, float a2, float a3, float b)
		{
			_a1 = a1;
			_a2 = a2;
			_a3 = a3;
			_b = b;

			_isVoid = false;
		}

		// Returns the intersection point of a line and this plane
		Vector3& Intersect(const Vector3 l) const;
	};

}

