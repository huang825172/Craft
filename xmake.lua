add_rules("mode.debug", "mode.release")
add_requires("libsdl", "libsdl_image", "gtest")

target("Craft")
    set_kind("binary")
    set_languages("c++17")
    add_files(
        "src/*.cpp",
        "src/world/*.cpp",
        "src/window/*.cpp",
        "src/misc/*.cpp")
    add_packages("libsdl", "libsdl_image")
    on_run(function()
        os.exec("build/windows/x64/release/Craft.exe")
    end)

target("test_world")
    set_kind("binary")
    set_languages("c++17")
    add_files(
        "test/world.cpp",
        "src/world/*.cpp",
        "src/misc/*.cpp")
    add_packages("gtest")

target("test_noise")
    set_kind("binary")
    set_languages("c++17")
    add_files("test/noise.cpp")
    add_packages("gtest")
