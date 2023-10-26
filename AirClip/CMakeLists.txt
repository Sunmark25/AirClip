cmake_minimum_required(VERSION 3.23)
project(AirClip)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        AirClip AirClipServer.cpp
        NetworkConnection.cpp
        NetworkConnection.h
        AirClipServer.h
)
