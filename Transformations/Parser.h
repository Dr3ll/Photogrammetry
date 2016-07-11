#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "MImage.h";
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
#include <vector>
#include <GL\glew.h>
#include <GL\freeglut.h>

using namespace std;

#define BUFSIZE MAX_PATH

namespace Protoone
{
	class Parser
	{
	private:
		std::string filename;
		char* _rootDirectory;
		char* _resourceDirectory;

		TCHAR* _buff;

		char* appendCharsToCharArray(char* array, char* a)
		{
			size_t lengthArray = strlen(array);
			size_t lengthA = strlen(a);

			char* out = new char[lengthArray+lengthA];

			strcpy(out, array);
			for(int i=lengthArray; i<lengthArray+lengthA; ++i)
			{
				out[i] = a[i-lengthArray];
			}
			out[lengthArray+lengthA] = '\0';

			return out;
		}

		char* convertToImageName(unsigned int number)
		{
			char* out = new char[11];
			char* digits = new char[11];
			_ultoa_s(number,digits,sizeof(digits),10);

			for(int i=0; i<6; ++i)
			{
				if(i<(6-strlen(digits)))
				{
					out[i] = '0';
				}
				else
				{
					out[i] = digits[i-(6-strlen(digits))];
				}
			}
			out[6] = '.';
			out[7] = 'b';
			out[8] = 'm';
			out[9] = 'p';
			out[10] = '\0';

			return out;
		}

	public:
		Parser(char* resourceFolder)
		{
			_buff = new TCHAR[BUFSIZE];
			TCHAR buffer[BUFSIZE];
			GetCurrentDirectory(BUFSIZE, buffer);
			_rootDirectory = new char[strlen(buffer)-15];

			for(int i=0; i<(strlen(buffer)-16); ++i)
			{
				_rootDirectory[i] = buffer[i];
			}
			_rootDirectory[strlen(buffer)-16] = '\0';

			_resourceDirectory = new char[strlen(_rootDirectory)+1+strlen(resourceFolder)];
			_resourceDirectory = appendCharsToCharArray("\\", resourceFolder);					// modify path to point to resource folder
			_resourceDirectory = appendCharsToCharArray(_rootDirectory, _resourceDirectory);	//

			SetCurrentDirectory(_resourceDirectory);
			
			_buff = _rootDirectory;
		}

		~Parser(void);

		string buffer()
		{
			string out = _buff;

			return out;
		}

		MImage* readImage(const char* fileName)
		{
			MImage* out = new MImage(fileName);

			return out;
		}
		void readImageSet(const char* folder);

	};

}

