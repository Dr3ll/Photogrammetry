#include "Parser.h"

namespace Protoone
{

	Parser::~Parser(void)
	{
	}

	void Parser::readImageSet(const char* folder)
	{
		// Set current directory to image set directory
		char* setDirectory = new char[strlen(folder)];
		strcpy(setDirectory, folder);

		setDirectory = appendCharsToCharArray("\\", setDirectory);					// modify path to point to image set folder
		setDirectory = appendCharsToCharArray(_resourceDirectory, setDirectory);	//

		//SetCurrentDirectory(setDirectory);
		DWORD error = GetLastError();

		// prepare filename string (count images to iterate over them; filename has to be image number plus leading 0s to fill up to 6 digits)
		WIN32_FIND_DATA ffd;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		char* searchPath = new char[MAX_PATH];
		unsigned int counter = 0;

		//
		TCHAR meh[BUFSIZE];
		GetCurrentDirectory(BUFSIZE, meh);
		char* meh2 = new char[strlen(meh)];
		strcpy(meh2, meh);
		//

		StringCchCopy(searchPath, MAX_PATH, setDirectory);
		StringCchCat(searchPath, MAX_PATH, TEXT("\\*"));
		hFind = FindFirstFile(searchPath, &ffd);

		if (INVALID_HANDLE_VALUE == hFind)
			_tprintf("", "meh");

		while (FindNextFile(hFind, &ffd) != 0)
		{
			counter++;
		}
		counter--;		// account for directory-entry dummy file

		_buff = convertToImageName(counter);
	}
}
