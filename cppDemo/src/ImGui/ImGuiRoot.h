#pragma once
#include "Events/EventListener.h"

class ImGuiRoot : public EventListener
{
public:
	ImGuiRoot();
	~ImGuiRoot() {};
	void OnAttach() override;
	void OnDetach() override;
	void OnEvent(Event& event) override;
	
	void Begin();
	void End();
};

