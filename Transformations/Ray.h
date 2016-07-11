#pragma once

#include "Vector3.h";
#include "Drawable.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

namespace Math
{

	class Ray : public Protoone::Drawable
	{
	private:
		static int min(const double a, const double b, const double c);

	public:
		Ray(double xB, double yB, double zB, double xDir, double yDir, double zDir);
		~Ray(void);


		Vector3 _base;	// basepoint of the line
		Vector3 _dir;	// direction
		/*
		/	Returns the z coordinate at which two rays are closest to each other.
		*/
		static Vector3 virtualIntersection(const Ray a, const Ray b);
		static Vector3 virtualIntersection2pointO(const Ray a, const Ray b);
		Vector3 pointAtX(double x) const;			// returns the point at which the line arrives with base + x * direction
		void draw();
		void draw(double scale);
	};

}