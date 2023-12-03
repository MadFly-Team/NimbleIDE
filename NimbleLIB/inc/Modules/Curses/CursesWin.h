/**----------------------------------------------------------------------------

    @file       CursesWin.h
    @defgroup   NimbleLIBCurses Nimble Library Curses Module
    @brief      Curse window class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

        please see CursesWin.cpp for full details.

Version:

        0.0.1.0     First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include <cinttypes>

extern "C"
{
#include "../../../../ExternalLibraries/PDCurses/curses.h"
}

#include "../ErrorHandling/Errors.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

class CursesWin
{
  public:
    // Constructors and destructors ---------------------------------------------
    CursesWin();
    CursesWin( uint32_t width, uint32_t height, uint32_t x, uint32_t y, uint32_t inkColour, uint32_t paperColour );
    ~CursesWin();

    // Member functions ---------------------------------------------------------
    // Getters ------------------------------------------------------------------
    uint32_t GetWidth() const noexcept;
    uint32_t GetHeight() const noexcept;
    uint32_t GetX() const noexcept;
    uint32_t GetY() const noexcept;
    uint32_t GetInkColour() const noexcept;
    uint32_t GetPaperColour() const noexcept;
    // Setters ------------------------------------------------------------------
    void SetWidth( uint32_t width );
    void SetHeight( uint32_t height );
    void SetX( uint32_t x );
    void SetY( uint32_t y );
    void SetInkColour( uint32_t inkColour );
    void SetPaperColour( uint32_t paperColour );
    // Control ------------------------------------------------------------------
    LibraryError Init();
    LibraryError Draw();
    LibraryError Clear();
    LibraryError Refresh();

  private:
    // Member variables ---------------------------------------------------------
    uint32_t winWidth;       //!< Width of the window
    uint32_t winHeight;      //!< Height of the window
    uint32_t winX;           //!< X position of the window
    uint32_t winY;           //!< Y position of the window
    uint32_t winInkColour;   //!< Colour of the ink
    uint32_t winPaperColour; //!< Colour of the paper
    WINDOW*  win;            //!< The curses window

    // Member functions ---------------------------------------------------------
};

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: CursesWin.h
// ----------------------------------------------------------------------------
