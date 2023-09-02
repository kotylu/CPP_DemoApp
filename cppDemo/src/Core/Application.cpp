#include "pch.h"
#include "Core/Application.h"
#include "Events/WindowEvent.h"
// -- TEST ImGui -> display demo window
#include "ImGui/ImGuiTest.h"

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
	DestroyAllListeners();
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

	// ------------ ImGui ------------
	m_ImGui = new ImGuiRoot();
	RegisterListener(m_ImGui);
	// -- TEST ImGui
	RegisterListener(new ImGuiTest());
}

void Application::Run()
{
	while (m_Running)
	{
	// ------------ App Logic ------------

	// ------------ ImGui ------------
		m_ImGui->Begin();
		for (auto listener : m_Listeners)
		{
			listener->OnImGuiRender();
		}
		m_ImGui->End();
		// Brakes with dockspace -> looks like dockspace is doing it's own clear
		// with two clears in one frame imgui windows are hidden while in/over dockspace
		/*
			glClearColor(0.2, 0.2, 0.2, 0);
			glClear(GL_COLOR_BUFFER_BIT);
		*/

		m_Window->OnUpdate();
	}
}

void Application::Close()
{
	m_Running = false;
}

void Application::RegisterListener(EventListener* listener)
{
	listener->OnAttach();
	m_Listeners.push_back(listener);
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

void Application::DestroyAllListeners()
{
	for (EventListener* listener : m_Listeners)
	{
		DestroyListener(listener);
	}
}

void Application::DestroyListener(EventListener* listener)
{
	auto it = std::find(m_Listeners.begin(), m_Listeners.end(), listener);
	if (it != m_Listeners.end())
	{
		auto ix = it - m_Listeners.begin();
		m_Listeners[ix]->OnDetach();
		delete m_Listeners[ix];
		m_Listeners.erase(it);
	}
}

