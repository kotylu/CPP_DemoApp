#pragma once
#include "Core/Window.h"
#include "Events/EventListener.h"
#include "Events/WindowEvent.h"
#include "ImGui/ImGuiRoot.h"

class Application : public EventListener
{
public:
	static Application& Create();
	~Application();

	static inline Application& Get() { return *Application::s_Instance.get(); };
	inline Window& GetWindow() const { return *m_Window.get(); };

	void Initialize();
	void Run();
	void OnEvent(Event& e) override;
	void Close();

	void RegisterListener(EventListener* listener); // currently taking ownership of the pointer

	bool OnWindowClose(const WindowCloseEvent& e);
	bool OnWindowResize(const WindowResizeEvent& e);
private:
	void DestroyAllListeners();
	void DestroyListener(EventListener* listener); // currently taking ownership of the pointer

private:
	static std::unique_ptr<Application> s_Instance;
	Application();
	std::vector<EventListener*> m_Listeners;
	std::unique_ptr<Window> m_Window;
	ImGuiRoot* m_ImGui;
	bool m_Running = true;
};
