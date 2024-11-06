project "Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest" -- For now it is 23
    staticruntime "off"

    targetdir (bin_out)
    objdir (int_out)

    location "%{wks.location}/Blackjack/Build/ProjectFiles"
    
    files
    {
        "%{wks.location}/Blackjack/Source/Core/**.h",
        "%{wks.location}/Blackjack/Source/Core/**.cpp",
        "%{wks.location}/Blackjack/ThirdParty/glm/glm/**.hpp",
        "%{wks.location}/Blackjack/ThirdParty/glm/glm/**.inl"
    }

    includedirs
    {
        "%{wks.location}/Blackjack/Source/Core/Private",
        "%{wks.location}/Blackjack/Source/Core/Public",
        "%{wks.location}/Blackjack/ThirdParty",
        "%{IncludeDir.SDL}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.nfd}"
    }

    libdirs 
    { 
        bin_out,
        "%{wks.location}/Blackjack/ThirdParty/SDL/lib",
        "%{wks.location}/Blackjack/ThirdParty/nfd/lib"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    links 
    {
        "SDL2", 
        "SDL2_ttf",
        "SDL2_image",
        "SDL2_mixer",
        "SDL2main",
        "nfd"
    }

    postbuildcommands {
        "{COPY} \"%{wks.location}/Blackjack/ThirdParty/SDL/lib/SDL2.dll\" \"%{cfg.targetdir}\"",
        "{COPY} \"%{wks.location}/Blackjack/ThirdParty/SDL/lib/SDL2_ttf.dll\" \"%{cfg.targetdir}\"",
        "{COPY} \"%{wks.location}/Blackjack/ThirdParty/SDL/lib/SDL2_image.dll\" \"%{cfg.targetdir}\"",
        "{COPY} \"%{wks.location}/Blackjack/ThirdParty/SDL/lib/SDL2_mixer.dll\" \"%{cfg.targetdir}\"",
    }

    filter "system:windows"
        systemversion "latest"
        defines { "SDL_MAIN_HANDLED" }

    
    filter "configurations:Debug"
        defines "BJ_DEBUG"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        defines "BJ_RELEASE"
        runtime "Release"
        optimize "on"
        symbols "off"

