/**----------------------------------------------------------------------------

    @file       CursesWin.cpp
    @defgroup   NimbleLIBCurses Nimble Library Curses Module
    @brief      Curse window class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

        please see CursesWin.cpp for full details.

Version:

        0.0.1.0     First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include "../../../inc/Modules/Curses/CursesWin.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class Support Functions
// ----------------------------------------------------------------------------

// Constructors and destructors ------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Default constructor for the curses window class
  --------------------------------------------------------------------------*/
CursesWin::CursesWin()
{
    // initialise variables
    winWidth       = 0;
    winHeight      = 0;
    winX           = 0;
    winY           = 0;
    winInkColour   = 0;
    winPaperColour = 0;
    win            = nullptr;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Constructor for the curses window class
    @param      width       The width of the window
    @param      height      The height of the window
    @param      x           The x position of the window
    @param      y           The y position of the window
    @param      inkColour   The ink colour of the window
    @param      paperColour The paper colour of the window
  --------------------------------------------------------------------------*/
CursesWin::CursesWin( uint32_t width, uint32_t height, uint32_t x, uint32_t y, uint32_t inkColour, uint32_t paperColour )
{
    winWidth       = width;
    winHeight      = height;
    winX           = x;
    winY           = y;
    winInkColour   = inkColour;
    winPaperColour = paperColour;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Destructor for the curses window class
  --------------------------------------------------------------------------*/
CursesWin::~CursesWin()
{
}

// Getters ---------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Gets the width of the window
    @return     The width of the window
  --------------------------------------------------------------------------*/
uint32_t CursesWin::GetWidth() const noexcept
{
    return winWidth;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Gets the height of the window
    @return     The height of the window
  --------------------------------------------------------------------------*/
uint32_t CursesWin::GetHeight() const noexcept
{
    return winHeight;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Gets the x position of the window
    @return     The x position of the window
  --------------------------------------------------------------------------*/
uint32_t CursesWin::GetX() const noexcept
{
    return winX;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Gets the y position of the window
    @return     The y position of the window
  --------------------------------------------------------------------------*/
uint32_t CursesWin::GetY() const noexcept
{
    return winY;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Gets the ink colour of the window
    @return     The ink colour of the window
  --------------------------------------------------------------------------*/
uint32_t CursesWin::GetInkColour() const noexcept
{
    return winInkColour;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Gets the paper colour of the window
    @return     The paper colour of the window
  --------------------------------------------------------------------------*/
uint32_t CursesWin::GetPaperColour() const noexcept
{
    return winPaperColour;
}

// Setters ---------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Sets the width of the window
    @param      width   The width of the window
  --------------------------------------------------------------------------*/
void CursesWin::SetWidth( uint32_t width )
{
    winWidth = width;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Sets the height of the window
    @param      height  The height of the window
  --------------------------------------------------------------------------*/
void CursesWin::SetHeight( uint32_t height )
{
    winHeight = height;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Sets the x position of the window
    @param      x       The x position of the window
  --------------------------------------------------------------------------*/
void CursesWin::SetX( uint32_t x )
{
    winX = x;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Sets the y position of the window
    @param      y       The y position of the window
  --------------------------------------------------------------------------*/
void CursesWin::SetY( uint32_t y )
{
    winY = y;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Sets the ink colour of the window
    @param      inkColour   The ink colour of the window
  --------------------------------------------------------------------------*/
void CursesWin::SetInkColour( uint32_t inkColour )
{
    winInkColour = inkColour;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Sets the paper colour of the window
    @param      paperColour The paper colour of the window
  --------------------------------------------------------------------------*/
void CursesWin::SetPaperColour( uint32_t paperColour )
{
    winPaperColour = paperColour;
}

// Other Functions ------------------------------------------------------------

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: CursesWin.cpp
// ----------------------------------------------------------------------------
