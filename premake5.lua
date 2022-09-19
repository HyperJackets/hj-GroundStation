workspace "Morph"
    architecture "x64"
    startproject "MorphApp" -- Generic for different apps

    configurations 
    {
        "Debug",
        "Release",
        "Distribution"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

Include = {}
Include["Morph"] = "%{wks.location}/Morph/Source";
Include["GLFW"] = "%{wks.location}/ThirdParty/GLFW/include";
Include["glad"] = "%{wks.location}/ThirdParty/glad/include";

Library = {}
Library["GLFW"] = "GLFW";
Library["glad"] = "glad";

include "ThirdParty/GLFW"
include "ThirdParty/glad"

include "Morph"
include "MorphApp"
