cmake_minimum_required(VERSION 3.25)
project(cpp_intro_exercises LANGUAGES C CXX)

# Every exercise is built with modern C++ (C++23 gives us std::print / std::println).
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_GRAPHICAL_EXERCISES "Build the raylib-based exercises of parts 13 and 14" OFF)
option(BUILD_TESTED_EXERCISES "Build exercises that come with Catch2 unit tests" ON)

if(BUILD_TESTED_EXERCISES)
    include(FetchContent)
    FetchContent_Declare(Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.7.1)
    FetchContent_MakeAvailable(Catch2)
    enable_testing()
endif()

if(BUILD_GRAPHICAL_EXERCISES)
    include(FetchContent)
    FetchContent_Declare(raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(raygui
        GIT_REPOSITORY https://github.com/raysan5/raygui.git
        GIT_TAG 4.0)
    FetchContent_MakeAvailable(raylib raygui)
    # raygui is a single header; a program defines RAYGUI_IMPLEMENTATION in one .cpp file.
    add_library(raygui INTERFACE)
    target_include_directories(raygui SYSTEM INTERFACE ${raygui_SOURCE_DIR}/src)
    target_link_libraries(raygui INTERFACE raylib)
endif()

if(MSVC)
    set(EXERCISE_WARNINGS /W4 /utf-8)
else()
    set(EXERCISE_WARNINGS -Wall -Wextra)
endif()

# Common settings for every exercise target. The $<1:...> generator expression keeps
# multi-config generators (Visual Studio) from adding a Debug/ or Release/ subfolder.
function(exercise_defaults target)
    target_compile_options(${target} PRIVATE ${EXERCISE_WARNINGS})
    set_target_properties(${target} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY $<1:${EXERCISE_OUTPUT_DIR}>)
endfunction()

# An exercise directory is built in one of two ways:
#  * it has its own CMakeLists.txt  -> add_subdirectory (tests, raylib, data files ...)
#  * otherwise                      -> one executable from all *.cpp files in it
file(GLOB PART_DIRS LIST_DIRECTORIES true ${CMAKE_CURRENT_SOURCE_DIR}/part*)
foreach(part_dir IN LISTS PART_DIRS)
    file(GLOB EXERCISE_DIRS LIST_DIRECTORIES true ${part_dir}/*)
    foreach(ex_dir IN LISTS EXERCISE_DIRS)
        if(NOT IS_DIRECTORY ${ex_dir})
            continue()
        endif()
        get_filename_component(part_name ${part_dir} NAME)
        get_filename_component(ex_name ${ex_dir} NAME)
        set(target "${part_name}_${ex_name}")

        # Each exercise gets its own output folder: build/partNN/<exercise>/<exercise>
        # Data files (*.txt, *.csv, *.tsv, *.png, *.wav) are copied next to the program, so run it from there.
        set(EXERCISE_OUTPUT_DIR ${CMAKE_BINARY_DIR}/${part_name}/${ex_name})
        file(GLOB data_files ${ex_dir}/*.txt ${ex_dir}/*.csv ${ex_dir}/*.tsv ${ex_dir}/*.png ${ex_dir}/*.wav)
        list(FILTER data_files EXCLUDE REGEX "CMakeLists\\.txt$")
        if(data_files)
            file(COPY ${data_files} DESTINATION ${EXERCISE_OUTPUT_DIR})
        endif()

        if(EXISTS ${ex_dir}/CMakeLists.txt)
            if(EXISTS ${ex_dir}/.graphical AND NOT BUILD_GRAPHICAL_EXERCISES)
                continue()
            endif()
            if(EXISTS ${ex_dir}/.tested AND NOT BUILD_TESTED_EXERCISES)
                continue()
            endif()
            # The exercise's own CMakeLists.txt uses EXERCISE_TARGET as its main target
            # name and calls exercise_defaults() on every target it creates.
            set(EXERCISE_TARGET ${target})
            add_subdirectory(${ex_dir} ${CMAKE_CURRENT_BINARY_DIR}/_cmake/${part_name}/${ex_name})
            set_target_properties(${target} PROPERTIES OUTPUT_NAME ${ex_name})
        else()
            # all *.cpp files of the exercise, also in subfolders (chapter 11 uses folders)
            file(GLOB_RECURSE sources CONFIGURE_DEPENDS ${ex_dir}/*.cpp)
            add_executable(${target} ${sources})
            target_include_directories(${target} PRIVATE ${ex_dir})
            exercise_defaults(${target})
            set_target_properties(${target} PROPERTIES OUTPUT_NAME ${ex_name})
        endif()
    endforeach()
endforeach()
