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
    LibraryError eError = CursesWin::init( x, y, width, height, ink, paper );
    if ( eError != LibraryError::No_Error )
    {
        return eError;
    }
    // initialise the dialog
    nFrameCount  = 0;
    sTitle       = "";
    sStatus      = "";
    sButtonLeft  = "";
    sButtonRight = "";

    setReady();

    // return state of initialisation
    return ( eError );
}

// initialisation -----------------------------------------------------------

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
    return ( LibraryError::No_Error );
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
    return ( LibraryError::No_Error );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Setup the buttons
    @param      inButtonLeft    Left button string for the dialog
    @param      inButtonRight   Right button string for the dialog
    @return     LibraryError enum
----------------------------------------------------------------------------*/
LibraryError IDEDialog::buttons( const std::string& inButtonLeft, const std::string& inButtonRight )
{
    LibraryError eError = LibraryError::No_Error;
    if ( isReady() )
    {
        if ( inButtonLeft.length() > 0 )
        {
            sButtonLeft = inButtonLeft;
            setUserFlag( DialogFlags::ButtonLeft );
        }
        if ( inButtonRight.length() > 0 )
        {
            sButtonRight = inButtonRight;
            setUserFlag( DialogFlags::ButtonRight );
        }
    }
    else
    {
        eError = LibraryError::IDEDialog_InitNotCalled;
    }

    // return state of initialisation
    return ( LibraryError::No_Error );
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
    return ( LibraryError::No_Error );
}

// Drawing --------------------------------------------------------------------

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
            drawHorizontalLine( 1, getHeight() - 3, getWidth() - 2 );
            print( 2, getHeight() - 2, sStatus );
        }
        // draw the buttons
        if ( isUserFlagSet( DialogFlags::ButtonLeft ) || isUserFlagSet( DialogFlags::ButtonRight ) )
        {
            // drawButtons();
        }
        // draw the vertical scroll bar
        if ( isUserFlagSet( DialogFlags::VerticalScroll ) )
        {
            drawVerticalLine( getWidth() - 3, 3, getHeight() - 6 );
            print( getWidth() - 2, 3, "\xDB" );
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

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEDialog.cpp
// ----------------------------------------------------------------------------
