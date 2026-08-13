cmake_minimum_required(VERSION 3.22)

project(PhysicsEngine VERSION 1.0 LANGUAGES CXX)

# --------------------------------------------------
# C++ standard
# --------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --------------------------------------------------
# SFML dependency
# --------------------------------------------------

set(SFML_BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TEST_SUITE OFF CACHE BOOL "" FORCE)

option(ENGINE_FETCH_DEPS "Download project dependencies" OFF)

if(ENGINE_FETCH_DEPS)

    include(FetchContent)

    FetchContent_Declare(
        SFML
        URL https://github.com/SFML/SFML/archive/refs/tags/3.0.2.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        SOURCE_DIR "${CMAKE_SOURCE_DIR}/.deps/sfml-src"
        BINARY_DIR "${CMAKE_SOURCE_DIR}/.deps/sfml-build"
    )

    FetchContent_MakeAvailable(SFML)

else()

    if(NOT EXISTS "${CMAKE_SOURCE_DIR}/.deps/sfml-src/CMakeLists.txt")
        message(FATAL_ERROR
            "SFML dependency not found.\n"
            "Run 'engine deps' first."
        )
    endif()

    add_subdirectory(
        "${CMAKE_SOURCE_DIR}/.deps/sfml-src"
        "${CMAKE_SOURCE_DIR}/.deps/sfml-build"
    )

endif()

# --------------------------------------------------
# Engine executable
# --------------------------------------------------

add_executable(engine

    src/main.cpp

    src/physics/PhysicsObject.cpp
    src/physics/PhysicsWorld.cpp

    src/input/InputHandler.cpp

    src/rendering/Renderer.cpp

    src/collision/Collider.cpp
    src/collision/Collision.cpp
)


# --------------------------------------------------
# Link SFML
# --------------------------------------------------

target_link_libraries(engine PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)


# --------------------------------------------------
# Output
# --------------------------------------------------

set_target_properties(engine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)


# --------------------------------------------------
# Windows: copy SFML DLLs
# --------------------------------------------------

if(WIN32)

    add_custom_command(TARGET engine POST_BUILD

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SFML::Graphics>
        $<TARGET_FILE:SFML::Window>
        $<TARGET_FILE:SFML::System>

        "${CMAKE_SOURCE_DIR}/bin"

    )

endif()