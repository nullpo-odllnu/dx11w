#pragma once

// 拡張機能スイッチ
#define DX11W_EXT_DIRECTXTK

// ライブラリリンク
#ifdef _DEBUG
	#define DX11W_LIB_SUFFIX "d"
#else
	#define DX11W_LIB_SUFFIX ""
#endif

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dx11" DX11W_LIB_SUFFIX)
#pragma comment(lib, "dxerr")
#pragma comment(lib, "dxgi")
// DXTRACE_ERR_MSGBOXを使うために追加
#pragma comment(lib, "legacy_stdio_definitions")
#pragma comment(lib, "winmm")

#ifdef DX11W_EXT_DIRECTXTK
	// debug / releaseを分けるために
	// debug版ではファイル名末尾にdを付与していることを想定
	#pragma comment(lib, "DirectXTK" DX11W_LIB_SUFFIX)
#endif

// マクロ再定義の警告を無視
#pragma warning(disable : 4005)

#ifdef DX11W_EXT_DIRECTXTK
	// エラーの都合でインクルード順序変更
	#include <GeometricPrimitive.h>
#endif

#include <sdkddkver.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <D3DX11.h>
#include <DxErr.h>

#include <memory>
#include <tchar.h>
#include <string>
#include <locale>
#include <mmsystem.h>
#include <vector>
#include <DirectXCollision.h>
#include <map>

#include "Object.h"
#include "Common.h"
#include "DXMath.h"
