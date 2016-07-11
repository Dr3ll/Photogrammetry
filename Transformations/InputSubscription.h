#pragma once
#include <functional>

namespace Protoone
{
	typedef std::function<void(int x, int y)> MouseMotionHandle;
	typedef std::function<void(int button, int state, int x, int y)> MouseHandle;
	typedef std::function<void(unsigned char key, int x, int y)> KeyHandle;


	/** Stores pointers to functions that are to be called on keystrokes.
	  *  The multiple designation of keys is acounting for the german keyboard layout. */

	class KeyTable
	{
	private:
		KeyHandle _special[13];
		KeyHandle _numbers[19];
		KeyHandle _alphabet[26];

		// The marks are used to check wether a function is registered on a key
		bool _specialMarks[13];
		bool _numbersMarks[19];
		bool _alphabetMarks[26];

		/// Returns the designated position in the table for special keys (ASCII 0-32)
		int hashSpecial(int ascii)
		{
			return ascii % 13;
		}

		/// Returns the designated position in the table for numbers and some symbols (ASCII 33-63 and ASCII 91-96)
		int hashNumbers(int ascii)
		{
			switch(ascii)
			{
				case -89: return 3;		// §
				case -33: return 11;	// ß
				case -76: return 12;	// ´
				case 33: return 1;		// !
				case 34: return 2;		// "
				case 35: return 14;		// #
				case 36: return 4;		// $
				case 37: return 5;		// %
				case 38: return 6;		// &
				case 39: return 14;		// '
				case 40: return 8;		// (
				case 41: return 9;		// )
				case 42: return 13;		// *
				case 43: return 13;		// +
				case 44: return 17;		// ,
				case 45: return 15;		// -
				case 46: return 16;		// .
				case 47: return 7;		// slash
				case 48: return 10;		// 0
				case 49: return 1;		// 1
				case 50: return 2;		// 2
				case 51: return 3;		// 3
				case 52: return 4;		// 4
				case 53: return 5;		// 5
				case 54: return 6;		// 6
				case 55: return 7;		// 7
				case 56: return 8;		// 8
				case 57: return 9;		// 9
				case 58: return 16;		// :
				case 59: return 17;		// ;
				case 60: return 18;		// <
				case 61: return 10;		// =
				case 62: return 18;		// >
				case 63: return 11;		// ?
				case 91: return 8;		// [
				case 92: return 11;		// backslash
				case 93: return 9;		// ]
				case 94: return 0;		// ^
				case 95: return 15;		// _
				case 96: return 12;		// `
			}

			return 0;
		}

		/// Returns the designated position in the table for letter keys (ASCII 64-90 and 97-122)
		int hashAlphabet(int ascii)
		{
			if(ascii == 64) 
				return 16;

			if(ascii <= 90)
			{
				return ascii - 65;
			}
			
			return ascii - 97;
		}

	public:
		KeyTable() 
		{
			for(int i=0; i<13; ++i)
				_specialMarks[i] = false;
			for(int i=0; i<19; ++i)
				_numbersMarks[i] = false;
			for(int i=0; i<26; ++i)
				_alphabetMarks[i] = false;
		}
		~KeyTable() 
		{
			delete[] _special;
			delete[] _numbers;
			delete[] _alphabet;

			delete[] _specialMarks;
			delete[] _numbersMarks;
			delete[] _alphabetMarks;
		}

		/// Stores a function pointer its respective table
		void storeKeyHandle(KeyHandle handle, unsigned char key)
		{
			int ascii = (int)key;

			// certain special symbols associated with number keys or keys in close proximity (§, ß)
			if(ascii < 0)
			{
				int hash = hashNumbers(ascii);
				_numbers[hash] = handle;
				_numbersMarks[hash] = true;
				return;
			}

			// special keys like TAB etc. (ASCII 0-32)
			if(ascii <= 32)
			{
				int hash = hashSpecial(ascii);
				_special[hash] = handle;
				_specialMarks[hash] = true;
				return;
			}

			// numbers and signs (ASCII 33-63, 91-96)
			if(ascii <= 63 || (ascii >= 91 && ascii <= 96))
			{
				int hash = hashNumbers(ascii);
				_numbers[hash] = handle;
				_numbersMarks[hash] = true;
				return;
			}

			// letters (ASCII 64-90, 97-122)
			if(ascii <= 90 || (ascii >= 97 && ascii <= 122))
			{
				int hash = hashAlphabet(ascii);
				_alphabet[hash] = handle;
				_alphabetMarks[hash] = true;
				return;
			}
		}

		void storeKeyHandle(KeyHandle handle, int key)
		{
			if(key < 0)
			{
				int hash = hashNumbers(key);
				_numbers[hash] = handle;
				_numbersMarks[hash] = true;
				return;
			}

			// special keys like TAB etc. (ASCII 0-32)
			if(key <= 32)
			{
				int hash = hashSpecial(key);
				_special[hash] = handle;
				_specialMarks[hash] = true;
				return;
			}

			// numbers and signs (ASCII 33-63, 91-96)
			if(key <= 63 || (key >= 91 && key <= 96))
			{
				int hash = hashNumbers(key);
				_numbers[hash] = handle;
				_numbersMarks[hash] = true;
				return;
			}

			// letters (ASCII 64-90, 97-122)
			if(key <= 90 || (key >= 97 && key <= 122))
			{
				int hash = hashAlphabet(key);
				_alphabet[hash] = handle;
				_alphabetMarks[hash] = true;
				return;
			}
		}

		/** Calls all functions assigned to the button associated with [key] regardless of capslock.
		  * If a distinction between caps modes is intended, key has to be checked in the called function itself. */
		void callKey(const unsigned int key, const int x, const int y)
		{
			unsigned int ascii = (unsigned int)key;

			if(ascii <= 32)
			{
				int hash = hashSpecial(ascii);
				if(_specialMarks[hash])
					_special[hash](key, x, y);
				return;
			}

			if(ascii <= 63 || (ascii >= 91 && ascii <= 96))
			{
				int hash = hashNumbers(ascii);
				if(_numbersMarks[hash])
					_numbers[hash](key, x, y);
				return;
			}

			if(ascii <= 90 || (ascii >= 97 && ascii <= 122))
			{
				int hash = hashAlphabet(ascii);
				if(_alphabetMarks[hash])
					_alphabet[hash](key, x, y);
				return;
			}
		}

	};
}
