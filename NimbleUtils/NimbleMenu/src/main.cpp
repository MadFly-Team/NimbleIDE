/**----------------------------------------------------------------------------

    @file       main.cpp
    @defgroup   NimbleIDE Nimble IDE
    @brief      Main entry and control point for the Nimble IDE

    @copyright  Neil Beresford 2023

Notes:

-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Headers
//-----------------------------------------------------------------------------

// #include <windows.h>
#if defined( _WIN32 )
#include <windows.h>
#include <tchar.h>
#endif
#include <memory>
#include <stdio.h>
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
#include "../inc/Modules/MenuConfig.h"

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
    int32_t optionSelected;

    // load the menu config file
    MenuConfig menuConfig;
    menuConfig.MenuConfigInit();

    // process the menu
    do {

        setlocale( LC_ALL, "" );
        initscr();

        keypad( stdscr, TRUE );
        nodelay( stdscr, TRUE );
        noecho();
        start_color();
        CursesColour::getInstance().init();

        winStatus = std::make_unique<CursesWin>( COLS, 1, 0, LINES - 1, COLOR_BLACK, COLOR_WHITE );
        winTitle  = std::make_unique<CursesWin>( COLS, 1, 0, 0, COLOR_WHITE, COLOR_BLUE );
        winTitle->colourWindow( TITLECOLOR, 0 );
        winTitle->print( 2, 0, "Nimble MENU : Version 0.0.1" );
        winStatus->colourWindow( STATUSCOLOR, 0 );
        winStatus->print( 2, 0, "Status Bar : PWD - " );
        std::filesystem::path path = std::filesystem::current_path();
        winStatus->print( 22, 0, path.string() );

        std::string strCommand;

        CursesMenu  menu;

        // setup the menu text...
        std::string menuTitle    = "Nimble Menu Application (written by Neil Beresford) : Version 0.0.1";
        std::string menuFooter   = "Navigation: Arrow Keys, Enter to Select, Q to Quit";
        std::string menuSubTitle = "Choose Selection";
        menu.setMenuTitle( menuTitle );
        menu.setMenuFooter( menuFooter );
        menu.setMenuSubTitle( menuSubTitle );

        // setup  and run the menu options...
        menu.setMenuOptions( menuConfig.GetMenuDescriptions() );

        // check that menu only quits on Exit
        optionSelected = menu.processMenu();
        endwin();

        if ( optionSelected != -1 )
        {
            strCommand = menuConfig.GetMenuCommand( optionSelected );
            system( strCommand.c_str() );

            // check if the command is a change directory command
            if ( strCommand.compare( 0, 3, "cd " ) == 0 && strCommand.compare( 0, 8, "cd build" ) != 0 )
            {
                // remove the cd command
                strCommand.erase( 0, 3 );
                // remove the newline character
                std::string::size_type pos = strCommand.find( '\n', 0 );
                if ( pos != std::string::npos )
                {
                    strCommand.erase( pos, 1 );
                }
                // change the directory
                std::filesystem::current_path( strCommand );
            }
        }

    } while ( optionSelected != -1 );

    // Return success
    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
// Internal Functionality
//-----------------------------------------------------------------------------
#if 0

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
        attrset( COLOR_PAIR( 6 ) );
        mvaddstr( tmarg - 3, lmarg - 5, "PDCurses Test Program" );
        attrset( A_NORMAL );
        attrset( COLOR_PAIR( 8 ) );

        for ( i = 0; i < MAX_OPTIONS; i++ ) mvaddstr( tmarg + i, lmarg, menuItems[ i ].text.c_str() );
    }
    else
        mvaddstr( tmarg + old_option, lmarg, menuItems[ old_option ].text.c_str() );

    attrset( A_REVERSE );
    mvaddstr( tmarg + new_option, lmarg, menuItems[ new_option ].text.c_str() );
    attrset( A_NORMAL );
    attrset( COLOR_PAIR( 7 ) );
    mvaddstr( tmarg + MAX_OPTIONS + 2, lmarg - 23, "Use Up and Down Arrows to select - Enter to run - Q to quit" );
    attrset( COLOR_PAIR( 8 ) );
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
    std::ifstream inputFile( "story.txt" );

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

    attrset( COLOR_PAIR( 7 ) );
    clear();
    nLine = 0;
    while ( ( nLine < LINES ) && ( nLine + nFileLine < lines.size() ) )
    {
        mvaddstr( nLine, 1, lines[ nLine + nFileLine ].c_str() );
        nLine++;
    }

    while ( true )
    {
        int ch = wgetch( stdscr );

        if ( ch != ERR )
        {

            if ( ch == 'q' || ch == 'Q' )
            {
                break;
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

    ResetScreenToMenu();
}

void ResetScreenToMenu()
{
    clear();
    old_option = -1;
    new_option = 0;
    winTitle->colourWindow( TITLECOLOR, false );
    winTitle->print( 2, 0, "Nimble IDE : Version 0.0.1" );
    winStatus->colourWindow( STATUSCOLOR, 0 );
    winStatus->print( 2, 0, "Status Bar : " );
    display_menu( old_option, new_option );
    refresh();

    attrset( COLOR_PAIR( 8 ) );
}
#endif

//-----------------------------------------------------------------------------
// End of file: main.cpp
//-----------------------------------------------------------------------------
