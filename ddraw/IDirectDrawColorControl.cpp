/**
* Copyright (C) 2019 Elisha Riedlinger
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
*/

#include "ddraw.h"

HRESULT m_IDirectDrawColorControl::QueryInterface(REFIID riid, LPVOID FAR * ppvObj)
{
	Logging::LogDebug() << __FUNCTION__;

	if (!ProxyInterface)
	{
		if ((riid == IID_IDirectDrawColorControl || riid == IID_IUnknown) && ppvObj)
		{
			AddRef();

			*ppvObj = this;

			return S_OK;
		}
	}

	return ProxyQueryInterface(ProxyInterface, riid, ppvObj, WrapperID, this);
}

ULONG m_IDirectDrawColorControl::AddRef()
{
	Logging::LogDebug() << __FUNCTION__;

	if (!ProxyInterface)
	{
		return InterlockedIncrement(&RefCount);
	}

	return ProxyInterface->AddRef();
}

ULONG m_IDirectDrawColorControl::Release()
{
	Logging::LogDebug() << __FUNCTION__;

	ULONG ref;

	if (!ProxyInterface)
	{
		ref = InterlockedDecrement(&RefCount);
	}
	else
	{
		ref = ProxyInterface->Release();
	}

	if (ref == 0)
	{
		delete this;
	}

	return ref;
}

HRESULT m_IDirectDrawColorControl::GetColorControls(LPDDCOLORCONTROL lpColorControl)
{
	Logging::LogDebug() << __FUNCTION__;

	if (!lpColorControl)
	{
		return DDERR_INVALIDPARAMS;
	}

	if (!ProxyInterface)
	{
		ConvertColorControl(*lpColorControl, ColorControl);

		return DD_OK;
	}

	return ProxyInterface->GetColorControls(lpColorControl);
}

HRESULT m_IDirectDrawColorControl::SetColorControls(LPDDCOLORCONTROL lpColorControl)
{
	Logging::LogDebug() << __FUNCTION__;

	if (!lpColorControl)
	{
		return DDERR_INVALIDPARAMS;
	}

	if (!ProxyInterface)
	{
		ConvertColorControl(ColorControl, *lpColorControl);

		return DD_OK;
	}

	return ProxyInterface->SetColorControls(lpColorControl);
}
