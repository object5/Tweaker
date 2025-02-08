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
