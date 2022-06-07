#pragma once

#include <string>
#include <tchar.h>

#define SAFE_DELETE(x) { \
	if (x) \
	{ \
		delete (x); \
		(x) = nullptr; \
	} \
}

typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>> tstring;

namespace dx
{
	void printd(const tstring& string);
}
