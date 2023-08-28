#pragma once
#include "Core/Window.h"
#include "Events/EventListener.h"
#include "Events/WindowEvent.h"

class Application : public EventListener
{
public:
	static Application& Create();
	~Application();

	const static Application& Get() { return *Application::s_Instance.get(); };
	void Initialize();
	void Run();
	void OnEvent(Event& e) override;
	void Close();
	bool OnWindowClose(const WindowCloseEvent& e);
	bool OnWindowResize(const WindowResizeEvent& e);

private:
	static std::unique_ptr<Application> s_Instance;
	Application();
	std::vector<EventListener*> m_Listeners;
	std::unique_ptr<Window> m_Window;
	bool m_Running = true;
};
