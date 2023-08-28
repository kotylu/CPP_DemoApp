#pragma once
#include "GLFW/glfw3.h"
#include "Core/Window.h"

class WinWindow : public Window
{
public:
	WinWindow(const WindowProps& props);
	~WinWindow();
	inline unsigned int GetWidth() const override { return m_Data.Width; };
	inline unsigned int GetHeight() const override { return m_Data.Height; };
	inline bool IsVSyncEnabled() const override { return m_Data.VSync; };

	void SetEventCallbackFn(const EventCallbackFn& callback) override;
	void SetVSync(bool enable) override;

	void OnUpdate() override;
private:
	void Init(const WindowProps& props);
	void SetupGLFWCallbacks();
	void Shutdown();
	struct WindowData
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		bool VSync;

		EventCallbackFn EventCallback;
	};
private:
	static unsigned char GLFW_WINDOW_COUNT;
	GLFWwindow* m_Window;
	WindowData m_Data;
};
