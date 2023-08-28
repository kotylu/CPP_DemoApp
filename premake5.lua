include "dependencies.lua"

-- solution
workspace "cppDemo"
	configurations { "Debug", "Release" }
	platforms { "Win64" }
	startproject "cppDemo"

outputdir = "%{cfg.buildcfg}/%{cfg.platform}"

group "Dependencies"
	include "Dependencies/glfw"
group ""

group "Core"
	include "cppDemo"
group ""