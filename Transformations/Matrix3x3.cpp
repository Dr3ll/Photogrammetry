#include "Matrix3x3.h"

namespace Math
{

	Matrix3x3::Matrix3x3(double r11, double r12, double r13, 
						 double r21, double r22, double r23,
						 double r31, double r32, double r33)
	{
		_elements[0][0] = r11;
		_elements[0][1] = r12;
		_elements[0][2] = r13;
		_elements[1][0] = r21;
		_elements[1][1] = r22;
		_elements[1][2] = r23;
		_elements[2][0] = r31;
		_elements[2][1] = r32;
		_elements[2][2] = r33;
	}


	Matrix3x3::~Matrix3x3(void)
	{
	}

}