#include "ImageScreen.h"


namespace Protoone
{
	ImageScreen::ImageScreen(float x, float y, float z, float scale, GLuint image)
		: _position(x, y, z), _scale(scale), _image(image), _r(1), _g(1), _b(1)
	{
	}

	ImageScreen::ImageScreen(float x, float y, float z, float scale, float r, float g, float b)
		: _position(x, y, z), _scale(scale), _image(0), _r(r), _g(g), _b(b)
	{
	}

	ImageScreen::~ImageScreen(void)
	{
	}

	void ImageScreen::drawQuad(float x, float y, float z)
	{
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,y,z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+_scale-.17,y,z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+_scale-.17,y+_scale,z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y+_scale,z);
		glEnd();
	}

	void ImageScreen::draw()
	{
		//glPushMatrix();

		//glTranslatef(_position.X(),_position.Y(), _position.Z());

		//glClear(GL_COLOR_BUFFER_BIT);

		
		glBindTexture(GL_TEXTURE_2D, _image);

		
		//glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, 2, 0, 2, 0, 100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glColor3f(_r, _g, _b);

		drawQuad(_position.X(), _position.Y(), _position.Z());

		//glEnable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, 0);
		glEnable(GL_LIGHTING);

		/*glPopMatrix();*/
	}
}