#pragma once

// 拡張機能スイッチ
#define DX11W_EXT_DIRECTXTK

// ライブラリリンク
#ifdef _DEBUG
	#define DX11W_EXT_LIB_SUFFIX "d"
#else
	#define DX11W_EXT_LIB_SUFFIX ""
#endif

#ifdef DX11W_EXT_DIRECTXTK
	// debug / releaseを分けるために
	// debug版ではファイル名末尾にdを付与していることを想定
	#pragma comment(lib, "DirectXTK" DX11W_EXT_LIB_SUFFIX)
#endif
