/**----------------------------------------------------------------------------

    @file       ScreenControl.h
    @defgroup   NimbleLIBScreen Nimble Library Screen Module
    @brief      Basde class for screen objects

    @copyright  Neil Beresford 2023

Notes:

Version:

        0.0.1.0   First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include <stdint.h>
#include <string>
#include "../../../../ExternalLibraries/PDCurses/curses.h"

//-----------------------------------------------------------------------------
// Namespace access
//-----------------------------------------------------------------------------

namespace Nimble
{
namespace Screen
{

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

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
// Class Definition
//-----------------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBScreen Nimble Library Screen Module
    @brief      Colour pair structure, sets the background an
                foreground colours

  --------------------------------------------------------------------------*/
typedef struct
{
    int16_t iForeground; // Foirground colour
    int16_t iBackground; // Background colour

} COLOUR_PAIR, *PCOLOUR_PAIR;

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBScreen Nimble Library Screen Module
    @brief      SCreen Control class, controls the screen
  --------------------------------------------------------------------------*/
class ScreenControl
{
  public:
    ScreenControl();
    ~ScreenControl();

  private:
    // Data Members

    // Functions
    void RefreshScreen();
    void SetColour( int16_t iColour );
    void SetBackground( int16_t iColour );
    void InitialiseColourPairs( const PCOLOUR_PAIR pColourPairs, int16_t iNumColourPairs );
};

//-----------------------------------------------------------------------------

} // namespace Screen
} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: ScreenControl.h
//-----------------------------------------------------------------------------
