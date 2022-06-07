#pragma once

// ライブラリリンク
#ifdef _DEBUG
	#define DX11W_LIB_PREFIX "d"
#else
	#define DX11W_LIB_PREFIX ""
#endif

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dx11" DX11W_LIB_PREFIX)
#pragma comment(lib, "dxerr")
// DXTRACE_ERR_MSGBOXを使うために追加
#pragma comment(lib, "legacy_stdio_definitions")

// マクロ再定義の警告を無視
#pragma warning(disable : 4005)

#include <sdkddkver.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <D3DX11.h>
#include <DxErr.h>

#include <memory>
#include <tchar.h>
#include <string>
#include <locale>

#include "Object.h"
#include "Common.h"
#include "DXMath.h"
