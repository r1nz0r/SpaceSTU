#include "EntryPoint.h"
#include "Framework/Application.h"

int main()
{
	SSTU::Application* app = GetApplication();
	app->Run();
	delete app;
}