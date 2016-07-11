#include "ActionScreen.h"
#include "CImg.h";

using namespace cimg_library;

#define SCALE 1//.05f

namespace Protoone
{
	ActionScreen::ActionScreen(void)
		: _setup(SCALE), _drawVisual(false)
	{
		float distance = 25.0f;
		float theta = 1.4f;
		float phi = 0.0f;

		float x = 0.0;
		float y = 0.0;
		float z = -6.0f;

		Handler* handlerLeft = new Handler(this, -120, 80, 1850, 0, 0, 683, 400, 250);
		Handler* handlerRight = new Handler(this, 380, 0, 0, 683, 0, 683, 400, 750);

		_camLeft = &(*handlerLeft).Cam();
		_camRight = &(*handlerRight).Cam();


		ImageScreen* screenMask = new ImageScreen(0, -4.2, -.5f, 5, 0, 0, 0);

		Add2D(screenMask);

		float scale = 100.0f;

		cout << "Press Enter to get to menu.\n";

		this->registerInputKey(std::bind(&ActionScreen::handleAction, this), 13);	

	}

	void ActionScreen::handleAction()
	{
		string input("");
		
		while(1)
		{
		int x(-1), y(-1);

		std::cout << "\nSource images and camera calibrations need to be in the same folder as the executable.\n";
		std::cout << "\nPlease enter command\n";
		std::cout << "\nc : creates visualisation\n";
		std::cout << "\nr : allows to set source image resolution\n";
		std::cout << "\n";

		std::cin >> input;

		if(input == "c")
		{
			cout << "\n";
			createVisualisation();
			break;
		}
		if(input =="r")
		{
			cout << "\nCurrent resolution is   X: "<< _setup._cellsX << ",  Y: " << _setup._cellsY << "\n";

			while(x < 0 || x > 656)
			{
				cout << "\nX: \n";
				cin >> x;
				if(x < 0 || x > 656)
					cout << "\nOnly values between 0 and 656";
			}
			while(y < 0 || y > 491)
			{
				cout << "\nY: \n";
				cin >> y;
				if(x < 0 || x > 491)
					cout << "\nOnly values between 0 and 491";
			}

			_setup._cellsX = x;
			_setup._cellsY = y;
		}
		if(input == "back")
			break;

		}

	}

	void ActionScreen::display()
	{
		applyInput();

		glClearColor( 0.0, 0.0, 0.0, 1.0 );
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		drawLeftScreen();
		drawRightScreen();


		glViewport(0,0,1367,800);					
		glMatrixMode(GL_PROJECTION);					
		glLoadIdentity();								

		if(glewInit() != GLEW_OK)
			cout << "GLEW init failed!" << endl;

		gluPerspective(45.0f,(GLfloat)1367/(GLfloat)800,1.0f,1000.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		glDisable(GL_STENCIL_TEST);

		for (int i=0; i<_dElements2D.size(); ++i)
		{
			_dElements2D[i]->draw();
		}
	}

	void ActionScreen::drawLeftScreen()
	{
		glViewport(0,400,683,400);

		glMatrixMode(GL_PROJECTION);					
		glLoadIdentity();								

		gluPerspective(45.0f,(GLfloat)683/(GLfloat)400,1.0f,5000.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glLoadIdentity();
		_camLeft->Look();

		if(_drawVisual)
			_setup.drawGeometrie();
	}

	void ActionScreen::drawRightScreen()
	{		
		glViewport(683,400,683,400);

		glMatrixMode(GL_PROJECTION);					
		glLoadIdentity();								

		gluPerspective(45.0f,(GLfloat)683/(GLfloat)400,1.0f,5000.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glLoadIdentity();
		_camRight->Look();

		if(_drawVisual)
			_setup.drawCorrelations();
	}

	void ActionScreen::createVisualisation()
	{
		long long int snapZero = StopWatch::GetTimeMs64();

		Parser parser("Sequenz_Zylinder"); 
		_setup._imageA = parser.readImage("A.bmp");
		_setup._imageB = parser.readImage("B.bmp");

		bool legit(false);
		
		std::cout << "Parsing data...";

		parseCamCalib();

		if(_setup._imageA->_data != nullptr &&
		   _setup._imageB->_data != nullptr &&
		   _setup._imageA->_width == 656 &&
		   _setup._imageA->_height == 491 &&
		   _setup._imageB->_width == 656 &&
		   _setup._imageB->_height == 491)
		   legit = true;
		

		long long int snapParse = StopWatch::GetTimeMs64();
		
		if(legit)
		{
			std::cout << "Parsing took " << snapParse - snapZero << " milliseconds.\n";

			_setup.createVisualisation(0, 0, 656, 490, 40, 5, 50, 100, 15, 15);
			_drawVisual = true;
		}
		else
		{
			std::cout << "Error during parsing\n";
		}

		cout << "\nPress Enter in main window to get to menu.\n";

						ImageScreen* screenA = new ImageScreen(.3, 0, 0, .8f, 1);
		ImageScreen* screenB = new ImageScreen(1.04, 0, 0, .8f, 2);
		Add2D(screenA);
		Add2D(screenB);

	}

	float ActionScreen::parseValue(string line)
	{
		int pos(0);
		while(pos < line.length()-1)
		{
			if(line[pos] == '=')
				break;
			pos++;
		}
		pos++;

		char* value = new char[50];
		int vPos(0);
		while(pos < line.length()-1)
		{
			if(line[pos != ' '])
			{
				value[vPos] = line[pos];
				pos++;
				vPos++;
			}
			else
				break;
		}
		float vOut; 

		return vOut = (float)strtod(value, NULL);
	}

	void ActionScreen::parseCamCalib()
	{
		float pxA, pyA, pzA, omegaA, phiA, kappaA, xMainA, yMainA, cA, yScaleA, passA, dis1A, dis2A;
		float pxB, pyB, pzB, omegaB, phiB, kappaB, xMainB, yMainB, cB, yScaleB, passB, dis1B, dis2B;

		std::string line;

		std::ifstream calibA ("CalibA.kam");

		if(!calibA.is_open())
		{
			cout << "Could not find calibration file A.\n";
			return;
		}

		if (calibA.is_open())
		{
			int count(0);
			while (calibA.good())
			{
				getline(calibA,line);
				switch(count)
				{
				case 1:
					pxA = parseValue(line);
					break;
				case 2:
					pyA = parseValue(line);
					break;
				case 3:
					pzA = parseValue(line);
					break;
				case 4:
					omegaA = parseValue(line);
					break;
				case 5:
					phiA = parseValue(line);
					break;
				case 6:
					kappaA = parseValue(line);
					break;
				case 9:
					xMainA = parseValue(line);
					break;
				case 10:
					yMainA = parseValue(line);
					break;
				case 11:
					cA = parseValue(line);
					break;
				case 12:
					yScaleA = parseValue(line);
					break;
				case 13:
					passA = parseValue(line);
					break;
				case 14:
					dis1A = parseValue(line);
					break;
				case 15:
					dis2A = parseValue(line);
					break;
				}
				count++;
			}
			calibA.close();
		}
		else
		{
			std::cout << "Unable to open file" << std::endl << std::endl;
		}

		std::ifstream calibB ("CalibB.kam");

		if(!calibB.is_open())
		{
			cout << "Could not find calibration file B.\n";
			return;
		}

		if (calibB.is_open())
		{
			int count(0);
			while (calibB.good())
			{
				getline(calibB,line);
				switch(count)
				{
				case 1:
					pxB = parseValue(line);
					break;
				case 2:
					pyB = parseValue(line);
					break;
				case 3:
					pzB = parseValue(line);
					break;
				case 4:
					omegaB = parseValue(line);
					break;
				case 5:
					phiB = parseValue(line);
					break;
				case 6:
					kappaB = parseValue(line);
					break;
				case 9:
					xMainB = parseValue(line);
					break;
				case 10:
					yMainB = parseValue(line);
					break;
				case 11:
					cB = parseValue(line);
					break;
				case 12:
					yScaleB = parseValue(line);
					break;
				case 13:
					passB = parseValue(line);
					break;
				case 14:
					dis1B = parseValue(line);
					break;
				case 15:
					dis2B = parseValue(line);
					break;
				}
				count++;
			}
		
			calibA.close();
		}
		else
		{
			std::cout << "Unable to open file" << std::endl << std::endl;
		}


		StereoCam* view1 = new StereoCam(pxA, pyA, pzA, 
										 omegaA, phiA, kappaA,
										 319.5402871360f, 247.2584081171f,
										 cA, -0.9999568829, 200.0000000000, -007, 0,
										 SCALE);

		StereoCam* view2 = new StereoCam(pxB, pyB, pzB,
									omegaB, phiB, kappaB,
									319.5402871360f, 247.2584081171f,
									cB, -0.9999568829, 200.0000000000, -007, 0,
									SCALE);


		_setup.DeliverSetup(*view1, *view2);

	}

	ActionScreen::~ActionScreen(void)
	{

	}

}