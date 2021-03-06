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

void ConvertColorControl(DDCOLORCONTROL &ColorControl, DDCOLORCONTROL &ColorControl2)
{
	DWORD dwSize = min(sizeof(DDCOLORCONTROL), ColorControl.dwSize);
	ZeroMemory(&ColorControl, dwSize);
	CopyMemory(&ColorControl, &ColorControl2, min(dwSize, ColorControl2.dwSize));
	ColorControl.dwSize = dwSize;
}

void ConvertSurfaceDesc(DDSURFACEDESC &Desc, DDSURFACEDESC &Desc2)
{
	DWORD dwSize = min(sizeof(DDSURFACEDESC), Desc.dwSize);
	DWORD ddpfPixelFormat_dwSize = (dwSize > 88) ? Desc.ddpfPixelFormat.dwSize : 0;
	ZeroMemory(&Desc, dwSize);
	CopyMemory(&Desc, &Desc2, min(dwSize, Desc2.dwSize));
	Desc.dwSize = dwSize;
	if (ddpfPixelFormat_dwSize)
	{
		Desc.ddpfPixelFormat.dwSize = ddpfPixelFormat_dwSize;
	}
}

void ConvertSurfaceDesc(DDSURFACEDESC2 &Desc, DDSURFACEDESC2 &Desc2)
{
	DWORD dwSize = min(sizeof(DDSURFACEDESC2), Desc.dwSize);
	DWORD ddpfPixelFormat_dwSize = (dwSize > 96) ? Desc.ddpfPixelFormat.dwSize : 0;
	ZeroMemory(&Desc, dwSize);
	CopyMemory(&Desc, &Desc2, min(dwSize, Desc2.dwSize));
	Desc.dwSize = dwSize;
	Desc.dwSize = dwSize;
	if (ddpfPixelFormat_dwSize)
	{
		Desc.ddpfPixelFormat.dwSize = ddpfPixelFormat_dwSize;
	}
}

void ConvertSurfaceDesc(DDSURFACEDESC &Desc, DDSURFACEDESC2 &Desc2)
{
	// Prepare varables
	DWORD dwSize = min(sizeof(DDSURFACEDESC), Desc.dwSize);
	ZeroMemory(&Desc, dwSize);
	DDSURFACEDESC tmpDesc = { NULL };
	DDSURFACEDESC2 tmpDesc2 = { NULL };
	CopyMemory(&tmpDesc2, &Desc2, min(sizeof(DDSURFACEDESC2), Desc2.dwSize));
	// Convert varables
	tmpDesc.dwSize = dwSize;
	tmpDesc.dwFlags = tmpDesc2.dwFlags & ~(DDSD_ZBUFFERBITDEPTH | DDSD_TEXTURESTAGE | DDSD_FVF | DDSD_SRCVBHANDLE | DDSD_DEPTH);		// Remove unsupported flags
	tmpDesc.dwHeight = tmpDesc2.dwHeight;
	tmpDesc.dwWidth = tmpDesc2.dwWidth;
	tmpDesc.dwLinearSize = tmpDesc2.dwLinearSize;
	if (tmpDesc2.dwFlags & DDSD_BACKBUFFERCOUNT)
	{
		tmpDesc.dwBackBufferCount = tmpDesc2.dwBackBufferCount;
	}
	if (tmpDesc2.dwFlags & (DDSD_REFRESHRATE | DDSD_MIPMAPCOUNT))
	{
		tmpDesc.dwRefreshRate = tmpDesc2.dwRefreshRate;
	}
	tmpDesc.dwAlphaBitDepth = tmpDesc2.dwAlphaBitDepth;
	tmpDesc.dwReserved = tmpDesc2.dwReserved;
	tmpDesc.lpSurface = tmpDesc2.lpSurface;
	if (tmpDesc2.dwFlags & DDSD_CKSRCOVERLAY)
	{
		tmpDesc.ddckCKDestOverlay.dwColorSpaceLowValue = tmpDesc2.ddckCKDestOverlay.dwColorSpaceLowValue;
		tmpDesc.ddckCKDestOverlay.dwColorSpaceHighValue = tmpDesc2.ddckCKDestOverlay.dwColorSpaceHighValue;
	}
	tmpDesc.ddckCKDestBlt.dwColorSpaceLowValue = tmpDesc2.ddckCKDestBlt.dwColorSpaceLowValue;
	tmpDesc.ddckCKDestBlt.dwColorSpaceHighValue = tmpDesc2.ddckCKDestBlt.dwColorSpaceHighValue;
	tmpDesc.ddckCKSrcOverlay.dwColorSpaceLowValue = tmpDesc2.ddckCKSrcOverlay.dwColorSpaceLowValue;
	tmpDesc.ddckCKSrcOverlay.dwColorSpaceHighValue = tmpDesc2.ddckCKSrcOverlay.dwColorSpaceHighValue;
	tmpDesc.ddckCKSrcBlt.dwColorSpaceLowValue = tmpDesc2.ddckCKSrcBlt.dwColorSpaceLowValue;
	tmpDesc.ddckCKSrcBlt.dwColorSpaceHighValue = tmpDesc2.ddckCKSrcBlt.dwColorSpaceHighValue;
	if (tmpDesc2.dwFlags & DDSD_PIXELFORMAT)
	{
		tmpDesc.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
		ConvertPixelFormat(tmpDesc.ddpfPixelFormat, tmpDesc2.ddpfPixelFormat);
	}
	ConvertCaps(tmpDesc.ddsCaps, tmpDesc2.ddsCaps);
	// Copy to variable
	CopyMemory(&Desc, &tmpDesc, dwSize);
}

void ConvertSurfaceDesc(DDSURFACEDESC2 &Desc2, DDSURFACEDESC &Desc)
{
	// Prepare varables
	DWORD dwSize = min(sizeof(DDSURFACEDESC2), Desc2.dwSize);
	ZeroMemory(&Desc2, dwSize);
	DDSURFACEDESC2 tmpDesc2 = { NULL };
	DDSURFACEDESC tmpDesc = { NULL };
	CopyMemory(&tmpDesc, &Desc, min(sizeof(DDSURFACEDESC), Desc.dwSize));
	// Convert varables
	tmpDesc2.dwSize = dwSize;
	tmpDesc2.dwFlags = tmpDesc.dwFlags & ~(DDSD_ZBUFFERBITDEPTH | DDSD_TEXTURESTAGE | DDSD_FVF | DDSD_SRCVBHANDLE | DDSD_DEPTH);		// Remove unsupported flags
	tmpDesc2.dwHeight = tmpDesc.dwHeight;
	tmpDesc2.dwWidth = tmpDesc.dwWidth;
	tmpDesc2.dwLinearSize = tmpDesc.dwLinearSize;
	tmpDesc2.dwBackBufferCount = tmpDesc.dwBackBufferCount;
	if (tmpDesc.dwFlags & (DDSD_REFRESHRATE | DDSD_MIPMAPCOUNT))
	{
		tmpDesc2.dwRefreshRate = tmpDesc.dwRefreshRate;
	}
	tmpDesc2.dwAlphaBitDepth = tmpDesc.dwAlphaBitDepth;
	tmpDesc2.dwReserved = tmpDesc.dwReserved;
	tmpDesc2.lpSurface = tmpDesc.lpSurface;
	tmpDesc2.ddckCKDestOverlay.dwColorSpaceLowValue = tmpDesc.ddckCKDestOverlay.dwColorSpaceLowValue;
	tmpDesc2.ddckCKDestOverlay.dwColorSpaceHighValue = tmpDesc.ddckCKDestOverlay.dwColorSpaceHighValue;
	tmpDesc2.ddckCKDestBlt.dwColorSpaceLowValue = tmpDesc.ddckCKDestBlt.dwColorSpaceLowValue;
	tmpDesc2.ddckCKDestBlt.dwColorSpaceHighValue = tmpDesc.ddckCKDestBlt.dwColorSpaceHighValue;
	tmpDesc2.ddckCKSrcOverlay.dwColorSpaceLowValue = tmpDesc.ddckCKSrcOverlay.dwColorSpaceLowValue;
	tmpDesc2.ddckCKSrcOverlay.dwColorSpaceHighValue = tmpDesc.ddckCKSrcOverlay.dwColorSpaceHighValue;
	tmpDesc2.ddckCKSrcBlt.dwColorSpaceLowValue = tmpDesc.ddckCKSrcBlt.dwColorSpaceLowValue;
	tmpDesc2.ddckCKSrcBlt.dwColorSpaceHighValue = tmpDesc.ddckCKSrcBlt.dwColorSpaceHighValue;
	tmpDesc2.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
	if (tmpDesc.dwSize == sizeof(DDSURFACEDESC) && tmpDesc.dwFlags & DDSD_PIXELFORMAT && !tmpDesc.ddpfPixelFormat.dwSize)
	{
		tmpDesc.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
	}
	ConvertPixelFormat(tmpDesc2.ddpfPixelFormat, tmpDesc.ddpfPixelFormat);
	ConvertCaps(tmpDesc2.ddsCaps, tmpDesc.ddsCaps);
	// Extra parameters
	tmpDesc2.dwTextureStage = 0;			// Stage identifier that is used to bind a texture to a specific stage
	// Copy to variable
	CopyMemory(&Desc2, &tmpDesc2, dwSize);
}

void ConvertPixelFormat(DDPIXELFORMAT &Format, DDPIXELFORMAT &Format2)
{
	DWORD dwSize = min(sizeof(DDPIXELFORMAT), Format.dwSize);
	ZeroMemory(&Format, dwSize);
	CopyMemory(&Format, &Format2, min(dwSize, Format2.dwSize));
	Format.dwSize = dwSize;
}

void ConvertDeviceIdentifier(DDDEVICEIDENTIFIER2 &DeviceID, DDDEVICEIDENTIFIER2 &DeviceID2)
{
	CopyMemory(&DeviceID, &DeviceID2, sizeof(DDDEVICEIDENTIFIER2));
}

void ConvertDeviceIdentifier(DDDEVICEIDENTIFIER &DeviceID, DDDEVICEIDENTIFIER2 &DeviceID2)
{
	CopyMemory(&DeviceID, &DeviceID2, sizeof(DDDEVICEIDENTIFIER));
}

void ConvertDeviceIdentifier(DDDEVICEIDENTIFIER2 &DeviceID2, DDDEVICEIDENTIFIER &DeviceID)
{
	CopyMemory(&DeviceID2, &DeviceID, sizeof(DDDEVICEIDENTIFIER));
	// Extra parameters
	DeviceID2.dwWHQLLevel = 0;
}

void ConvertDeviceIdentifier(DDDEVICEIDENTIFIER2 &DeviceID2, D3DADAPTER_IDENTIFIER9 &Identifier9)
{
	memcpy(DeviceID2.szDriver, Identifier9.Driver, MAX_DDDEVICEID_STRING);
	memcpy(DeviceID2.szDescription, Identifier9.Description, MAX_DDDEVICEID_STRING);
	DeviceID2.guidDeviceIdentifier = Identifier9.DeviceIdentifier;
	DeviceID2.liDriverVersion.LowPart = Identifier9.DriverVersion.LowPart;
	DeviceID2.liDriverVersion.HighPart = Identifier9.DriverVersion.HighPart;
	DeviceID2.dwDeviceId = Identifier9.DeviceId;
	DeviceID2.dwRevision = Identifier9.Revision;
	DeviceID2.dwSubSysId = Identifier9.SubSysId;
	DeviceID2.dwVendorId = Identifier9.VendorId;
	DeviceID2.dwWHQLLevel = Identifier9.WHQLLevel;
}

void ConvertCaps(DDSCAPS2 &Caps, DDSCAPS2 &Caps2)
{
	Caps.dwCaps = Caps2.dwCaps;
	Caps.dwCaps2 = Caps2.dwCaps2;
	Caps.dwCaps3 = Caps2.dwCaps3;
	Caps.dwCaps4 = Caps2.dwCaps4;
}

void ConvertCaps(DDSCAPS &Caps, DDSCAPS2 &Caps2)
{
	Caps.dwCaps = Caps2.dwCaps;
}

void ConvertCaps(DDSCAPS2 &Caps2, DDSCAPS &Caps)
{
	Caps2.dwCaps = Caps.dwCaps;
	// Extra parameters
	Caps2.dwCaps2 = 0;				// Additional surface capabilities
	Caps2.dwCaps3 = 0;				// Not used
	Caps2.dwCaps4 = 0;				// Not used
}

void ConvertCaps(DDCAPS &Caps, DDCAPS &Caps7)
{
	// Convert caps
	DWORD dwSize = min(sizeof(DDCAPS), Caps.dwSize);
	ZeroMemory(&Caps, dwSize);
	CopyMemory(&Caps, &Caps7, min(dwSize, Caps7.dwSize));
	Caps.dwSize = dwSize;

	// Set available memory, some games have issues if this is set to high
	if (Caps.dwVidMemTotal > 0x8000000)
	{
		Caps.dwVidMemFree = (Caps.dwVidMemFree < 0x8000000) ? Caps.dwVidMemFree : 0x7e00000;
		Caps.dwVidMemTotal = 0x8000000;
	}
}

void ConvertCaps(DDCAPS &Caps7, D3DCAPS9 &Caps9)
{
	DDCAPS tmpCaps7 = { NULL };
	tmpCaps7.dwSize = min(sizeof(DDCAPS), Caps7.dwSize);

	// General settings
	tmpCaps7.dwVidMemTotal = 0x8000000;			// Just hard code the memory size
	tmpCaps7.dwVidMemFree = 0x7e00000;			// Just hard code the memory size
	tmpCaps7.dwMaxVisibleOverlays = 0x1;
	tmpCaps7.dwNumFourCCCodes = 0x12;
	tmpCaps7.dwRops[6] = 4096;
	tmpCaps7.dwMinOverlayStretch = 0x1;
	tmpCaps7.dwMaxOverlayStretch = 0x4e20;

	// Caps
	tmpCaps7.dwCaps = (Caps9.Caps & (D3DCAPS_OVERLAY | D3DCAPS_READ_SCANLINE)) |
		(DDCAPS_3D | DDCAPS_BLT | DDCAPS_BLTQUEUE | DDCAPS_BLTFOURCC | DDCAPS_BLTSTRETCH | DDCAPS_GDI | DDCAPS_OVERLAYCANTCLIP | DDCAPS_OVERLAYFOURCC |
			DDCAPS_OVERLAYSTRETCH | DDCAPS_ZBLTS | DDCAPS_COLORKEY | DDCAPS_ALPHA | DDCAPS_COLORKEYHWASSIST | DDCAPS_BLTCOLORFILL | DDCAPS_BLTDEPTHFILL);
	tmpCaps7.dwCaps2 = (Caps9.Caps2 & (D3DCAPS2_FULLSCREENGAMMA | D3DCAPS2_CANCALIBRATEGAMMA | D3DCAPS2_CANMANAGERESOURCE | D3DCAPS2_DYNAMICTEXTURES | D3DCAPS2_CANAUTOGENMIPMAP)) |
		(DDCAPS2_CANBOBINTERLEAVED | DDCAPS2_CANBOBNONINTERLEAVED | DDCAPS2_NONLOCALVIDMEM | DDCAPS2_WIDESURFACES | DDCAPS2_CANFLIPODDEVEN | DDCAPS2_COPYFOURCC |
			DDCAPS2_CANRENDERWINDOWED | DDCAPS2_FLIPINTERVAL | DDCAPS2_FLIPNOVSYNC);
	tmpCaps7.dwCKeyCaps = (DDCKEYCAPS_DESTOVERLAY | DDCKEYCAPS_SRCBLT | DDCKEYCAPS_SRCOVERLAY);
	tmpCaps7.dwFXCaps = (DDFXCAPS_BLTARITHSTRETCHY | DDFXCAPS_BLTMIRRORLEFTRIGHT | DDFXCAPS_BLTMIRRORUPDOWN | DDFXCAPS_BLTSHRINKX | DDFXCAPS_BLTSHRINKY | DDFXCAPS_BLTSTRETCHX |
		DDFXCAPS_BLTSTRETCHY | DDFXCAPS_OVERLAYARITHSTRETCHY | DDFXCAPS_OVERLAYSHRINKX | DDFXCAPS_OVERLAYSHRINKY | DDFXCAPS_OVERLAYSTRETCHX | DDFXCAPS_OVERLAYSTRETCHY |
		DDFXCAPS_OVERLAYMIRRORLEFTRIGHT | DDFXCAPS_OVERLAYMIRRORUPDOWN | DDFXCAPS_OVERLAYDEINTERLACE);
	tmpCaps7.ddsCaps.dwCaps = (DDSCAPS_BACKBUFFER | DDSCAPS_COMPLEX | DDSCAPS_FLIP | DDSCAPS_FRONTBUFFER | DDSCAPS_OFFSCREENPLAIN | DDSCAPS_OVERLAY | DDSCAPS_PALETTE |
		DDSCAPS_PRIMARYSURFACE | DDSCAPS_TEXTURE | DDSCAPS_3DDEVICE | DDSCAPS_VIDEOMEMORY | DDSCAPS_ZBUFFER | DDSCAPS_OWNDC | DDSCAPS_MIPMAP | DDSCAPS_LOCALVIDMEM |
		DDSCAPS_NONLOCALVIDMEM);
	ConvertCaps(tmpCaps7.ddsOldCaps, tmpCaps7.ddsCaps);
	tmpCaps7.ddsOldCaps.dwCaps = tmpCaps7.ddsCaps.dwCaps;

	// Copy to variable
	CopyMemory(&Caps7, &tmpCaps7, tmpCaps7.dwSize);
}

DWORD GetBitCount(DDPIXELFORMAT ddpfPixelFormat)
{
	if ((ddpfPixelFormat.dwFlags & DDPF_RGB) != 0)
	{
		return ddpfPixelFormat.dwRGBBitCount;
	}
	else if ((ddpfPixelFormat.dwFlags & DDPF_YUV) != 0)
	{
		return ddpfPixelFormat.dwYUVBitCount;
	}
	else if ((ddpfPixelFormat.dwFlags & DDPF_ALPHA) != 0)
	{
		return ddpfPixelFormat.dwAlphaBitDepth;
	}
	else if ((ddpfPixelFormat.dwFlags & DDPF_ZBUFFER) != 0)
	{
		return ddpfPixelFormat.dwZBufferBitDepth;
	}
	else if ((ddpfPixelFormat.dwFlags & DDPF_LUMINANCE) != 0)
	{
		return ddpfPixelFormat.dwLuminanceBitCount;
	}
	else if ((ddpfPixelFormat.dwFlags & DDPF_BUMPDUDV) != 0)
	{
		return ddpfPixelFormat.dwBumpBitCount;
	}

	Logging::Log() << __FUNCTION__ << " Failed to get BitCount from PixelFormat!";
	return 0;
}

DWORD GetBitCount(D3DFORMAT Format)
{
	switch (Format)
	{
	case D3DFMT_R5G6B5:
	case D3DFMT_X1R5G5B5:
	case D3DFMT_A1R5G5B5:
		return 16;
	case D3DFMT_X8R8G8B8:
	case D3DFMT_A8R8G8B8:
	case D3DFMT_A2R10G10B10:
		return 32;
	}

	Logging::Log() << __FUNCTION__ << " Display format not Implemented: " << Format;
	return 0;
}

D3DFORMAT GetDisplayFormat(DDPIXELFORMAT ddpfPixelFormat)
{
	if (ddpfPixelFormat.dwFlags & DDPF_RGB)
	{
		DWORD BitCount = GetBitCount(ddpfPixelFormat);
		switch (BitCount)
		{
		case 8:
			// Default 8-bit
			return D3DFMT_X8R8G8B8;
		case 16:
			if (ddpfPixelFormat.dwGBitMask == 0x3E0)
			{
				if (ddpfPixelFormat.dwFlags & DDPF_ALPHAPIXELS)
				{
					return D3DFMT_A1R5G5B5;
				}
				else
				{
					return D3DFMT_X1R5G5B5;
				}
			}
			// Default 16-bit
			return D3DFMT_R5G6B5;
		case 24:
			Logging::Log() << __FUNCTION__ << " 24-bit RGB not Implemented";
			return D3DFMT_UNKNOWN;
		case 32:
			if (ddpfPixelFormat.dwBBitMask == 0xFF)
			{
				if (ddpfPixelFormat.dwFlags & DDPF_ALPHAPIXELS)
				{
					return D3DFMT_A8R8G8B8;
				}
			}
			else if (ddpfPixelFormat.dwBBitMask == 0x3FF && ddpfPixelFormat.dwRGBAlphaBitMask == 0xC0000000)
			{
				return D3DFMT_A2R10G10B10;
			}
			// Default 32-bit
			return D3DFMT_X8R8G8B8;
		}

		Logging::Log() << __FUNCTION__ << " Error, could not find RGB format for BitCount: " << BitCount;
		return D3DFMT_UNKNOWN;
	}
	else if (ddpfPixelFormat.dwFlags & DDPF_YUV)
	{
		Logging::Log() << __FUNCTION__ << " YUV format not Implemented";
		return D3DFMT_UNKNOWN;
	}
	else if (ddpfPixelFormat.dwFlags & DDPF_ALPHA)
	{
		Logging::Log() << __FUNCTION__ << " Alpha format not Implemented";
		return D3DFMT_UNKNOWN;
	}
	else if (ddpfPixelFormat.dwFlags & DDPF_ZBUFFER)
	{
		Logging::Log() << __FUNCTION__ << " zBuffer format not Implemented";
		return D3DFMT_UNKNOWN;
	}
	else if (ddpfPixelFormat.dwFlags & DDPF_LUMINANCE)
	{
		Logging::Log() << __FUNCTION__ << " Luminance format not Implemented";
		return D3DFMT_UNKNOWN;
	}
	else if (ddpfPixelFormat.dwFlags & DDPF_BUMPDUDV)
	{
		Logging::Log() << __FUNCTION__ << " Bump DUVU format not Implemented";
		return D3DFMT_UNKNOWN;
	}

	Logging::Log() << __FUNCTION__ << " Error, PixelFormat not Implemented see flags: " << ddpfPixelFormat.dwFlags;
	return D3DFMT_UNKNOWN;
}

void GetPixelDisplayFormat(D3DFORMAT Format, DDPIXELFORMAT &ddpfPixelFormat)
{
	DWORD dwSize = min(sizeof(DDPIXELFORMAT), ddpfPixelFormat.dwSize);
	DDPIXELFORMAT tmpPixelFormat = { NULL };
	CopyMemory(&tmpPixelFormat, &ddpfPixelFormat, dwSize);
	tmpPixelFormat.dwSize = dwSize;

	// Supported RGB formats
	if (Format == D3DFMT_R5G6B5 || Format == D3DFMT_X1R5G5B5 || Format == D3DFMT_A1R5G5B5 || Format == D3DFMT_X8R8G8B8 || Format == D3DFMT_A8R8G8B8 || Format == D3DFMT_A2R10G10B10)
	{
		tmpPixelFormat.dwFlags = DDPF_RGB;
		tmpPixelFormat.dwRGBBitCount = GetBitCount(Format);

		// Set BitCount and BitMask
		switch (Format)
		{
		case D3DFMT_R5G6B5:
			tmpPixelFormat.dwRBitMask = 0xF800;
			tmpPixelFormat.dwGBitMask = 0x7E0;
			tmpPixelFormat.dwBBitMask = 0x1F;
			break;
		case D3DFMT_A1R5G5B5:
			tmpPixelFormat.dwFlags |= DDPF_ALPHAPIXELS;
			tmpPixelFormat.dwRGBAlphaBitMask = 0x8000;
		case D3DFMT_X1R5G5B5:
			tmpPixelFormat.dwRBitMask = 0x7C00;
			tmpPixelFormat.dwGBitMask = 0x3E0;
			tmpPixelFormat.dwBBitMask = 0x1F;
			break;
		case D3DFMT_A8R8G8B8:
			tmpPixelFormat.dwFlags |= DDPF_ALPHAPIXELS;
			tmpPixelFormat.dwRGBAlphaBitMask = 0xFF000000;
		case D3DFMT_X8R8G8B8:
			tmpPixelFormat.dwRBitMask = 0xFF0000;
			tmpPixelFormat.dwGBitMask = 0xFF00;
			tmpPixelFormat.dwBBitMask = 0xFF;
			break;
		case D3DFMT_A2R10G10B10:
			tmpPixelFormat.dwFlags |= DDPF_ALPHAPIXELS;
			tmpPixelFormat.dwRGBAlphaBitMask = 0xC0000000;
			tmpPixelFormat.dwRBitMask = 0x3FF00000;
			tmpPixelFormat.dwGBitMask = 0xFFC00;
			tmpPixelFormat.dwBBitMask = 0x3FF;
			break;
		}

		// Copy to variable
		CopyMemory(&ddpfPixelFormat, &tmpPixelFormat, dwSize);
		return;
	}

	Logging::Log() << __FUNCTION__ << " Display format not Implemented: " << Format;
	return;
}
