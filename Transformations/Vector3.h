#pragma once

#include "Vector.h";
#include <math.h>
#include <algorithm>

namespace Math
{
	class Vector3 : public Vector
	{
	private:

	public:
		static Vector3 cross(const Vector3& a, const Vector3& b)
		{
			Vector3 res(0);
			res[0] = (a)[1] * (b)[2] + (a)[2] * (b)[1];
			res[1] = (a)[2] * (b)[0] + (a)[0] * (b)[2];
			res[2] = (a)[0] * (b)[1] + (a)[1] * (b)[0];

			return res;
		}

		Vector3(void)
			: Vector(3)
		{ }

		Vector3(Element value)
			: Vector(3, value)
		{ }

		Vector3(const double x, const double y, const double z) 
			: Vector(3)
		{
			_elements[0] = x;
			_elements[1] = y;
			_elements[2] = z;
		}

		Vector3(const Vector3& vector);

		~Vector3() {}

		void normalize()
		{
			double sum = _elements[0] * _elements[0] + _elements[1] * _elements[1] + _elements[2] * _elements[2];
			if(sum == 0.0) 
				return;

			sum = std::sqrt(sum);
			sum = 1.0 / sum;
			_elements[0] *= sum;
			_elements[1] *= sum;
			_elements[2] *= sum;
		}

		double length() const
		{
			return std::sqrt(_elements[0] * _elements[0] + _elements[1] * _elements[1] + _elements[2] * _elements[2]);
		}

		/// Returns element at a given position.
		/// \param index	
		/// \return Reference to last element if index is invalid 
		Element operator [] (unsigned int index) const
		{
			if(index >= _size) index = _size-1;
			return _elements[index];
		}

		/// Returns reference to element at a given position.
		/// \param index	
		/// \return Reference to last element if index is invalid
		Element& operator [] (unsigned int index)
		{
			if(index >= _size) index = _size-1;
			return _elements[index];
		}

		Element X() const
		{
			return _elements[0];
		}

		Element Y() const
		{
			return _elements[1];
		}

		Element Z() const
		{
			return _elements[2];
		}

		Element& X()
		{
			return _elements[0];
		}

		Element& Y()
		{
			return _elements[1];
		}

		Element& Z()
		{
			return _elements[2];
		}

		Vector3 operator + (const Vector3& right) const
		{
			Vector3 out(0.0f);
			for(unsigned int i=0; i<3; ++i)
				out[i] = (*this)[i] + right[i];
			return out;
		}

		Vector3 operator += (const Vector3& right) const
		{
			Vector3 out(0.0f);
			for(unsigned int i=0; i<3; ++i)
				out[i] = (*this)[i] + right[i];
			return out;
		}

		Vector3 operator - (const Vector3& right) const
		{
			Vector3 out(0.0f);
			for(unsigned int i=0; i<out.getNumElements(); ++i)
				out[i] = (*this)[i] - right[i];
			return out;
		}

		Vector3 operator * (const Element& right) const
		{
			Vector3 out(*this);
			for(unsigned int i=0; i<out.getNumElements(); ++i)
				out[i] *= right;
			return out;
		}

		Vector3 operator *= (const Element& right) const
		{
			Vector3 out(*this);
			for(unsigned int i=0; i<out.getNumElements(); ++i)
				out[i] *= right;
			return out;
		}

		Element operator * (const Vector3& right) const
		{
			float out = 0.0f;
			unsigned int numElements = std::max(_size, right._size);
			for(unsigned int i=0; i<numElements; ++i)
				out += (*this)[i] * right[i];
			return out;
		}
	};
}
