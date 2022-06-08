#include "Common.h"

namespace dx
{
	void printd(const tstring& string)
	{
		OutputDebugString(string.c_str());
	}

	tstring format(const TCHAR* format, ...)
	{
		va_list argList;

		va_start(argList, format);

		auto length = _vsctprintf(format, argList) + 1;
		std::unique_ptr<TCHAR> buffer(new TCHAR[length]);

		_vstprintf_s(buffer.get(), length, format, argList);

		va_end(argList);

		return tstring(buffer.get());
	}
}