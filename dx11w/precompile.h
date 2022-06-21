#pragma once

// �g���@�\�X�C�b�`
#define DX11W_EXT_DIRECTXTK

// ���C�u���������N
#ifdef _DEBUG
	#define DX11W_LIB_SUFFIX "d"
#else
	#define DX11W_LIB_SUFFIX ""
#endif

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dx11" DX11W_LIB_SUFFIX)
#pragma comment(lib, "dxerr")
#pragma comment(lib, "dxgi")
// DXTRACE_ERR_MSGBOX���g�����߂ɒǉ�
#pragma comment(lib, "legacy_stdio_definitions")
#pragma comment(lib, "winmm")

#ifdef DX11W_EXT_DIRECTXTK
	// debug / release�𕪂��邽�߂�
	// debug�łł̓t�@�C����������d��t�^���Ă��邱�Ƃ�z��
	#pragma comment(lib, "DirectXTK" DX11W_LIB_SUFFIX)
#endif

// �}�N���Ē�`�̌x���𖳎�
#pragma warning(disable : 4005)

#ifdef DX11W_EXT_DIRECTXTK
	// �G���[�̓s���ŃC���N���[�h�����ύX
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
