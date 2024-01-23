/**----------------------------------------------------------------------------

    @file       CursesMouse.h
    @defgroup   NimbleLIBCurses Nimble Library Curses Module
    @brief      Curses Mouse class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

        please see CursesMouse.cpp for full details.

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include <cinttypes>
#include <cstdint>
#include <functional>

extern "C"
{
#include "../../../../ExternalLibraries/PDCurses/curses.h"
}

#include "../ErrorHandling/ErrorHandler.h"
#include "../Utilities/StatusCtrl.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

class CursesMouse
{
  public:
    // Constructor and destructor ---------------------------------------------
    CursesMouse();
    ~CursesMouse();
    // Public functions -------------------------------------------------------
    void enableMouse();
    void disableMouse();
    bool processMouse( void );
    void drawMouse( WINDOW* win );
    // Getters ----------------------------------------------------------------
    bool     getMouseEnabled() const;
    bool     getMouseLeftPressed() const;
    bool     getLeftButtonState() const;
    bool     getRightButtonState() const;
    bool     getMiddleButtonState() const;
    uint32_t getMouseX() const;
    uint32_t getMouseY() const;

  private:
    // Private variables ------------------------------------------------------
    MEVENT   mouseEvent;       //!< Mouse event structure
    bool     mouseEnabled;     //!< Mouse enabled flag
    bool     mouseLeftPressed; //!< Mouse left button pressed flag
    uint32_t mouseX;           //!< Mouse X position
    uint32_t mouseY;           //!< Mouse Y position
    uint32_t mouseOldX;        //!< MouseOldX position
    uint32_t mouseOldY;        //!< MouseOldY position
    // Private functions ------------------------------------------------------
};

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: CursesMouse.h
// ----------------------------------------------------------------------------
