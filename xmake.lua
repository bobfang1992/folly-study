add_rules("mode.debug", "mode.release")
add_requires("folly 2022.08.29", {configs = {cxxstd = "c++20"}})
add_requires("fmt")

set_languages("c++20")


target("xmake-test")
    set_kind("binary")
    add_files("src/*.cpp")
    add_defines("FOLLY_HAS_COROUTINES")
    add_packages("folly")
    add_packages("fmt")

