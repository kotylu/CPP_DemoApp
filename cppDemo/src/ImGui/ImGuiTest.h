#pragma once
#include "Events/EventListener.h"

class ImGuiTest : public EventListener
{
	void OnImGuiRender();
};

