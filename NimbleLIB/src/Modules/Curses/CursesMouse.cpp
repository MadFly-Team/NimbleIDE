/**----------------------------------------------------------------------------

    @file       CursesMouse.cpp
    @defgroup   NimbleLIBCurses Nimble Library Curses Module
    @brief      Curses Mouse class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

    This class provides mouse support for the Nimble Library Curses Module.
    Simplely create an instance of this class and then call the processMouse()
    function passing it the input character.  This will then process any mouse
    events and update the class variables accordingly.  The drawMouse() function
    will then draw the mouse on the window passed to it.

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include "..\..\..\inc\Modules\Curses\CursesMouse.h"

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
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Constructor for CursesMouse class
----------------------------------------------------------------------------*/
CursesMouse::CursesMouse()
{
    // initialise mouse
    mousemask( ALL_MOUSE_EVENTS, NULL );

    // initial the class variables
    mouseEnabled     = false;
    mouseLeftPressed = false;
    mouseX           = 0;
    mouseY           = 0;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Destructor for CursesMouse class
----------------------------------------------------------------------------*/
CursesMouse::~CursesMouse()
{
}

// Processing -----------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Processing any mouse events
    @return     bool   True if mouse event needs processing
----------------------------------------------------------------------------*/
bool CursesMouse::processMouse( void )
{
    bool bProcessMouse = false;

    if ( mouseEnabled == true )
    {
        // get mouse event
#if defined( _WIN32 )
        if ( nc_getmouse( &mouseEvent ) == OK )
#else
        if ( getmouse( &mouseEvent ) == OK )
#endif
        {
            // check if left button pressed
            bProcessMouse    = true;
            mouseLeftPressed = ( mouseEvent.bstate & BUTTON1_PRESSED ) ? true : false;
            mouseX           = mouseEvent.x;
            mouseY           = mouseEvent.y;
        }
    }
    return bProcessMouse;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Draw mouse
    @param      win     Window to draw mouse on
    @return     void
----------------------------------------------------------------------------*/
void CursesMouse::drawMouse( WINDOW* win )
{
    uint32_t xAdj = win->_begx;
    uint32_t yAdj = win->_begy;
    uint32_t maxX = win->_begx + win->_maxx;
    uint32_t maxY = win->_begy + win->_maxy;
    if ( mouseOldX != mouseX || mouseOldY != mouseY )
    {
        if ( mouseOldX >= xAdj + LEFT_BORDER && mouseOldX <= maxX - WIDTH_ADJ_BORDER && mouseOldY >= yAdj + LEFT_BORDER && mouseOldY <= maxY - WIDTH_ADJ_BORDER )
        {
            mvwchgat( win, mouseOldY - yAdj, mouseOldX - xAdj, 1, A_REVERSE, 0, nullptr );
        }
        mouseOldX = mouseX;
        mouseOldY = mouseY;
    }
    if ( mouseX >= xAdj + LEFT_BORDER && mouseX <= maxX - WIDTH_ADJ_BORDER && mouseY >= yAdj + LEFT_BORDER && mouseY <= maxY - WIDTH_ADJ_BORDER )
    {
        mvwchgat( win, mouseY - yAdj, mouseX - xAdj, 1, A_REVERSE, 5, nullptr );
    }
}
// Control --------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Enable mouse
    @return     void
----------------------------------------------------------------------------*/
void CursesMouse::enableMouse()
{
    mouseEnabled = true;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Disable mouse
    @return     void
----------------------------------------------------------------------------*/
void CursesMouse::disableMouse()
{
    mouseEnabled = false;
}

// getters --------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Get mouse X position
    @return     uint32_t   Mouse X position
----------------------------------------------------------------------------*/
uint32_t CursesMouse::getMouseX() const
{
    return mouseX;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Get mouse Y position
    @return     uint32_t   Mouse Y position
----------------------------------------------------------------------------*/
uint32_t CursesMouse::getMouseY() const
{
    return mouseY;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Get left button state
    @return     bool     Left button state
----------------------------------------------------------------------------*/
bool CursesMouse::getLeftButtonState() const
{
    return mouseEvent.bstate & BUTTON1_PRESSED;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Get right button state
    @return     bool     Right button state
----------------------------------------------------------------------------*/
bool CursesMouse::getRightButtonState() const
{
    return mouseEvent.bstate & BUTTON3_PRESSED;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Get middle button state
    @return     bool     Middle button state
----------------------------------------------------------------------------*/
bool CursesMouse::getMiddleButtonState() const
{
    return mouseEvent.bstate & BUTTON2_PRESSED;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Get mouse enabled state
    @return     bool     Mouse enabled state
-----------------------------------------------------------------------------*/
bool CursesMouse::getMouseEnabled() const
{
    return mouseEnabled;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Get mouse left pressed state
    @return     bool     Mouse left pressed state
-----------------------------------------------------------------------------*/
bool CursesMouse::getMouseLeftPressed() const
{
    return mouseLeftPressed;
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: CursesMouse.cpp
// ----------------------------------------------------------------------------
