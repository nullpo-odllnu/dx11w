#pragma once

// ライブラリリンク
#ifdef _DEBUG
#define DX11W_LIB_PREFIX "d"
#else
#define DX11W_LIB_PREFIX ""
#endif

#pragma comment(lib, "dx11w" DX11W_LIB_PREFIX)

// 必要ヘッダのインクルード
#include <precompile.h>
