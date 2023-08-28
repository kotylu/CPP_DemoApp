#pragma once
#include "Events/Event.h"

class WindowResizeEvent : public Event
{
public:
	EVENT_TYPE(WindowResize);
	WindowResizeEvent(int width, int height)
		: m_Width(width), m_Height(height) {};
	virtual ~WindowResizeEvent() {};
	int GetWidth() { return m_Width; };
	int GetHeight() { return m_Height; };

private:
	int m_Width, m_Height;
};

class WindowCloseEvent : public Event
{
public:
	EVENT_TYPE(WindowClose);
	virtual ~WindowCloseEvent() {};
};
