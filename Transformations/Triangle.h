#define TRIANGLE_H

#include "VectorVOA.h"

using namespace Math;

namespace Protoone
{
	class Triangle 
	{

		public:
   
		Triangle(VectorVOA p0, VectorVOA p1, VectorVOA p2); 
		void draw(bool drawFaceNormal); 
		VectorVOA getNormal() { return mNormal; };
		VectorVOA getPoint(int i) {return mVertices[i]; };

		private:
   
			VectorVOA mVertices[3]; 
			VectorVOA mNormals[3]; 
			VectorVOA mColor; 
			VectorVOA mNormal; 
	};
}


