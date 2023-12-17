/**----------------------------------------------------------------------------

    @file       main.cpp
    @defgroup   NimbleCalc NimbleCalc
    @brief      Main entry and control point for the NimbleCalc

    @copyright  Neil Beresford 2023

Notes:

Version:

        0.0.1.0   First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Headers
//-----------------------------------------------------------------------------

// #include <windows.h>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <cstddef>
#include <functional>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <format>
#include <filesystem>
// #include <conio.h>

extern "C"
{
#include "../../../ExternalLibraries/PDCurses/curses.h"
}

#include "../../../NimbleLIB/inc/NimbleLib.h"

//-----------------------------------------------------------------------------
// Namespace access
//-----------------------------------------------------------------------------

using namespace Nimble;
using namespace Nimble::Screen;

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

#define DELAYSIZE        20
#define MAX_OPTIONS      7
#define TITLECOLOR       57 /* color pair indices */
#define MAINMENUCOLOR    ( 2 | A_BOLD )
#define MAINMENUREVCOLOR ( 3 | A_BOLD | A_REVERSE )
#define SUBMENUCOLOR     ( 4 | A_BOLD )
#define SUBMENUREVCOLOR  ( 5 | A_BOLD | A_REVERSE )
#define BODYCOLOR        6
#define STATUSCOLOR      ( 58 )
#define INPUTBOXCOLOR    8
#define EDITBOXCOLOR     ( 9 | A_BOLD | A_REVERSE )
#define A_ATTR           ( A_ATTRIBUTES ^ A_COLOR ) /* A_BLINK, A_REVERSE, A_BOLD */

//-----------------------------------------------------------------------------
// Typedefs, enums and structs
//-----------------------------------------------------------------------------

typedef void ( *FN_COMMAND )();

typedef struct
{
    std::string text;
    FN_COMMAND  function;

} MENUCOMMAND, *PMENUCOMMAND;

//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------

void display_menu( int old_option, int new_option );
void colorbox( WINDOW* win, chtype color, int hasbox );
void setcolor( WINDOW* win, chtype color );

// menu functions
void TerminateProgram();
void LoadProgramAndDisplay();
void ResetScreenToMenu();

//-----------------------------------------------------------------------------
// Variables
//-----------------------------------------------------------------------------

std::unique_ptr<CursesWin> winTitle;
std::unique_ptr<CursesWin> winStatus;

WINDOW*                    winMenu;
WINDOW*                    winBody;

int                        old_option = -1, new_option = 0, ch;

//-----------------------------------------------------------------------------
// External Functionality
//-----------------------------------------------------------------------------

int main( int argc, char* argv[] )
{
    setlocale( LC_ALL, "" );
    initscr();

    keypad( stdscr, TRUE );
    nodelay( stdscr, TRUE );
    noecho();
    start_color();
    CursesColour::getInstance().init();

    endwin();
    // Return success
    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
// Internal Functionality
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// End of file: main.cpp
//-----------------------------------------------------------------------------
