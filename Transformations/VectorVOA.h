#pragma once
#define VECTOR_H

//#include <cassert>
#include <cmath>
#include "Vector3.h";

#define SQR(x)   ((x) * (x))

const int X = 0;
const int Y = 1;
const int Z = 2;

/**
 * Klasse zur Beschreibung eines Richtungsvektors im R3.
 * Der Vektor hat keinen Stuetzpunkt, nur eine Richtung, ausgehend vom Nullpunkt.
 */

namespace Math
{

class VectorVOA
{
   public:
   
      VectorVOA(); // Leerer Konstruktor
	  VectorVOA(Vector3 v)
	  {
		  mElement[0] = v.X();
		  mElement[1] = v.Y();
		  mElement[2] = v.Z();
	  }
      VectorVOA(float x, float y, float z); // Konstruktor ueber Werte
      VectorVOA(const VectorVOA &p); // Copy Konstruktor 
      
      // Vector worldToCam();
      
	inline void setValues(float x, float y, float z); // Setzt die Tupel mit eigenen Werten

      inline float length()    const; // Laenge des Vektors
      inline float lengthSqr() const; // Quadrat der Laenge
      inline void  normalize();
      inline void  normalizeCheck();
      
      inline VectorVOA operator -() const; // Ueberladener Operator fuer Invertierung

      inline VectorVOA operator +(const VectorVOA& v) const; // Ueberladener Operator fuer Addition
      inline VectorVOA operator -(const VectorVOA& v) const; // Ueberladener Operator fuer Subtraktion

      inline VectorVOA operator *(float s) const; // Ueberladener Operator fuer Multiplikation
      inline VectorVOA operator /(float s) const; // Ueberladener Operator fuer Division
      inline VectorVOA operator *(const VectorVOA &v) const;
      inline VectorVOA operator /(const VectorVOA &v) const;

      inline float& operator [](int index); // Ueberladener Operator fuer schreibzugriff
      inline const float& operator [](int index) const; // Ueberladener Operator fuer Lesezugriff

	  inline VectorVOA calcDifVector() const; //Funktion setzt die kleinste Komponente des Vektors auf 1
		
     
  private:
   
        float mElement[3]; //! Werte
};

inline float  dot  (const VectorVOA& v1, const VectorVOA& v2); // Skalarprodukt
inline VectorVOA cross(const VectorVOA& v1, const VectorVOA& v2); // Kreuzprodukt

inline VectorVOA normalize(const VectorVOA& v); // Normalisiert einen Vektor
// inline Vector normalizeCheck(const Vector& v); // Normalisiert einen Vektor

inline VectorVOA operator *(float s, const VectorVOA& v); // Operator fuer Skalarmultiplikation

/**
* Vektor mit Werte fuellen
 */
inline void VectorVOA::setValues(float x, float y, float z)
{
	mElement[X] = x;
	mElement[Y] = y;
	mElement[Z] = z;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/**
* Laenge des Vektors.
 * \return Laenge des Vektors
 */
float VectorVOA::length() const
{
	return (float)sqrt(SQR(mElement[X]) + SQR(mElement[Y]) + SQR(mElement[Z]));
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/**
* Laenge des Vektors zum Quadrat.
 * \return Laenge des Vektors ohne die Wurzel zu ziehen
 */
float VectorVOA::lengthSqr() const
{
	return SQR(mElement[X]) + SQR(mElement[Y]) + SQR(mElement[Z]);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/**
* Normalisiert den Vektor auf die L�ge 1.
 */
void VectorVOA::normalize()
{
	float len = length();
	
	//assert(len != 0.0);
	if (len > 0.0001) {	                   // *** remove this check !!!
		mElement[X] /= len;
		mElement[Y] /= len;
		mElement[Z] /= len;
	}
	else {
		mElement[X] = mElement[Y] = mElement[Z] = 0.0;
	}
}

#if 0
void Vector::normalizeCheck()
{
	float len = length();
	
	if (len != 0.0) {
	
		mElement[X] /= len;
		mElement[Y] /= len;
		mElement[Z] /= len;
	}
	else {
		mElement[X] = mElement[Y] = mElement[Z] = 0.0;
	}
	// return this;
}
#endif

/**
* Ueberladener negierungs-Operator.
 */
VectorVOA VectorVOA::operator -() const
{
	return VectorVOA(-mElement[X], -mElement[Y], -mElement[Z]);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/**
* Ueberladener Operator fuer die Addtion.
 */
VectorVOA VectorVOA::operator +(const VectorVOA& v) const
{
	return VectorVOA(mElement[X] + v[X], mElement[Y] + v[Y], mElement[Z] + v[Z]);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/**
* Ueberladener Operator fuer die Subtraktion.
 */
VectorVOA VectorVOA::operator -(const VectorVOA& v) const
{
	return VectorVOA(mElement[X] - v[X], mElement[Y] - v[Y], mElement[Z] - v[Z]);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/** 
* Ueberladener Operator fuer die Multiplikation mit einem Skalar.
*/
VectorVOA VectorVOA::operator *(float s) const
{
	return VectorVOA(s * mElement[X], s * mElement[Y], s * mElement[Z]);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/** 
* Komponentenweise Multiplikation 
*/
VectorVOA VectorVOA::operator *(const VectorVOA &v) const
{
	return VectorVOA(v[X] * mElement[X], v[Y] * mElement[Y], v[Z] * mElement[Z]);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/** 
* Komponentenweise Division 
*/
VectorVOA VectorVOA::operator /(const VectorVOA &v) const
{
	return VectorVOA(v[X] / mElement[X], v[Y] / mElement[Y], v[Z] / mElement[Z]);
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/**
* Ueberladener Operator fuer die Division durch einen Skalar.
 */
VectorVOA VectorVOA::operator /(float s) const
{
	//assert(s != 0);
	
	return VectorVOA(mElement[X] / s, mElement[Y] / s, mElement[Z] / s);
}


//------------------------------------------------------------------------------

/**
* Liefert das Skalar-(Vektor-)Produkt zweier Vektoren.
 * \param v1 Erster Vektor
 * \param v2 Zweiter Vektor
 * \return Skalarprodukt (Winkel)
 */
float dot(const VectorVOA& v1, const VectorVOA& v2)
{
	return (v1[X] * v2[X] + v1[Y] * v2[Y] + v1[Z] * v2[Z]);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/**
* Liefert das Kreuzprodukt zweier Vektoren.
 * \param v1 Erster Vektor
 * \param v2 Zweiter Vektor
 * \return Kreuzprodukt (Normalenvektor, nicht normalisiert)
 */
VectorVOA cross(const VectorVOA& v1, const VectorVOA& v2)
{
	return VectorVOA(v1[Y] * v2[Z] - v1[Z] * v2[Y],
				  v1[Z] * v2[X] - v1[X] * v2[Z],
				  v1[X] * v2[Y] - v1[Y] * v2[X]);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/**
* Liefert den Normalisierten Vektor zu dem uebergebenen.
 * Alternative zu der Membervariante, da hier der urspruengliche Vektor nicht veraendert wird.
 * \param v Zu normalisierender Vektor
 * \return Normalisierter Vektor
 */
VectorVOA normalize(const VectorVOA& v)
{
	float len = v.length();
	
	// //assert(len != 0);
	if (len > 0)
		return v / len;
	else 
		return VectorVOA(0,0,0);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/**
* Ueberladener Operator zur Multiplikation mit einem Skalar.
 * Notwendig fuer die Kommutativitaet der Multiplikation
 */
VectorVOA operator *(float s, const VectorVOA& v)
{
	return v * s;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/**
* Ueberladener Operator fuer den schreibenden Parameterzguriff.
 */
float& VectorVOA::operator [](int index)
{
	//assert(index >= X && index <= Z);
	
	return mElement[index];
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/**
* Ueberladener Operator fuer den lesenden Parameterzugriff.
 */
const float& VectorVOA::operator [](int index) const
{
	//assert(index >= X && index <= Z);
	
	return mElement[index];
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/**
* Setzt die kleinste Komponente des bergebenen Vektors auf 1
 * \param v Zu veraendernder Vektor
 * \return Vektor mit anderer Richtung
 */

VectorVOA VectorVOA::calcDifVector() const
{
	if (( fabsf(mElement[X]) <= fabsf(mElement[Y])) && ( fabsf(mElement[X]) <= fabsf(mElement[Z])))  
	{
		return VectorVOA(1.0f, mElement[Y], mElement[Z]);
	}
	else if (( fabsf(mElement[Y]) <= fabsf(mElement[X])) && ( fabsf(mElement[Y]) <= fabsf(mElement[Z]))) 
	{
		return VectorVOA(mElement[X], 1.0f, mElement[Z]);
	}
	else 
		return VectorVOA(mElement[X], mElement[Y], 1.0f);
	
}

}