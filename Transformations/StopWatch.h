#pragma once

#include <Windows.h>

namespace Protoone
{
	class StopWatch
	{
	public:
		static long long int GetTimeMs64()
		{
			 FILETIME ft;
			 LARGE_INTEGER li;

			 /* Get the amount of 100 nano seconds intervals elapsed since January 1, 1601 (UTC) and copy it
			  * to a LARGE_INTEGER structure. */
			 GetSystemTimeAsFileTime(&ft);
			 li.LowPart = ft.dwLowDateTime;
			 li.HighPart = ft.dwHighDateTime;

			 long long int ret = li.QuadPart;
			 ret -= 116444736000000000LL; /* Convert from file time to UNIX epoch time. */
			 ret /= 10000; /* From 100 nano seconds (10^-7) to 1 millisecond (10^-3) intervals */

			 return ret;
		}
	};
}
