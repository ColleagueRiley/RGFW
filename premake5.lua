location ("build")

workspace "RGFW"
    configurations { "Debug", "Release" }
    startproject "examples"

    -- cross compiling windows
    if _ACTION and _ACTION:find("xcode") then
        platforms({ "Native" })
    else
        platforms({
            "Native",
            "Win32",
            "Win64"
        })
    end
    defaultplatform("Native")

    filter("platforms:Win32")
        system("windows")
        architecture("x86")
        gccprefix("i686-w64-mingw32-")

    filter("platforms:Win64")
        system("windows")
        architecture("x86_64")
        gccprefix("x86_64-w64-mingw32-")

    filter({})

    -- clean command
    newaction({
        trigger = "clean",
        description = "Clean the files",
        execute = function()
            os.rmdir("bin")
            os.rmdir("bin-int")
            os.rmdir("build")
        end
    })

    -- Custom Options
    newoption {
        trigger = "wayland",
        description = "Enable Wayland support"
    }
    newoption {
        trigger = "no-vulkan",
        description = "Disable Vulkan example"
    }
    newoption {
        trigger = "no-gles",
        description = "Disable GLES example"
    }
    newoption {
        trigger = "no-osmesa",
        description = "Disable OSMesa example"
    }

    -- Variables
    local isWindows = os.host() == "windows"
    local isLinux   = os.host() == "linux"
    local isMac     = os.host() == "macosx"

    local no_vulkan = _OPTIONS["no-vulkan"]
    local no_gles   = _OPTIONS["no-gles"] or not isLinux
    local no_osmesa = _OPTIONS["no-osmesa"] or not isLinux
    local use_wayland = _OPTIONS["wayland"]

group "examples"
    -- List of simple examples
    local exampleOutputs = {
        "basic",
        "buffer",
        "events",
        "callbacks",
        "flags",
        "monitor",
        "gl33_ctx",
        "smooth-resize",
        "multi-window"
    }

    for _, example in ipairs(exampleOutputs) do
        project(example)
            kind "ConsoleApp"
            language "C"
            targetdir "bin/%{cfg.buildcfg}"
            objdir "bin-int/%{cfg.buildcfg}"

            files { "examples/" .. example .. "/" .. example .. ".c", "RGFW.h" }
            includedirs { "." }

            filter "system:windows"
                links { "gdi32", "opengl32" }

            filter "system:linux"
                if use_wayland then
                    links { "EGL", "GL" }
                else
                    links { "GL", "X11", "Xrandr", "dl", "pthread" }
                end

            filter "system:macosx"
                links { "Cocoa.framework", "OpenGL.framework", "IOKit.framework", "CoreVideo.framework" }
    end

    -- List of special examples (conditionally compiled)
    local exampleCustomOutputs = {
        { name = "icons/icons" },
        { name = "gamepad/gamepad" },
        { name = "silk/silk" },
        { name = "first-person-camera/camera", projectname = "camera" },
        { name = "microui_demo/microui_demo" },
        { name = "gl33/gl33" },
        { name = "portableGL/pgl", condition = not (os.target() == "emscripten") },
        { name = "gles2/gles2", condition = not no_gles },
        { name = "dx11/dx11", system = "windows", condition = isWindows },
        { name = "metal/metal", system = "macosx", condition = isMac },
        { name = "webgpu/webgpu", system = "emscripten", condition = (os.target() == "emscripten") },
        { name = "minimal_links/minimal_links" },
        { name = "osmesa_demo/osmesa_demo", condition = not no_osmesa },
        { name = "vk10/vk10", condition = not no_vulkan },
    }

    for _, e in ipairs(exampleCustomOutputs) do
        if e.condition == nil or e.condition then
            project(e.projectname or path.getname(e.name))
                kind "ConsoleApp"
                language "C"
                targetdir "bin/%{cfg.buildcfg}"
                objdir "bin-int/%{cfg.buildcfg}"

                files { "examples/" .. e.name .. ".c", "RGFW.h" }
                includedirs { "." }

                if e.name == "gles2/gles2" then
                    links {"EGL"}
                end
                
                if e.name == "osmesa_demo/osmesa_demo" then
                    links { "OSMesa" }
                end
                
                if e.name == "microui_demo/microui_demo" then
                    files { "examples/microui_demo/microui.c" }
                end
 

                filter "system:windows"
                    if e.name == "dx11/dx11" then
                        links { "d3d11", "dxgi", "d3dcompiler", "uuid", "gdi32" }
                    else
                        links { "gdi32", "opengl32" }
                    end

                filter "system:linux"
                    if use_wayland then
                        links { "EGL", "GL" }
                    else    
                        links { "GL", "X11", "Xrandr", "dl", "pthread", "m" }
                    end
                filter "system:macosx"
                    if e.name == "metal/metal" then
                        files { "RGFW.c" }
                        buildoptions { "-x objective-c" }
                        links { "Metal.framework", "QuartzCore.framework", "Cocoa.framework", "IOKit.framework", "CoreVideo.framework" }
                    else
                        links { "Cocoa.framework", "OpenGL.framework", "IOKit.framework", "CoreVideo.framework" }
                    end
        end
    end
