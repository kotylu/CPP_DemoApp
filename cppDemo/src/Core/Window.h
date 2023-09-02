#pragma once
#include "GLFW/glfw3.h"
#include "Events/Event.h"

class WindowProps
{
public:
	std::string Title;
	unsigned int Width, Height;

	WindowProps(const std::string& title = "Default Title",
		unsigned int width = 1280,
		unsigned int height = 720)
		: Title(title), Width(width), Height(height)
	{
	}
private:
};

class Window
{
public:
	using EventCallbackFn = std::function<void(Event&)>;

	static Window* Create(const WindowProps& props = WindowProps());
	virtual ~Window() {};

	virtual void* GetNative() const = 0;
	virtual unsigned int GetWidth() const = 0;
	virtual unsigned int GetHeight() const = 0;
	virtual bool IsVSyncEnabled() const = 0;

	virtual void SetEventCallbackFn(const EventCallbackFn& callback) = 0;
	virtual void SetVSync(bool enable) = 0;

	virtual void OnUpdate() = 0;
private:
};
