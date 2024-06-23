cmake_minimum_required(VERSION 3.28)
project(Moneky_typer)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS FALSE)
include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         10.2.1
)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)


FetchContent_MakeAvailable(fmt)

FetchContent_MakeAvailable(SFML)


add_executable(Moneky_typer MonkeyTyper/main.cpp
        MonkeyTyper/Word.cpp
        MonkeyTyper/Word.h
        MonkeyTyper/WordGame.cpp
        MonkeyTyper/WordGame.h
        MonkeyTyper/Menu.h
        MonkeyTyper/Menu.cpp
        MonkeyTyper/Ranking.h
        MonkeyTyper/Ranking.cpp
        MonkeyTyper/Ranking.cpp
)

target_link_libraries(Moneky_typer sfml-graphics sfml-audio fmt)

add_custom_command(
        TARGET Moneky_typer
        COMMENT "copy stuff"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Moneky_typer>
        VERBATIM
)

