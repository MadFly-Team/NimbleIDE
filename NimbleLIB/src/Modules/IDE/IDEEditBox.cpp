/**----------------------------------------------------------------------------

    @file       IDEEditBox.cpp
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEEditBox class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

-----------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include <iomanip>
#include "../../../inc/Modules/IDE/IDEEditBox.h"
#include <sstream>

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
    @brief      Constructor for IDEEditBox class

----------------------------------------------------------------------------*/
IDEEditBox::IDEEditBox()
{
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Destructor for IDEEditBox class

----------------------------------------------------------------------------*/
IDEEditBox::~IDEEditBox()
{
}

// initialisation -----------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Initialise the IDEEditBox class
    @param      x       x position of the window
    @param      y       y position of the window
    @param      width   width of the window
    @param      height  height of the window
    @param      ink     ink colour of the window
    @param      paper   paper colour of the window
    @return     LibraryError     Any errors generated, otherwise No_Error
----------------------------------------------------------------------------*/
LibraryError IDEEditBox::initBox( int16_t x, int16_t y, int16_t width, int16_t height, int16_t ink, int16_t paper )
{
    LibraryError error = LibraryError::IDEEditBox_InitAlreadyCalled;

    if ( isInitialized() == false )
    {
        // initialise the base class Editline
        std::string edittext = "Edit text here";
        error                = IDEEditline::init( edittext, 1, 2 );

        if ( error == LibraryError::No_Error )
        {
            // set the editline as editable
            setParams( 0, ink, paper );
            setLineBufferLimit( width - 3 );
            // and initialise the curses window
            error = CursesWin::init( width, height, x, y, ink, paper );
            if ( error == LibraryError::No_Error )
            {
                draw();
                // set as initialised
                setInitialized();
            }
            else
            {
                ErrorHandler::getInstance().handleError( ErrorType::Error, LibraryError::IDEEditBox_FailedToCreateWindow, "IDEEditBox - init() failed to create window" );
            }
        }
    }
    else
    {
        ErrorHandler::getInstance().handleError( ErrorType::Warning, LibraryError::IDEEditBox_InitAlreadyCalled, "IDEEditBox - init() already called, ignored" );
    }

    return ( error );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Process the IDEEditBox class
    @return     LibraryError     Any errors generated, otherwise No_Error
-----------------------------------------------------------------------------*/
LibraryError IDEEditBox::process( uint32_t key )
{
    LibraryError error = LibraryError::No_Error;

    nFrameCount++;
    std::string text = getLineString();

    if ( key != ERR )
    {
        switch ( key )
        {
            case 8:
            case 330:
            {
                deleteChar();
                text = getLineString();
                break;
            }
            case KEY_LEFT:
            {
                moveCursorLeft();
                break;
            }
            case KEY_RIGHT:
            {
                moveCursorRight();
                break;
            }
            case 262: // home
            {
                moveCursorHome();
                break;
            }
            case 358: // end
            {
                moveCursorEnd();
                break;
            }
            default:
            {
                if ( key >= 30 && key < 128 )
                {
                    addChar( key );
                    text = getLineString();
                }
                break;
            }
        }
    }

    uint32_t len = text.length();
    if ( len > getWidth() - 3 )
        text = text.substr( len - getWidth() + 3, getWidth() - 3 );

    std::string blankString = "";
    for ( int16_t i = 0; i < getWidth() - 2; i++ ) blankString += " ";

    print( 1, 1, blankString );
    print( 1, 1, text );

    uint32_t cursorPos = getLineCursor();
    if ( getLineLength() > getWidth() - 3 )
    {
        cursorPos = getLineCursor() - ( getLineLength() - ( getWidth() - 3 ) );
    }

    // print the cursor, if required
    if ( ( nFrameCount & 7 ) == 0 )
        bCursorDrawn = bCursorDrawn ? false : true;

    if ( bCursorDrawn )
    {
        if ( cursorPos > getWidth() - 3 )
        {
            cursorPos = getWidth() - 3;
        }
        print( cursorPos + 1, 1, "\xDB" );
    }

    draw();
    return ( error );
}

// special functions ----------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      special function - displays line numbers
    @param      nLine    Starting line number
    @param      nTotalLines Total number of lines
    @return     LibraryError     Any errors generated, otherwise No_Error
-----------------------------------------------------------------------------*/
LibraryError IDEEditBox::displayLineNumbers( uint32_t nLine, uint32_t nTotalLines )
{
    LibraryError error = LibraryError::IDEEditBox_InitNotCalled;

    if ( isInitialized() )
    {
        uint32_t nAmount = getHeight() - 2;
        for ( uint32_t i = 0; i < nAmount; i++ )
        {
            std::stringstream strStream;
            strStream << std::setw( 6 ) << std::setfill( ' ' ) << nLine + i;
            std::string line = strStream.str();
            if ( nLine + i > nTotalLines )
            {
                line = "      ";
            }
            print( 1, i + 1, line );
        }
        draw();
        error = LibraryError::No_Error;
    }

    return error;
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEEditBox.cpp
// ----------------------------------------------------------------------------
