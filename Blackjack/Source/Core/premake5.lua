project "Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
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
        "%{IncludeDir.glm}"
    }

    libdirs 
    { 
        bin_out,
        "%{wks.location}/Blackjack/ThirdParty/SDL/lib"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }


    filter "system:windows"
        systemversion "latest"
        defines { "SDL_MAIN_HANDLED" }

    
    filter "configurations:Debug"
        defines "BJ_DEBUG"
        runtime "Debug"
        symbols "on"

        links { "SDL2d", "SDL2main" }

        postbuildcommands {
            "{COPY} \"%{wks.location}/Blackjack/ThirdParty/SDL/lib/SDL2d.dll\" \"%{cfg.targetdir}\""
        }
    
    filter "configurations:Release"
        defines "BJ_RELEASE"
        runtime "Release"
        optimize "on"
        symbols "off"

        links { "SDL2", "SDL2main" }

        postbuildcommands {
            "{COPY} \"%{wks.location}/Blackjack/ThirdParty/SDL/lib/SDL2d.dll\" \"%{cfg.targetdir}\""
        }
