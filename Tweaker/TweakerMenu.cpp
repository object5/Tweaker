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
}

void TweakerMenu::Fill()
{
	ImGui::Begin("Tweaker");
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
	if (ImGui::Button("Apply"))
		TweakerMenu::ApplyCallback();
	if (ImGui::Button("Toggle console"))
		::ShowWindow(::GetConsoleWindow(), cfg.consoleshown ? SW_SHOW : SW_HIDE);
		cfg.consoleshown = !cfg.consoleshown;
	ImGui::End();
}
