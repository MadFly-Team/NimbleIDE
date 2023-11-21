
/**----------------------------------------------------------------------------

    @file       main.cpp
    @defgroup   NimbleIDE Nimble IDE
    @brief      Main entry and control point for the Nimble IDE

    @copyright  Neil Beresford 2023

Notes:

Version:

        0.0.1.0   First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Headers
//-----------------------------------------------------------------------------

// #include <windows.h>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <format>
// #include <conio.h>

extern "C"
{
#include "../../ExternalLibraries/PDCurses/curses.h"
}

#include "../../NimbleLIB/inc/NimbleLib.h"

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
#define TITLECOLOR       1 /* color pair indices */
#define MAINMENUCOLOR    ( 2 | A_BOLD )
#define MAINMENUREVCOLOR ( 3 | A_BOLD | A_REVERSE )
#define SUBMENUCOLOR     ( 4 | A_BOLD )
#define SUBMENUREVCOLOR  ( 5 | A_BOLD | A_REVERSE )
#define BODYCOLOR        6
#define STATUSCOLOR      ( 5 )
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

// menu functions
void TerminateProgram();
void LoadProgramAndDisplay();

//-----------------------------------------------------------------------------
// Variables
//-----------------------------------------------------------------------------

MENUCOMMAND menuItems[ MAX_OPTIONS ] = {
    {"New Project",      LoadProgramAndDisplay},
    { "Open Project",    nullptr              },
    { "Save Project",    nullptr              },
    { "Save Project As", nullptr              },
    { "Build Project",   nullptr              },
    { "Run Project",     nullptr              },
    { "Exit",            TerminateProgram     }
};

WINDOW* winTitle;
WINDOW* winMenu;
WINDOW* winStatus;
WINDOW* winBody;

//-----------------------------------------------------------------------------
// External Functionality
//-----------------------------------------------------------------------------

int main( int argc, char* argv[] )
{
    int old_option = -1, new_option = 0, ch;

    setlocale( LC_ALL, "" );
    initscr();

    keypad( stdscr, TRUE );
    nodelay( stdscr, TRUE );
    noecho();

    start_color();

    init_pair( TITLECOLOR & ~A_ATTR, COLOR_WHITE, COLOR_CYAN );
    init_pair( MAINMENUCOLOR & ~A_ATTR, COLOR_WHITE, COLOR_CYAN );
    init_pair( MAINMENUREVCOLOR & ~A_ATTR, COLOR_WHITE, COLOR_BLACK );
    init_pair( SUBMENUCOLOR & ~A_ATTR, COLOR_WHITE, COLOR_CYAN );
    init_pair( SUBMENUREVCOLOR & ~A_ATTR, COLOR_WHITE, COLOR_BLACK );
    init_pair( BODYCOLOR & ~A_ATTR, COLOR_WHITE, COLOR_BLUE );
    init_pair( STATUSCOLOR & ~A_ATTR, COLOR_BLACK, COLOR_WHITE );
    init_pair( INPUTBOXCOLOR & ~A_ATTR, COLOR_BLACK, COLOR_CYAN );
    init_pair( EDITBOXCOLOR & ~A_ATTR, COLOR_WHITE, COLOR_BLACK );

    winTitle  = subwin( stdscr, 1, COLS, 0, 0 );
    winStatus = subwin( stdscr, 1, COLS, LINES - 1, 0 );

    colorbox( winTitle, TITLECOLOR, 0 );
    mvwaddstr( winTitle, 0, 2, "Nimble IDE : Version 0.0.1" );
    colorbox( winStatus, STATUSCOLOR, 0 );
    mvwaddstr( winStatus, 0, 2, "Status Bar : " );

    display_menu( old_option, new_option );

    while ( true )
    {
        ch = wgetch( stdscr );

        if ( ch != ERR )
        {
            if ( ch == 'q' || ch == 'Q' )
                break;

            if ( ch == KEY_UP )
            {
                old_option = new_option;
                new_option = ( new_option == 0 ) ? MAX_OPTIONS - 1 : new_option - 1;
                display_menu( old_option, new_option );
            }
            else if ( ch == KEY_DOWN )
            {
                old_option = new_option;
                new_option = ( new_option == MAX_OPTIONS - 1 ) ? 0 : new_option + 1;
                display_menu( old_option, new_option );
            }
            else if ( ch == 0xA /* KEY_ENTER */ )
            {
                if ( menuItems[ new_option ].function != nullptr )
                {
                    menuItems[ new_option ].function();
                    clear();
                    display_menu( old_option, new_option );
                }
            }
        }

        napms( DELAYSIZE );
        refresh();
    }

    endwin();

    // Return success
    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
// Internal Functionality
//-----------------------------------------------------------------------------
void setcolor( WINDOW* win, chtype color )
{
    chtype attr = color & A_ATTR; /* extract Bold, Reverse, Blink bits */

    attr &= ~A_REVERSE; /* ignore reverse, use colors instead! */
    wattrset( win, COLOR_PAIR( color & A_CHARTEXT ) | attr );
}

void colorbox( WINDOW* win, chtype color, int hasbox )
{
    int    maxy;
    chtype attr = color & A_ATTR; /* extract Bold, Reverse, Blink bits */

    setcolor( win, color );

    wbkgd( win, COLOR_PAIR( color & A_CHARTEXT ) | ( attr & ~A_REVERSE ) );

    werase( win );

    maxy = getmaxy( win );
    if ( hasbox && ( maxy > 2 ) )
        box( win, 0, 0 );

    touchwin( win );
    wrefresh( win );
}

void display_menu( int old_option, int new_option )
{
    int lmarg = ( COLS - 14 ) / 2, tmarg = ( LINES - ( MAX_OPTIONS + 2 ) ) / 2;

    if ( old_option == -1 )
    {
        int i;

        attrset( A_BOLD );
        mvaddstr( tmarg - 3, lmarg - 5, "PDCurses Test Program" );
        attrset( A_NORMAL );

        for ( i = 0; i < MAX_OPTIONS; i++ ) mvaddstr( tmarg + i, lmarg, menuItems[ i ].text.c_str() );
    }
    else
        mvaddstr( tmarg + old_option, lmarg, menuItems[ old_option ].text.c_str() );

    attrset( A_REVERSE );
    mvaddstr( tmarg + new_option, lmarg, menuItems[ new_option ].text.c_str() );
    attrset( A_NORMAL );
    attrset( COLOR_PAIR( 3 ) );
    mvaddstr( tmarg + MAX_OPTIONS + 2, lmarg - 23, "Use Up and Down Arrows to select - Enter to run - Q to quit" );
    attrset( COLOR_PAIR( 1 ) );
    refresh();
}

//-----------------------------------------------------------------------------
// Menu Functions
//-----------------------------------------------------------------------------

void TerminateProgram()
{
    endwin();
    exit( EXIT_SUCCESS );
}

void LoadProgramAndDisplay()
{
    // Open a file for reading
    std::ifstream inputFile( "example.txt" );

    // Check if the file is opened successfully
    if ( !inputFile.is_open() )
    {
        std::cerr << "Unable to open the file." << std::endl;
        return;
    }

    // Read the contents of the file into a vector of strings
    std::vector<std::string> lines;
    std::string              line;
    while ( std::getline( inputFile, line ) )
    {
        lines.push_back( line );
    }

    // Close the file
    inputFile.close();

    // display a full screen of the example text
    int nFileLine = 0;
    int nLine     = 0;

    while ( true )
    {
        int ch = wgetch( stdscr );

        if ( ch != ERR )
        {

            if ( ch == 'q' || ch == 'Q' )
            {
                return;
            }

            if ( ch == KEY_UP )
            {
                nFileLine = ( nFileLine == 0 ) ? 0 : nFileLine - 1;
            }
            else if ( ch == KEY_DOWN )
            {
                nFileLine = ( nFileLine == lines.size() - 1 ) ? lines.size() - 1 : nFileLine + 1;
            }

            clear();
            nLine = 0;
            while ( ( nLine < LINES ) && ( nLine + nFileLine < lines.size() ) )
            {
                mvaddstr( nLine, 1, lines[ nLine + nFileLine ].c_str() );
                nLine++;
            }
        }
        // napms( DELAYSIZE );
        refresh();
    }
}

//-----------------------------------------------------------------------------
// End of file: main.cpp
//-----------------------------------------------------------------------------
