#include "pch.h"
#include "settings.h"

int Settings::width;
int Settings::height;
int Settings::refresh;

bool Settings::Load(std::string& path)
{
	toml::table settings;

	try
	{
		settings = toml::parse_file(path + "\\autores.toml");

		std::cout << "[AutoRes] Settings loaded." << std::endl;
	}
	catch (std::exception& exception)
	{
		char buffer[1024];
		sprintf_s(buffer, "Failed to parse autores.toml. Current resolution will not change.\n%s", exception.what());
		MessageBoxA(nullptr, buffer, "AutoRes", MB_OK | MB_ICONERROR);

		return false;
	}

	width = settings["width"].value_or(-1);
	height = settings["height"].value_or(-1);
	refresh = settings["refresh"].value_or(-1);

	return true;
}
