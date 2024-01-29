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
#if 0
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::cout << "Contents of current directory: " << currentPath << "\n";
    for ( const auto& entry : std::filesystem::directory_iterator( currentPath ) )
    {
        std::cout << entry.path() << "\n";
    }
#endif
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

    if ( false )
    {
        // test the dialog...
        IDEDialog   winDialog;
        std::string dialogString = "Test Dialog";
        winDialog.initDialog( 15, 5, 50, 15, COLOR_BLACK, COLOR_WHITE );

        winDialog.colourWindow( COLOUR_INDEX( IDE_COL_FG_BLACK, IDE_COL_BG_YELLOW ), true );
        winDialog.print( 3, 4, "Test Dialog" );
        winDialog.print( 3, 5, "Press 'q' to continue" );
        winDialog.title( dialogString );
        winDialog.status( "Status Bar Text" );
        winDialog.setVerticalScroll();
        winDialog.drawDialog();

        winDialog.refresh();

        uint32_t key = 0;
        while ( key != 'q' )
        {
            key = getch();
            delay_output( DELAYSIZE );
        }
    }

    if ( false )
    {
        IDEFileDialog winFileDialog;
        winFileDialog.initLoader( "./", "TEST.TXT", "Load a file to edit" );
        uint32_t colour = COLOUR_INDEX( winFileDialog.getInkColour(), winFileDialog.getPaperColour() );
        winFileDialog.colourWindow( colour, true );
        winFileDialog.drawDialog();

        winFileDialog.refresh();

        uint32_t key = 0;
        while ( key != 'q' )
        {
            key = getch();
            delay_output( DELAYSIZE );
        }
        refresh();
    }

    winEditorStatus.display();
    winEditorProject.display();
    winEditorTitle.display();
    winLineNumbers.display();
    winEditor.displayEditor();
    winEditorHex.display();
    wrefresh( winEditorHex.getWindow() );

    bool     bHexWindow = false;
    uint32_t key        = 0;
    MEVENT   event;

    while ( key != 'q' )
    {
        bool forceUpdate = false;
        key              = getch();
        delay_output( DELAYSIZE );

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
        if ( bHexWindow == true )
        {
            winEditorHex.display();
        }
        else
        {
            /*if ( event.bstate & BUTTON0_CLICKED )
            {
                winEditor.setCursorPosition( event.x, event.y );
            }
            if ( event.bstate & BUTTON3_PRESSED )
            {
                winEditor.scrollEditor( true );
                forceUpdate = true;
            }
            if ( event.bstate & BUTTON4_PRESSED )
            {
                winEditor.scrollEditor( false );
                forceUpdate = true;
            }*/
            if ( winEditor.processKeyEdit( key ) == true || forceUpdate == true )
            {
                winEditor.displayEditor();
                winLineNumbers.display();
            }
            winEditor.processMouse();
            winEditor.processDisplay();
        }

        // display the other windows...
        winEditorTitle.display();
        winEditorStatus.display();
        winEditorProject.display();
    }
    curs_set( 1 );

#if 0

    CursesMenu menu;

    // setup the menu text...
    std::string menuTitle    = "Nimble IDE : Version 0.0.1";
    std::string menuFooter   = "Navigation: Arrow Keys, Enter to Select, Q to Quit";
    std::string menuSubTitle = "Main Menu";
    menu.setMenuTitle( menuTitle );
    menu.setMenuFooter( menuFooter );
    menu.setMenuSubTitle( menuSubTitle );

    // setup  and run the menu options...
    std::vector<std::string> meniItems = { "New Project", "Open Project", "Save Project", "Save Project As", "Build Project", "Run Project", "Exit" };
    menu.setMenuOptions( meniItems );

    // check that menu only quits on Exit
    int32_t optionSelected = menu.processMenu();
    switch ( optionSelected )
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        {
            std::stringstream message;
            message << "User selected Exit from the menu with " << optionSelected + 1;
            ErrorHandler::getInstance().LogMessage( message.str() );
            break;
        }
    }
#endif
    // Return success
    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
// End of file: main.cpp
//-----------------------------------------------------------------------------
