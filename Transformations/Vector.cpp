#include "Vector.h"

namespace Math
{
	Vector::Vector(unsigned int size, Element value) :
		_elements(new Element[size]),
		_size(size)
	{
		for(unsigned int i=0; i<_size; ++i)
			_elements[i] = value;
	}

	Vector::Vector(const Vector& vector) :
		_elements(new Element[vector._size]),
		_size(vector._size)
	{
		for(unsigned int i=0; i<_size; ++i)
			_elements[i] = vector._elements[i];
	}

	Vector& Vector::operator = (const Vector& right)
	{
		_size = right._size;
		_elements.reset(new Element[right._size]);
		for(unsigned int i=0; i<_size; ++i)
			_elements[i] = right._elements[i];
		return *this;
	}
}