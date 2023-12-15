/**----------------------------------------------------------------------------

    @file       ScreenControl.cpp
    @defgroup   NimbleLIBScreen Nimble Library Screen Module
    @brief      Basde class for screen objects

    @copyright  Neil Beresford 2023

Notes:

Version:

        0.0.1.0   First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Headers
//-----------------------------------------------------------------------------

#include <iostream>
extern "C"
{
#include "../../../../ExternalLibraries/PDCurses/curses.h"
}

#include "../../../inc/Modules/Screen/ScreenControl.h"
#include "../../../inc/Modules/ErrorHandling/ErrorHandler.h"

//-----------------------------------------------------------------------------
// Namespace access
//-----------------------------------------------------------------------------

namespace Nimble
{
namespace Screen
{

//-----------------------------------------------------------------------------
// Supporting Functionality for ScreenControl
//-----------------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBScreen Nimble Library Screen Module
    @brief      Constructor for the ScreenControl class.
----------------------------------------------------------------------------*/
ScreenControl::ScreenControl()
{
    uint32_t returnResult = 0; //!< Local: Return result from functions

    //-----------------------------------------------------------------------------
    // Create the screen
    //-----------------------------------------------------------------------------
    initscr();

    returnResult = start_color();
    if ( returnResult == ERR )
    {
        ErrorHandler::getInstance().LogError( LibraryError::Screen_StartColorFailed, "Failed to start color" );
    }
    returnResult = cbreak();
    if ( returnResult == ERR )
    {
        ErrorHandler::getInstance().LogError( LibraryError::Screen_CBreakFailed, "Failed to set cbreak" );
    }
    returnResult = noecho();
    if ( returnResult == ERR )
    {
        ErrorHandler::getInstance().LogError( LibraryError::Screen_NoEchoFailed, "Failed to set noecho" );
    }
    returnResult = keypad( stdscr, TRUE );
    if ( returnResult == ERR )
    {
        ErrorHandler::getInstance().LogError( LibraryError::Screen_KeyPadFailed, "Failed to set keypad" );
    }
    returnResult = curs_set( 0 );
    if ( returnResult == ERR )
    {
        ErrorHandler::getInstance().LogError( LibraryError::Screen_CursSetFailed, "Failed to set curs_set" );
    }
    returnResult = refresh();
    if ( returnResult == ERR )
    {
        ErrorHandler::getInstance().LogError( LibraryError::Screen_RefreshFailed, "Failed to refresh the screen" );
    }
    //-----------------------------------------------------------------------------
    // Create the color pairs
    //-----------------------------------------------------------------------------
    chtype colours[] = { TITLECOLOR,   COLOR_WHITE, COLOR_BLUE, MAINMENUCOLOR,   COLOR_WHITE, COLOR_BLUE, MAINMENUREVCOLOR, COLOR_WHITE, COLOR_BLUE,
                         SUBMENUCOLOR, COLOR_WHITE, COLOR_BLUE, SUBMENUREVCOLOR, COLOR_WHITE, COLOR_BLUE, BODYCOLOR,        COLOR_WHITE, COLOR_BLUE,
                         STATUSCOLOR,  COLOR_WHITE, COLOR_BLUE, INPUTBOXCOLOR,   COLOR_WHITE, COLOR_BLUE, EDITBOXCOLOR,     COLOR_WHITE, COLOR_BLUE };

    for ( uint32_t i = 0; i < ( sizeof( colours ) / sizeof( chtype ) ); i += 3 )
    {
        returnResult = init_pair( (uint16_t)colours[ i ], (uint16_t)colours[ i + 1 ], (uint16_t)colours[ i + 2 ] );
        if ( returnResult == ERR )
        {
            ErrorHandler::getInstance().LogError( LibraryError::Screen_InitPairFailed, "Failed to set the colour pair" );
            break;
        }
    }
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBScreen Nimble Library Screen Module
    @brief      Destructor for the ScreenControl class.
----------------------------------------------------------------------------*/
ScreenControl::~ScreenControl()
{
    //-----------------------------------------------------------------------------
    // Destroy the screen
    //-----------------------------------------------------------------------------
    if ( endwin() == ERR )
    {
        ErrorHandler::getInstance().LogError( LibraryError::Screen_EndWinFailed, "Failed to end the screen" );
    }
}

//-----------------------------------------------------------------------------

} // namespace Screen
} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: ScreenControl.cpp
//-----------------------------------------------------------------------------
