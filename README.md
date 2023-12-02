# Nimble IDE Suite

## Application list

- [NimbleLIB](#nimblelib)
- [NimbleIDE](#nimbleide)
- [TestNimbleIDE](#testnimbleide)

## NimbleLIB

NimbleLIB is the library of modules used by NimbleIDE and TestNimbleIDE. It contains the following modules:

## Screen

This module is used to create a screen buffer and display it on the screen. It is used by the `NimbleIDE` and `TestNimbleIDE` applications.

## NimbleIDE

The main IDE, linked with NimbleLIB. It contains the following modules:

TODO: Add module list

## TestNimbleIDE

Tests the modules developed in NimbleIDE and NimbleLIB.

NimbleLIB does not have it's own test suite, this is handled in the NimbleIDE test suite.

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
