#pragma once

// �g���@�\�X�C�b�`
#define DX11W_EXT_DIRECTXTK

// ���C�u���������N
#ifdef _DEBUG
	#define DX11W_EXT_LIB_SUFFIX "d"
#else
	#define DX11W_EXT_LIB_SUFFIX ""
#endif

#ifdef DX11W_EXT_DIRECTXTK
	// debug / release�𕪂��邽�߂�
	// debug�łł̓t�@�C����������d��t�^���Ă��邱�Ƃ�z��
	#pragma comment(lib, "DirectXTK" DX11W_EXT_LIB_SUFFIX)
#endif
