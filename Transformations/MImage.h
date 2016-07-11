#pragma once

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "CImg.h";

using namespace std;
using namespace cimg_library;

namespace Protoone
{
	class MImage
	{
	public:
		MImage() : _handle(0), _data(nullptr) { }
		MImage(const char* fileName, int d);
		MImage(const char* fileName, bool b);
		MImage(const char* fileName);
		~MImage(void);
		GLuint _handle;
		CImg<unsigned char> _image;
		int _width;
		int _height;
		
		string sampleToString();
		unsigned int** _data;

	private:

	};

}