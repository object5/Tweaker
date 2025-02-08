#pragma once
#include "config.h"
#include <windows.h>
namespace RegistryTweaks
{
	int Addkey(HKEY rootKey, LPCSTR subkey, const char* valuename, DWORD valuedata);
	int DisableWindowsDefender(config cfg);
	int DisableSpotlight(config cfg);
	int DisableTelemetry(config cfg);
};
