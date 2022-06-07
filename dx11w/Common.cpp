#include "Common.h"

namespace dx
{
	void printd(const tstring& string)
	{
		OutputDebugString(string.c_str());
	}
}