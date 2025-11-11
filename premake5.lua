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
local use_wayland = _OPTIONS["wayland"]

-- List of special examples (conditionally compiled)
local exampleRules = {
    ["first-person-camera"]    = { projectname = "camera" },
    ["portableGL"]         = { condition = not (os.target() == "emscripten") },
    ["gles2"]            = { condition = not no_gles },
    ["egl"]            = { condition = not no_gles },
    ["dx11"]              = { condition = isWindows },
    ["metal"]            = { condition = isMac },
    ["webgpu"]          = { condition = (os.target() == "emscripten") },
    ["minimal_links"] = { condition = true },
    ["osmesa_demo"]= { condition = not no_osmesa },
    ["vk10"]              = { condition = not no_vulkan },
}

local dirs = os.matchdirs("examples/*")
table.sort(dirs)

for _, example in ipairs(dirs) do
    local rel   = path.getrelative("examples", example)
    local rule  = exampleRules[rel]
    local name  = rule and rule.projectname or path.getname(example)
    local build = (rule == nil) or (rule.condition ~= false)

    print(example, rel, name, rule, build)

    if build then
        project(name)
            kind "ConsoleApp"
            language "C"
            targetdir "bin/%{cfg.buildcfg}"
            objdir "bin-int/%{cfg.buildcfg}"

            files { example .. "/**.c", "RGFW.h" }
            includedirs { "." }

            --
            if name == "gles2" then
                links {"EGL"}
            end
            if name == "osmesa_demo" then
                links { "OSMesa" }
            end
            if name == "microui_demo" then
                removefiles { example .. "/renderer.c" }
            end
            if name == "metal" then
                files { example .. "/**.m" }
                buildoptions { "-x objective-c" }
            end

            --
            filter { "system:windows", "action:not xcode*" }
                links { "gdi32", "opengl32" }

            filter "system:linux"
                if use_wayland then
                    links { "EGL", "GL" }
                else
                    links { "GL", "X11", "Xrandr", "dl", "pthread" }
                end

            filter "system:macosx"
                if name == "metal" then
                    links { "Metal.framework", "QuartzCore.framework", "Cocoa.framework", "IOKit.framework", "CoreVideo.framework" }
                else
                    links { "Cocoa.framework", "OpenGL.framework", "IOKit.framework", "CoreVideo.framework" }
                end
                xcodebuildsettings {
                    ALWAYS_SEARCH_USER_PATHS = "YES"
                }
    end
end
