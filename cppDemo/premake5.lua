-- project
project "cppDemo"
	kind "ConsoleApp"
	language "C++"
	location "./" 
	targetdir ("%{wks.location}/bin/" .. outputdir)
	objdir ("%{wks.location}/bin-int/" .. outputdir)

	pchheader "pch.h"
	pchsource "%{wks.location}/%{prj.name}/src/pch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp"
	 }

	defines
	{
		
	}

	includedirs
	{
		"src",
		"%{IncludeDirs.GLFW}"
	}

	links
	{
		"GLFW",
		"%{LibFiles.OPENGL}"
	}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "RELEASE" }
		optimize "On"

