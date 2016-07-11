#include "screen.h"

using namespace std;


namespace Protoone
{
	Screen::Screen()
	{
		_exitNotifier = new Subject();
		_keyboardState.x = 0;
		_keyboardState.y = 0;
		
		for(int i=0; i<127; ++i)
			_keyboardState.keyFlags[i] = false;
	}

	Screen::~Screen()
	{
	}

	void Screen::display()
	{
		applyInput();

		for (int i=0; i<_dElements3D.size(); ++i)
		{
			_dElements3D[i]->draw();
		}
	}

	void Screen::Add2D(Drawable* e)
	{
		_dElements2D.push_back(e);
	}

	void Screen::Add3D(Drawable* e)
	{
		_dElements3D.push_back(e);
	}

	void Screen::Exit(NotificationArgs* args)
	{
		_exitNotifier->Notify(args);
	}

	void Screen::SubscribeExit(Observer* obs)
	{
		_exitNotifier->Attach(obs);
	}

	void Screen::UnsubscribeExit(Observer* obs)
	{
		_exitNotifier->Detach(obs);
	}

	void Screen::keyboard(unsigned char key, int x, int y)
	{
		if(key > 0 && key < 127)
		{
			_keyboardState.keyFlags[key] = true; 
			_keyboardState.x = x;
			_keyboardState.y = y;
		}
	}

	void Screen::keyboardUp(unsigned char key, int x, int y)
	{
		if(key > 0 && key < 127)
		{
			_keyboardState.keyFlags[key] = false; 
			_keyboardState.x = x;
			_keyboardState.y = y;
		}
	}

	void Screen::applyInput()
	{
		for(int i=0; i<127; ++i)
		{
			if(_keyboardState.keyFlags[i])
			{
				_keySubs.callKey(i, _keyboardState.x, _keyboardState.y);
			}
		}
	}

	void Screen::mouseMotion(int x, int y)
	{
		for(int i=0; i<_mouseMotionSubs.size(); ++i)
		{
			_mouseMotionSubs[i](x, y);
		}
	}

	void Screen::mouse(int button, int state, int x, int y)
	{
		for(int i=0; i<_mouseSubs.size(); ++i)
		{
			_mouseSubs[i](button, state, x, y);
		}
	}

	void Screen::passiveMouseMotion(int x, int y)
	{
		for(int i=0; i<_mouseMotionSubs.size(); ++i)
		{
			_mouseMotionSubs[i](x, y);
		}
	}

	void Screen::registerInputMMotion(MouseMotionHandle handle)
	{
		_mouseMotionSubs.push_back(handle);
	}

	void Screen::registerPassiveInputMMotion(MouseMotionHandle handle)
	{
		_passiveMouseSubs.push_back(handle);
	}

	void Screen::registerInputMouse(MouseHandle handle)
	{
		_mouseSubs.push_back(handle);
	}

	void Screen::registerInputKey(KeyHandle handle, unsigned char key)
	{
		_keySubs.storeKeyHandle(handle, key);
	}
}