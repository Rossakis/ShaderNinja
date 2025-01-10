cmake_minimum_required(VERSION 3.16)
project(ShaderNinja)

set(CMAKE_CXX_STANDARD 17)

include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT error)
if(ipo_supported)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    add_compile_options(/arch:AVX2)
endif()

# Disable unnecessary GLFW build options
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/imgui)
add_subdirectory(dependencies/glm/glm)
add_subdirectory(dependencies/SOIL2)

# Collect all source files
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS 
"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}")

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC 
    GLFW_INCLUDE_NONE=1 
    RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/" 
    PRODUCTION_BUILD=0
)

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${SOURCE_FILES})

if(MSVC)
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)
    set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"  
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Core"  
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Game"  
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Graphics"  
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Physics"  
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Scene"  
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Utilities"  
    "${CMAKE_CURRENT_SOURCE_DIR}/dependencies" 
)


# option(GLM_BUILD_LIBRARY "Build GLM as a static or shared library" ON)
# set(GLM_BUILD_LIBRARY ON CACHE BOOL "Build GLM as a static or shared library" FORCE)#we want to build glm as a static libray, not header file
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glfw glad imgui glm::glm-header-only soil2)

# Add a custom target to build and run the project
add_custom_target(run
    COMMAND $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
    DEPENDS "${CMAKE_PROJECT_NAME}"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
add_dependencies(run "${CMAKE_PROJECT_NAME}")