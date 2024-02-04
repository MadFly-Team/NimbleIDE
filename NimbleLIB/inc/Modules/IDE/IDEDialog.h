/**----------------------------------------------------------------------------

    @file       IDEDialog.h
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEDialog class for the Nimble Library

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
#include "../Curses/CursesKeyboard.h"
#include "IDEEditline.h"
#include "IDEButton.h"

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
    @brief      Basic Dialog, including Title, status and buttons
------------------------------------------------------------------------------*/
class IDEDialog : public CursesWin, public CursesKeyboard, public StatusCtrl
{
  public:
    // Eenums ------------------------------------------------------------------
    enum DialogFlags : uint32_t
    {
        TitleBar = 0,
        StatusBar,
        ButtonLeft,
        ButtonRight,
        VerticalScroll,
    };
    // constructors & destructors --------------------------------------------
    IDEDialog();
    ~IDEDialog();
    // initialisation ----------------------------------------------------------
    LibraryError initDialog( int16_t x, int16_t y, int16_t width, int16_t height, int16_t ink, int16_t paper );
    // process and control -----------------------------------------------------
    LibraryError processDialog();
    LibraryError processControls( uint32_t key, uint32_t mouseX, uint32_t mouseY, uint32_t mouseButton );
    // setup -------------------------------------------------------------------
    LibraryError title( const std::string& inTitle );
    LibraryError status( const std::string& inStatus );
    LibraryError buttons( WINDOW* inWin, const std::string& inButtonLeft, const std::string& inButtonRight );
    LibraryError setVerticalScroll();
    // draw --------------------------------------------------------------------
    LibraryError drawDialog();

  private:
    // private vairables --------------------------------------------------------
    uint32_t    nFrameCount;  //!< frame count for the IDEEditBox
    std::string sTitle;       //!< title of the dialog
    std::string sStatus;      //!< status of the dialog
    std::string sButtonLeft;  //!< button text
    std::string sButtonRight; //!< button text
    IDEButton   leftButton;   //!< button left
    IDEButton   rightButton;  //!< button right

}; // class IDEDialog

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEDialog.h
// ----------------------------------------------------------------------------
