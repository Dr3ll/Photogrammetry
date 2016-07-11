#pragma once

#include "Vector3.h";
#include "Model.h";
#include "screen.h";
#include "Camera.h";

#include <iostream>

namespace Protoone
{
	class Handler : public Drawable
	{
	private:
		Camera _cam;
		Math::Vector3 _position;
		MouseHandle _mouseHandle;
		MouseMotionHandle _motionHandle;
		float _movespeed;
		float _rotspeed;
		float _yAngle;

		int _x, _y, _width, _height;


		float _distance;
		float _oldX, _oldY;
		int _motionState;
		float _theta;
		float _phi;

		float _PI; 
		static const unsigned char UP = 'q';
		static const unsigned char DOWN = 'e';
		static const unsigned char LEFT = 'a';
		static const unsigned char RIGHT = 'd';
		static const unsigned char FORWARD = 'w';
		static const unsigned char BACKWARD = 's';
		static const unsigned char ROTATERIGHT = 'x';
		static const unsigned char ROTATELEFT = 'y';

		static const unsigned int ROTATE = 1;
		static const unsigned int MOVE = 2;

		void setPosition(const Math::Vector3* position);	// Set the position
		void upHandle(unsigned char key, int x, int y);
		void downHandle(unsigned char key, int x, int y);
		void leftHandle(unsigned char key, int x, int y);
		void rightHandle(unsigned char key, int x, int y);
		void forHandle(unsigned char key, int x, int y);
		void backHandle(unsigned char key, int x, int y);
		void rotRightHandle(unsigned char key, int x, int y);
		void rotLeftHandle(unsigned char key, int x, int y);
		void mouseMotionHandle(int x, int y);
		void mouseHandle(int button, int state, int x, int y);

	public:
		Handler(Screen* screen, float x, float y, float z, int boxX, int boxY, int boxWidth, int boxHeight, float dist);
		~Handler(void);

		Camera& Cam()
		{
			return _cam;
		}
		void keyboardHandling(unsigned char key, int x, int y);
		void mouseHandling(int button, int state, int x, int y);
		void mouseMotionHandling(int x, int y);
		void passiveMouseMotionHandling(int x, int y);
		void draw();
	};
}
