#pragma once

// ���C�u���������N
#ifdef _DEBUG
#define DX11W_LIB_PREFIX "d"
#else
#define DX11W_LIB_PREFIX ""
#endif

#pragma comment(lib, "dx11w" DX11W_LIB_PREFIX)

// �K�v�w�b�_�̃C���N���[�h
#include <precompile.h>
