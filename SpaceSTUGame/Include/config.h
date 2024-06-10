#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG // Release configuration
	return "assets/";
#else
	return "D:/Programming/CPP/SpaceSTU/SpaceSTUGame/assets/";
#endif
}
