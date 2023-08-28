#pragma once

enum class EventType
{
	None = 0,
	WindowResize, WindowClose,
	AppUpdate, AppRender,
	MouseButtonPressed, MouseButtonReleased, MouseScrolled, MouseMoved,
	KeyPressed, KeyReleased
};

#define EVENT_TYPE(x)static EventType GetStaticType() { return EventType::x; };\
	EventType GetType() const override { return EventType::x; };\
	std::string GetDebug() const override { return #x; }
	

class Event
{
public:
	bool Handled = false;
	virtual ~Event() {};
	virtual EventType GetType() const = 0;
	virtual std::string GetDebug() const = 0;
};

class EventDispatcher
{
public:
	EventDispatcher(Event& event)
		: m_Event(event) {};

	// typename F - used because we don't know EventType meaning we can't specify actual func signature
	// otherwise would use std::functional<bool(Event&) -- this would get only BaseClass functionality
	template<typename T, typename F>
	bool Dispatch(const F& func)
	{
		if (m_Event.GetType() == T::GetStaticType())
		{
			m_Event.Handled = func(static_cast<T&>(m_Event));
		}
		return m_Event.Handled;
	}
private:
	Event& m_Event;
};
