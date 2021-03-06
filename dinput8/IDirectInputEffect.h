#pragma once

class m_IDirectInputEffect8 : public IDirectInputEffect, public AddressLookupTableDinput8Object
{
private:
	IDirectInputEffect *ProxyInterface;

public:
	m_IDirectInputEffect8(IDirectInputEffect *aOriginal) : ProxyInterface(aOriginal)
	{
		ProxyAddressLookupTableDinput8.SaveAddress(this, ProxyInterface);
	}
	~m_IDirectInputEffect8()
	{
		ProxyAddressLookupTableDinput8.DeleteAddress(this);
	}

	IDirectInputEffect *GetProxyInterface() { return ProxyInterface; }

	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID * ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

	/*** IDirectInputEffect methods ***/
	STDMETHOD(Initialize)(THIS_ HINSTANCE, DWORD, REFGUID);
	STDMETHOD(GetEffectGuid)(THIS_ LPGUID);
	STDMETHOD(GetParameters)(THIS_ LPDIEFFECT, DWORD);
	STDMETHOD(SetParameters)(THIS_ LPCDIEFFECT, DWORD);
	STDMETHOD(Start)(THIS_ DWORD, DWORD);
	STDMETHOD(Stop)(THIS);
	STDMETHOD(GetEffectStatus)(THIS_ LPDWORD);
	STDMETHOD(Download)(THIS);
	STDMETHOD(Unload)(THIS);
	STDMETHOD(Escape)(THIS_ LPDIEFFESCAPE);
};
