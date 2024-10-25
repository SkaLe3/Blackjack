project "Blackjack"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir (bin_out)
    objdir (int_out)
    targetname ("Blackjack")

    location "%{wks.location}/Blackjack/Build/ProjectFiles"

    files
    {
        "%{wks.location}/Blackjack/Source/Game/**.h",
        "%{wks.location}/Blackjack/Source/Game/**.cpp"
    }

    includedirs
    {
        "%{wks.location}/Blackjack/Source/Game/Public",
        "%{wks.location}/Blackjack/Source/Game/Private",
        "%{wks.location}/Blackjack/Source/Core/Public",
        "%{IncludeDir.SDL}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Core"
    }
    
    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "BJ_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "BJ_RELEASE"
        runtime "Release"
        optimize "on"
        symbols "off"