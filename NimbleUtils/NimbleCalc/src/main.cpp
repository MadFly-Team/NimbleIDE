/**----------------------------------------------------------------------------

    @file       main.cpp
    @defgroup   NimbleCalc NimbleCalc
    @brief      Main entry and control point for the NimbleCalc

    @copyright  Neil Beresford 2023

Notes:

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
    // iniialise the curses screen
    setlocale( LC_ALL, "" );
    initscr();
    keypad( stdscr, TRUE );
    nodelay( stdscr, TRUE );
    noecho();

    // start the colour system and clear the screen, turning off the cursor
    start_color();
    CursesColour::getInstance().init();
    clear();
    curs_set( 0 );

    // create the main window
    winMain = std::make_unique<CursesWin>( COLS, LINES, 0, 0, COLOR_WHITE, COLOR_GREEN );
    winMain->print( 0, 0, "Nimble Calculator : Version 0.0.1" );
    winMain->print( 0, LINES - 1, "Enter commands or press 'Q' to quit" );

    // test the edit box
    IDEEditBox editBox;
    editBox.initBox( 10, 10, 60, 3, COLOR_WHITE, COLOR_GREEN ); // TODO remove the color params
    editBox.colourWindow( COLOUR_INDEX( IDE_COL_FG_WHITE, IDE_COL_BG_BLACK ), true );
    editBox.print( 1, 1, "Edit box test" );

    // scan key for input, quit if 'q' pressed
    uint32_t key = 0;
    while ( key != 'q' )
    {
        // check for key press
        delay_output( 25 );
        key = wgetch( stdscr );

        // pass the key to the edit box
        editBox.process( key );

        // process the key within the main window
        if ( key != ERR )
        {
            if ( key == 'q' || key == 'Q' )
            {
                // quit program
                break;
            }

            // print the key to the screen
            std::stringstream ss;
            ss << "Key pressed : " << key;
            if ( key < 128 && key > 30 )
            {
                ss << " : " << (char)key;
            }
            ss << "      ";
            ss << "Cursor position : " << editBox.getLineCursor() << "      ";
            winMain->print( 2, 5, ss.str() );
            winMain->draw();
        }
    }

    // terminate the program
    curs_set( 1 );
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
