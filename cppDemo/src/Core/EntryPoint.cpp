#include "pch.h"
#include "Core/Application.h"

int main()
{
	Application& app = Application::Create();
	app.Initialize();
	app.Run();
}