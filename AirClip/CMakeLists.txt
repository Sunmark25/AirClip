cmake_minimum_required(VERSION 3.21)

# Set the name of the project (the exec file)
SET(MY_PROJECT_NAME AirClip)
project(${MY_PROJECT_NAME})

# Set the C++ version
set(CMAKE_CXX_STANDARD 20)

# Set the path to for the local software installation
set(LOCAL_SOFTWARE_DIR /usr/local)
# Include directories for the locally installed header files
include_directories(${LOCAL_SOFTWARE_DIR}/include ${Boost_INCLUDE_DIRS})
# Include link directories for libraries
link_directories(${LOCAL_SOFTWARE_DIR}/lib)

# Find the SQLite3 library
find_package(SQLite3 REQUIRED)

# Find the Wt library
find_package(Wt REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)

include(FetchContent)

# Fetch Crow
FetchContent_Declare(
        Crow
        GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
        GIT_TAG master
)
FetchContent_MakeAvailable(Crow)

# Source files
set(SOURCES
        UI.cpp
        UI.h
        DatabaseController.cpp
        DatabaseController.h
        ClipboardHelper.cpp
        ClipboardHelper.h
        ClipboardEntry.cpp
        ClipboardEntry.h
        main.cpp
        NetworkConnection.cpp
        NetworkConnection.h
)

#Include the css file
configure_file("styles.css" "styles.css")

# Create the executable
add_executable(${MY_PROJECT_NAME} ${SOURCES})

# Link against the libraries
target_link_libraries(${MY_PROJECT_NAME}
        Wt::Wt
        Wt::HTTP

        SQLite::SQLite3
        ${Boost_LIBRARIES}

        Crow::Crow
)

# Set the RPATH to include the library directory
set_target_properties(${MY_PROJECT_NAME} PROPERTIES
        INSTALL_RPATH ${LOCAL_SOFTWARE_DIR}/lib
        INSTALL_RPATH_USE_LINK_PATH TRUE
)