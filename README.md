# Nimble IDE Suite

## IMPORTANT NOTE

This is in initial development, the project has only just started.

* develop branch will always have a buildable project.
* development is via issues and created branchs from develop.
* releases will go to the main branch, as and when
 

## Application list

- [NimbleLIB](#nimblelib)
- [NimbleIDE](#nimbleide)
- [TestNimbleIDE](#testnimbleide)
- [TestNimbleLIB](#testnimblelib)

## NimbleLIB

NimbleLIB is the library of modules used by NimbleIDE and TestNimbleIDE. It contains the following modules:

### Screen

This module contains basic support for screen clear, displaying text and moving the cursor.

Basic ASCII extended codes are used to clear, write to and move the cursor on the screen.

### Curses

The Curses module is used to create a screen buffer and display it on the screen. It is used by the `NimbleIDE` and `TestNimbleIDE` applications.

Curses supports not only the screen display and handling, but also windows and input handling.

### ErrorHandling

This static class handles all errors that occur in the application. It can be used to log errors to a file or to the screen.

### Utilities

Functionality that is used by multiple modules is placed in the Utilities module.

#### Global

Defines and data that are used within all the modules are placed in the Global module.

#### Logger

Linked into the ErrorHandling module, this module handles logging to a file.

#### Framework

This module will handle the framework for the hardware.
 

## NimbleIDE

The main IDE, linked with NimbleLIB. It currently tests the development of the NimbleLIB modules.


## TestNimbleIDE

Tests the modules developed in NimbleIDE and NimbleLIB.

## TestNimbleLIB

Complete tests for the NimbleLIB modules.
Currently only tests the Screen and ErrorHandling modules.

## Pre-requisites

- CMake - for creating and building the projects.
- Visual Studio 2022 - for building the projects.
- Git - for cloning the repository.
- Doxygen - for generating the documentation.
- .Net 7.0 SDK - for building the projects.
- .Net 7.0 Runtime - for running the projects.

### Optional

- Visual Studio Code - for editing the projects.
- NeoVim - for editing the projects. (I use LazyVim)
- LazyGit - for managing the repository.

## Installation

Please follow the instructions below to install the application.

Retrieve the source code from GitHub:

```bash
    git clone https://github.com/MadFly-Team/NimbleIDE.git NimbleIDE
```

## Building the applications

```bash
    cd NimbleIDE
    mkdir build
    cd build
    cmake ..
    cmake --build .
```

## Running the applications

```bash
    cd NimbleIDE
    ./build/NimbleIDE/Debug/NimbleIDE.exe
```

Run the tests:

```bash
    cd NimbleIDE
    ./build/NimbleIDE/TestNimbleIDE/Debug/TestNimbleIDE.exe
```
