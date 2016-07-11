#pragma once

#include <iostream>
#include "screen.h";
#include "Handler.h";
#include "CameraSetup.h";
#include "Parser.h";
#include "MImage.h";
#include "ImageScreen.h"
#include "Ray.h"
#include "StopWatch.h";

namespace Protoone
{
	class ActionScreen : public Screen
	{
	private:
		CameraSetup _setup;
		Drawable* _leftScreen;
		Drawable* _rightScreen;
		GLuint _screenTextLeft;
		GLuint _screenTextRight;
		bool _drawVisual;


		Camera* _camLeft;
		Camera* _camRight;

		void drawLeftScreen();
		void drawRightScreen();
		void createVisualisation();
		void handleAction();
		void parseCamCalib();
		float parseValue(string line);

	public:
		ActionScreen();
		~ActionScreen();

		void display();


	};
}

