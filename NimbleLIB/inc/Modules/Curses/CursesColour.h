/**----------------------------------------------------------------------------

    @file       CursesColour.h
    @defgroup   NimbleLIBCurses Nimble Library Curses Module
    @brief      Curses Colour class for the Nimble Library

    @copyright  Neil Bereford 2023

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
// defines
// ----------------------------------------------------------------------------

// Please use the colours and macro when using the curses module

#define COLOUR_INDEX( ink, paper ) ( ( ink ) + ( ( paper ) << 3 ) ) //!< Macro to calculate colour index
#if ( __linux__ )
#define IDE_COL_FG_WHITE   7 //!< White foreground colour for the IDE
#define IDE_COL_FG_YELLOW  6 //!< Yellow foreground colour for the IDE
#define IDE_COL_FG_MAGENTA 5 //!< Magenta foreground colour for the IDE
#define IDE_COL_FG_RED     1 //!< Red foreground colour for the IDE
#define IDE_COL_FG_CYAN    3 //!< Cyan foreground colour for the IDE
#define IDE_COL_FG_GREEN   2 //!< Green foreground colour for the IDE
#define IDE_COL_FG_BLUE    4 //!< Blue foreground colour for the IDE
#define IDE_COL_FG_BLACK   0 //!< Black foreground colour for the IDE
#define IDE_COL_BG_WHITE   7 //!< White background colour for the IDE
#define IDE_COL_BG_YELLOW  6 //!< Yellow background colour for the IDE
#define IDE_COL_BG_MAGENTA 5 //!< Magenta background colour for the IDE
#define IDE_COL_BG_RED     1 //!< Red background colour for the IDE
#define IDE_COL_BG_CYAN    3 //!< Cyan background colour for the IDE
#define IDE_COL_BG_GREEN   2 //!< Green background colour for the IDE
#define IDE_COL_BG_BLUE    4 //!< Blue background colour for the IDE
#define IDE_COL_BG_BLACK   0 //!< Black background colour for the IDE
#else
#define IDE_COL_FG_WHITE   7 //!< White foreground colour for the IDE
#define IDE_COL_FG_YELLOW  6 //!< Yellow foreground colour for the IDE
#define IDE_COL_FG_MAGENTA 5 //!< Magenta foreground colour for the IDE
#define IDE_COL_FG_RED     4 //!< Red foreground colour for the IDE
#define IDE_COL_FG_CYAN    3 //!< Cyan foreground colour for the IDE
#define IDE_COL_FG_GREEN   2 //!< Green foreground colour for the IDE
#define IDE_COL_FG_BLUE    1 //!< Blue foreground colour for the IDE
#define IDE_COL_FG_BLACK   0 //!< Black foreground colour for the IDE
#define IDE_COL_BG_WHITE   7 //!< White background colour for the IDE
#define IDE_COL_BG_YELLOW  6 //!< Yellow background colour for the IDE
#define IDE_COL_BG_MAGENTA 5 //!< Magenta background colour for the IDE
#define IDE_COL_BG_RED     4 //!< Red background colour for the IDE
#define IDE_COL_BG_CYAN    3 //!< Cyan background colour for the IDE
#define IDE_COL_BG_GREEN   2 //!< Green background colour for the IDE
#define IDE_COL_BG_BLUE    1 //!< Blue background colour for the IDE
#define IDE_COL_BG_BLACK   0 //!< Black background colour for the IDE
#endif
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
    const uint32_t MAX_COLOURS     = 64;
    const uint32_t NUM_BASE_COLORS = 8;
    // Member variables ---------------------------------------------------------
    std::vector<ColourPair> colourPairs; //!< Vector of colour pairs

    // Member functions ---------------------------------------------------------
};

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: CursesColour.h
// ----------------------------------------------------------------------------
