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

void        display_menu( int old_option, int new_option );
void        colorbox( WINDOW* win, chtype color, int hasbox );
void        setcolor( WINDOW* win, chtype color );

// menu functions
void TerminateProgram();
void LoadProgramAndDisplay();
void ResetScreenToMenu();

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

std::unique_ptr<CursesWin> winTitle;
std::unique_ptr<CursesWin> winStatus;
std::unique_ptr<CursesWin> winProject;

WINDOW*                    winMenu;
WINDOW*                    winBody;

int                        old_option = -1, new_option = 0, ch;

//-----------------------------------------------------------------------------
// External Functionality
//-----------------------------------------------------------------------------

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

    CursesColour::getInstance().init();

    winStatus  = std::make_unique<CursesWin>( COLS, 3, 0, LINES - 3, COLOR_BLACK, COLOR_WHITE );
    winTitle   = std::make_unique<CursesWin>( COLS, 3, 0, 0, COLOR_WHITE, COLOR_YELLOW );
    winProject = std::make_unique<CursesWin>( 30, LINES - 6, COLS - 30, 3, COLOR_WHITE, COLOR_YELLOW );
    winTitle->colourWindow( COLOUR_INDEX( IDE_COL_FG_WHITE, IDE_COL_BG_BLUE ), true );
    winTitle->print( 2, 0, "Nimble IDE : Version 0.0.1" );
    winTitle->drawVerticalLine( COLS - 22, 1, 1 );
    winStatus->colourWindow( COLOUR_INDEX( IDE_COL_FG_WHITE, IDE_COL_BG_BLUE ), true );
    winStatus->print( 2, 0, "Status Bar : Press 'q' to quit" );
    winStatus->drawVerticalLine( COLS - 37, 1, 1 );
    winProject->colourWindow( COLOUR_INDEX( IDE_COL_FG_WHITE, IDE_COL_BG_BLUE ), true );
    winProject->print( 2, 0, "Project Window" );
    winProject->drawHorizontalLine( 1, 3, 30 - 2 );

    IDEEditBox winLineNumbers;
    IDEEditor  winEditor;
    winEditor.init( COLS - 38, LINES - 8, 8, 4 );
    std::string filename = "test.txt";
    winEditor.start( filename );

    winLineNumbers.initBox( 0, 3, 7, LINES - 6, COLOR_WHITE, COLOR_BLACK );
    winLineNumbers.colourWindow( COLOUR_INDEX( IDE_COL_FG_WHITE, IDE_COL_BG_BLUE ), true );
    winLineNumbers.setLineInkColour( COLOUR_INDEX( IDE_COL_FG_YELLOW, IDE_COL_BG_BLUE ) );
    winLineNumbers.displayLineNumbers( winEditor.getCurrentLine() + 1, winEditor.getTotalLines() );

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
    }
    touchwin( stdscr );
    touchwin( winTitle->getWindow() );
    touchwin( winStatus->getWindow() );
    wrefresh( stdscr );
    wrefresh( winTitle->getWindow() );
    wrefresh( winStatus->getWindow() );

    winTitle->draw();
    winStatus->draw();
    winEditor.displayEditor();
    winLineNumbers.displayLineNumbers( winEditor.getCurrentLine() + 1, winEditor.getTotalLines() );

    uint32_t key = 0;
    while ( key != 'q' )
    {
        key = getch();
        delay_output( DELAYSIZE );
        if ( winEditor.processKeyEdit( key ) == true )
        {
            winEditor.displayEditor();
            winLineNumbers.displayLineNumbers( winEditor.getCurrentLine() + 1, winEditor.getTotalLines() );
        }
        winEditor.processDisplay();
        // display the time and date...
        std::string streamString = return_current_time_and_date();
        winTitle->print( COLS - 1 - streamString.length(), 1, streamString );
        mvwchgat( winTitle->getWindow(), 1, COLS - 1 - streamString.length(), streamString.length(), A_NORMAL, COLOUR_INDEX( IDE_COL_FG_YELLOW, IDE_COL_BG_BLUE ), nullptr );
        winTitle->draw();
        // display the number of lines and cursor position...
        std::string linesString = std::format( "Lines: {:5d} Cursor: {},{}", winEditor.getTotalLines(), winEditor.getCursorX(), winEditor.getCursorY() );
        linesString.resize( 34, ' ' );
        mvwprintw( winStatus->getWindow(), 1, COLS - 35, linesString.c_str() );
        mvwchgat( winStatus->getWindow(), 1, COLS - 28, 5, A_NORMAL, COLOUR_INDEX( IDE_COL_FG_GREEN, IDE_COL_BG_BLUE ), nullptr );
        mvwchgat( winStatus->getWindow(), 1, COLS - 14, 13, A_NORMAL, COLOUR_INDEX( IDE_COL_FG_GREEN, IDE_COL_BG_BLUE ), nullptr );
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
