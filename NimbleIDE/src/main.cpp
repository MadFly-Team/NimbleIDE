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
#include <cstddef>
#include <filesystem>
#include <functional>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <vector>
#include <string>
#include <format>
// #include <conio.h>
#include <chrono>  // chrono::system_clock
#include <ctime>   // localtime
#include <iomanip> // put_time

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

#if ( __linux__ )
#define DELAYSIZE ( 10 )
#else
#define DELAYSIZE ( 1 )
#endif
#define MAX_OPTIONS      ( 7 )
#define TITLECOLOR       ( 57 ) /* color pair indices */
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
// External Functionality
//-----------------------------------------------------------------------------

int main( int argc, char* argv[] )
{
    bool     bHexWindow = false;
    uint32_t key        = 0;

    // initialise the Curses screen and control
    setlocale( LC_ALL, "" );
    initscr();
    keypad( stdscr, TRUE );
    nodelay( stdscr, TRUE );
    noecho();
    curs_set( 0 );
    mousemask( ALL_MOUSE_EVENTS, nullptr );

    // initialise the colours
    CursesColour::getInstance().init();

    // main editor windows
    IDEEditor            winEditor;
    EditorStatusWin      winEditorStatus;
    EditorProjectWin     winEditorProject;
    EditorTitleWin       winEditorTitle;
    EditorHexWin         winEditorHex;
    EditorLineNumbersWin winLineNumbers;
    IDEManager           dialogManager;

    // setup the editor
    winEditor.init( COLS - 39, LINES - 9, 9, 4 );
    std::string filename = "test.txt";
    winEditor.start( filename );

    // setup the other windoews
    winEditorStatus.setIDEEditor( &winEditor );
    winEditorProject.setIDEEditor( &winEditor );
    winEditorTitle.setIDEEditor( &winEditor );
    winEditorHex.setIDEEditor( &winEditor );
    winLineNumbers.setIDEEditor( &winEditor );

    winEditorStatus.display();
    winEditorProject.display();
    winEditorTitle.display();
    winLineNumbers.display();
    winEditor.displayEditor();

    while ( key != 'q' )
    {
        bool forceUpdate = false;
        delay_output( DELAYSIZE );

        // display the other windows...
        winEditorTitle.display();
        winEditorStatus.display();
        winEditorProject.display();

        GControl.ProcessMouse();

        key = getch();
        if ( dialogManager.areControlsActive() == true )
        {
            dialogManager.process( key );
            if ( dialogManager.redrawNeeded() )
            {
                winEditorStatus.display( true );
                winEditorProject.display( true );
                winEditorTitle.display( true );
                winLineNumbers.display( true );
                winEditor.redrawBackground();
                winEditor.displayEditor();
                dialogManager.clearRedrawNeeded();
            }
        }
        else
        {
            if ( key == KEY_F( 1 ) )
            {
                bHexWindow = !bHexWindow;
                if ( bHexWindow == true )
                {
                    winEditor.hideWindow();
                    winLineNumbers.hideWindow();
                    winEditorHex.showWindow();
                    winEditorHex.redrawBackground();
                }
                else
                {
                    winEditor.showWindow();

                    winLineNumbers.showWindow();
                    winEditorHex.hideWindow();
                    winLineNumbers.redrawBackground();
                }
            }
            if ( key == KEY_F( 2 ) || key == KEY_F( 3 ) )
            {
                ManagerControlID dialogID = ( key == KEY_F( 2 ) ) ? ManagerControlID::ID_LoadFile : ManagerControlID::ID_LoadFile;
                dialogManager.addControl( dialogID );
            }
            if ( bHexWindow == true )
            {
                winEditorHex.display();
            }
            else
            {
                if ( winEditor.processKeyEdit( key ) == true || forceUpdate == true )
                {
                    winEditor.displayEditor();
                    winLineNumbers.display();
                }
                winEditor.processMouse();
                winEditor.processDisplay();
            }
        }
    }
    curs_set( 1 );

    // Return success
    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
// End of file: main.cpp
//-----------------------------------------------------------------------------
