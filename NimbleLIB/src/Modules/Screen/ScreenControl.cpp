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

#include "../../../inc/Modules/Screen/ScreenControl.h"

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

ScreenControl::ScreenControl()
{
    //-----------------------------------------------------------------------------
    // Create the screen
    //-----------------------------------------------------------------------------
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad( stdscr, TRUE );
    curs_set( 0 );
    refresh();
    //-----------------------------------------------------------------------------
    // Create the color pairs
    //-----------------------------------------------------------------------------
    init_pair( TITLECOLOR, COLOR_WHITE, COLOR_BLUE );
    init_pair( MAINMENUCOLOR, COLOR_WHITE, COLOR_BLUE );
    init_pair( MAINMENUREVCOLOR, COLOR_WHITE, COLOR_BLUE );
    init_pair( SUBMENUCOLOR, COLOR_WHITE, COLOR_BLUE );
    init_pair( SUBMENUREVCOLOR, COLOR_WHITE, COLOR_BLUE );
    init_pair( BODYCOLOR, COLOR_WHITE, COLOR_BLUE );
    init_pair( STATUSCOLOR, COLOR_WHITE, COLOR_BLUE );
    init_pair( INPUTBOXCOLOR, COLOR_WHITE, COLOR_BLUE );
    init_pair( EDITBOXCOLOR, COLOR_WHITE, COLOR_BLUE );
}

ScreenControl::~ScreenControl()
{
    //-----------------------------------------------------------------------------
    // Destroy the screen
    //-----------------------------------------------------------------------------
    endwin();
}

//-----------------------------------------------------------------------------

} // namespace Screen
} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: ScreenControl.cpp
//-----------------------------------------------------------------------------
