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

    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender", "DisableAntiSpyware", DWORD(1));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender", "DisableRoutinelyTakingAction", DWORD(1));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender", "ServiceKeepAlive", DWORD(1));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender", "AllowFastServiceStartup", DWORD(1));
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
        return 1;
    }
    Addkey(HKEY_CURRENT_USER, "SOFTWARE\\Policies\\Microsoft\\Windows\\CloudContent", "DisableWindowsSpotlightFeatures", DWORD(1));

    return 0;
}

int RegistryTweaks::DisableTelemetry(config cfg) {
    if (!cfg.disabletelemetry) {
        return 1;
    }
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\DataCollection", "AllowTelemetry", DWORD(0));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\DataCollection", "AllowDesktopAnalytics", DWORD(0));
	Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\DataCollection", "DisableDeviceNameUsage", DWORD(1));

    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\AdvertisingInfo", "Enabled", DWORD(0));
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Privacy", "TailoredExperiencesWithDiagnosticDataEnabled", DWORD(0));
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Speech_OneCore\\Settings\\OnlineSpeechPrivacy", "HasAccepted", DWORD(0));
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Input\\TIPC", "Enabled", DWORD(0));
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\InputPersonalization", "RestrictImplicitInkCollection", DWORD(1));
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\InputPersonalization", "RestrictImplicitTextCollection", DWORD(1));
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\InputPersonalization\\TrainedDataStore", "HarvestContacts", DWORD(0));
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Personalization\\Settings", "AcceptedPrivacyPolicy", DWORD(0));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\DataCollection", "AllowTelemetry", DWORD(0));
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "Start_TrackProgs", DWORD(0));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\System", "PublishUserActivities", DWORD(0));
    Addkey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Siuf\\Rules", "NumberOfSIUFInPeriod", DWORD(0));
    Addkey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Siuf\\Rules", "PeriodInNanoSeconds", DWORD(-1));
    return 0;
}

int RegistryTweaks::DisableCopilot(config cfg) {
    if (!cfg.disablecopilot) {
        return 1;
    }
    Addkey(HKEY_CURRENT_USER, "SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsCopilot", "TurnOffWindowsCopilot", DWORD(1));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsCopilot", "TurnOffWindowsCopilot", DWORD(1));
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "ShowCopilotButton", DWORD(0));
    Addkey(HKEY_CURRENT_USER, "Software\\Policies\\Microsoft\\Windows\\Explorer", "DisableSearchBoxSuggestions", DWORD(1));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", "AllowCortana", DWORD(0));
    return 0;
}

int RegistryTweaks::DisableRecall(config cfg) {
    if (!cfg.disablerecall) {
        return 1;
    }
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsAI", "DisableAIDataAnalysis", DWORD(1));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsAI", "AllowRecallEnablement", DWORD(0));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsAI", "DisableClickToDo", DWORD(1));
    return 0;
}

int RegistryTweaks::DisableAds(config cfg) {
    if (!cfg.disableads) {
        return 1;
    }
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "Start_IrisRecommendations", DWORD(0));
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "Start_AccountNotifications", DWORD(0));
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "RotatingLockScreenEnabled", DWORD(0));
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SubscribedContent-338387Enabled", DWORD(0));
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SilentInstalledAppsEnabled", DWORD(0));
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SystemPaneSuggestionsEnabled", DWORD(0));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\CloudContent", "DisableWindowsConsumerFeatures", DWORD(1));
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "ShowSyncProviderNotifications", DWORD(0));
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\SearchSettings", "IsDynamicSearchBoxEnabled", DWORD(0));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\AdvertisingInfo", "DisabledByGroupPolicy", DWORD(1));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\System", "EnableActivityFeed", DWORD(0));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\System", "UploadUserActivities", DWORD(0));
    return 0;
}

int RegistryTweaks::DisableWidgets(config cfg) {
    if (!cfg.disablewidgets) {
        return 1;
    }
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "TaskbarDa", DWORD(0));
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "TaskbarMn", DWORD(0));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Chat", "ChatIcon", DWORD(3));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Communications", "ConfigureChatAutoInstall", DWORD(0));
    return 0;
}

int RegistryTweaks::DisableGameDvr(config cfg) {
    if (!cfg.disablegamedvr) {
        return 1;
    }
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\GameDVR", "AppCaptureEnabled", DWORD(0));
    Addkey(HKEY_CURRENT_USER, "System\\GameConfigStore", "GameDVR_Enabled", DWORD(0));
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\GameDVR", "AllowGameDVR", DWORD(0));
    return 0;
}

int RegistryTweaks::OptimizeExplorer(config cfg) {
    if (!cfg.optimizeexplorer) {
        return 1;
    }
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "LaunchTo", DWORD(1));
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "HideFileExt", DWORD(0));
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "Hidden", DWORD(1));
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "TaskbarEndTask", DWORD(1));
    return 0;
}

int RegistryTweaks::DisableDelivery(config cfg) {
    if (!cfg.disabledelivery) {
        return 1;
    }
    Addkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\DeliveryOptimization", "DODownloadMode", DWORD(0));
    Addkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\DeliveryOptimization", "SystemSettingsDownloadMode", DWORD(0));
    return 0;
}