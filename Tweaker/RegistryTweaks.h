#pragma once
#include "config.h"
#include <windows.h>
namespace RegistryTweaks
{
	int DisableWindowsDefender(config cfg);
	int Addkey(LPCSTR subkey, const char* valuename, DWORD valuedata);
};
