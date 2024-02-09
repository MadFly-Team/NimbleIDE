/**----------------------------------------------------------------------------

    @file       IDEDialog.cpp
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEDialog class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

-----------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include "../../../inc/Modules/ErrorHandling/ErrorHandler.h"
#include <functional>
#include "../../../inc/Modules/IDE/IDEDialog.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

// constructors & destructors -------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Constructor for IDEDialog class

----------------------------------------------------------------------------*/
IDEDialog::IDEDialog()
{
    setInitialized();
    nScrollPos    = 0;
    nOldScrollPos = 0;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Destructor for IDEDialog class

----------------------------------------------------------------------------*/
IDEDialog::~IDEDialog()
{
}

// initialisation -----------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Initialise the IDEDialog class
    @param      x       x position of the window
    @param      y       y position of the window
    @param      width   width of the window
    @param      height  height of the window
    @param      ink     ink colour of the window
    @param      paper   paper colour of the window
    @return     LibraryError enum
----------------------------------------------------------------------------*/
LibraryError IDEDialog::initDialog( int16_t x, int16_t y, int16_t width, int16_t height, int16_t ink, int16_t paper )
{
    // initialise the window
    LibraryError eError = CursesWin::init( width, height, x, y, ink, paper );
    if ( eError == LibraryError::No_Error )
    {
        // initialise the dialog
        nFrameCount  = 0;
        sTitle       = "";
        sStatus      = "";
        sButtonLeft  = "";
        sButtonRight = "";

        setReady();
    }
    // return state of initialisation
    return ( eError );
}

// creation -----------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Setup the title bar
    @param      inTitle     Title string for the dialog
    @return     LibraryError enum
----------------------------------------------------------------------------*/
LibraryError IDEDialog::title( const std::string& inTitle )
{
    LibraryError eError = LibraryError::No_Error;

    if ( isReady() )
    {
        sTitle = inTitle;
        setUserFlag( DialogFlags::TitleBar );
    }
    else
    {
        eError = LibraryError::IDEEditline_InitNotCalled;
    }

    // return state of initialisation
    return ( eError );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Setup the status bar
    @param      inStatus    Status string for the dialog
    @return     LibraryError enum
----------------------------------------------------------------------------*/
LibraryError IDEDialog::status( const std::string& inStatus )
{
    LibraryError eError = LibraryError::No_Error;
    if ( isReady() )
    {
        sStatus = inStatus;
        setUserFlag( DialogFlags::StatusBar );
    }
    else
    {
        eError = LibraryError::IDEEditline_InitNotCalled;
    }
    // return state of initialisation
    return ( eError );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Setup the buttons
    @param      inWin           Window to draw the buttons on
    @param      inButtonLeft    Left button string for the dialog
    @param      inButtonRight   Right button string for the dialog
    @return     LibraryError enum
----------------------------------------------------------------------------*/
LibraryError IDEDialog::buttons( WINDOW* inWin, const std::string& inButtonLeft, const std::string& inButtonRight )
{
    LibraryError eError = LibraryError::No_Error;
    if ( isReady() )
    {
        if ( inButtonLeft.length() > 0 )
        {
            sButtonLeft = inButtonLeft;
            setUserFlag( DialogFlags::ButtonLeft );
            leftButton.initButton( 2, getHeight() - 4, 10, 3, getInkColour(), getPaperColour() );
            leftButton.setButtonText( sButtonLeft );
            leftButton.setWindowHandle( inWin );
            // callbacks.push_back( leftButtonCB );
            // leftButton.setCallback( std::bind( &IDEDialog::leftButtonCB, &leftButton, std::placeholders::_2 ) );
        }
        if ( inButtonRight.length() > 0 )
        {
            sButtonRight = inButtonRight;
            setUserFlag( DialogFlags::ButtonRight );
            rightButton.initButton( getWidth() - 12, getHeight() - 4, 10, 3, getInkColour(), getPaperColour() );
            rightButton.setButtonText( sButtonRight );
            rightButton.setWindowHandle( inWin );
        }
    }
    else
    {
        eError = LibraryError::IDEDialog_InitNotCalled;
    }

    // return state of initialisation
    return ( eError );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Setup the vertical scroll bar
    @return     LibraryError enum
----------------------------------------------------------------------------*/
LibraryError IDEDialog::setVerticalScroll()
{
    LibraryError eError = LibraryError::No_Error;
    if ( isReady() )
    {
        setUserFlag( DialogFlags::VerticalScroll );
    }
    else
    {
        eError = LibraryError::IDEDialog_InitNotCalled;
    }
    // return state of initialisation
    return ( eError );
}

// setters --------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Set the vertical scroll position
    @param      inPos     0-100 vertical scroll position
    @return     void
----------------------------------------------------------------------------*/
void IDEDialog::setVerticalScrollPos( uint32_t inPos )
{
    nScrollPos = inPos;
}

// Drawing and Control --------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      process the dialog conrols ( key and mouse )
    @param      key     Key press
    @return     LibraryError enum
----------------------------------------------------------------------------*/
LibraryError IDEDialog::processDialog( uint32_t key )
{
    LibraryError eError = LibraryError::No_Error;

    if ( isReady() )
    {
        // monotor key and mouse presses
        if ( key != ERR )
            setKey( key );
        processMouse();
        processKeyMaps();
        processControls( key, getMouseX(), getMouseY(), getLeftButtonState() );
    }
    else
    {
        eError = LibraryError::IDEDialog_InitNotCalled;
    }
    // return state of initialisation
    return ( eError );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Process the dialog
    @param      inKey       Key press
    @param      mouseX      Mouse x position
    @param      mouseY      Mouse y position
    @param      mouseButton Mouse button press
    @return     LibraryError enum
----------------------------------------------------------------------------*/
LibraryError IDEDialog::processControls( uint32_t inKey, uint32_t mouseX, uint32_t mouseY, bool leftMouseButton )
{
    LibraryError eError = LibraryError::No_Error;

    if ( isReady() )
    {
        // process the dialog
        if ( isUserFlagSet( DialogFlags::ButtonLeft ) )
        {
            leftButton.processClick( mouseX, mouseY );
        }
    }
    else
    {
        eError = LibraryError::IDEDialog_InitNotCalled;
    }

    // return state of process
    return ( eError );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Draw the dialog
    @return     LibraryError enum
----------------------------------------------------------------------------*/
LibraryError IDEDialog::drawDialog()
{
    LibraryError eError = LibraryError::No_Error;
    if ( isReady() )
    {
        // draw the title bar
        if ( isUserFlagSet( DialogFlags::TitleBar ) )
        {
            drawHorizontalLine( 1, 2, getWidth() - 2 );
            print( 2, 1, sTitle );
        }
        // draw the status bar
        if ( isUserFlagSet( DialogFlags::StatusBar ) )
        {
            drawHorizontalLine( 1, getHeight() - 6, getWidth() - 2 );
            print( 2, getHeight() - 5, sStatus );
        }
        // draw the buttons
        if ( isUserFlagSet( DialogFlags::ButtonLeft ) || isUserFlagSet( DialogFlags::ButtonRight ) )
        {
            // drawButtons();
            if ( isUserFlagSet( DialogFlags::ButtonLeft ) )
            {
                leftButton.drawButton();
            }
            if ( isUserFlagSet( DialogFlags::ButtonRight ) )
            {
                rightButton.drawButton();
            }
        }
        // draw the vertical scroll bar
        if ( isUserFlagSet( DialogFlags::VerticalScroll ) )
        {
            drawVerticalLine( getWidth() - 3, 3, getHeight() - 9 );
            // calculate the scroll position
            uint32_t nScrollHeight = getHeight() - 9;
            uint32_t nPos          = ( nScrollHeight * nScrollPos ) / 100;
            print( getWidth() - 2, nOldScrollPos + 3, " " );
            print( getWidth() - 2, nPos + 3, "\xDB" );
            nOldScrollPos = nPos;
        }
        // draw the window
        draw();
    }
    else
    {
        eError = LibraryError::IDEEditline_InitNotCalled;
        ErrorHandler::getInstance().handleError( ErrorType::Critical, eError, "IDEDialog::drawDialog" );
    }
    // return state of initialisation
    return ( LibraryError::No_Error );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      left button callback
    @param      mX      Mouse x position
    @param      mY      Mouse y position
    @return     void
----------------------------------------------------------------------------*/
void IDEDialog::leftButtonCB() noexcept
{
    leftButtonPressed = true;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      right button callback
    @param      mX      Mouse x position
    @param      mY      Mouse y position
    @return     void
----------------------------------------------------------------------------*/
void IDEDialog::rightButtonCB()
{
    leftButtonPressed = true;
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEDialog.cpp
// ----------------------------------------------------------------------------
