cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 20)

include(CheckIPOSupported)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) #link time optimization

if(MSVC)
    add_compile_options(/arch:AVX2) #make sure SIMD optimizations take place
endif()

project(ShaderNinja)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/imgui)
add_subdirectory(dependencies/stb_image)
add_subdirectory(dependencies/glm)

# SOURCE_FILES is defined to be a list of all the source files for the game
# So no need to add the source files by hand, since they are already added with this macro
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS 
                            "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
                            "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

add_executable("${CMAKE_PROJECT_NAME}")

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 17)
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC GLFW_INCLUDE_NONE=1)

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${SOURCE_FILES} )


if(MSVC) # If using the VS compiler...
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)
    set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") #no console
endif()

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

#enet not working yet on linux for some reason
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glfw glad imgui glm stb_image)


# Add a custom target to build and run the project
add_custom_target(run
    COMMAND "${CMAKE_PROJECT_NAME}" 
    DEPENDS "${CMAKE_PROJECT_NAME}"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

# With this, you will be able to both build and run the program with a single command "cmake --build ./build --target run  "
add_dependencies(run "${CMAKE_PROJECT_NAME}") 