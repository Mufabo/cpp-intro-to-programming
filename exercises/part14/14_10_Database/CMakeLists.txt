# Downloads the SQLite amalgamation (one C file) and builds it as a library.
include(FetchContent)
FetchContent_Declare(sqlite3
    URL https://www.sqlite.org/2024/sqlite-amalgamation-3460100.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
FetchContent_MakeAvailable(sqlite3)

if(NOT TARGET sqlite3_library)
    add_library(sqlite3_library STATIC ${sqlite3_SOURCE_DIR}/sqlite3.c)
    target_include_directories(sqlite3_library SYSTEM PUBLIC ${sqlite3_SOURCE_DIR})
    find_package(Threads REQUIRED)
    target_link_libraries(sqlite3_library PUBLIC Threads::Threads ${CMAKE_DL_LIBS})
endif()

add_executable(${EXERCISE_TARGET} main.cpp TodoDao.cpp)
target_link_libraries(${EXERCISE_TARGET} PRIVATE sqlite3_library)
exercise_defaults(${EXERCISE_TARGET})
