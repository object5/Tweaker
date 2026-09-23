#pragma once
#include "config.h"
#include <windows.h>
namespace RegistryTweaks
{
	int Addkey(HKEY rootKey, LPCSTR subkey, const char* valuename, DWORD valuedata);
	int DisableWindowsDefender(config cfg);
	int DisableSpotlight(config cfg);
	int DisableTelemetry(config cfg);
	int DisableCopilot(config cfg);
	int DisableRecall(config cfg);
	int DisableAds(config cfg);
	int DisableWidgets(config cfg);
	int DisableGameDvr(config cfg);
	int OptimizeExplorer(config cfg);
	int DisableDelivery(config cfg);
	int EnableGameMode(config cfg);
	int EnableHags(config cfg);
	int DisablePowerThrottle(config cfg);
	int DisableNetworkThrottle(config cfg);
	int DisableGameBar(config cfg);
};
