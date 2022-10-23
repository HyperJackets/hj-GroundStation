project "GroundStation"
    language "C++"
    cppdialect "C++20"
    kind "ConsoleApp"
    staticruntime "off"

    targetdir ("%{wks.location}/Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/Binaries-Int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "Source/**.h",
        "Source/**.cpp"
    }

    includedirs 
    {
        "Source",
        "%{Include.Morph}",
        "%{Include.Morph}/Morph",
        "%{Include.ImGui}"
    }

    links
    {
        "Morph",
        "%{Library.ImGui}"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "MORPH_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "MORPH_CONFIG_DEBUG"
        runtime "Debug"
        optimize "off"
        symbols "on"

    filter "configurations:Release"
        defines "MORPH_CONFIG_RELEASE"
        runtime "Release"
        optimize "on"
        symbols "on"

    filter "configurations:Distribution"
        defines "MORPH_CONFIG_DISTRIBUTION"
        runtime "Release"
        optimize "full"
        symbols "off"
