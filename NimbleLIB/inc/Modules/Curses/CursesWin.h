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

#include "../ErrorHandling/ErrorHandler.h"

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
    uint32_t getWidth() const noexcept;
    uint32_t getHeight() const noexcept;
    uint32_t getX() const noexcept;
    uint32_t getY() const noexcept;
    uint32_t getInkColour() const noexcept;
    uint32_t getPaperColour() const noexcept;
    // Setters ------------------------------------------------------------------
    void setWidth( uint32_t width );
    void setHeight( uint32_t height );
    void setX( uint32_t x );
    void setY( uint32_t y );
    void setInkColour( uint32_t inkColour );
    void setPaperColour( uint32_t paperColour );
    // Control ------------------------------------------------------------------
    LibraryError init();
    LibraryError draw();
    LibraryError clear();
    LibraryError refresh();

    // display functions --------------------------------------------------------
    LibraryError print( uint32_t x, uint32_t y, const char* text );
    LibraryError colourWindow( uint32_t inkColour, uint32_t paperColour );

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
