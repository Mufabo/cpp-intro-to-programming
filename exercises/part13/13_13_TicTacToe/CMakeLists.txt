# A graphical exercise: built only with -DBUILD_GRAPHICAL_EXERCISES=ON
file(GLOB_RECURSE sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(${EXERCISE_TARGET} ${sources})
target_include_directories(${EXERCISE_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${EXERCISE_TARGET} PRIVATE raylib raygui)
exercise_defaults(${EXERCISE_TARGET})
