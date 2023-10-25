cmake_minimum_required(VERSION 3.23)
project(AirClip)

set(CMAKE_CXX_STANDARD 20)

add_executable(AirClip AirClipServer.cpp
        UserManager.cpp
        UserManager.h
        User.cpp
        User.h
        DeviceInfo.cpp
        DeviceInfo.h
        Device.cpp
        Device.h
        UI.cpp
        UI.h
        ClipboardEntry.cpp
        ClipboardEntry.h
        ClipboardHelper.cpp
        ClipboardHelper.h
        NetworkConnection.cpp
        NetworkConnection.h
        DatabaseController.cpp
        DatabaseController.h)
