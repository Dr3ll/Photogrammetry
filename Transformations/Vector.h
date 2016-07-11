#pragma once
#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <algorithm>

namespace Math
{
	class Vector
	{
	public:
		/// Vector number-type.
		typedef float Element;
		
		Vector() {}

		/// Create empty from size, filled with a given value.
		/// \param size		vectors size
		/// \param value	value applied to all elements
		explicit Vector(unsigned int size, Element value = 0);

		/// additional move constructor

		Vector(Vector&& move) : _elements(std::move(move._elements)), _size(move._size) {}

		/// Copy constructor.
		Vector(const Vector& vector);

		/// Destructor, releases allocated memory.
		~Vector() {}

		void mimik(const Vector& vector)
		{
			this->_elements.reset(new Element[vector._size]);
			_size = vector._size;

			for(int i=0; i<_size; ++i)
				_elements[i] = vector._elements[i];
		}

		/// Returns number of elements
		unsigned int getNumElements() const { return _size; }

		/// Destroys content of this instance and copies all data from the right one
		/// \param right	assigned Math::Vector
		/// \return Reference to this
		Vector& operator = (const Vector& right);

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

		Vector operator + (const Vector& right) const
		{
			Vector out(std::max(_size, right._size));
			for(unsigned int i=0; i<out.getNumElements(); ++i)
				out[i] = (*this)[i] + right[i];
			return out;
		}
		
		Vector operator - (const Vector& right) const
		{
			Vector out(std::max(_size, right._size));
			for(unsigned int i=0; i<out.getNumElements(); ++i)
				out[i] = (*this)[i] - right[i];
			return out;
		}

		Vector operator * (const Element& right) const
		{
			Vector out(*this);
			for(unsigned int i=0; i<out.getNumElements(); ++i)
				out[i] *= right;
			return out;
		}

		Element operator * (const Vector& right) const
		{
			float out = 0.0f;
			unsigned int numElements = std::max(_size, right._size);
			for(unsigned int i=0; i<numElements; ++i)
				out += (*this)[i] * right[i];
			return out;
		}

		std::string toString()
		{
			std::string out;
			for(unsigned int i=0; i<_size; ++i)
			{
				out.append(std::to_string(static_cast<long long>((*this)[i])));
				if(i<_size-1)
					out.append(", ");
			}

			return out;
		}
		
	protected:
		/// intern element array
		std::unique_ptr<Element[]> _elements;

		/// number of elements
		unsigned int _size;
	};

	inline Vector operator * (const Vector::Element& left, const Vector right)
	{
		Vector out(right);
		for(unsigned int i=0; i<out.getNumElements(); ++i)
			out[i] *= left;
		return out;
	}

	/// Output to std::ostream
	inline std::ostream& operator << (std::ostream& left, const Vector& right)
	{
		left << "(";
		for(unsigned int i=0; i<right.getNumElements()-1; ++i)
			left << right[i] << " | ";
		return left << right[right.getNumElements()-1] << ")";
	}
}