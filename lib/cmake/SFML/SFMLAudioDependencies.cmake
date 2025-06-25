list(APPEND CMAKE_MODULE_PATH .)

include(CMakeFindDependencyMacro)

# detect the OS
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(FIND_SFML_OS_WINDOWS 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(FIND_SFML_OS_LINUX 1)

    if()
        set(FIND_SFML_USE_DRM 1)
    endif()
elseif(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
    set(FIND_SFML_OS_FREEBSD 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Android")
    set(FIND_SFML_OS_ANDROID 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "iOS")
    set(FIND_SFML_OS_IOS 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(FIND_SFML_OS_MACOS 1)
endif()

# When installing, save whether SFML was built using system dependencies.
set(SFML_BUILT_USING_SYSTEM_DEPS OFF)

# start with an empty list
set(FIND_SFML_DEPENDENCIES_NOTFOUND)

if(SFML_BUILT_USING_SYSTEM_DEPS)
    find_dependency(Vorbis)
    find_dependency(FLAC)
else()
    find_dependency(Vorbis CONFIG PATHS "../../../../../../Downloads/SFML-3.0.0-windows-gcc-14.2.0-mingw-64-bit/SFML-3.0.0")
    find_dependency(FLAC CONFIG PATHS "../../../../../../Downloads/SFML-3.0.0-windows-gcc-14.2.0-mingw-64-bit/SFML-3.0.0")
endif()

if(FIND_SFML_DEPENDENCIES_NOTFOUND)
    set(FIND_SFML_ERROR "SFML found but some of its dependencies are missing (${FIND_SFML_DEPENDENCIES_NOTFOUND})")
    set(SFML_FOUND OFF)
endif()
