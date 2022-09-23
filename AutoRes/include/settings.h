#pragma once

class Settings
{
public:
	static int width;
	static int height;
	static int refresh;

	static bool Load(std::string& path);
};
