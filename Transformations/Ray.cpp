#include "Ray.h"

namespace Math
{

	Ray::Ray(double xB, double yB, double zB, double xDir, double yDir, double zDir)
		: _base(xB, yB, zB), _dir(xDir, yDir, zDir)
	{
		_dir.normalize();
	}

	Ray::~Ray(void)
	{
	}

	// Returns information over which value is smaller between a, b and c
	// a : -1; b : 0; c : 1
	// if a xor c are equal to b, the decision falls on b by default
	// if a and c are equal 42 is returned (see virtualIntersection() for what this indicates)
	int Ray::min(const double a, const double b, const double c)
	{
		if(a == b || c == b)
		{
			return 0;
		}

		if(a == c)
		{
			return 42;
		}

		if(a<b && a<c)
		{
			return -1;
		}
		if(b<a && b<c)
		{
			return 0;
		}
		if(c<a && c<b)
		{
			return 1;
		}

		return -100;
	}

	// Returns the approximated closest point between two given lines
	Vector3 Ray::virtualIntersection(const Ray a, const Ray b)
	{
		/*
		The algorithm defines 3 guessed X values along the lines; A, B and C.
		At all times it is true that A < B < C and the distance between the points is pairwise with B == stepsize
		For each iteration the distances between the point pairs for X = A, B or C on the lines are calculated.
		Depending on which point pairs are closest the guesses are redefined for the next iteration.
		
		If A or C is the closest guess, A', B' and C' are defined like so that the guesses traverse in the 
		indicated direction by stepsize (or -stepsize in case of A = closest).

		If B is the closest guess, the stepsize is halfed and A', B' and C' are redefined like so that they cover the area between B 
		and whichever was closer out of A and C.

		The algorithm stops either when the maximum number of iterations is reached or the guesses A and C are of equal quality (indicating that B is the perfect X).
		*/

		//return 500;

		int max_depth = 50;
		double stepsize = 50;
		//float guessA = 10;
		//float guessB = 50;
		//float guessC = 110;

		double guessA = 10;
		double guessB = 250;
		double guessC = 500;

		double distA(0);
		double distB(0);
		double distC(0);

		for(int i(0); i<max_depth; ++i)
		{
			distA = (a.pointAtX(guessA) - b.pointAtX(guessA)).length();
			distB = (a.pointAtX(guessB) - b.pointAtX(guessB)).length();
			distC = (a.pointAtX(guessC) - b.pointAtX(guessC)).length();

			if(min(distA, distB, distC) == -1)			// case 1: A is nearest,  A' is A - step, B' is A, C' is B
			{
				double H(guessB);
				guessB = guessA;
				guessA = guessA - stepsize;
				guessC = H;

				continue;
			}

			if(min(distA, distB, distC) == 1)			// case 2: C is nearest,  A' is B, B' is C, C' is C + step
			{
				double H(guessB);
				guessB = guessC;
				guessC = guessC + stepsize;
				guessA = H;

				continue;
			}

			if(min(distA, distB, distC) == 0)			// case 3: B is nearest
			{
				if(distA < distC)						// subcase 1: A is closer than C -> X is between A and B
				{
					stepsize *= .5f;
					guessB = guessA + stepsize;
					guessC = guessB + stepsize;
				}
				if(distC < distA)						// subcase 1: C is closer than A -> X is between B and C
				{
					stepsize *= .5f;
					guessB = guessC - stepsize;
					guessA = guessB - stepsize;
				}

				continue;
			}

			if(min(distA, distB, distC) == 42)			// case 4: B is the perfect guess
			{
				break;
			}
		}

		if(guessB < 0)
			guessB = 1500;
		else
			guessB -= 2000;

		//guessB = 1500;

		Vector3 leftApprox = a.pointAtX(guessB);
		Vector3 rightApprox = b.pointAtX(guessB);

		Vector3 out((leftApprox.X() + rightApprox.X() / 2), 
					leftApprox.Y(), 
					leftApprox.Z());
		out = leftApprox;

		//std::cout << guessB;

		//out[0] *= .9f;

		return out;
	}

	Vector3 Ray::virtualIntersection2pointO(const Ray rayB, const Ray rayA)
	{
		Vector3 w0 = rayA._base - rayB._base;
		double a = rayA._dir * rayA._dir;
		double b = rayA._dir * rayB._dir;
		double c = rayB._dir * rayB._dir;
		double d = rayA._dir * w0;
		double e = rayB._dir * w0;

		double sC = ((b * e) - (c * d))/((a * c) - (b * b));
		double tC = ((a * e) - (b * d))/((a * c) - (b * b));

		Vector3 average = (rayA.pointAtX(sC) + rayB.pointAtX(tC)) * .5f;

		//average = rayB.pointAtX(tC);
		
		//std::cout << "A: " << rayA.pointAtX(sC).toString() << "   B: " << rayB.pointAtX(tC).toString() << "  average: " << average.toString();

		//average[2] *= -1;

		return average;
	}

	Vector3 Ray::pointAtX(double x) const
	{
		Vector3 out(0);
		out = _base + (_dir * x);

		double z = out[2];

		return out;
	}

	void Ray::draw()
	{
		glDisable(GL_LIGHTING);

		glColor4f(1,0,0,1);
		glBegin(GL_LINE_STRIP);
				glVertex3f(_base.X(), _base.Y(), _base.Z());
				glVertex3f(_dir.X() * 100000, _dir.Y() * 100000, _dir.Z() * -100000);
		glEnd();

		glEnable(GL_LIGHTING);
	}

	void Ray::draw(double scale)
	{
		glDisable(GL_LIGHTING);

		glColor4f(1,0,0,1);
		glBegin(GL_LINE_STRIP);
				glVertex3f(scale * _base.X(), scale * _base.Y(), scale * _base.Z());
				glVertex3f(_dir.X() * 100000, _dir.Y() * 100000, _dir.Z() * 100000);
		glEnd();

		glEnable(GL_LIGHTING);
	}

}