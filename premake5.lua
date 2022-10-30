workspace "hj-GroundStation"
    architecture "x64"
    startproject "GroundStation" -- Generic for different apps

    configurations 
    {
        "Debug",
        "Release",
        "Distribution"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

MorphDir = ".."

group "Dependencies"
    include "Vendor.lua"
group ""

include "GroundStation"
