/**----------------------------------------------------------------------------

    @file       IDEWindow.cpp
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEWindow class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include "../../../inc/Modules/IDE/IDEWindow.h"
#include "../../../inc/Modules/Curses/CursesColour.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class functions
// ----------------------------------------------------------------------------

// constructors & destructors -------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Constructor for IDEWindow class
----------------------------------------------------------------------------*/
IDEWindow::IDEWindow()
{
    // enable the mouse control
    enableMouse();
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Destructor for IDEWindow class
----------------------------------------------------------------------------*/
IDEWindow::~IDEWindow()
{
}

// Initialisation -------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Initialise the IDEWindow class
    @param      x           x position of the window
    @param      y           y position of the window
    @param      width       width of the window
    @param      height      height of the window
    @param      colourPair  colour pair to use for the window
    @return     LibraryError error code
----------------------------------------------------------------------------*/
LibraryError IDEWindow::init( uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t colourPair )
{
    LibraryError error = LibraryError::IDEWindow_FailedToCreateWindow;

    // create the window
    if ( CursesWin::init( width, height, x, y, IDE_COL_FG_WHITE, IDE_COL_BG_BLACK ) == LibraryError::No_Error )
    {
        error = LibraryError::No_Error;
    }
    return error;
}

// Setters --------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Set the title of the IDEWindow
    @param      title       title of the window
    @return     none
----------------------------------------------------------------------------*/
void IDEWindow::setTitle( std::string title )
{
    m_title = title;
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEWindow.cpp
// ----------------------------------------------------------------------------
