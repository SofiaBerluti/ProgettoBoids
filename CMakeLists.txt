cmake_minimum_required(VERSION 3.16)
project(Boids)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")

string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address -fno-omit-frame-pointer")

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(boids-sfml main.cpp boids.cpp vector2D.cpp)
target_link_libraries(boids-sfml PRIVATE sfml-graphics)

if (BUILD_TESTING)

  add_executable(rules.t test_rules.cpp boids.cpp vector2D.cpp)
  target_link_libraries(rules.t PRIVATE sfml-graphics)
  add_executable(vector2D.t test_vector2D.cpp vector2D.cpp)
  target_link_libraries(vector2D.t PRIVATE sfml-graphics)

  add_test(NAME rules.t COMMAND boids.t)
  add_test(NAME vector2D.t COMMAND boids.t)


endif()