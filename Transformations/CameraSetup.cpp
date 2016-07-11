#include "CameraSetup.h"

using namespace Math;

namespace Protoone
{

	CameraSetup::CameraSetup(float scale)
		: _cL(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0), 
		  _cR(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0), 
		  _recPlane(), count(0), _globalIndex(0), _scaling(scale), average(0), _cellsX(50), _cellsY(100)
	{
		_nBlocksX = 0;
		_nBlocksY = 0;
	}

	CameraSetup::~CameraSetup(void)
	{
	}

	bool CameraSetup::DeliverSetup(StereoCam& cL, StereoCam& cR)
	{
		_cL = cL;
		_cR = cR;

		return true;
	}

	// This function calculates the coordinate form for the rectified projection plane.
	// A plane in normal form is calculated with a normal perpendicular to the y-axis and the 
	// line intersecting the two projection centers.
	// The base vector is defined as the left projection center.
	void CameraSetup::CalcPlane()
	{

	}

	void CameraSetup::generateTriangle(VectorVOA v0, VectorVOA v1, VectorVOA v2, unsigned int& index)
	{
		int T = 60;

		if((v0 - v1).length() > T || (v1 - v2).length() > T || (v0 - v2).length() > T)
			return;

		if(v0[2] < 1000)
			return;

		double zScale = 1.0;
		v0[2] *= zScale;
		v1[2] *= zScale;
		v2[2] *= zScale;

		Triangle tri = Triangle(v0, v1, v2); 
		_positions.push_back(v0);
		_positions.push_back(v1);
		_positions.push_back(v2);

		_normals.push_back(1.0*tri.getNormal());
		_normals.push_back(1.0*tri.getNormal());
		_normals.push_back(1.0*tri.getNormal());

		_indices.push_back(index);
		index++;
		_indices.push_back(index);
		index++;
		_indices.push_back(index);
		index++;
	}


	void CameraSetup::generateGeometrie()
	{
		// Initialize light source
		GLfloat light_pos[] = {10, 10, -5000, 1};
		GLfloat light_col[] = { 1,  1,  1, 1};

		glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
		glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_col);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_col);

		std::cout << "\ngenerating geometrie...\n";

		unsigned int globalIndex(0);

		for(int x(0); x<_rawPoints.size()-_nBlocksX-2; x++ )
		{
			//if(x%(int)_nBlocksX != _nBlocksX-1)
			if(false)
			{
				generateTriangle(_rawPoints[x] * _scaling, 
								 _rawPoints[x+1] * _scaling,
								 _rawPoints[x+_nBlocksX+1] * _scaling,
								 globalIndex);
				generateTriangle(_rawPoints[x+1] * _scaling, 
								 _rawPoints[x+_nBlocksX+2] * _scaling,
								 _rawPoints[x+_nBlocksX+1] * _scaling,
								 globalIndex);
			}

				generateTriangle(_rawPoints[x] * _scaling, 
								 _rawPoints[x+1] * _scaling,
								 _rawPoints[x+_nBlocksX] * _scaling,
								 globalIndex);
				generateTriangle(_rawPoints[x+1] * _scaling, 
								 _rawPoints[x+_nBlocksX+1] * _scaling,
								 _rawPoints[x+_nBlocksX] * _scaling,
								 globalIndex);

			//if(x == _rawPoints.size() *.5)
			//	std::cout << (_rawPoints[x])[0] << ", " << (_rawPoints[x])[1] << ", " << (_rawPoints[x])[2] << "\n";
		}


		// Positions VBO
		glGenBuffersARB(1, &_positionBufferHandle);    // generate handle
		glBindBufferARB(GL_ARRAY_BUFFER, _positionBufferHandle);       // bind buffer
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(float) * 3 * _positions.size(), &_positions[0], GL_STATIC_DRAW);  // load data
		glBindBufferARB(GL_ARRAY_BUFFER, 0);   // unbind

		// Normals VBO
		glGenBuffersARB(1, &_normalBufferHandle);      // generate handle
		glBindBufferARB(GL_ARRAY_BUFFER, _normalBufferHandle);     // bind buffer
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(float) * 3 * _normals.size(), &_normals[0], GL_STATIC_DRAW);    // load data
		glBindBufferARB(GL_ARRAY_BUFFER, 0);    // unbind

		// Inidices VBO
		glGenBuffersARB(1, &_indexBufferHandle);     // generate handle
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, _indexBufferHandle);     // bind buffer
		glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * _indices.size(), &_indices[0], GL_STATIC_DRAW);      // load data
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, 0);     // unbind

		// VAO
		glGenVertexArrays(1, &_vertexArrayHandle);     // generate handle
		glBindVertexArray(_vertexArrayHandle);       // bind VAO

		// positions
		glBindBufferARB(GL_ARRAY_BUFFER, _positionBufferHandle);    // bind position VBO
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);     // 

		glBindBufferARB(GL_ARRAY_BUFFER, 0);

		// normals
		glBindBufferARB(GL_ARRAY_BUFFER, _normalBufferHandle);      // bind normals VBO
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindBufferARB(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void CameraSetup::drawCorrelations()
	{
		glDisable(GL_LIGHTING);
		//glTranslatef(-15.5231613748f, 87.4983429759f, 946.3892141258f);
		// Draw correlations visualisation
		if(true)
		{
			glPushMatrix();
			for(int i(0); i<_correlationsB.size(); i++)
			{
				glBegin(GL_LINE_STRIP);
					glColor3f(0, 1, 0);
					glVertex3f(_correlationsA[i].X(), _correlationsA[i].Y(), _correlationsA[i].Z());
					glColor3f(1, 0, 0);
					glVertex3f(_correlationsB[i].X(), _correlationsB[i].Y(), _correlationsB[i].Z());
				glEnd();
			}
			glPopMatrix();
		}

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}

	void CameraSetup::drawGeometrie()
	{
		// Draw Vertex buffer object with geometrie
		unsigned int numTriangles = _positions.size();

		//glLoadIdentity();

		//_progDepth.use();

		glColor3f(1, 0, 0);
		glBindVertexArray(_vertexArrayHandle);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, _indexBufferHandle);

		glDrawElements(GL_TRIANGLES, numTriangles, GL_UNSIGNED_INT, NULL);
	
		glBindVertexArray(0);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, 0);
		
		glEnable(GL_LIGHTING);

		//glUseProgram(0);
	}

	//void CameraSetup::createVisualisation(int xBlockoffset, int yBlockoffset, int width, int height)
	//{
	//	//_rawPoints = new VectorVOA*[_imageA->_width];
	//	//for(int i(0); i<_imageA->_width; ++i)
	//	//{
	//	//	_rawPoints[i] = new VectorVOA[_imageA->_height];
	//	//}

	//	// calculate how many blocks are needed of the specified size to span the whole image
	//	_nBlocksX = _imageA->_width / width;
	//	_nBlocksY = _imageA->_height / height;

	//	std::cout << "X: " << _nBlocksX << "  Y: " << _nBlocksY;

	//	// iterate over all blocks
	//	for(int x(0); x<_nBlocksX; ++x)
	//	{
	//		for(int y(0); y<_nBlocksY; ++y)
	//		{
	//			computeBlock(xBlockoffset, yBlockoffset, x, y, width, height);
	//		}
	//	}

	//	std::cout << "\n average: " << average/(_nBlocksX*_nBlocksY);

	//	generateGeometrie(width, height);
	//}

	void CameraSetup::quantizeImages()
	{
		float boxes = 50;

		for(int y(0); y<_imageA->_height; ++y)
		{
			for(int x(0); x<_imageA->_width; ++x)
			{
				float grey = (float)_imageA->_data[x][y];
				_imageA->_data[x][y] = ((unsigned int)(grey / boxes)) * boxes;

				grey = (float)_imageB->_data[x][y];

				_imageB->_data[x][y] = ((unsigned int)(grey / boxes)) * boxes;
			}
		}


	}

	void CameraSetup::clearAll()
	{
		_rawPoints.clear();



	}

	void CameraSetup::createVisualisation(int startX, int startY,
										  int endX, int endY, 
										  int xBlockoffset, int yBlockoffset, 
										  int cellsX, int cellsY,
										  int blockWidth, int blockHeight)
	{
		clearAll();

		cellsX = _cellsX;
		cellsY = _cellsY;

		// calculate how many blocks are needed of the specified size to span the whole image

		// It is calculated how many blocks would cover the whole image but only relevant ones are computed
		//int totalBlocksX = _imageA->_width / blockWidth;
		//int totalBlocksY = _imageA->_height / blockHeight;
		int totalCellsX = cellsX;
		int totalCellsY = cellsY;

		int cellWidth = _imageA->_width / cellsX;
		int cellHeight = _imageA->_height / cellsY;

		int startBlockX = startX / cellWidth;
		int startBlockY = startY / cellHeight;

		int endBlockX = totalCellsX - (_imageA->_width - endX) / cellWidth;
		int endBlockY = totalCellsY - (_imageA->_height - endY) / cellHeight;

		
		_nBlocksX = endBlockX - startBlockX;
		_nBlocksY = endBlockY - startBlockY;

		if((int)_nBlocksX % 2 == 1)
			_nBlocksX -= 1;
		//if((int)_nBlocksY % 2 == 1)
		//	_nBlocksY -= 1;


		//quantizeImages();


		long long int snapZero = StopWatch::GetTimeMs64();

		std::cout << "\nStarting computation...\n";

		// iterate over all blocks
		if(true)
		for(float y(-.5*(float)totalCellsY); y<.5*(float)totalCellsY; ++y)
		{
			for(float x(-.5*(float)totalCellsX); x<.5*(float)totalCellsX; ++x)
			{
				if(x + .5*totalCellsX < startBlockX || x + .5*totalCellsX > endBlockX || y + .5*totalCellsY < startBlockY || y + .5*totalCellsY > endBlockY)
				{
					continue;
				}
				computeBlockDoubleScan(xBlockoffset, yBlockoffset, x + .45*totalCellsX, y, x + .5*totalCellsX, y + .5*totalCellsY, cellWidth, cellHeight, blockWidth, blockHeight);
				
				if(y == -.25*(float)totalCellsY && x == 0)
					std::cout << "\n25% done...";
				if(y == 0  && x == 0)
					std::cout << "\n50% done...";
				if(y == .25*(float)totalCellsY && x == 0)
					std::cout << "\n75% done...";					
			}
		}

		std::cout << "\n100% done...\n";

		//std::cout <<  << average/(blocksX*blocksY);

		long long int snapComp = StopWatch::GetTimeMs64();

		std::cout << "Computation took " << snapComp - snapZero << " milliseconds.\n";

		generateGeometrie();

		long long int snapGeo = StopWatch::GetTimeMs64();

		std::cout << "Geometry generation took " << snapGeo - snapComp << " milliseconds.\n";
	}

	// Returns the SAD similarity between 2 blocks
	double CameraSetup::matchBlocksSAD(int xA, int yA, int xB, int yB, int width, int height)
	{
		double out(0);

		for(int x(0); x<width; ++x)
		{
			for(int y(0); y<height; ++y)	// iterate through blocks
			{
				int tempXA(xA+x);
				int tempYA(yA+y);
				int tempXB(xB+x);
				int tempYB(yB+y);

				if(tempXA < 0 || tempXB < 0 || tempYA < 0 || tempYB < 0 || tempXA >= _imageA->_width || tempYA >= _imageA->_height || tempXB >= _imageB->_width || tempYB >= _imageB->_height)
				{
					continue;									// skip pixel if it lies outside of image bounds (assume perfect match for pixel)
				}
				else
				{
					unsigned char greyA, greyB;
					greyA = _imageA->_data[tempXA][tempYA];
					greyB = _imageB->_data[tempXB][tempYB];

					out += abs((int)greyA-(int)greyB);				// add absolute of grey value difference to output variable
				}
			}
		}

		if(out != 0)
			out *= (1.0/((double)width*(double)height));				// normalize error

		return out;
	}

	void CameraSetup::adjustForAnomalies(double** errors, int xBlockoffset, int yBlockoffset, double& xOut, double& yOut)
	{
		double normalizedX(0);
		double normalizedY(0);

		// initialise errors array
		double** normalizedErrors = new double*[xBlockoffset*2+1];
		for(int i(0); i<xBlockoffset*2; ++i)
		{
			normalizedErrors[i] = new double[yBlockoffset*2];
		}

		double min(999999);
		double minX(0), minY(0);
		double tempError(0);
		for(int x(1); x<xBlockoffset*2-1; ++x)
		{
			for(int y(1); y<yBlockoffset*2-1; ++y)
			{
				tempError = ((double)errors[x][y] + 
							 (double)errors[x+1][y] + 
							 (double)errors[x][y+1] + 
							 (double)errors[x+1][y+1] + 
							 (double)errors[x-1][y] + 
							 (double)errors[x][y-1+1] + 
							 (double)errors[x-1][y-1] + 
							 (double)errors[x+1][y-1]+ 
							 (double)errors[x-1][y+1]) / 9.0f;

				if(tempError <= min)
				{
					min = tempError;
					minX = x - xBlockoffset;
					minY = y - yBlockoffset;
				}
			}
		}

		xOut = minX;
		yOut = minY;

		return;
	}

	// Computes a block in the image in that it compares it with all blocks within the specified range and then chooses the most similar one to calculate the z coordinates
	void CameraSetup::computeBlockWholeKernel(int xBlockoffset, int yBlockoffset, int xA, int yA, int width, int height)
	{
		// initialise errors array
		double** errors = new double*[xBlockoffset*2];
		for(int i(0); i<xBlockoffset*2; ++i)
		{
			errors[i] = new double[yBlockoffset*2];
		}

		// fill errors array by matching blocks around the image A block with corresponding blocks in image B within range of the offset
		for(int x(-xBlockoffset); x<xBlockoffset; ++x)
		{
			for(int y(-yBlockoffset); y<yBlockoffset; ++y)
			{
				errors[x+xBlockoffset][y+yBlockoffset] = matchBlocksSAD(xA*width, yA*height, x+xA*width, y+yA*height, width, height);
			}
		}

		// find min error
		double min(999999);
		double minX(0), minY(0);
		float threshhold(7);
		for(int x(0); x<xBlockoffset*2; ++x)
		{
			for(int y(0); y<yBlockoffset*2; ++y)
			{
				//std::cout << "error: " << errors[x][y] << "           x: " << xA << "y: " << yA << "  \n";

				if(errors[x][y]<min)
				{
					min = errors[x][y];
					minX = x - xBlockoffset;
					minY = y - yBlockoffset;
				}
			}
		}

		if(minX == -xBlockoffset)
		{
			minX = 0;
			minY = 0;
		}


		if(minX > 0)
		{
			minX *= -1;
			minY *= -1;
		}


		//std::cout << "\n match:" << minX << ",  " << minY;
		// calculate z coordinates for all point in the current block
		if(false)	// do for all points in the block
		{
			for(int x(xA); x<xA+width; ++x)
			{
				for(int y(yA); y<yA+height; ++y)
				{
					_rawPoints.push_back(VectorVOA(calcZCoordinate(x, y, x - xBlockoffset, y - yBlockoffset)));
				}
			}
		}
		else	// do only for upper left corner
		{
			_rawPoints.push_back(VectorVOA(calcZCoordinate(xA * width, yA * height, (xA * width) - minX, (yA * height) - minY)));

			_correlationsA.push_back(Vector3(xA * width, yA * height, 0));
			if(minX == 10)
			{
				_correlationsB.push_back(Vector3((xA * width) - 1, (yA * height) - 1, 0));
			}
			else
				_correlationsB.push_back(Vector3((xA * width) - minX, (yA * height) - minY, 0));
		}
	}

	// Computes a block in the image in that it compares it with all blocks within the specified range and then chooses the most similar one to calculate the z coordinates
	void CameraSetup::computeBlock(int xBlockoffset, int yBlockoffset, int xA, int yA, int width, int height)
	{
		// initialise errors array
		double** errors = new double*[xBlockoffset];
		for(int i(0); i<xBlockoffset; ++i)
		{
			errors[i] = new double[yBlockoffset*2];
		}

		// fill errors array by matching blocks around the image A block with corresponding blocks in image B within range of the offset
		for(int x(0); x<xBlockoffset; ++x)
		{
			for(int y(-yBlockoffset); y<yBlockoffset; ++y)
			{
				errors[x][y+yBlockoffset] = matchBlocksSAD(xA*width, yA*height, -1*x+xA*width, y+yA*height, width, height);
			}
		}

		// find min error
		double min(999999);
		double minX(0), minY(0);
		float threshhold(7);
		for(int x(0); x<xBlockoffset; ++x)
		{
			for(int y(0); y<yBlockoffset*2; ++y)
			{
				//std::cout << "error: " << errors[x][y] << "           x: " << xA << "y: " << yA << "  \n";

				if(errors[x][y]<min)
				{
					min = errors[x][y];
					minX = -x;
					minY = y - yBlockoffset;
				}
			}
		}

		//std::cout << "\n match:" << minX << ",  " << minY;
		// calculate z coordinates for all point in the current block
		if(false)	// do for all points in the block
		{
			for(int x(xA); x<xA+width; ++x)
			{
				for(int y(yA); y<yA+height; ++y)
				{
					_rawPoints.push_back(VectorVOA(calcZCoordinate(x, y, x - xBlockoffset, y - yBlockoffset)));
				}
			}
		}
		else	// do only for upper left corner
		{
			_rawPoints.push_back(VectorVOA(calcZCoordinate(xA * width, yA * height, (xA * width) - minX, (yA * height) - minY)));

			_correlationsA.push_back(Vector3(xA * width, yA * height, 0));
			if(minX == 10)
			{
				_correlationsB.push_back(Vector3((xA * width) - 1, (yA * height) - 1, 0));
			}
			else
				_correlationsB.push_back(Vector3((xA * width) - minX, (yA * height) - minY, 0));
		}
	}

	void CameraSetup::computeBlockDoubleScan(int xBlockoffset, int yBlockoffset, float xAMath, float yAMath, float xAIndex, float yAIndex, int cWidth, int cHeight, int bWidth, int bHeight)
	{
		// initialise errors array
		double** errors = new double*[xBlockoffset];
		for(int i(0); i<xBlockoffset; ++i)
		{
			errors[i] = new double[yBlockoffset*2];
		}

		// fill errors array by matching blocks around the image A block with corresponding blocks in image B within range of the offset
		for(int x(0); x<xBlockoffset; ++x)
		{
			for(int y(-yBlockoffset); y<yBlockoffset; ++y)
			{
				errors[x][y+yBlockoffset] = matchBlocksSAD(xAIndex*cWidth, yAIndex*cHeight, 1*x+xAIndex*cWidth, y+yAIndex*cHeight, bWidth, bHeight);
			}
		}

		// find min error
		double min(999);
		min = errors[yBlockoffset][yBlockoffset];
		double minX(0);
		double minY(0);
		float threshhold(7);
		for(int x(0); x<xBlockoffset; ++x)
		{
			for(int y(0); y<yBlockoffset*2; ++y)
			{
				//std::cout << "error: " << errors[x][y] << "           x: " << xA << "y: " << yA << "  \n";

				if(errors[x][y] < min)
				{
					min = errors[x][y];
					minX = x;// - xBlockoffset;
					minY = y - yBlockoffset;
				}
			}
		}

		if(min < 2)
		{
			minX = 100000;
			minY = 100000;
		}

		_rawPoints.push_back(VectorVOA(calcZCoordinate(xAMath * cWidth, yAMath * cHeight, ((xAMath * cWidth) - minX), ((yAMath * cHeight) - minY))));

		if(((int)xAIndex)%2 == 0 && ((int)yAIndex)%6 == 0)
		{
			_correlationsA.push_back(Vector3(xAIndex * cWidth, 1.0*(yAIndex * cHeight) - 201, 0));

			if(min < 2)
			{
				minX = 0;
				minY = 0;
			}
				_correlationsB.push_back(Vector3((xAIndex * cWidth) - minX, 1.0*((yAIndex * cHeight) - minY) - 200, 0));
		}
	}

	// Finds the z coordinate at which the given rays are crossing
	Vector3 CameraSetup::calcZCoordinate(double xA, double yA, double xB, double yB)
	{
		Math::Ray rayA = _cL.getProjectionRay((double)xA, (double)yA);
		Math::Ray rayB = _cR.getProjectionRay((double)xB, (double)yB);

		count++;

		Vector3 out = Math::Ray::virtualIntersection2pointO(rayA, rayB);

		return out;
	}
}
