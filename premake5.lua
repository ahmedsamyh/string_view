workspace "string_view"
    configurations {"Debug", "Release"}
    location "build"

project "string_view"
    kind "ConsoleApp"
    language "C"
    architecture "x64"
    cdialect "C17"
    staticruntime "On"
    targetdir "bin/%{cfg.buildcfg}"

files {"src/**.c"}
includedirs {"include"}

filter "configurations:Debug"
    runtime "Debug"
    defines {"DEBUG"}
    symbols "On"

filter "configurations:Release"
    runtime "Release"
    defines {"NDEBUG"}
    optimize "On"

filter {}
----------------------------------------------------
