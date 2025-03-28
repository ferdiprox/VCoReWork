#include "xglobal.h"

bool XBuffer::subcompare(const std::string& string, unsigned int at, bool considerCase)
{
	for (unsigned int i = 0; i < string.size(); i++)
	{
		if (considerCase)
		{
			if (buf[i + at] != string[i])
			{
				return false;
			}

			continue;
		}

		if (toupper(buf[i + at]) != toupper(string[i]))
		{
			return false;
		}
	}

	return true;
}

bool XBuffer::search(const std::string& what, unsigned char mode, bool considerCase)
{
	unsigned int curOffset = offset;

	if(mode == XB_GLOBAL)
	{
		mode = XB_FORWARD;
	}

	bool comparedSuccessfull;

	char offsetStep = mode == XB_BACKWARD ? -1 : 1;

	while(buf[curOffset])
	{
		if(subcompare(what, curOffset, considerCase))
		{
		    offset = curOffset;
			return true;
		}

		curOffset += offsetStep;
	}

	return false;
}
