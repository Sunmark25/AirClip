cmake_minimum_required(VERSION 3.21)
project(AirClip)

set(CMAKE_CXX_STANDARD 20)

# Find the SQLite3 library
find_package(SQLite3 REQUIRED)

#add_executable(
#        AirClip AirClipServer.cpp
#        AirClipServer.h
#        NetworkConnection.cpp
#        NetworkConnection.h
#        User.cpp
#        UserManager.cpp
#        DeviceInfo.cpp
#        Device.cpp
#        UI.cpp
#        DatabaseController.cpp
#        ClipboardHelper.cpp
#        ClipboardHelper.h
#)

# For the DatabaseTest file
add_executable(
        AirClip DatabaseTest.cpp
        DatabaseController.cpp
        DatabaseController.h
)

# Link your target against SQLite3
target_link_libraries(AirClip SQLite::SQLite3)