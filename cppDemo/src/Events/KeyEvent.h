#pragma once
#include "Events/Event.h"
#include "Inputs/KeyCodes.h"

class KeyEvent : public Event
{
public:
	KeyCode GetKeyCode() const { return p_Key; };
protected:
	KeyEvent(KeyCode key)
		: p_Key(key) {};
	KeyCode p_Key;
};

class KeyPressedEvent : public KeyEvent
{
public:
	EVENT_TYPE(KeyPressed);
	KeyPressedEvent(KeyCode key, bool repeat)
		: KeyEvent(key), m_Repeat(repeat) {};
	bool IsRepeated() const { return m_Repeat; };
private:
	bool m_Repeat;
};

class KeyReleasedEvent : public KeyEvent
{
public:
	EVENT_TYPE(KeyReleased);
	KeyReleasedEvent(KeyCode key)
		: KeyEvent(key) {};
private:
};
