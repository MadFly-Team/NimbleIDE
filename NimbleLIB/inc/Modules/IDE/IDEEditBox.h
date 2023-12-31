/**----------------------------------------------------------------------------

    @file       IDEEditBox.h
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEEditBox class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

        please see IDEEditBox.cpp for full details.

Version:

        0.0.1.0     First Release, development phase. Draft copy

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

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

class IDEEditBox : public IDEEditline, public CursesWin
{
  public:
    // constructors & destructors ----------------------------------------------
    IDEEditBox();
    ~IDEEditBox();
    // initialisation -----------------------------------------------------------
    LibraryError initBox( int16_t x, int16_t y, int16_t width, int16_t height, int16_t ink, int16_t paper );
    // process and control ------------------------------------------------------
    LibraryError process( uint32_t key );
    // special functions --------------------------------------------------------
    LibraryError displayLineNumbers( uint32_t nLine, uint32_t nTotalLines );

  private:
    // private vairables --------------------------------------------------------
    uint32_t nFrameCount;  //!< frame count for the IDEEditBox
    bool     bCursorDrawn; //!< flag to indicate if the cursor has been drawn
};

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEEditBox.h
// ----------------------------------------------------------------------------
 