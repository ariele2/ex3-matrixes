cmake_minimum_required(VERSION 3.0.0)
project(Game)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(CMAKE_CXX_COMPILER /usr/bin/g++ CACHE PATH "" FORCE)
set(MTM_FLAGS_DEBUG "-std=c++11 -Wall -Werror -pedantic-errors")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDBUG")
set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})
add_executable(my_exe  Matrix.h Auxiliaries.cpp test_partC.cpp Character.cpp Exception.cpp Game.cpp Medic.cpp Sniper.cpp Soldier.cpp)



