#pragma once

#include "Camera.h";
#include "Drawable.h";
#include <vector>
#include "Subject.h";
#include "Model.h";
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "Subject.h";
#include "NotificationArgs.h";
#include "InputSubscription.h";

namespace Protoone
{
	class Screen
	{
	protected:
		struct KeyboardState
		{
		public:
			bool keyFlags[127];
			int x;
			int y;
		};

		Screen();

		Camera* cam;
		std::vector<Drawable*> _dElements2D;
		std::vector<Drawable*> _dElements3D;
		std::vector<MouseHandle> _mouseSubs;
		std::vector<MouseMotionHandle> _mouseMotionSubs;
		std::vector<MouseMotionHandle> _passiveMouseSubs;
		KeyTable _keySubs;
		Subject* _exitNotifier;
		KeyboardState _keyboardState;

		void Add3D(Drawable* e);
		void Add2D(Drawable* e);

	public:
		virtual ~Screen();

		void SubscribeExit(Observer* obs);
		void UnsubscribeExit(Observer* obs);

		virtual void display();
		virtual void keyboard(unsigned char key, int x, int y);
		virtual void keyboardUp(unsigned char key, int x, int y);
		virtual void applyInput();
		virtual void mouseMotion(int x, int y);
		virtual void mouse(int button, int state, int x, int y);
		virtual void passiveMouseMotion(int x, int y);
		virtual void idle() { glutPostRedisplay(); }
		virtual void Exit(NotificationArgs* args = NotificationArgs::Empty());
		void registerInputMMotion(MouseMotionHandle handle);
		void registerPassiveInputMMotion(MouseMotionHandle handle);
		void registerInputMouse(MouseHandle handle);
		void registerInputKey(KeyHandle handle, unsigned char key);
	};
}