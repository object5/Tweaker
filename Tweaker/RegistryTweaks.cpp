#include "RegistryTweaks.h"
#include <windows.h>
#include <iostream>
#include "TweakerMenu.h"

int RegistryTweaks::Addkey(HKEY rootKey, LPCSTR subkey, const char* valuename, DWORD valuedata) {
	HKEY hKey;
	LONG result;
	result = RegCreateKeyExA(rootKey, subkey, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	if (result == ERROR_SUCCESS) {
		std::cout << "Key :" << subkey << std::endl;
		result = RegSetValueExA(hKey, valuename, 0, REG_DWORD, (const BYTE*)&valuedata, sizeof(valuedata));
		if (result == ERROR_SUCCESS) {
			std::cout << "Value written successfully!" << std::endl;
		}
		else {
			std::cerr << "Error writing value: " << result << std::endl;
		}
		RegCloseKey(hKey);
	}
	else {
		std::cerr << "Error creating key: " << result << std::endl;
	}
	return 0;
}



int RegistryTweaks::DisableWindowsDefender(config cfg) {
    if (!cfg.antivirus) {
        return 0;
    }

    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender", "DisableAntiSpyware", DWORD(0));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender", "DisableRoutinelyTakingAction", DWORD(0));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender", "ServiceKeepAlive", DWORD(0));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender", "AllowFastServiceStartup", DWORD(0));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender", "DisableLocalAdminMerge", DWORD(1));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection", "DisableIOAVProtection", DWORD(1));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection", "DisableRealtimeMonitoring", DWORD(1));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection", "DisableBehaviorMonitoring", DWORD(1));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection", "DisableOnAccessProtection", DWORD(1));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection", "DisableScanOnRealtimeEnable", DWORD(1));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection", "RealtimeScanDirection", DWORD(2));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection", "DisableInformationProtectionControl", DWORD(1));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection", "DisableIntrusionPreventionSystem", DWORD(1));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection", "DisableRawWriteNotification", DWORD(1));

    if (cfg.antivirusmode == 1) {
        Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection", "LocalSettingOverrideDisableOnAccessProtection", DWORD(0));
        Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection", "LocalSettingOverrideRealtimeScanDirection", DWORD(0));
        Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection", "LocalSettingOverrideDisableIOAVProtection", DWORD(0));
        Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection", "LocalSettingOverrideDisableBehaviorMonitoring", DWORD(0));
        Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection", "LocalSettingOverrideDisableIntrusionPreventionSystem", DWORD(0));
        Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection", "LocalSettingOverrideDisableRealtimeMonitoring", DWORD(0));
    }

    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\PolicyManager\\default\\Defender\\AllowBehaviorMonitoring", "value", DWORD(0));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Policies\\Microsoft\\Windows Defender", "DisableRoutinelyTakingAction", DWORD(1));

    return 0;
}

int RegistryTweaks::DisableSpotlight(config cfg) {
    if (!cfg.disablespotlight) {
        return 0;
    }
    Addkey(HKEY_CURRENT_USER, "SOFTWARE\\Policies\\Microsoft\\Windows\\CloudContent", "DisableWindowsSpotlightFeatures", DWORD(1));

    return 0;
}