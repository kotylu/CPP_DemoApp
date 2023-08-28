#pragma once
#include "Events/Event.h"
#include "Events/AppEvent.h"

class EventListener
{
public:
	virtual ~EventListener() {};
	virtual void OnEvent(Event& event) {};
	virtual void OnUpdate(AppUpdateEvent& event) {};
	virtual void OnRender(AppRenderEvent& event) {};
};
