#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG // Release configuration
	return "assets/";
#else
	return "E:/Visual Studio/CPP/SpaceSTU/SpaceSTUGame/assets/";
#endif
}
