# === Project Definition ===

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 14)

project("ASCII RogueLike" CXX)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)

# === Build options ===

option(DEBUG_MODE
    "Prints some aditional information during the program run."
    ON
    )

# turn on all warnings (cgg/clang only, remember to delete later)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GCC")
    add_definitions ("-Wall")
endif()

option(SANITY_CHECK_ALL
    "Checks the sanity of each map before playing."
    ON
    )

# === Configuration ===

configure_file(
    "${PROJECT_SOURCE_DIR}/src/config.hpp.in" # template
    "${PROJECT_BINARY_DIR}/conf/config.hpp"   # output
    )

include_directories("${PROJECT_BINARY_DIR}/conf")

# === Boost ===

find_package(Boost 1.55.0 COMPONENTS system filesystem REQUIRED)
include_directories("${Boost_INCLUDE_DIR}")

# === Build Libraries ===

add_library(random lib/random/random.cpp)
include_directories(lib/random)

add_library(system lib/system/system.cpp)
target_link_libraries(system ${Boost_LIBRARIES} text)
include_directories(lib/system)

add_library(text lib/text/text.cpp)
include_directories(lib/text)

# === Build Executables ===

add_executable(main
    src/main.cpp
    src/Coordinates.hpp
    src/Coordinates.cpp
    src/Enemy.hpp
    src/Enemy.cpp
    src/Entity.hpp
    src/Entity.cpp
    src/GameMaster.hpp
    src/GameMaster.cpp
    src/Map.hpp
    src/Map.cpp
    src/MapComponents.hpp
    src/MapComponents.cpp
    src/Player.hpp
    src/Player.cpp
    )
target_link_libraries(
    main
    # program libraries
    random system text
    )

# copy resources to build directory if the build is successfull
add_custom_target(
    resources ALL
    COMMAND ${CMAKE_COMMAND} -E remove_directory
        $<TARGET_FILE_DIR:main>/resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:main>/resources
    COMMENT "Copying resources folder"
    )

# === Documentation ===

# To generate the documentation with Doxygen, remember to 'make doc' after
# generating the Makefile.

find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(
        ${PROJECT_SOURCE_DIR}/doc/Doxyfile.in
        ${PROJECT_BINARY_DIR}/doc/Doxyfile
    )

    add_custom_target(
        doc #ALL
        ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/doc/Doxyfile
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)
