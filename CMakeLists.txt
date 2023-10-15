cmake_minimum_required(VERSION 3.26)
project(Pacman)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)

file(GLOB SOURCE_FILES "${PROJECT_SOURCE_DIR}/include/*.h" "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_executable(Pacman ${SOURCE_FILES})

file(COPY resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
target_link_libraries(Pacman -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf)
