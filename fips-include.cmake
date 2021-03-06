# cmake options
set(ORYOL_SAMPLE_URL "http://floooh.github.com/oryol/" CACHE STRING "Sample data URL")
if (FIPS_MACOS OR FIPS_LINUX OR FIPS_ANDROID)
    option(ORYOL_USE_LIBCURL "Use libcurl instead of native APIs" ON)
else() 
    option(ORYOL_USE_LIBCURL "Use libcurl instead of native APIs" OFF)
endif()

if (ORYOL_USE_LIBCURL)
    add_definitions(-DORYOL_USE_LIBCURL=1)
endif()

# for TurboBadger UI support, override the search path for the 
# tb_config.h overriden header file
include_directories(code/Modules/TBUI/tb)

# profiling enabled?
if (FIPS_PROFILING)
    add_definitions(-DORYOL_PROFILING=1)
endif()

# use Visual Leak Detector?
# see https://github.com/floooh/fips-vld
if (FIPS_USE_VLD)
    add_definitions(-DORYOL_USE_VLD=1)
endif()

# use OpenAL?
if (FIPS_OSX OR FIPS_EMSCRIPTEN)
    set(ORYOL_OPENAL 1)
else()
    set(ORYOL_OPENAL 0)
endif()

# POSIX platforms
if (FIPS_POSIX)
    set(ORYOL_OPENGL 1)
    add_definitions(-DORYOL_POSIX=1)
    if (FIPS_LINUX)
        set(ORYOL_OPENGL_CORE_PROFILE 1)
        add_definitions(-DORYOL_LINUX=1)
    endif()
    if (FIPS_OSX)
        add_definitions(-DORYOL_OSX=1)
        if (FIPS_MACOS)
            set(ORYOL_OPENGL_CORE_PROFILE 1)
            add_definitions(-DORYOL_MACOS=1)
        endif()
        if (FIPS_IOS)
            set(ORYOL_OPENGLES2 1)
            add_definitions(-DORYOL_IOS=1)
        endif()
    endif()
    if (FIPS_PNACL)
        set(ORYOL_OPENGLES2 1)
        add_definitions(-DORYOL_PNACL=1)
    endif()
    if (FIPS_EMSCRIPTEN)
        set(ORYOL_OPENGLES2 1)
        add_definitions(-DORYOL_EMSCRIPTEN=1)
    endif()
    if (FIPS_ANDROID)
        set(ORYOL_OPENGLES3 1)
        add_definitions(-DORYOL_ANDROID=1)
    endif()
endif()

# Windows platforms
if (FIPS_WINDOWS)

    option(ORYOL_WINDOWS_USE_OPENGL "Use OpenGL on Windows (default)" ON)
    option(ORYOL_WINDOWS_USE_D3D11  "Use D3D11 on Windows" OFF)
    
    if (ORYOL_WINDOWS_USE_OPENGL AND ORYOL_WINDOWS_USE_D3D11)
        message(FATAL_ERROR "OpenGL and D3D11 can't both be enabled!")
    endif()

    if (ORYOL_WINDOWS_USE_OPENGL) 
        set(ORYOL_OPENGL 1)
        set(ORYOL_OPENGL_CORE_PROFILE 1)
    endif()
    if (ORYOL_WINDOWS_USE_D3D11)
        set(ORYOL_D3D11 1)
    endif()
        
    add_definitions(-DORYOL_WINDOWS=1)
    if (FIPS_WIN32)
        add_definitions(-DORYOL_WIN32=1)
    endif()
    if (FIPS_WIN64)
        add_definitions(-DORYOL_WIN64=1)
    endif()
endif()

# OpenGL defines
if (ORYOL_OPENGL)
    add_definitions(-DORYOL_OPENGL=1)
    if (ORYOL_OPENGLES2)
        add_definitions(-DORYOL_OPENGLES2=1)
    endif()
    if (ORYOL_OPENGLES3)
        add_definitions(-DORYOL_OPENGLES3=1)
    endif()
    if (ORYOL_OPENGL_CORE_PROFILE)
        add_definitions(-DORYOL_OPENGL_CORE_PROFILE=1)
    endif()
endif()

# D3D11 defines
if (ORYOL_D3D11)
    add_definitions(-DORYOL_D3D11=1)
endif()

# OpenAL defines
if (ORYOL_OPENAL)
    add_definitions(-DORYOL_OPENAL=1)
endif()

# misc defines
if (FIPS_ALLOCATOR_DEBUG)
    add_definitions(-DORYOL_ALLOCATOR_DEBUG=1)
endif()
if (FIPS_UNITTESTS)
    add_definitions(-DORYOL_UNITTESTS=1)
    if (FIPS_UNITTESTS_HEADLESS)
        add_definitions(-DORYOL_UNITTESTS_HEADLESS=1)
    endif()
endif()
if (FIPS_NO_ASSERTS_IN_RELEASE)
    add_definitions(-DORYOL_NO_ASSERT=1)
endif()
if (FIPS_FORCE_NO_THREADS)
    add_definitions(-DORYOL_FORCE_NO_THREADS=1)
endif()
if (FIPS_EMSCRIPTEN OR FIPS_PNACL)
    add_definitions(-DORYOL_SAMPLE_URL=\"http://localhost/\")
else()
    add_definitions(-DORYOL_SAMPLE_URL=\"${ORYOL_SAMPLE_URL}\")
endif()

#-------------------------------------------------------------------------------
#   Add a sample file to the web samples description file
#
file(REMOVE ${FIPS_DEPLOY_DIR}/oryol-webpage/websamples.yml)
macro(oryol_add_web_sample name desc type image src)
    file(APPEND ${FIPS_DEPLOY_DIR}/oryol-webpage/websamples.yml "- name: ${name}\n  desc: ${desc}\n  type: ${type}\n  image: ${CMAKE_CURRENT_LIST_DIR}/${image}\n  src: ${src}\n")
endmacro()

