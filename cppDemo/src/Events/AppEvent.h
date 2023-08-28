#pragma once
#include "Events/Event.h"

class AppUpdateEvent : public Event
{
	EVENT_TYPE(AppUpdate);
};

class AppRenderEvent : public Event
{
	EVENT_TYPE(AppRender);
};
