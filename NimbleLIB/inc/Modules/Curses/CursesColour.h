/**----------------------------------------------------------------------------

    @file       CursesColour.h
    @defgroup   NimbleLIBCurses Nimble Library Curses Module
    @brief      Curses Colour class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

        please see CursesColour.cpp for full details.

Version:

        0.0.1.0     First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include <cinttypes>
#include <vector>

extern "C"
{
#include "../../../../ExternalLibraries/PDCurses/curses.h"
}

#include "../ErrorHandling/ErrorHandler.h"
#include "../Utilities/StatusCtrl.h"
#include "CursesWin.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Colour pair structure for curses
--------------------------------------------------------------------------*/
struct ColourPair
{
    uint16_t index; //!< Index of colour pair
    uint16_t ink;   //!< Ink colour
    uint16_t paper; //!< Paper colour
};

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Curses colour class for the Nimble Library
--------------------------------------------------------------------------*/
class CursesColour : public StatusCtrl
{
  public:
    // Function to access the singleton -----------------------------------------
    static CursesColour& getInstance()
    {
        static CursesColour instance; // Created only once
        return instance;
    }
    // Member functions ---------------------------------------------------------
    LibraryError init();
    LibraryError setColorPair( uint32_t pair, uint32_t fg, uint32_t bg );
    LibraryError setInkColourPair( uint32_t pair, uint32_t ink );
    LibraryError setPaperColourPair( uint32_t pair, uint32_t paper );
    LibraryError setColour( std::unique_ptr<CursesWin> win, uint32_t pair );

  private:
    // Singleton constructor and destructor ------------------------------------
    CursesColour();
    ~CursesColour();
    CursesColour( const CursesColour& )            = delete;
    CursesColour& operator=( const CursesColour& ) = delete;
    // Constants ----------------------------------------------------------------
    const uint32_t MAX_COLOURS      = 64;
    const uint32_t NUUM_BASE_COLORS = 8;
    // Member variables ---------------------------------------------------------
    std::vector<ColourPair> colourPairs; //!< Vector of colour pairs

    // Member functions ---------------------------------------------------------
};

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: CursesColour.h
// ----------------------------------------------------------------------------
