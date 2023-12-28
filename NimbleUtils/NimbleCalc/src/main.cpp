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

#include <stdint.h>
#include <iostream>
#include <sstream>
#include <string>

#undef MOUSE_MOVED

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

std::unique_ptr<CursesWin> winMain;

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
    clear();

    winMain = std::make_unique<CursesWin>( COLS, LINES, 0, 0, COLOR_WHITE, COLOR_GREEN );
    winMain->print( 0, 0, "Nimble Calculator : Version 0.0.1" );
    winMain->print( 0, LINES - 1, "Enter commands or press 'Q' to quit" );

    // test the edit box
    IDEEditBox editBox;
    editBox.initBox( 10, 10, 30, 3, COLOR_WHITE, COLOR_GREEN );
    editBox.colourWindow( 24, true );
    editBox.print( 1, 1, "Edit box test" );
    // scan key for input, quit if 'q' pressed
    uint32_t key = 0;
    while ( key != 'q' )
    {
        key = wgetch( stdscr );
        if ( key != ERR )
        {
            if ( key == 'q' || key == 'Q' )
            {
                // quit program
                break;
            }

            std::stringstream ss;
            ss << "Key pressed : " << key;
            if ( key < 128 && key > 30 )
            {
                ss << " : " << (char)key;
            }
            ss << "      ";
            winMain->print( 2, 5, ss.str() );
            winMain->draw();
        }
    }

    // Create the main window
    winMain = std::make_unique<CursesWin>( COLS, LINES, 0, 0, 2, 7 );
    winMain->colourWindow( 3, false );
    winMain->print( 0, 0, "NimbleCalculator : Version 0.0.1" );
    winMain->refresh();

    // scan for keypresses
    key = 0;
    while ( true )
    {
        key = wgetch( stdscr );

        // if a key was pressed
        if ( key != ERR )
        {
            if ( key == 'q' || key == 'Q' )
                break;
            std::stringstream ss;
            ss << "Key pressed >  " << std::hex << key << std::dec;
            if ( key >= 30 && key < 128 )
            {
                ss << " ( " << (char)key << " )        ";
            }
            winMain->print( 2, 2, ss.str() );
            winMain->refresh();
        }
    }
    endwin();
    // Return success
    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
// Internal Functionality
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// End of file: main.cpp
// ----------------------------------------------------------------------------
