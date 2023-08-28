#pragma once
#include "Events/Event.h"
#include "Inputs/MouseCodes.h"

class MouseMovedEvent : public Event
{
public:
	EVENT_TYPE(MouseMoved);
	MouseMovedEvent(float x, float y)
		: m_X(x), m_Y(y) {};
	float GetX() const { return m_X; };
	float GetY() const { return m_Y; };
private:
	float m_X, m_Y;
};

class MouseScrolledEvent : public Event
{
public:
	EVENT_TYPE(MouseScrolled);
	MouseScrolledEvent(float offX, float offY)
		: m_OffsetX(offX), m_OffsetY(offY) {};
	float GetOffsetX() const { return m_OffsetX; };
	float GetOffsetY() const { return m_OffsetY; };
private:
	float m_OffsetX, m_OffsetY;
};

class MouseButtonEvent : public Event
{
public:
	MouseCode GetMouseButton() const { return p_Button; };
protected:
	MouseButtonEvent(MouseCode button)
		: p_Button(button) {};
	MouseCode p_Button;
private:
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	EVENT_TYPE(MouseButtonPressed);
	MouseButtonPressedEvent(MouseCode button)
		: MouseButtonEvent(button) {};
private:
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	EVENT_TYPE(MouseButtonReleased);
	MouseButtonReleasedEvent(MouseCode button)
		: MouseButtonEvent(button) {};
private:
};
