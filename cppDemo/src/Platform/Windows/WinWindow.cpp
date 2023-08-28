#include "pch.h"
#include "Core/Window.h"
#include "Platform/Windows/WinWindow.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "Inputs/KeyCodes.h"
#include "Inputs/MouseCodes.h"


Window* Window::Create(const WindowProps& props)
{
	return new WinWindow(props);
}


unsigned char WinWindow::GLFW_WINDOW_COUNT = 0;

void WinWindow::SetEventCallbackFn(const EventCallbackFn& callback)
{
	m_Data.EventCallback = callback;
}

void WinWindow::SetVSync(bool enable)
{
	if (enable)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);
	m_Data.VSync = enable;
}

void WinWindow::OnUpdate()
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

void WinWindow::Init(const WindowProps& props)
{
	m_Data.Title = props.Title;
	m_Data.Width = props.Width;
	m_Data.Height = props.Height;

	if (!WinWindow::GLFW_WINDOW_COUNT)
	{
		bool success = glfwInit();
		if (success)
			WinWindow::GLFW_WINDOW_COUNT++;
	}

	m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, &m_Data);
	SetVSync(m_Data.VSync);

	SetupGLFWCallbacks();
}

void WinWindow::SetupGLFWCallbacks()
{
	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
		WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		WindowCloseEvent event;
		data.EventCallback(event);
	});

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
		WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		
		WindowResizeEvent event(width, height);
		data.EventCallback(event);
	});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int _button, int action, int mods) {
		WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		MouseCode button = static_cast<MouseCode>(_button);

		switch (action)
		{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
		}
		
	});
	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
		WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
		data.EventCallback(event);
	});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double posX, double posY) {
		WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		
		MouseMovedEvent event(static_cast<float>(posX), static_cast<float>(posY));
		data.EventCallback(event);
	});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int _key, int scancode, int action, int mods) {
		WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		KeyCode key = static_cast<KeyCode>(_key);

		switch (action)
		{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, false);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, true);
				data.EventCallback(event);
				break;
			}
		}
	});

}

void WinWindow::Shutdown()
{
	glfwDestroyWindow(m_Window);
	--WinWindow::GLFW_WINDOW_COUNT;
	if (!WinWindow::GLFW_WINDOW_COUNT)
		glfwTerminate(); // unload glfw on last window close
}

WinWindow::WinWindow(const WindowProps& props)
{
	Init(props);
}

WinWindow::~WinWindow()
{
	Shutdown();
}

