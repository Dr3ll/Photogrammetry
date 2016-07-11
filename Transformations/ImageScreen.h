#pragma once
#include "Vector3.h"
#include "Drawable.h"
#include <GL\glew.h>
#include <GL\freeglut.h>

namespace Protoone
{
	class ImageScreen : public Drawable
	{
	private:
		float _width, _height;
		Math::Vector3 _position;
		float _scale;
		GLuint _image;
		float _r, _g, _b;

		void drawQuad(float x, float y, float z);

	public:
		ImageScreen(float x, float y, float z, float scale, GLuint image);
		ImageScreen(float x, float y, float z, float scale, float r, float g, float b);
		~ImageScreen(void);

		void draw();
	};
}
