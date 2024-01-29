/**----------------------------------------------------------------------------

    @file       IDEWindow.h
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEWindow class for the Nimble Library

    @copyright  Neil Bereford 2023

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include <cinttypes>
#include <cstdint>

#include "../ErrorHandling/ErrorHandler.h"
#include "../Utilities/StatusCtrl.h"
#include "../Curses/CursesWin.h"
#include "IDEEditline.h"
#include "../Curses/CursesMouse.h"
#include "../Curses/CursesKeyboard.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEWindow class for the Nimble Library
                Please note that CursesMouse is inherited privately, so thatthe
                the IDEWindow can control the mouse events.
    @return     none
-----------------------------------------------------------------------------*/
class IDEWindow : public CursesWin, CursesKeyboard
{
  public:
    // Constructor & destructor -----------------------------------------------
    IDEWindow();
    ~IDEWindow();
    // Public functions -------------------------------------------------------
    // initialisation ---------------------------------------------------------
    LibraryError init( uint32_t X, uint32_t y, uint32_t width, uint32_t height, uint32_t colourPair );
    // setters ----------------------------------------------------------------
    void setTitle( std::string title );

  private:
    // Private functions ------------------------------------------------------
    // Private members --------------------------------------------------------
    std::string m_title;
};

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEWindow.h
// ----------------------------------------------------------------------------
