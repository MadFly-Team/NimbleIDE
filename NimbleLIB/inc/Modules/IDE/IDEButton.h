/**----------------------------------------------------------------------------

    @file       IDEButton.h
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEButton class for the Nimble Library

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
#include "IDEEditline.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

class IDEButton : public StatusCtrl
{
  public:
    // Eenums ------------------------------------------------------------------
    enum ButtonFlags : uint32_t
    {
        ButtonLeft = 0,
        ButtonRight,
    };
    // constructors & destructors --------------------------------------------
    IDEButton();
    ~IDEButton();
    // initialisation ----------------------------------------------------------
    LibraryError initButton( int16_t x, int16_t y, int16_t width, int16_t height, int16_t ink, int16_t paper );
    LibraryError setButtonText( const std::string& inText );
    // process and control -----------------------------------------------------
    LibraryError process( uint32_t key );
    LibraryError drawButton();

  private:
    // variables ---------------------------------------------------------------
    std::string mButtonText;
    uint32_t    mButtonFlags;
    uint32_t    mButtonX;
    uint32_t    mButtonY;
    uint32_t    mButtonWidth;
    uint32_t    mButtonHeight;
    uint32_t    mButtonInk;
    uint32_t    mButtonPaper;
    // functions ---------------------------------------------------------------
};

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEButton.h
// ----------------------------------------------------------------------------
