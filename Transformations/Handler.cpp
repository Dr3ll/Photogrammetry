#include "Handler.h"

namespace Protoone
{

	Handler::Handler(Screen* screen, float x, float y, float z, int boxX, int boxY, int boxWidth, int boxHeight, float dist) :
		_cam(x, y, z),
		_movespeed(2.30f),
		_rotspeed(.02),
		_position(x, y, z),
		_yAngle(-4.8f),
		_PI(3.141592f),
		_theta(_PI / 2.0f - 0.01f),
		_phi(0),
		_distance(dist),
		_motionState(0),
		_x(boxX),
		_y(boxY),
		_width(boxWidth),
		_height(boxHeight)
	{
		//_cam.phi = _yAngle;

		_cam.setParameters(_distance, _theta, _phi);

		//screen->registerInput(std::bind(&Handler::upHandle, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), UP);
		//screen->registerInput(std::bind(&Handler::downHandle, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), DOWN);
		//screen->registerInput(std::bind(&Handler::leftHandle, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), LEFT);
		//screen->registerInput(std::bind(&Handler::rightHandle, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), RIGHT);	
		//screen->registerInput(std::bind(&Handler::forHandle, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), FORWARD);	
		//screen->registerInput(std::bind(&Handler::backHandle, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), BACKWARD);	
		//screen->registerInput(std::bind(&Handler::rotRightHandle, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), ROTATERIGHT);	
		//screen->registerInput(std::bind(&Handler::rotLeftHandle, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), ROTATELEFT);	
		screen->registerInputMouse(std::bind(&Handler::mouseHandle, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));	
		screen->registerInputMMotion(std::bind(&Handler::mouseMotionHandle, this, std::placeholders::_1, std::placeholders::_2));	

		backHandle(BACKWARD, 0, 0);
	}

	Handler::~Handler(void)
	{
	}

	void Handler::draw()
	{
		
	}

	void Handler::setPosition(const Math::Vector3* position)
	{
		_position.mimik(*position);
		_cam.setPosition(position);
	}

	void Handler::forHandle(unsigned char key, int x, int y)
	{
		Math::Vector3 move(0, 0, 1.0 * _movespeed);
		Math::Vector3 pos = move + _position;
		(*this).setPosition(&pos);

		//std::cout << _position.toString()  << "\n";
	}

	void Handler::backHandle(unsigned char key, int x, int y)
	{
		Math::Vector3 move(0, 0, -1.0 * _movespeed);
		Math::Vector3 pos = move + _position;
		(*this).setPosition(&pos);
	}

	void Handler::rightHandle(unsigned char key, int x, int y)
	{
		Math::Vector3 move(-1.0 * _movespeed, 0, 0);
		Math::Vector3 pos = move + _position;
		(*this).setPosition(&pos);

		//std::cout << _position.toString()  << "\n";
	}

	void Handler::leftHandle(unsigned char key, int x, int y)
	{
		Math::Vector3 move(1.0 * _movespeed, 0, 0);
		Math::Vector3 pos = move + _position;
		(*this).setPosition(&pos);

		//std::cout << _position.toString() << "\n";
	}

	void Handler::downHandle(unsigned char key, int x, int y)
	{
		Math::Vector3 move(0, -1.0 * _movespeed, 0);
		Math::Vector3 pos = move + _position;
		(*this).setPosition(&pos);

		//std::cout << _position.toString()  << "\n";
	}

	void Handler::upHandle(unsigned char key, int x, int y)
	{
		Math::Vector3 move(0, 1.0 * _movespeed, 0);
		Math::Vector3 pos = move + _position;
		(*this).setPosition(&pos);

		//std::cout << _position.toString() << "\n";
	}

	void Handler::rotRightHandle(unsigned char key, int x, int y)
	{
		//_cam.setTheta(-_rotspeed);

		//std::cout << _position.toString() << "\n";
	}

	void Handler::rotLeftHandle(unsigned char key, int x, int y)
	{
		//_cam.setTheta(_rotspeed);

		//std::cout << _yAngle << "\n";
	}

	void Handler::mouseMotionHandle(int x, int y)
	{
		if(x < _x || x > _x + _width || y < _y || y > _y + _height)
		{
			_motionState = 0;
			return;
		}

		float deltaX = x - _oldX;
		float deltaY = y - _oldY;
	
		if (_motionState == ROTATE) {
			_theta -= 0.01f * deltaY;

			if (_theta < 0.01f) _theta = 0.01f;
			else if (_theta > _PI*1.0f - 0.01f) _theta = _PI*1.0f - 0.01f;

			_phi += 0.01f * deltaX;	
			if (_phi < 0) _phi += 2*_PI;
			else if (_phi > 2*_PI) _phi -= 2*_PI;
		}
		else if (_motionState == MOVE) {
			_distance += 0.15f * deltaY;
		}

		_oldX = (float)x;
		_oldY = (float)y;

		glutPostRedisplay();

		_cam.setParameters(_distance, _theta, _phi);
	}

	void Handler::mouseHandle(int button, int state, int x, int y)
	{
		if(x < _x || x > _x + _width || y < _y || y > _y + _height)
			return;

		_oldX = (float)x;
		_oldY = (float)y;

		if(state == GLUT_UP)
		{
			_motionState = 0;
			return;
		}

		if (button == GLUT_LEFT_BUTTON) {
			if (state == GLUT_DOWN) {
				_motionState = ROTATE;
			}
		}
		else if (button == GLUT_RIGHT_BUTTON) {
			if (state == GLUT_DOWN) {
				_motionState = MOVE;
			}
		}
	}
}