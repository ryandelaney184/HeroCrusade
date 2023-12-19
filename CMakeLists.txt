#-----------------------------------------------------------------------------------------------------------------------
# Hero Crusade CMake
# Description: This CMake will build the project based on the desired configuration. This will allow you to choose
# which library to use for rendering graphics, and allow you to choose if you want to build for VR. After that it will
# find and link to the local libraries found in the libraries folder. Then will build the game, and copy the DLL files
# if building on Windows.
#
# Developer Notes:
# You need to download the necessary libraries to build this project check the README in the libraries folder. Please
# don't mess with the library paths,include, libraries paths or any other variable not listed below this may break the
# CMake project.
#
# Option Details
# Vulkan - Will render the game using Vulkan API. Need to select this or OpenGL, and you can't select both.
# OpenGL - Will render the game using OpenGL. Need to select this or Vulkan, and you can't select both.
# VR - Will allow the game to be run as a VR game. This only works with Vulkan selected.
# Debug - Will print out debugging messages when building the CMake
#
#
# Author: Ryan Delaney
# Version: 0.0.1
#-----------------------------------------------------------------------------------------------------------------------
# Setting up the initial CMake project
cmake_minimum_required(VERSION 3.26)
project(HC)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if (${Debug})
    message("[HeroCrusade]: Setting up the initial project.")
    message("[HeroCrusade]: Done.")
endif ()
#-----------------------------------------------------------------------------------------------------------------------
# Setting up the config variables
#-----------------------------------------------------------------------------------------------------------------------

# Static Variables
# Determining the bit size
if (${CMAKE_SIZEOF_VOID_P} EQUAL 8)
    set(BIT_SIZE "64")
else()
    set(BIT_SIZE "86")
endif ()

# Sets the build type name for the build output folder structure
if(${OpenGL})
    set(BUILD_TYPE "OpenGL")
endif ()

if(${Vulkan})
    set(BUILD_TYPE "Vulkan")
endif ()

if(${VR})
    set(BUILD_TYPE "Vulkan-VR")
endif ()

# Setting build location base on OS, configuration, and architecture
set(BUILD_OUTPUT ${CMAKE_SOURCE_DIR}/build)

if(${WIN32})
    set(BUILD_OUTPUT ${BUILD_OUTPUT}/Window/${CMAKE_BUILD_TYPE}/${BUILD_TYPE}/x${BIT_SIZE}/${PROJECT_NAME})
ENDIF ()

if (${APPLE})
    set(BUILD_OUTPUT ${BUILD_OUTPUT}/macosx/${CMAKE_BUILD_TYPE}x${BIT_SIZE}/${PROJECT_NAME})
endif ()

if(${UNIX})
    set(BUILD_OUTPUT ${BUILD_OUTPUT}/linux/${CMAKE_BUILD_TYPE}x${BIT_SIZE}/${PROJECT_NAME})
endif ()

if (${Debug})
    message("[HeroCrusade]: === Computer Info === ")
    message("[HeroCrusade]: Architecture Size: ${BIT_SIZE}")
    message("[HeroCrusade]: OS - ${CMAKE_SYSTEM_NAME}")
    message("[HeroCrusade]: Build Path - ${BUILD_OUTPUT}")
    message("[HeroCrusade]: ")
    message("[HeroCrusade]: Setting up config variables")
    message("[HeroCrusade]: === Config Variables ===")
endif ()

# Settable config
set(Vulkan OFF CACHE STRING
        "Will render the game using Vulkan API. Need to select this or OpenGL, and you can't select both.")
set(OpenGL OFF CACHE STRING
        "Will render the game using OpenGL. Need to select this or Vulkan, and you can't select both.")
set(VR OFF CACHE STRING
        "Will allow the game to be run as a VR game. This only works with Vulkan selected.")
set(Debug OFF CACHE STRING
        "Will print out debugging messages when building the CMake")

if (${Debug})
    message("[HeroCrusade]: Vulkan - ${Vulkan}")
    message("[HeroCrusade]: OpenGL - ${OpenGL}")
    message("[HeroCrusade]: VR - ${VR}")
    message("[HeroCrusade]: Debug - ${Debug}")
endif ()

# Sets the build output
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_OUTPUT})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_OUTPUT})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT})

if (${Debug})
   message("[Hero Crusade]: Finished setting up / gathering config settings")
endif ()

# Define Preprocessors
if (${Debug})
    add_compile_definitions(DEBUG "")
endif ()

if(${Vulkan})
    add_compile_definitions(VULKAN "")
endif ()

if(${OpenGL})
    add_compile_definitions(OPENGL "")
endif ()

if(${VR})
    add_compile_definitions(VR "")
endif ()

#-----------------------------------------------------------------------------------------------------------------------
# Finding and linking libraries
#-----------------------------------------------------------------------------------------------------------------------

if (${Debug})
    message("[Hero Crusade]: ")
    message("[Hero Crusade]: Setting up the libraries to be found")
    message("[Hero Crusade]: == SDL 2 ==")
endif ()

# Setting local SDL2
set(SDL2_DIR "${CMAKE_SOURCE_DIR}/libraries/SDL2-2.28.3" CACHE STRING "SDL2 directory. DO NOT TOUCH" FORCE)
file(GLOB_RECURSE SDL2_LIBRARY "${SDL2_DIR}/lib/x${BIT_SIZE}/*.lib")
set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include" CACHE FILEPATH "SDL2 Include DO NOT TOUCH" FORCE)
if (${Debug})
    message("[Hero Crusade]: SDL DIR - ${SDL2_DIR}")
    message("[Hero Crusade]: SDL2_LIBRARY - ${SDL2_LIBRARY}")
    message("[Hero Crusade]: SDL2_INCLUDE_DIR - ${SDL2_INCLUDE_DIR}")
    message("[Hero Crusade]:")
endif ()

if (${Debug})
message("[Hero Crusade]: == SDL 2 Image ==")
endif ()

# Setting the local SDL2 Image
set(SDL2_IMAGE_PATH "${CMAKE_SOURCE_DIR}/libraries/SDL2_image-2.6.3" CACHE STRING "SDL2 Image directory. DO NOT TOUCH" FORCE)
file(GLOB_RECURSE SDL2_IMAGE_LIBRARIES "${SDL2_IMAGE_PATH}/lib/x${BIT_SIZE}/*.lib")
set(SDL2_IMAGE_INCLUDE_DIRS "${SDL2_IMAGE_PATH}/include" CACHE FILEPATH "SDL2 Image Include. DO NOT TOUCH" FORCE)

if (${Debug})
message("[Hero Crusade]: SDL2_IMAGE_PATH - ${SDL2_IMAGE_PATH}")
message("[Hero Crusade]: SDL2_IMAGE_LIBRARIES - ${SDL2_IMAGE_LIBRARIES}")
message("[Hero Crusade]: SDL2_IMAGE_INCLUDE_DIRS - ${SDL2_IMAGE_INCLUDE_DIRS}")
message("[Hero Crusade]:")
endif ()

if(${Debug})
message("[Hero Crusade]: == SDL 2 TTF ==")
endif ()

# Setting the local SDL2 TTF
set(SDL2_TTF_PATH "${CMAKE_SOURCE_DIR}/libraries/SDL2_ttf-2.20.2" CACHE STRING "SDL2 TTF directory. DO NOT TOUCH" FORCE)
file(GLOB_RECURSE SDL2_TTF_LIBRARY "${SDL2_TTF_PATH}/lib/x${BIT_SIZE}/*.lib")
set(SDL_TTF_INCLUDE_DIR "${SDL2_TTF_PATH}/include" CACHE FILEPATH "SDL2 TTF Include. DO NOT TOUCH" FORCE)

if(${Debug})
message("[Hero Crusade]: SDL2_TTF_PATH - ${SDL2_TTF_PATH}")
message("[Hero Crusade]: SDL2_TTF_LIBRARY - ${SDL2_TTF_LIBRARY}")
message("[Hero Crusade]: SDL_TTF_INCLUDE_DIR - ${SDL_TTF_INCLUDE_DIR}")
message("[Hero Crusade]:")
endif ()

if (${Debug})
message("[Hero Crusade]: == SDL 2 Mixer ==")
endif ()

# Setting the local SDL2 Mixer
set(SDL2_MIXER_PATH "${CMAKE_SOURCE_DIR}/libraries/SDL2_mixer-2.6.3" CACHE STRING "SDL2 Mixer directory. DO NOT TOUCH" FORCE)
file(GLOB_RECURSE SDL2_MIXER_LIBRARY "${SDL2_MIXER_PATH}/lib/x${BIT_SIZE}/*.lib")
set(SDL2_MIXER_INCLUDE_DIR "${SDL2_MIXER_PATH}/include" CACHE FILEPATH "SDL2 Mixer Include. DO NOT TOUCH" FORCE)

if(${Debug})
message("[Hero Crusade]: SDL2_MIXER_PATH - ${SDL2_MIXER_PATH}")
message("[Hero Crusade]: SDL2_MIXER_LIBRARY- ${SDL2_MIXER_LIBRARY}")
message("[Hero Crusade]: SDL2_MIXER_INCLUDE_DIR - ${SDL2_MIXER_INCLUDE_DIR}")
message("[Hero Crusade]:")
endif ()

# Setting the Vulkan library
if (${Vulkan})
    if(${Debug})
        message("[Hero Crusade]: == Vulkan ==")
    endif ()

    set(VULKAN_PATH "C:/VulkanSDK/1.3.261.1" CACHE STRING "Vulkan directory. DO NOT TOUCH" FORCE)

    if(${BIT_SIZE} STREQUAL "64")
        file(GLOB_RECURSE Vulkan_LIBRARY "${VULKAN_PATH}/Lib/*.lib")
    else ()
        file(GLOB_RECURSE Vulkan_LIBRARY "${VULKAN_PATH}/Lib32/*.lib")
    endif ()

    list(REMOVE_ITEM Vulkan_LIBRARY ${Vulkan_LIBRARY}/SDL2.lib)
    set(Vulkan_INCLUDE_DIR "${VULKAN_PATH}/include" CACHE FILEPATH "Vulkan Include. DO NOT TOUCH" FORCE)

    if(${Debug})
        message("[Hero Crusade]: VULKAN_PATH - ${VULKAN_PATH}")
        message("[Hero Crusade]: Vulkan_LIBRARY- ${Vulkan_LIBRARY}")
        message("[Hero Crusade]: Vulkan_INCLUDE_DIR - ${Vulkan_INCLUDE_DIR}")
        message("[Hero Crusade]:")
    endif ()
endif ()

# If using OpenGL add the GLEW library as well
if (${OpenGL})
    if (${Debug})
        message("[Hero Crusade]: == GLEW == ")
    endif ()

    set(GLEW_ROOT  "${PROJECT_SOURCE_DIR}/libraries/glew-2.2.0")
    set(GLEW_INCLUDE_DIR FILEPATH ${GLEW_ROOT}/include)
    if(${BIT_SIZE} STREQUAL "64")
        set(GLEW_LIBRARIES "${GLEW_ROOT}/lib/Release/x64")
    else ()
        set(GLEW_LIBRARIES ${GLEW_ROOT}/lib/Release/Win32)
    endif ()

    if(${Debug})
        message("[Hero Crusade]: GLEW_ROOT - ${GLEW_ROOT}")
        message("[Hero Crusade]: GLEW_LIBRARIES - ${GLEW_LIBRARIES}")
        message("[Hero Crusade]: GLEW_INCLUDE_DIR - ${GLEW_INCLUDE_DIR}")
    endif ()
endif ()


if(${VR})
    if (${Debug})
        message("[Hero Crusade]: == OpenVR ==")
    endif ()
    set(OPENVR_ROOT_DIR "${PROJECT_SOURCE_DIR}/libraries/openvr-master")
    set(OpenVR_INCLUDE_DIR ${OPENVR_ROOT_DIR}/headers)

    if (${Debug})

        message("[Hero Crusade]: OPENVR_PATH - ${OPENVR_ROOT_DIR}")
        message("[Hero Crusade ]: OpenVR_INCLUDE_DIR - ${OpenVR_INCLUDE_DIR}")
    endif ()

    if (${WIN32})
        set(OpenVR_LIBRARY ${OPENVR_ROOT_DIR}/lib)
        if (${BIT_SIZE} STREQUAL "86")
            file(GLOB_RECURSE OpenVR_LIBRARY ${OpenVR_LIBRARY}/win32)
        else ()
            set(OpenVR_LIBRARY ${OpenVR_LIBRARY}/win64)
        endif ()
    endif ()

    if (${Debug})
        message("[Hero Crusade]: OpenVR_LIBRARY- ${OpenVR_LIBRARY}")
        message("[Hero Crusade]:")
    endif ()
endif ()

if (${Debug})
message("[Hero Crusade]:Finding the libraries")
endif ()

# Finding Libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

if (${Vulkan})
    find_package(Vulkan REQUIRED)
endif ()

if (${OpenGL})
    find_package(OpenGL REQUIRED)
    find_package(GLEW REQUIRED)
endif ()

if(${VR})
    find_package(OpenVR REQUIRED)
endif ()
if (${Debug})
message("[Hero Crusade]: Done")
endif ()
#-------------------------------------------------------------------------------
# Building and linking
#-------------------------------------------------------------------------------

if (${Debug})
message("[Hero Crusade]: Finding the game src")
endif ()

# Load game files
file(GLOB_RECURSE game_file src/*.hpp src/*.h src/*.cpp src/*.c)

if (${Debug})
message("[Hero Crusade]:Done")
message("[Hero Crusade]:Building game")
endif ()

set(PROJECT_NAME "${PROJECT_NAME}${VERSION}-${BUILD_TYPE}")
# Compiling game code
add_executable(${PROJECT_NAME} ${game_file})

if (${Debug})
message("[Hero Crusade]:Done")
endif ()

target_include_directories(${PROJECT_NAME} PUBLIC
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL_TTF_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARY}
        ${SDL2_MIXER_LIBRARY})

if(${Vulkan})
    target_include_directories(${PROJECT_NAME} PUBLIC
            ${Vulkan_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME}
            ${Vulkan_LIBRARIES})

else()
    target_include_directories(${PROJECT_NAME} PUBLIC
            ${OPENGL_INCLUDE_DIR}
            ${GLEW_INCLUDE_DIRS}
    )
    target_link_libraries(${PROJECT_NAME}
            ${OPENGL_LIBRARIES}
            ${GLEW_LIBRARIES})
endif ()

if(${VR})
    set(VR_LIB ${OPENVR_LIBRARY})

    target_include_directories(${PROJECT_NAME} PUBLIC
            ${OpenVR_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME}
            ${VR_LIB})
endif ()

#-------------------------------------------------------------------------------
# Post compile
#-------------------------------------------------------------------------------
if (${WIN32})

    # Copys DLL to the build output.
    file(GLOB_RECURSE DLL
            "${SDL2_DIR}/lib/x${BIT_SIZE}/*.dll"
            "${SDL2_IMAGE_PATH}/lib/x${BIT_SIZE}/*.dll"
            "${SDL2_TTF_PATH}/lib/x${BIT_SIZE}/*.dll"
            "${SDL2_MIXER_PATH}/lib/x${BIT_SIZE}/*.dll"
    )

    if (${VR})
        if(${BIT_SIZE} STREQUAL "86")
            file(GLOB_RECURSE VR_DLL "${OPENVR_ROOT_DIR}/bin/win32/*.dll")
        else ()
            file(GLOB_RECURSE VR_DLL "${OPENVR_ROOT_DIR}/bin/win64/*.dll")
        endif ()

    endif ()
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${DLL}
            ${BUILD_OUTPUT})
endif ()