set_project("seu-pgm")

set_languages("c++23")
set_warnings("all", "error")

if is_plat("windows") then
    add_cxflags("/wd4819", "/wd4866") -- Add this if using msvc
    -- add_cxflags("/Wall")
    add_defines("_CRT_SECURE_NO_WARNINGS")
else
    add_cxflags("-Wno-error=deprecated-declarations", "-fno-strict-aliasing", "-Wno-error=expansion-to-defined")
    add_mxflags("-Wno-error=deprecated-declarations", "-fno-strict-aliasing", "-Wno-error=expansion-to-defined")
end

add_rules("mode.debug", "mode.release")
add_rules("c++.unity_build")

add_requires("vcpkg::ryml", {alias = "ryml"})

add_includedirs("include")
add_links("c4core")

add_sysincludedirs("E:/Program Files/vcpkg/installed/x64-windows-static/include")

target("pgm")
    set_kind("static")
    add_packages("ryml")
    add_files("src/**/*.cpp")

target("example1")
    add_deps("pgm")
    add_files("examples/starter.cpp")
