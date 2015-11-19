# === Project Definition ===

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project("ASCII RogueLike" CXX)

set(CMAKE_CXX_STANDARD 14)

# === Build options ===

option(DEBUG_MODE
    "Prints some aditional information during the program run."
    ON
    )

# turn on all warnings (cgg/clang only, remember to delete later)
if( CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GCC")
    add_definitions ("-Wall")
endif()

option(SANITY_CHECK_ALL
    "Checks the sanity of each map before playing."
    ON
    )

# === Configuration ===
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
configure_file(
    "${PROJECT_SOURCE_DIR}/src/config.hpp.in" # template
    "${PROJECT_BINARY_DIR}/conf/config.hpp"   # output
    )
include_directories("${PROJECT_BINARY_DIR}/conf")

# === Boost ===

find_package(Boost 1.55.0 COMPONENTS system filesystem REQUIRED)
include_directories("${Boost_INCLUDE_DIR}")

# === Build Libraries ===

add_library(coordinates src/coordinates/Coordinates.cpp)
include_directories(src/coordinates)

add_library(entity src/entity/Entity.cpp)
target_link_libraries(entity coordinates map)
include_directories(src/entity)

add_library(enemy src/enemy/Enemy.cpp)
target_link_libraries(enemy coordinates entity random)
include_directories(src/enemy)

add_library(game_master src/game_master/GameMaster.cpp)
include_directories(src/game_master)

add_library(map src/map/Map.cpp)
target_link_libraries(map coordinates map_components)
include_directories(src/map)

add_library(map_components src/map_components/MapComponents.cpp)
include_directories(src/map_components)

add_library(player src/player/Player.cpp)
target_link_libraries(player coordinates enemy entity)
include_directories(src/player)

add_library(random src/random/random.cpp)
include_directories(src/random)

add_library(system src/system/system.cpp)
target_link_libraries(system ${Boost_LIBRARIES} text)
include_directories(src/system)

add_library(text src/text/text.cpp)
include_directories(src/text)

# === Build Executables ===

add_executable(main src/main)
target_link_libraries(
    main
    # program libraries
    coordinates entity enemy game_master map map_components player random system text
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
