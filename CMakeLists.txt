cmake_minimum_required(VERSION 3.11)
project(setup)

# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#### Setup Directories ####
# Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Output all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/SFML")
set(SFML_INCS "lib/SFML/include")
link_directories("${CMAKE_BINARY_DIR}/lib/SFML/lib")

#### Practical 1 ####
add_executable(lab1_tutorial lab1_tutorial/main.cpp)
target_include_directories(lab1_tutorial PRIVATE ${SFML_INCS})
target_link_libraries(lab1_tutorial sfml-graphics)

#### Practical 2: Pong ####
add_executable(lab2_pong lab2_pong/main.cpp)
target_include_directories(lab2_pong PRIVATE ${SFML_INCS})
target_link_libraries(lab2_pong sfml-graphics)
add_custom_command(TARGET lab2_pong POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:lab2_pong>/resources)

#### Practical 3: Space Invaders
add_executable(lab3_spaceInvaders lab3_spaceInvaders/main.cpp)
target_include_directories(lab3_spaceInvaders PRIVATE ${SFML_INCS})
target_link_libraries(lab3_spaceInvaders sfml-graphics)

#### Practical 4: Tile Engine
add_executable(lab4_tileEngine lab4_tileEngine/main.cpp
    lab4_tileEngine/game_system.hpp
    lab4_tileEngine/game_system.cpp)
target_include_directories(lab4_tileEngine PRIVATE ${SFML_INCS})
target_link_libraries(lab4_tileEngine sfml-graphics)