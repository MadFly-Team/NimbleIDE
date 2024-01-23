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
// Forward declarations
//-----------------------------------------------------------------------------

std::string return_current_time_and_date();

//-----------------------------------------------------------------------------
// Variables
//-----------------------------------------------------------------------------

std::unique_ptr<CursesWin> winTitle;
std::unique_ptr<CursesWin> winStatus;
std::unique_ptr<CursesWin> winProject;

WINDOW*                    winMenu;
WINDOW*                    winBody;

//-----------------------------------------------------------------------------
// External Functionality
//-----------------------------------------------------------------------------

void UpdateIDEScreen()
{
    winTitle->colourWindow( COLOUR_INDEX( IDE_COL_FG_BLACK, IDE_COL_BG_WHITE ), true );
    winTitle->print( 2, 0, " Nimble IDE : Version 0.0.1 " );
    winTitle->drawVerticalLine( COLS - 23, 1, 2 );
    winStatus->colourWindow( COLOUR_INDEX( IDE_COL_FG_BLACK, IDE_COL_BG_WHITE ), true );
    winStatus->print( 2, 0, " Status Bar : Press 'q' to quit " );
    winStatus->drawVerticalLine( COLS - 37, 1, 2 );
    winProject->colourWindow( COLOUR_INDEX( IDE_COL_FG_BLACK, IDE_COL_BG_WHITE ), true );
    winProject->print( 2, 0, " Project Window " );
    winProject->drawHorizontalLine( 1, 3, 30 - 2 );
}

int main( int argc, char* argv[] )
{
    std::filesystem::path currentPath = std::filesystem::current_path();

    std::cout << "Contents of current directory: " << currentPath << "\n";

    for ( const auto& entry : std::filesystem::directory_iterator( currentPath ) )
    {
        std::cout << entry.path() << "\n";
    }

    setlocale( LC_ALL, "" );
    initscr();

    keypad( stdscr, TRUE );
    nodelay( stdscr, TRUE );
    noecho();
    curs_set( 0 );
    mousemask( ALL_MOUSE_EVENTS, nullptr );

    CursesColour::getInstance().init();

    winStatus  = std::make_unique<CursesWin>( COLS, 4, 0, LINES - 4, COLOR_BLACK, COLOR_WHITE );
    winTitle   = std::make_unique<CursesWin>( COLS, 4, 0, 0, COLOR_WHITE, COLOR_YELLOW );
    winProject = std::make_unique<CursesWin>( 30, LINES - 8, COLS - 30, 4, COLOR_WHITE, COLOR_YELLOW );

    UpdateIDEScreen();

    IDEEditBox winLineNumbers;
    IDEEditor  winEditor;
    winEditor.init( COLS - 39, LINES - 9, 9, 4 );
    std::string filename = "test.txt";
    winEditor.start( filename );
    winTitle->print( 2, 1, "EDITING MODE: ./Test.txt " );
    winLineNumbers.initBox( 0, 4, 9, LINES - 8, IDE_COL_FG_BLACK, IDE_COL_BG_WHITE );
    winLineNumbers.colourWindow( COLOUR_INDEX( IDE_COL_FG_BLACK, IDE_COL_BG_WHITE ), true );
    winLineNumbers.displayLineNumbers( winEditor.getCurrentLine() + 1, winEditor.getTotalLines() );

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
        UpdateIDEScreen();
        refresh();
    }

    winTitle->draw();
    winStatus->draw();
    winEditor.displayEditor();
    winLineNumbers.colourWindow( COLOUR_INDEX( IDE_COL_FG_BLACK, IDE_COL_BG_WHITE ), true );
    winLineNumbers.displayLineNumbers( winEditor.getCurrentLine() + 1, winEditor.getTotalLines() );

    uint32_t key = 0;
    MEVENT   event;

    while ( key != 'q' )
    {
        bool forceUpdate = false;
        key              = getch();
        delay_output( DELAYSIZE );
        mvwprintw( winStatus->getWindow(), 2, COLS - 35, "Mouse: %d, %d    ", winEditor.getMouseX(), winEditor.getMouseY() );
        /*if ( event.bstate & BUTTON1_CLICKED )
        {
            winEditor.setCursorPosition( event.x, event.y );
        }
        if ( event.bstate & BUTTON4_PRESSED )
        {
            winEditor.scrollEditor( true );
            forceUpdate = true;
        }
        if ( event.bstate & BUTTON5_PRESSED )
        {
            winEditor.scrollEditor( false );
            forceUpdate = true;
        }*/
        if ( winEditor.processKeyEdit( key ) == true || forceUpdate == true )
        {
            winEditor.displayEditor();
            winLineNumbers.displayLineNumbers( winEditor.getCurrentLine() + 1, winEditor.getTotalLines() );
        }
        winEditor.processMouse();
        winEditor.processDisplay();

        // display the time and date...
        std::string streamString = return_current_time_and_date();
        winTitle->print( COLS - 2 - streamString.length(), 1, streamString );
        mvwchgat( winTitle->getWindow(), 1, COLS - 2 - streamString.length(), streamString.length(), A_NORMAL, COLOUR_INDEX( IDE_COL_FG_YELLOW, IDE_COL_BG_WHITE ), nullptr );
        winTitle->draw();

        // display the number of lines and cursor position...
        std::stringstream strStream = std::stringstream();
        strStream << "Lines: " << winEditor.getTotalLines() << " Cursor: " << winEditor.getCursorX() << "," << winEditor.getCursorY();
        std::string linesString = strStream.str();
        linesString.resize( 34, ' ' );
        mvwprintw( winStatus->getWindow(), 1, COLS - 35, linesString.c_str() );
        mvwchgat( winStatus->getWindow(), 1, COLS - 28, 5, A_NORMAL, COLOUR_INDEX( IDE_COL_FG_GREEN, IDE_COL_BG_WHITE ), nullptr );
        mvwchgat( winStatus->getWindow(), 1, COLS - 15, 13, A_NORMAL, COLOUR_INDEX( IDE_COL_FG_GREEN, IDE_COL_BG_WHITE ), nullptr );
        winStatus->draw();
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
/**----------------------------------------------------------------------------
    @ingroup    NimbleIDE Nimble IDE
    @brief      Function to return the current time and date as a string
    @return     std::string
 *----------------------------------------------------------------------------*/
std::string return_current_time_and_date()
{
    auto              now       = std::chrono::system_clock::now();
    auto              in_time_t = std::chrono::system_clock::to_time_t( now );

    std::stringstream ss;
    ss << std::put_time( std::localtime( &in_time_t ), "%Y-%m-%d %X" );
    return ss.str();
}

//-----------------------------------------------------------------------------
// End of file: main.cpp
//-----------------------------------------------------------------------------
