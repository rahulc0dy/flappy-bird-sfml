list(APPEND CMAKE_MODULE_PATH .)

include(CMakeFindDependencyMacro)

# When installing, save whether SFML was built using system dependencies.
set(SFML_BUILT_USING_SYSTEM_DEPS OFF)

# start with an empty list
set(FIND_SFML_DEPENDENCIES_NOTFOUND)

if(SFML_BUILT_USING_SYSTEM_DEPS)
    find_dependency(Freetype)
else()
    find_dependency(Freetype CONFIG PATHS "../../../../../../Downloads/SFML-3.0.0-windows-gcc-14.2.0-mingw-64-bit/SFML-3.0.0")
endif()

if(FIND_SFML_DEPENDENCIES_NOTFOUND)
    set(FIND_SFML_ERROR "SFML found but some of its dependencies are missing (${FIND_SFML_DEPENDENCIES_NOTFOUND})")
    set(SFML_FOUND OFF)
endif()
