#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include "ActionScreen.h"
#include "screen.h"
#include "NotificationArgs.h"
#include <vector>


using namespace Protoone;

#define SCALE .1f

int width = 1367;
int height = 800;

int cake = 0;
int cream = 0;

double angle = 0;

Screen* _currentScreen;
ActionScreen* _action;

// Screen events
Observer* _exitAction;
Observer* _exitMenu;

GLuint _positionBufferHandle;
vector<Vector> _positions;



	void display(void)	
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		_currentScreen->display();

		glutSwapBuffers();
	}

	void mouse(int button, int state, int x, int y)
	{
		_currentScreen->mouse(button, state, x, y);
	}

	void mouseMotion(int x, int y)
	{
		_currentScreen->mouseMotion(x, y);
	}

	void passiveMouseMotion(int x, int y)
	{
		_currentScreen->passiveMouseMotion(x, y);
	}

	void keyboard(unsigned char key, int x, int y)
	{
		_currentScreen->keyboard(key, x, y);
	}

	void keyboardUp(unsigned char key, int x, int y)
	{
		_currentScreen->keyboardUp(key, x, y);
	}

	void idle(void)
	{
		_currentScreen->idle();
	}


	int main(int argc, char **argv)
	{
		glClearColor( 1.0, 1.0, 1.0, 1.0 );

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
		glutInitWindowSize(width, height);
		glutCreateWindow("Photogrammetrie");

		glutMouseFunc(mouse);
		glutMotionFunc(mouseMotion);
		glutKeyboardFunc(keyboard);
		if(GLUT_XLIB_IMPLEMENTATION >= 13)
			glutKeyboardUpFunc(keyboardUp);
		glutPassiveMotionFunc(passiveMouseMotion);
		glutIdleFunc(idle);
		glutDisplayFunc(display);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);

		glViewport(0,0,width,height);					
		glMatrixMode(GL_PROJECTION);					
		glLoadIdentity();								

		if(glewInit() != GLEW_OK)
			cout << "GLEW init failed!" << endl;

		gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,1.0f,10000.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		_action = new ActionScreen();
		_currentScreen = _action;


		_action->SubscribeExit(_exitAction);


		glutMainLoop();

		return 0;
	}

