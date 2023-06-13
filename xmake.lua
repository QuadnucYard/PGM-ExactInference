set_project("seu-pgm")

set_languages("c++23")
set_warnings("all", "error")

if is_plat("windows") then
    add_cxflags("/wd4819") -- Add this if using msvc
    add_cxflags("/Wall")
else
    add_cxflags("-Wno-error=deprecated-declarations", "-fno-strict-aliasing", "-Wno-error=expansion-to-defined")
    add_mxflags("-Wno-error=deprecated-declarations", "-fno-strict-aliasing", "-Wno-error=expansion-to-defined")
end

add_rules("mode.debug", "mode.release")
-- add_rules("c.unity_build")
-- add_rules("c++.unity_build")

-- add_requires("vcpkg::fmt", {alias = "fmt"})
-- add_requires("vcpkg::argparse", {alias = "argparse"})
-- add_requires("vcpkg::tl-ranges", {alias = "tl-ranges"})

add_includedirs("include")

target("pgm")
    set_kind("static")
    add_files("src/**/*.cpp")

-- target("example1")
