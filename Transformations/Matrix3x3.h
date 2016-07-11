#pragma once

#include <memory>

namespace Math
{
	class Matrix3x3
	{
	protected:
		double _elements[3][3];

	public:
		Matrix3x3(double r11, double r12, double r13, 
				  double r21, double r22, double r23,
				  double r31, double r32, double r33);
		~Matrix3x3(void);

		double r11() const
		{
			return _elements[0][0];
		}
		double r12() const
		{
			return _elements[0][1];
		}
		double r13() const
		{
			return _elements[0][2];
		}
		double r21() const
		{
			return _elements[1][0];
		}
		double r22() const
		{
			return _elements[1][1];
		}
		double r23() const
		{
			return _elements[1][2];
		}
		double r31() const
		{
			return _elements[2][0];
		}
		double r32() const
		{
			return _elements[2][1];
		}
		double r33() const
		{
			return _elements[2][2];
		}
	};
}
