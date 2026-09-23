#pragma once
class config
{
public:
	struct apps {
		bool paint = false;
		bool music = false;
		bool phone = false;
		bool maps = false;
		bool camera = false;
		bool people = false;
		bool clipchamp = false;
		bool xbox = false;
		bool todo = false;
		bool alarms = false;
		bool weather = false;
		bool news = false;
		bool gethelp = false;
		bool getstarted = false;
		bool feedback = false;
		bool solitaire = false;
		bool soundrecorder = false;
		bool video = false;
		bool teams = false;
		bool outlook = false;
		bool devhome = false;
		bool cortana = false;
		bool copilot = false;
	};
	bool consoleshown = false;
	bool antivirus = false;
	int antivirusmode = 0;
	bool disablespotlight = false;
	bool disabletelemetry = false;
	bool disablecopilot = false;
	bool disablerecall = false;
	bool disableads = false;
	bool disablewidgets = false;
	bool disablegamedvr = false;
	bool optimizeexplorer = false;
	bool disabledelivery = false;
	bool restart = false;
};
