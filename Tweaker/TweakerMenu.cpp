#include "TweakerMenu.h"
#include "vendor/ImGui/imgui.h"
#include "config.h"
#include "PowershellTweaks.h"
#include <Windows.h>
#include "RegistryTweaks.h"
#include "iostream"


config::apps apps;
config cfg;

void TweakerMenu::ApplyCallback() {
	PowershellTweaks::DeletePackages(apps);
	RegistryTweaks::DisableWindowsDefender(cfg);
	RegistryTweaks::DisableSpotlight(cfg);
	RegistryTweaks::DisableTelemetry(cfg);
	RegistryTweaks::DisableCopilot(cfg);
	RegistryTweaks::DisableRecall(cfg);
	RegistryTweaks::DisableAds(cfg);
	RegistryTweaks::DisableWidgets(cfg);
	RegistryTweaks::DisableGameDvr(cfg);
	RegistryTweaks::OptimizeExplorer(cfg);
	RegistryTweaks::DisableDelivery(cfg);
	RegistryTweaks::EnableGameMode(cfg);
	RegistryTweaks::EnableHags(cfg);
	PowershellTweaks::EnableUltimatePerf(cfg);
	RegistryTweaks::DisablePowerThrottle(cfg);
	RegistryTweaks::DisableNetworkThrottle(cfg);
	RegistryTweaks::DisableGameBar(cfg);
	if (cfg.restart) {
		std::cout << "Restarting..." << std::endl;
		system("shutdown /r /t 0");
	}
}

void TweakerMenu::Fill()
{
	ImGui::Begin("Tweaker", nullptr, ImGuiWindowFlags_NoSavedSettings);
	ImGui::Text(ImGui::GetVersion());
	if (ImGui::CollapsingHeader("Microsoft apps"))
	{
		ImGui::Text("Select apps you want to delete.");
		ImGui::Checkbox("Paint", &apps.paint);
		ImGui::Checkbox("Music", &apps.music);
		ImGui::Checkbox("Phone", &apps.phone);
		ImGui::Checkbox("Maps", &apps.maps);
		ImGui::Checkbox("Camera", &apps.camera);
		ImGui::Checkbox("People", &apps.people);
		ImGui::Checkbox("Clipchamp", &apps.clipchamp);
		ImGui::Checkbox("Xbox", &apps.xbox);
		ImGui::Checkbox("To do", &apps.todo);
		ImGui::Checkbox("Alarms", &apps.alarms);
		ImGui::Checkbox("Weather", &apps.weather);
		ImGui::Checkbox("News", &apps.news);
		ImGui::Checkbox("GetHelp", &apps.gethelp);
		ImGui::Checkbox("GetStarted", &apps.getstarted);
		ImGui::Checkbox("Feedback", &apps.feedback);
		ImGui::Checkbox("Solitaire", &apps.solitaire);
		ImGui::Checkbox("SoundRecorder", &apps.soundrecorder);
		ImGui::Checkbox("Video", &apps.video);
		ImGui::Checkbox("Teams", &apps.teams);
		ImGui::Checkbox("Outlook", &apps.outlook);
		ImGui::Checkbox("DevHome", &apps.devhome);
		ImGui::Checkbox("Cortana", &apps.cortana);
		ImGui::Checkbox("Copilot", &apps.copilot);
	}
	ImGui::Separator();
	ImGui::Checkbox("Disable windows defender", &cfg.antivirus);
    if (ImGui::BeginCombo("Antivirus mode", cfg.antivirusmode == 0 ? "Normal mode" : "Aggressive mode")) {
		if (ImGui::Selectable("Normal mode", cfg.antivirusmode == 0)) {
			cfg.antivirusmode = 0;
		}
		if (ImGui::Selectable("Aggressive mode", cfg.antivirusmode == 1)) {
			cfg.antivirusmode = 1;
		}
    ImGui::EndCombo();
    }
	ImGui::Separator();
	ImGui::Checkbox("Disable Windows Spotlight", &cfg.disablespotlight);
	ImGui::Checkbox("Disable Telemetry", &cfg.disabletelemetry);
	ImGui::Checkbox("Disable Copilot", &cfg.disablecopilot);
	ImGui::Checkbox("Disable Recall", &cfg.disablerecall);
	ImGui::Checkbox("Disable Ads", &cfg.disableads);
	ImGui::Checkbox("Disable Widgets", &cfg.disablewidgets);
	ImGui::Checkbox("Disable GameDVR", &cfg.disablegamedvr);
	ImGui::Checkbox("Optimize Explorer", &cfg.optimizeexplorer);
	ImGui::Checkbox("Disable Delivery", &cfg.disabledelivery);
	ImGui::Separator();
	ImGui::Checkbox("Enable Game Mode", &cfg.gamemode);
	ImGui::Checkbox("Enable HAGS", &cfg.hags);
	ImGui::Checkbox("Ultimate Performance", &cfg.ultimateperf);
	ImGui::Checkbox("Disable Power Throttling", &cfg.disablepowerthrottle);
	ImGui::Checkbox("Disable Network Throttle", &cfg.disablenetworkthrottle);
	ImGui::Checkbox("Disable GameBar", &cfg.disablegamebar);
	if (ImGui::Button("Apply"))
		TweakerMenu::ApplyCallback();
	ImGui::SameLine();
	ImGui::Checkbox("Restart after apply", &cfg.restart);
	if (ImGui::Button("Activate windows"))
		PowershellTweaks::ActivateWindows();
	if (ImGui::Button("Toggle console")) {
		cfg.consoleshown = !cfg.consoleshown;
		::ShowWindow(::GetConsoleWindow(), cfg.consoleshown ? SW_SHOW : SW_HIDE);
	}
	ImGui::End();
}
