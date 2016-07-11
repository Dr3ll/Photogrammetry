#include "MenuScreen.h"
#include <math.h>
#include "Vector.h";
#include "Drawable.h";

namespace Protoone
{

	MenuScreen::MenuScreen()
	{
		float distance = 25.0f;
		float theta = 1.4f;
		float phi = 0.0f;

		float x = -6.0f;
		float y = 0.0;
		float z = 0.0;
		
		registerInputKey(std::bind(&MenuScreen::exitHandle, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), EXIT);
		registerInputKey(std::bind(&MenuScreen::startHandle, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), START);

		cam = new Camera(x, y, z);

	//		Model* pot = new Model([](){glutSolidTeapot(1);}, new Math::Vector3(), 1, 1 ,1);
		Model* circle = 
			new Model([](){ 
			double PI = 3.141592f;
			glBegin(GL_LINE_STRIP);

			glColor3f(0,0,0);

			double angleInc = (2*PI) / (double)50;
			double curAngle = 0.0;

			// Draw segments
			for(int i = 0; i <= 50; i++)
			{
				glVertex3f(
					cosf(curAngle) * (double)10, 
					0, 
					sinf(curAngle) * (double)10);

				curAngle += angleInc;
			}

			glEnd();
				;}, new Math::Vector3(), 1, 1 ,1);

		//Add3D(pot);
		Add3D(circle);
	}

	void MenuScreen::display()
	{
		applyInput();

		glClearColor( 0.0, 0.0, 0.0, 1.0 );

		glLoadIdentity();

		cam->Look();

		for (int i=0; i<_dElements3D.size(); ++i)
		{
			_dElements3D[i]->draw();
		}
	}

	MenuScreen::~MenuScreen()
	{
	}

	void MenuScreen::exitHandle(unsigned char key, int x, int y)
	{
		
	}

	void MenuScreen::startHandle(unsigned char key, int x, int y)
	{
		Exit();
	}
}