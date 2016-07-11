#pragma once

#include "Vector.h";
#include <math.h>

namespace Math
{
	class Vector2 : public Vector
	{
	private:
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

	public:
		static Vector2* cross(const Vector2* a, const Vector2* b)
		{
			Vector2* res = new Vector2();
			(*res)[0] = (*a)[1] * (*b)[2] + (*a)[2] * (*b)[1];
			(*res)[1] = (*a)[2] * (*b)[0] + (*a)[0] * (*b)[2];

			return res;
		}

		Vector2(void)
			: Vector(2)
		{ }

		Vector2(const double x, const double y) 
			: Vector(2)
		{
			_elements[0] = x;
			_elements[1] = y;
		}

		Vector2(const Vector2& vector);


		~Vector2() {}

		void normalize()
		{
			double sum = _elements[0] * _elements[0] + _elements[1] * _elements[1];
			if(sum == 0.0) 
				return;

			sum = std::sqrt(sum);
			sum = 1.0 / sum;
			_elements[0] *= sum;
			_elements[1] *= sum;
		}

		double length()
		{
			return std::sqrt(_elements[0] * _elements[0] + _elements[1] * _elements[1]);
		}

		Element X() const
		{
			return _elements[0];
		}

		Element Y() const
		{
			return _elements[1];
		}

		Element& X()
		{
			return _elements[0];
		}

		Element& Y()
		{
			return _elements[1];
		}

		Vector2 operator + (const Vector2& right) const
		{
			Vector2* out = new Vector2();
			for(unsigned int i=0; i<out->getNumElements(); ++i)
				(*out)[i] = (*this)[i] + right[i];
			return *out;
		}
	};
}
