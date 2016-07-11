#include "MImage.h"

namespace Protoone
{
	MImage::MImage(const char* fname)
	{
		using namespace std;
		unsigned char* data;
		unsigned char* tmp_data;		
		unsigned short planes;	// number of planes in image (must be 1) 	
		unsigned short bpp;		// number of bits per pixel (must be 24)	
		ifstream fin(fname, ios::in | ios::binary);	
		if( !fin )
		{
			cerr << "File not found " << fname << '\n';
			return;
		}  	
		fin.seekg(18, ios::cur);
		fin.read((char *)&_width, sizeof(unsigned));
		fin.read((char *)&_height, sizeof(unsigned));
		fin.read((char *)&planes, sizeof(unsigned short));
		if( planes != 1 )
		{
			cout << "Planes from " << fname << " is not 1: " << planes << "\n";
			return;
		}	
		fin.read((char *)&bpp, sizeof(unsigned short));	
		//if( bpp != 24 )	{
		//	cout << "Bpp from " << fname << " is not 24: " << bpp << "\n";
		//	return;
		//}
		fin.seekg(24, ios::cur);
		unsigned size(_width * _height * 3);				// size of the image in bytes (3 is to RGB component).	
		data = new unsigned char[size];
		tmp_data = new unsigned char[size];
		fin.read((char *)tmp_data, size);	
		unsigned char tmpR, tmpG, tmpB;					// temporary color storage for bgr-rgb conversion.	

		// First step/4: extract image from input tmp_data (wich is distorted because function expects 24bit depth)
		// one dimensional data array now contains displaced image
		for( unsigned int i(0); i < (size/3); ++i)
		{	
			data[(i+1)*3-2] = tmp_data[i];		
			data[(i+1)*3-1] = tmp_data[i];
			data[(i+1)*3] = tmp_data[i];
		}

		// Second step/4: displaced image is read into 2 dimensional data_displaced for easier computation
		unsigned int** data_displaced = new unsigned int*[_width];
		_data = new unsigned int*[_width];
		for(int i(0); i<_width; ++i)
		{
			_data[i] = new unsigned int[_height];
			data_displaced[i] = new unsigned int[_height];
		}

		for( unsigned int i(0); i < size; i += 3)
		{
			data_displaced[(i/3)%_width][(int)((i/3)/_width)] = data[i];
		}

		// Third step/4: displaced data is read into the _data array fixing the diplacement
		unsigned char H;
		unsigned int offset(_width*.5f+41);
		for(unsigned int y(0); y < _height; ++y)
		{
			for( unsigned int x(0); x < _width - offset; ++x)
			{
				_data[x][y] = data_displaced[x+offset][y];
			}
			for( unsigned int x(0); x < offset; ++x)
			{
				_data[x+_width - offset][y] = data_displaced[x][y];
			}
		}

		// Fourth step/4: fixed image is read back into image data to get a texture for visualisation
		for( unsigned int i(0); i < size; i += 3)
		{
			data[i] = _data[(i/3)%_width][(int)((i/3)/_width)];
			data[i+1] = _data[(i/3)%_width][(int)((i/3)/_width)];
			data[i+2] = _data[(i/3)%_width][(int)((i/3)/_width)];
		}

		// Diese Variable speichert den Texturnamen.
		_handle = 0;

		glGenTextures(1, &_handle);
		glBindTexture(GL_TEXTURE_2D, _handle);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, _width, _height, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);
	
		// Die Daten aus dem Hauptspeicher können weg, da sie nun im Video RAM liegen.
		delete[] tmp_data;
		delete[] data_displaced;
	}

	MImage::MImage(const char* fname, bool b)
	{

	}

	MImage::~MImage(void)
	{
		delete[] _data;
	}
}