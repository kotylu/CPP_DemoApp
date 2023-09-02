include "dependencies.lua"

-- solution
workspace "cppDemo"
	configurations { "Debug", "Release" }
	platforms { "Win64" }
	startproject "cppDemo"

outputdir = "%{cfg.buildcfg}/%{cfg.platform}"


group "Dependencies"
	include "Dependencies/glfw"
	include "Dependencies/imgui"
group ""

group "Core"
	include "cppDemo"
group ""

filter "system:windows"
	defines
	{
		"PLATFORM_WIN"
	}
filter ""
