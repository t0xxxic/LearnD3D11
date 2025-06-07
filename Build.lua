-- premake5.lua
workspace "dx11"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "game"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:__cplusplus" }
      systemversion "latest"
      defines { "WINDOWS" }

    filter "toolset:msc"
      buildoptions { "/Zc:preprocessor" }

    filter { "toolset:msc-llvm" }
      buildoptions { "/std:c++17",
                      "-Wno-c++98-compat-pedantic",
                      "-Wno-c++98-compat" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

project "render"
   kind "WindowedApp"
   language "C++"
   cppdialect "C++17"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"
   toolset "msc"

   files { "src/**.h", "src/**.cpp", "src/**.vs", "src/**.ps" }

   includedirs
   {
      "src",
      "include/",
   }

   -- Group shaders into a VS filter/folder called "Shaders"
   vpaths {
       ["Shaders"] = { "**.vs", "**.ps" }
   }

   -- Disable compilation of shader files in VS
   filter { "files:**.vs or files:**.ps" }
       buildaction "None"     -- Mark file as "Does not participate in build"
   

   targetdir ("./bin")
   objdir ("./bin-int/" .. OutputDir .. "/%{prj.name}")

   defines { "" }
   libdirs {""}

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"       
       links{

        }

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"
       links{
        }

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"
       links{
        }
