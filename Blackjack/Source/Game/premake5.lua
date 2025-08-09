project "Blackjack"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++latest" -- For now it is 23
    staticruntime "off"

    targetdir (bin_out)
    objdir (int_out)
    targetname ("Blackjack")

    location "%{wks.location}/Blackjack/Build/ProjectFiles"

    files
    {
        "%{wks.location}/Blackjack/Source/Game/**.h",
        "%{wks.location}/Blackjack/Source/Game/**.cpp",
        "%{wks.location}/Blackjack/Source/Game/Resources/**.*"
    }

    includedirs
    {
        "%{wks.location}/Blackjack/Source/Game/Public",
        "%{wks.location}/Blackjack/Source/Game/Private",
        "%{wks.location}/Blackjack/Source/Game/Resources",
        "%{wks.location}/Blackjack/Source/Core/Public",
        "%{IncludeDir.SDL}", -- needed for SDL_main.h
        "%{IncludeDir.glm}",
        "%{IncludeDir.nfd}"
    }

    links
    {
        "Core"
    }

    postbuildcommands {
        "{COPYDIR} \"%{wks.location}/Blackjack/Content\" \"%{cfg.targetdir}/Content\""
    }
    
    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "BJ_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Development" -- just release with debug logging
        defines "BJ_DEBUG"
        runtime "Release"
        optimize "on"
        symbols "off"

    filter "configurations:Release"
        defines "BJ_RELEASE"
        runtime "Release"
        optimize "on"
        symbols "off"