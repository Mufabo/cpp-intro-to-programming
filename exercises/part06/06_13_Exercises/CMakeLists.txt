# An exercise with unit tests: the program itself, and a separate test program.
add_executable(${EXERCISE_TARGET} main.cpp)
exercise_defaults(${EXERCISE_TARGET})

add_executable(${EXERCISE_TARGET}_tests ExerciseManagementTest.cpp)
target_link_libraries(${EXERCISE_TARGET}_tests PRIVATE Catch2::Catch2WithMain)
exercise_defaults(${EXERCISE_TARGET}_tests)
add_test(NAME ${EXERCISE_TARGET}_tests COMMAND ${EXERCISE_TARGET}_tests)
