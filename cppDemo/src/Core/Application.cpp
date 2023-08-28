#include "pch.h"
#include "Core/Application.h"
#include "Events/WindowEvent.h"

std::unique_ptr<Application> Application::s_Instance = nullptr;
Application& Application::Create()
{
	if (!Application::s_Instance.get())
	{
		Application::s_Instance = std::unique_ptr<Application>(new Application());
	}
	return *Application::s_Instance.get();
}

Application::~Application()
{
}

Application::Application()
{
}

void Application::Initialize()
{
	// ------------ WINDOW ------------
	WindowProps wPropsHD{ "My Application", 1280, 720 };
	m_Window = std::unique_ptr<Window>(Window::Create(wPropsHD));
	m_Window->SetEventCallbackFn(BIND_EVENT_FN(Application::OnEvent));
	m_Window->SetVSync(true);
}

void Application::Run()
{
	while (m_Running)
	{

		for (auto listener : m_Listeners)
		{
			AppUpdateEvent e;
			listener->OnUpdate(e);
			if (e.Handled)
				break;
		}
		for (auto listener : m_Listeners)
		{
			AppRenderEvent e;
			listener->OnRender(e);
			if (e.Handled)
				break;
		}
		m_Window->OnUpdate();
	}
}

void Application::Close()
{
	m_Running = false;
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
	dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

	for (auto listener : m_Listeners)
	{
		listener->OnEvent(e);
		if (e.Handled)
			break;
	}
}

bool Application::OnWindowClose(const WindowCloseEvent& e)
{
	Close();
	return true;
}

bool Application::OnWindowResize(const WindowResizeEvent& e)
{
	return true;
}
