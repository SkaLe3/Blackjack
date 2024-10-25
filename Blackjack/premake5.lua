-- Main premake
include "Dependencies.lua"

workspace "Blackjack"
    architecture "x64"
    startproject "Blackjack"
    configurations { "Debug", "Release"}
    platforms {"Win64"}
    buildoptions { "/MP "}
    location "..\\"

    outputdir = "%{cfg.platform}/%{cfg.buildcfg}"
    bin_out = "%{wks.location}/Blackjack/Binaries/" .. outputdir .. ""
    int_out = "%{wks.location}/Blackjack/Intermediate/" .. outputdir .. ""


group "Core"
    include "Source/Core"
group ""

group "Game"
    include "Source/Game"
group ""

