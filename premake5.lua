workspace "OpenGL-Platform"
    architecture "x64"
    configurations
    {
        "Debug",
        "Internal",
        "Release"
    }

out = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Foundations"
    location "Foundations"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("Build/" .. out .. "/%{prj.name}")
    objdir ("Build/int/" .. out .. "/%{prj.name}")

    files
    {
        "%{prj.name}/**",
    }

    includedirs
    {
        "Foundations",
        "Vendor",
        "Vendor/glm",
        "Vendor/glfw/include",
        "Vendor/glad/include"
    }

    libdirs {
        "vendor/glfw/lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        
        links {
            "glfw3",
            "opengl32"
        }
        defines
        {
            "OGP_WIN"
        }

    
    filter "system:macosx"
        cppdialect "C++17"

        links {
            "glfw3",
            "OpenGL.framework",
            "Cocoa.framework",
            "IOKit.framework",
            "CoreVideo.framework"
        }

        defines
        {
            "OGP_MAC"
        }

        linkoptions
        {
            "-isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk"
        }


    filter "action:vs*"  -- for Visual Studio actions
        pchheader "PCHeader.h"
        pchsource "%{prj.name}/PCHeader.cpp"

    filter "action:not vs*"  -- for everything else
        pchheader "%{prj.name}/PCHeader.h"

    filter "configurations:Debug"
        defines { "OGP_DEBUG" }
        symbols "On"

    filter "configurations:Debug"
        defines { "OGP_DEBUG", "OGP_INTERNAL" }
        optimize "On"
        symbols "On"

    filter "configurations:Release"
        defines { "OGP_NDEBUG" }
        optimize "On"