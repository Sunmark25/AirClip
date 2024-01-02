# AirClip

## About AirClip

AirClip is a server/client application designed for efficient clipboard history management
and synchronization across various devices and operating systems. Developed using modern C++, SQL and the Wt library,
it offers a user-friendly interface and robust features for both individual and collaborative work environments.

*Also see the AirClip [Windows Client](https://github.com/yxie447/WindowsClient) which is designed to connect to the
AirClip server.*

For any inquiries, feedback, or contributions, please feel free to contact the project's authors listed in the "Authors"
section below.

## Table of Contents

- [About AirClip](#about-airclip)
- [Key Features](#key-features)
- [Getting Started](#getting-started)
    - [Required Hardware](#required-hardware)
    - [Required Libraries and Third-Party Tools](#required-libraries-and-third-party-tools)
    - [Building from Source Code](#building-from-source-code)
- [Running the Application](#running-the-application)
    - [Running in the Background](#running-in-the-background)
        - [How to Run in the Background](#how-to-run-in-the-background)
        - [Controlling Background Processes](#controlling-background-processes)
        - [Viewing the Log File](#viewing-the-log-file)
- [Usage Guide](#usage-guide)
    - [Getting Started with AirClip](#getting-started-with-airclip)
    - [Managing Clipboard History](#managing-clipboard-history)
- [Troubleshooting](#troubleshooting)
    - [Common Issues and Solutions](#common-issues-and-solutions)
    - [Frequently Asked Questions (FAQs)](#frequently-asked-questions-faqs)
- [Authors](#authors)

## Key Features

- **Clipboard History Management**: Easily access and manage your previously copied text or images.
- **Cross-Device Synchronization**: Seamlessly synchronize clipboard content across different devices and operating
  systems.
- **User and Device Management:** Integrated management of user accounts and devices for personalized experience.
- **Web Application Interface:** Accessible via a web interface, providing flexibility and ease of use.
- **Secure Data Handling:** Emphasis on security and privacy in storing and transmitting clipboard data.

## Getting Started

To **build and run** the AirClip server, you will need the following hardware, libraries and tools:

### Required Hardware

- A system with a Unix based operating system (OS) installed is required. The recommended OS is Debian as AirClip was
  developed on a Debian installation.
- AirClip server was designed to be light-weight and was developed using a Raspberry Pi 4 Model B with 4 GB of RAM. So
  the majority of systems will be compatible.
    - ***NOTE:** For macOS currently you can only connect on using localhost, devices on the local network are unable to
      see
      AirClip server when ran from macOS.*

### Required Libraries and Third-Party Tools

1. **Wt**: A C++ library for developing web applications.
    - Version: (Refer to Wt's official documentation for compatible versions)
    - [Official Website](https://www.webtoolkit.eu/wt)
    - Installation: Follow the installation guidelines provided by the official Wt documentation.

2. **SQLite3**: A C library that provides a lightweight disk-based database.
    - [Official Website](https://www.sqlite.org/)
    - Installation:

        - Depending on your OS, you can typically use a package manager. For example, on Ubuntu/Debian you can use the
          command:
          ```
          sudo apt-get install libsqlite3-dev
          ```

        - On macOS, it is built-in.

3. **Asio** (Required for Crowcpp):
    - This library is essential for the network/server functionalities of Crowcpp.
    - Installation:

        - Depending on your OS, you can typically use a package manager. For example, on Ubuntu/Debian you can use the
          command:
          ```
          sudo apt-get install libasio-dev
          ```

        - On macOS you can use:
          ```
          brew install asio
          ```

4. **Qt**: A framework for cross-platform application and UI development
    - Used for developing sophisticated GUI applications.
    - [Official Website](https://www.qt.io/)
    - Installation: Follow the installation guidelines provided on the Qt website. Ensure compatibility with the version
      used in AirClip.

### Building from Source Code

#### Prerequisites

- A modern C++ compiler (e.g., GCC, Clang)
- CMake (Version 3.26 or higher recommended)
- Wt Library and its dependencies
- SQLite3
- Qt 6.6
- Asio

## Running the Application

1. **Clone the Repository:** Begin by cloning the AirClip repository to your local machine.
    ```
    git clone https://github.com/Sunmark25/AirClip.git
    ```

2. **Navigate to the Directory:** Change to the directory containing the source code.
    ```
    cd AirClip
    ```

3. **Create a Build Directory:** It's a good practice to keep build files separate from the source. Do this by creating
   a directory where the build files will be generated.
    ```
    mkdir build
    ```
    ```
    cd build
    ```

4. **Run CMake:** Use CMake to generate the build system.

   a. If Wt is installed in the standard directory, simply run:
    ```
    cmake ..
    ```

   b. Otherwise, if Wt is not installed in the standard directory, then you'll need to run the command below. And you'll
   to replace `[path_to_wt_config]` with the path to your `WtConfig.cmake` or `wt-config` file if it's not in the
   default system:
    ```
    cmake .. -DCMAKE_PREFIX_PATH=[path_to_wt_config]
    ``` 

5. **Build the project:** Compile the project using the build system generated by CMake.
    ```
    make
    ```

6. **Run the Application:**: After a successful build, you can run AirClip from the build directory:
    ```
    ./AirClip
    ```

### Running in the Background

#### How to Run in the Background

- You can run the AirClip server in the background just by adding "&" to the same command used to run in before:
  ```
  ./AirClip &
  ```

- However, the above isn't very useful as it still outputs to the terminal and AirClip quits when you close the terminal
  session. A slightly more useful way to background it is by running it like so:
  ```
  ./AirClip >server.log 2>&1 &
  ```
    - This will background the program and output to a log file. See [Viewing the Log File](#viewing-the-log-file) to
      learn how to view the log file. Note `2>&1` redirects errors to the same file, alternatively you could send them
      to a different file by doing `2>error.log`. You could also discard the output by changing what is after ">" to
      `/dev/null`. The ">" redirect also overwrites the file each time, you can change this to ">>" to prevent that.
      Finally, this [StackExchange](https://askubuntu.com/a/731237) post has other ways you can customize the output.
    - Also, an **IMPORTANT NOTE** the log file could get quite big, so you should only do that for short periods as it
      could use up a lot of storage and also add **PERMANENT** wear on your storage device, this is especially
      worry-some on SD cards. So running the following is better to prevent these issues:
      ```
      ./AirClip >/dev/null 2>&1 & disown
      ```

- To level up the background capabilities once more, you can add `disown` to detach the program from your terminal and
  now the OS won't kill your task when you close your shell or log out! Which can be done like so:
  ```
  ./AirClip >server.log 2>&1 & disown
  ```

#### Controlling Background Processes

- Now you're probably thinking, "WOW this is great!" (or maybe not) but you might also be wondering, how do you interact
  with the program now that it isn't running in the foreground of the terminal. Well fear not as I will go over how you
  can see the background program and how to end it.
- Enter stage, jobs!
    - You may have noticed after running the program in the background it outputted a line like this `[1] 1234` this is
      the job number and the process id, these will be used to interact with the background process (program).
    - You can also view the list of processes running in the background, by running the following which shows the list
      of processes running for your terminal session, where the number in "[]" is the job id:
      ```
      jobs
      ```

    - Now to bring this process back to the foreground you can run the following, where <job-id> is your job id from
      running `jobs`:
      ```
      fg %<job-id>
      ```
        - Now it will be running again in the foreground. You stop the program and have the ability to start again by
          pressing _ctrl + z_.

    - To send it back to the background again run, this will also start it if the process is stopped:
      ```
      bg %<job-id>
      ```

    - Similarly to the previous commands you can run the following to kill/end the process:
      ```
      kill %<job-id>
      ```

- Using the jobs command and job id is great but if you used `disown` in your background command and logged off, when
  you come back running `jobs` will likely show nothing. But fear not because there is a solution for this too!]
- Enter center stage, processes!
    - Like mentioned in the jobs section, the background task (and any task in general) has a process id (PID), if you
      recall when backgrounding the program the jobs id AND the process id was given to us. If you know the PID,
      then great you can continue. However, if you closed the terminal completely, this PID will be lost. But fear not
      again because you guessed it... there is a solution to this.
    - To determine the PID of the background process you can run:
       ```
       pidof AirClip
       ```
      
    - There are other ways to find the PID as well such as the following, which shows all processes running for user:
      ```
      ps -U <username>
      ```

    - Now that you have the PID you can interact with the process similar to jobs but in a more limited manner, and by
      that I mean the only option you have is to kill it... Seems a little harsh if you ask me... Anyways, to do this run:
      ```
      kill <PID>
      ```
        - I will also mention there are ways around this limitation, such as using the program "screens" but that is out
          of the scope of this documentation

#### Viewing the Log File

- Whether the program is running or not you may want to view the log file. You can view the whole thing using a command
  like `cat server.log` or `nano server.log`. However, the file can be quite long, and it is likely more useful
  to view the newest data first, to do this run:
  ```
  tail -n <number_of_lines> server.log
  ```
    - Note, "-n <number-of-lines>" is optional but by passing in a number you can change the default number of lines
      returned from 10 to however many you'd like

## Usage Guide

### Getting Started with AirClip

- **Accessing the Web Interface:** Open your web browser and navigate to the AirClip application URL.
- **Logging In:** Use your credentials to log in, or register if you're a new user.

### Managing Clipboard History

- **Viewing Clipboard History:**
    - Access your clipboard history via the dashboard.

- **Synchronizing Clipboard Across Devices**
    - Setting Up: Ensure AirClip is installed on all devices you want to synchronize.
    - Sync in Action: Copy items on one device and find them available on all other connected devices.

## Troubleshooting

### Common Issues and Solutions

- App Not Syncing: Check your internet connection and ensure all devices are logged into the same account.
- Installation Errors: Verify system requirements and ensure all dependencies are installed.

### Frequently Asked Questions (FAQs)

- Q: Can I use AirClip on multiple devices simultaneously?
    - A: Yes, AirClip supports multi-device synchronization.

## Authors

- Jarrett Norman Joseph Boersen (jboerse2@uwo.ca)
- Robert Ghita (rghita@uwo.ca)
- Yaopeng Xie (yxie447@uwo.ca)
- Binchi Zhang (bzhan484@uwo.ca)
- Tingrui Zhang (tzhan425@uwo.ca)
