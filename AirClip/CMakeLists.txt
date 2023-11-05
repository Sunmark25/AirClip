cmake_minimum_required(VERSION 3.21)
project(AirClip)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        AirClip AirClipServer.cpp
        AirClipServer.h
        NetworkConnection.cpp
        NetworkConnection.h
        User.cpp
        UserManager.cpp
        DeviceInfo.cpp
        Device.cpp
        UI.cpp
        DatabaseController.cpp
        ClipboardHelper.cpp
        ClipboardHelper.h
)
