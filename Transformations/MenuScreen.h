#pragma once

#include "screen.h";
#include "Model.h";

namespace Protoone
{
	class MenuScreen : public Screen
	{
	private:
		static const unsigned char START = 'c';
		static const unsigned char EXIT = 'x';

	public:
		MenuScreen();
		~MenuScreen();

		void display();
		void startHandle(unsigned char key, int x, int y);
		void exitHandle(unsigned char key, int x, int y);
	};
}

