/**
* Copyright (C) 2018 Elisha Riedlinger
*
* This software is  provided 'as-is', without any express  or implied  warranty. In no event will the
* authors be held liable for any damages arising from the use of this software.
* Permission  is granted  to anyone  to use  this software  for  any  purpose,  including  commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*   1. The origin of this software must not be misrepresented; you must not claim that you  wrote the
*      original  software. If you use this  software  in a product, an  acknowledgment in the product
*      documentation would be appreciated but is not required.
*   2. Altered source versions must  be plainly  marked as such, and  must not be  misrepresented  as
*      being the original software.
*   3. This notice may not be removed or altered from any source distribution.
*
* Created from source code found in Wine
* https://github.com/alexhenrie/wine/tree/master/dlls/d3d8
*/

#include "d3d8to9.h"
#include "External\d3d8to9\source\d3d8to9.hpp"
#include "External\d3d8to9\source\d3dx9.hpp"
#include "Logging\Logging.h"

typedef LPDIRECT3D9(WINAPI *PFN_Direct3DCreate9)(UINT SDKVersion);

namespace D3d8to9
{
	FARPROC Direct3DCreate9;
}

PFN_D3DXAssembleShader D3DXAssembleShader = nullptr;
PFN_D3DXDisassembleShader D3DXDisassembleShader = nullptr;
PFN_D3DXLoadSurfaceFromSurface D3DXLoadSurfaceFromSurface = nullptr;

void WINAPI d8_Direct3D8EnableMaximizedWindowedModeShim()
{
	return;
}

HRESULT WINAPI d8_ValidatePixelShader(DWORD* pixelshader, DWORD* reserved1, BOOL flag, DWORD* toto)
{
	UNREFERENCED_PARAMETER(flag);
	UNREFERENCED_PARAMETER(toto);

	if (!pixelshader)
	{
		return E_FAIL;
	}
	if (reserved1)
	{
		return E_FAIL;
	}
	switch (*pixelshader)
	{
	case 0xFFFF0100:
	case 0xFFFF0101:
	case 0xFFFF0102:
	case 0xFFFF0103:
	case 0xFFFF0104:
		return S_OK;
		break;
	default:
		return E_FAIL;
	}
}

HRESULT WINAPI d8_ValidateVertexShader(DWORD* vertexshader, DWORD* reserved1, DWORD* reserved2, BOOL flag, DWORD* toto)
{
	UNREFERENCED_PARAMETER(flag);
	UNREFERENCED_PARAMETER(toto);

	if (!vertexshader)
	{
		return E_FAIL;
	}
	if (reserved1 || reserved2)
	{
		return E_FAIL;
	}
	switch (*vertexshader)
	{
	case 0xFFFE0100:
	case 0xFFFE0101:
		return S_OK;
		break;
	default:
		return E_FAIL;
	}
}

void WINAPI d8_DebugSetMute()
{
	return;
}

Direct3D8 *WINAPI d8_Direct3DCreate8(UINT SDKVersion)
{
	Logging::Log() << "Enabling D3d8to9 function (" << SDKVersion << ")";

	// Declare Direct3DCreate9
	static PFN_Direct3DCreate9 Direct3DCreate9 = reinterpret_cast<PFN_Direct3DCreate9>(D3d8to9::Direct3DCreate9);
	if (!Direct3DCreate9)
	{
		Logging::Log() << "Failed to get 'Direct3DCreate9' ProcAddress of d3d9.dll!";
		return nullptr;
	}

	IDirect3D9 *const d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (d3d == nullptr)
	{
		return nullptr;
	}

	// Load D3DX
	if (!D3DXAssembleShader || !D3DXDisassembleShader || !D3DXLoadSurfaceFromSurface)
	{
		Loadd3dx9();
		D3DXAssembleShader = (PFN_D3DXAssembleShader)p_D3DXAssembleShader;
		D3DXDisassembleShader = (PFN_D3DXDisassembleShader)p_D3DXDisassembleShader;
		D3DXLoadSurfaceFromSurface = (PFN_D3DXLoadSurfaceFromSurface)p_D3DXLoadSurfaceFromSurface;
	}

	return new Direct3D8(d3d);
}
