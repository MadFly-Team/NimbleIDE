/**----------------------------------------------------------------------------

    @file       IDEButton.cpp
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEButton class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

-----------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include "../../../inc/Modules/Curses/CursesColour.h"
#include "../../../inc/Modules/IDE/IDEButton.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

// constructor and destructor --------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief     IDEButton constructor
    @return    none
-----------------------------------------------------------------------------*/
IDEButton::IDEButton()
{
    mButtonCallback = nullptr;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief     IDEButton destructor
    @return    none
-----------------------------------------------------------------------------*/
IDEButton::~IDEButton()
{
}

// initialisation -------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief     IDEButton initialisation
    @param     x            x position
    @param     y            y position
    @param     width        width of button
    @param     height       height of button
    @param     ink          ink colour
    @param     paper        paper colour
    @return    LibraryError error code
-----------------------------------------------------------------------------*/
LibraryError IDEButton::initButton( int16_t x, int16_t y, int16_t width, int16_t height, int16_t ink, int16_t paper )
{
    LibraryError error = LibraryError::No_Error;

    // set button position and size
    mButtonX      = x;
    mButtonY      = y;
    mButtonWidth  = width;
    mButtonHeight = height;
    mButtonInk    = ink;
    mButtonPaper  = paper;
    mWinParent    = nullptr;
    mWin          = nullptr;
    return error;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief     IDEButton set the displayed text
    @param     inText       text to display
    @return    LibraryError error code
-----------------------------------------------------------------------------*/
LibraryError IDEButton::setButtonText( const std::string& inText )
{
    LibraryError error = LibraryError::No_Error;
    mButtonText        = inText;
    return error;
}

// process and control --------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief     IDEButton process a click
    @param     mouseX       mouse x position
    @param     mouseY       mouse y position
    @return    LibraryError error code
-----------------------------------------------------------------------------*/
LibraryError IDEButton::processClick( uint32_t mouseX, uint32_t mouseY )
{
    LibraryError error = LibraryError::IDEButtin_WindowNotInitialised;

    if ( mWin != nullptr )
    {

        // check if mouse is in button area, exclude the border
        uint32_t x = ( mWinParent->_begx + mButtonX + 1 );
        uint32_t y = ( mWinParent->_begy + mButtonY + 1 );
        uint32_t w = ( mButtonWidth - 3 );
        uint32_t h = ( mButtonHeight - 3 );

        if ( mouseX >= x && ( mouseX <= ( x + w ) ) && mouseY >= y && ( mouseY <= ( y + h ) ) )
        {
            // call button function
            if ( mButtonCallback != nullptr )
            {
                mButtonCallback();
            }
            error = LibraryError::No_Error;
        }
    }

    return error;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief     IDEButton draw the button
    @return    LibraryError error code
-----------------------------------------------------------------------------*/
LibraryError IDEButton::drawButton()
{
    LibraryError error = LibraryError::No_Error;
    if ( mWinParent == nullptr )
    {
        error = LibraryError::IDEButtin_WindowNotInitialised;
    }
    else
    {
        if ( mWin == nullptr )
        {
            mWin = subwin( mWinParent, mButtonHeight, mButtonWidth, mWinParent->_begy + mButtonY, mWinParent->_begx + mButtonX );
        }
        wattron( mWin, COLOR_PAIR( COLOUR_INDEX( mButtonInk, mButtonPaper ) ) );
        wbkgd( mWin, COLOR_PAIR( COLOUR_INDEX( mButtonInk, mButtonPaper ) ) );
        box( mWin, 0, 0 );
        uint32_t xPos = ( mButtonWidth / 2 ) - ( mButtonText.length() / 2 );
        mvwaddstr( mWin, mButtonHeight / 2, xPos, mButtonText.c_str() );
        wattroff( mWin, COLOR_PAIR( COLOUR_INDEX( mButtonInk, mButtonPaper ) ) );
    }
    return error;
}

// general access -------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief     IDEButton set the window handle
    @param     handle       window handle
    @return    void
-----------------------------------------------------------------------------*/
void IDEButton::setWindowHandle( WINDOW* handle )
{
    mWinParent = handle;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief     IDEButton set the flag
    @param     flags        button flags
    @return    void
-----------------------------------------------------------------------------*/
void IDEButton::setFlag( ButtonFlags flag )
{
    mButtonFlags |= flag;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief     IDEButton clear the flag
    @param     flags        button flags
    @return    void
-----------------------------------------------------------------------------*/
void IDEButton::clearFlag( ButtonFlags flag )
{
    mButtonFlags &= ~flag;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief     IDEButton check the flag
    @param     flags        button flags
    @return    bool         true if flag set
-----------------------------------------------------------------------------*/
bool IDEButton::checkFlag( ButtonFlags flag )
{
    return ( mButtonFlags & flag );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief     IDEButton set the callback function
    @param     callback     callback function
    @return    void
-----------------------------------------------------------------------------*/
void IDEButton::setCallback( std::function<void()> callback ) noexcept
{
    mButtonCallback = callback;
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEButton.cpp
// ----------------------------------------------------------------------------
