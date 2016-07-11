#pragma once

#include <iostream>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "StereoCam.h";
#include "Plane.h";
#include <vector>
#include "MImage.h";
#include "Ray.h";
#include "Vector3.h";
#include "VectorVOA.h";
#include "Triangle.h";
#include <fstream>
#include "StopWatch.h";

using namespace std;
using namespace Math;

#define BUFFER MAX_PATH

namespace Protoone
{
	class CameraSetup
	{
	private:
		Math::Plane _recPlane; // Rectified image plane
		vector<VectorVOA> _rawPoints; // contains z-coordinates for the 3d-visualisation

		float _nBlocksX;
		float _nBlocksY;

		float _scaling;

		int _globalIndex;
		vector<int> _indices;
		vector<VectorVOA> _positions;
		vector<VectorVOA> _normals;
		vector<Triangle> _triangles;

		GLuint _positionBufferHandle;
		GLuint _normalBufferHandle;
		GLuint _indexBufferHandle;
		GLuint _vertexArrayHandle;

		float average;

		vector<Vector3> _correlationsA;
		vector<Vector3> _correlationsB;

		void CalcPlane();
		double matchBlocksSAD(int xA, int yA, int xB, int yB, int width, int height);				// Returns the SAD matching value of two given image blocks
		void computeBlock(int xBlockoffset, int yBlockoffset, int x, int y, int width, int height);	// Computes a specified block of image A
		void computeBlockWholeKernel(int xBlockoffset, int yBlockoffset, int xA, int yA, int width, int height);
		void computeBlockDoubleScan(int xBlockoffset, int yBlockoffset, float xAMath, float yAMath, float xAIndex, float yAIndex, int cWidth, int cHeight, int bWidth, int bHeight);
		Vector3 calcZCoordinate(double xA, double yA, double xB, double yB);														// Returns the Z coordinate resulting of given given corresponding points

		void generateTriangle(VectorVOA v0, VectorVOA v1, VectorVOA v2, unsigned int& index);
		void generateGeometrie();
		void readGeometrie();
		void quantizeImages();
		void adjustForAnomalies(double** errors, int xBlockoffset, int yBlockoffset, double& xOut, double& yOut);
		void clearAll();

	public:
		CameraSetup(float scale);
		~CameraSetup(void);

		StereoCam _cL;	// Left camera
		StereoCam _cR;  // Right camera

		bool DeliverSetup(StereoCam& cL, StereoCam& cR);
		void createVisualisation(int startX, int startY,
								 int endX, int endY, 
								 int xBlockoffset, int yBlockoffset,
								 int cellsX, int cellsY,
								 int blockWidth, int blockHeight);
		void drawGeometrie();
		void drawCorrelations();

		int _cellsX, _cellsY;;

		MImage* _imageA;
		MImage* _imageB;

		int count;
	};

}