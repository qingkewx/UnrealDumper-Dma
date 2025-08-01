#include "pch.h"
#include "Registry.h"
#include "Memory.h"

std::string c_registry::QueryValue(const char* path, e_registry_type type)
{
	if (!mem.vHandle)
		return "";

	BYTE buffer[0x128];
	DWORD _type = static_cast<DWORD>(type);
	DWORD size = sizeof(buffer);

	if (!VMMDLL_WinReg_QueryValueExU(mem.vHandle, const_cast<LPSTR>(path), &_type, buffer, &size))
	{
		LOG("[!] failed QueryValueExU call\n");
		return "";
	}
	//TODO: implement something nicer & better than this.
	if (type == e_registry_type::dword)
	{
		DWORD dwordValue = *reinterpret_cast<DWORD*>(buffer);
		return std::to_string(dwordValue);
	}
	std::wstring wstr = std::wstring(reinterpret_cast<wchar_t*>(buffer));
	return std::string(wstr.begin(), wstr.end());
}