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
#include <functional>

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

using pButtonCallback = std::function<void( uint32_t, uint32_t )>; //!< Keymap Function pointer type

class IDEButton : public StatusCtrl
{
  public:
    // Eenums ------------------------------------------------------------------
    enum ButtonFlags : uint32_t
    {
        ButtonLeft = 0,
        ButtonRight,
        Pressed,
        Processed,
    };
    // constructors & destructors --------------------------------------------
    IDEButton();
    ~IDEButton();
    // initialisation ----------------------------------------------------------
    LibraryError initButton( int16_t x, int16_t y, int16_t width, int16_t height, int16_t ink, int16_t paper );
    LibraryError setButtonText( const std::string& inText );
    // process and control -----------------------------------------------------
    LibraryError processClick( uint32_t mouseX, uint32_t mouseY );
    LibraryError drawButton();
    // general access ----------------------------------------------------------
    void setFlag( ButtonFlags flag );
    void clearFlag( ButtonFlags flag );
    bool checkFlag( ButtonFlags flag );
    void setCallback( pButtonCallback callback );
    void setWindowHandle( WINDOW* windowHandle );

  private:
    // variables ---------------------------------------------------------------
    std::string     mButtonText;     //!< button text
    uint32_t        mButtonFlags;    //!< button flags
    uint32_t        mButtonX;        //!< button x position
    uint32_t        mButtonY;        //!< button y position
    uint32_t        mButtonWidth;    //!< button width
    uint32_t        mButtonHeight;   //!< button height
    uint32_t        mButtonInk;      //!< button ink colour
    uint32_t        mButtonPaper;    //!< button paper colour
    pButtonCallback mButtonCallback; //!< button callback function
    WINDOW*         mWinParent;      //!< window handle
    WINDOW*         mWin;            //!< window handle
    // functions ---------------------------------------------------------------
};

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEButton.h
// ----------------------------------------------------------------------------
