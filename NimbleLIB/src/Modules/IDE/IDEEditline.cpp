/**----------------------------------------------------------------------------

    @file       IDEEditline.cpp
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEEditline class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

    TODO - Hightlighting params, cursor position, get set text, delete text

Version:

        0.0.1.0     First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include "../../../inc/Modules/IDE/IDEEditline.h"
#include <cstdint>

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

// constructors & destructors --------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      constructor for IDEEditline class

-----------------------------------------------------------------------------*/
IDEEditline::IDEEditline()
{
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Destructor for IDEEditline class
-----------------------------------------------------------------------------*/
IDEEditline::~IDEEditline()
{
}

// Getters ---------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Get the X position of the line
    @return     uint32_t    X position of the line
-----------------------------------------------------------------------------*/
uint32_t IDEEditline::getLineXpos() const
{
    return lineXpos;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Get the Y position of the line
    @return     uint32_t    Y position of the line
-----------------------------------------------------------------------------*/
uint32_t IDEEditline::getLineYpos() const
{
    return lineYpos;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Get the length of the line
    @return     uint32_t    length of the line
-----------------------------------------------------------------------------*/
uint32_t IDEEditline::getLineLength() const
{
    return lineLength;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Get the ink colour of the line
    @return     uint32_t    ink colour of the line
-----------------------------------------------------------------------------*/
uint32_t IDEEditline::getLineInkColour() const
{
    return lineInkColour;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Get the paper or background colour of the line
    @return     uint32_t    paper or background colour of the line
-----------------------------------------------------------------------------*/
uint32_t IDEEditline::getLinePaperColour() const
{
    return linePaperColour;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Get the cursor position of the line
    @return     uint32_t    cursor position of the line
-----------------------------------------------------------------------------*/
uint32_t IDEEditline::getLineCursor() const
{
    return lineCursor;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Get the character at the specified index of the line buffer
    @param      index   index of the character to get
    @return     int8_t   character at the specified index of the line buffer
-----------------------------------------------------------------------------*/
uint8_t IDEEditline::getLineBufferChar( uint32_t index ) const
{
    uint8_t charToReturn = 0;

    if ( index < lineLength )
    {
        charToReturn = lineBuffer[ index ];
    }
    else
    {
        ErrorHandler::getInstance().handleError( ErrorType::Error, LibraryError::IDEEditline_IncorrectBufferIndex, "IDEEditline::getLineBufferChar() : index out of bounds" );
    }

    return ( charToReturn );
}

// setters ---------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Set the X position of the line
    @param      xpos    X position of the line
-----------------------------------------------------------------------------*/
void IDEEditline::setLineXpos( uint32_t xpos )
{
    lineXpos = xpos;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Set the Y position of the line
    @param      ypos    Y position of the line
-----------------------------------------------------------------------------*/
void IDEEditline::setLineYpos( uint32_t ypos )
{
    lineYpos = ypos;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Set the length of the line
    @param      length  length of the line
-----------------------------------------------------------------------------*/
void IDEEditline::setLineLength( uint32_t length )
{
    lineLength = length;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Set the ink colour of the line
    @param      inkColour   ink colour of the line
-----------------------------------------------------------------------------*/
void IDEEditline::setLineInkColour( uint32_t inkColour )
{
    lineInkColour = inkColour;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Set the paper or background colour of the line
    @param      paperColour paper or background colour of the line
-----------------------------------------------------------------------------*/
void IDEEditline::setLinePaperColour( uint32_t paperColour )
{
    linePaperColour = paperColour;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Set the cursor position of the line
    @param      cursor  cursor position of the line
-----------------------------------------------------------------------------*/
void IDEEditline::setLineCursor( uint32_t cursor )
{
    lineCursor = cursor;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Set the character at the specified index of the line buffer
    @param      index   index of the character to set
    @param      charToSet   character to set at the specified index of the line buffer
-----------------------------------------------------------------------------*/
void IDEEditline::setLineBufferChar( uint32_t index, uint8_t charToSet )
{
    if ( index < lineLength )
    {
        lineBuffer[ index ] = charToSet;
    }
    else
    {
        ErrorHandler::getInstance().handleError( ErrorType::Error, LibraryError::IDEEditline_IncorrectBufferIndex, "IDEEditline::setLineBufferChar() : index out of bounds" );
    }
}

// Initialisation --------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Initialises the IDEEditline object
    @param      inText  text to initialise the line with
    @param      inXpos  X position of the line
    @param      inYpos  Y position of the line
    @return     LibraryError    Error code or LibraryError::No_Error
-----------------------------------------------------------------------------*/
LibraryError IDEEditline::init( std::string& inText, uint32_t inXpos, uint32_t inYpos )
{
    LibraryError returnError = LibraryError::IDEEditline_AlreadyInitialized;

    if ( isInitialized() == false )
    {
        // initialise the line members
        lineXpos        = inXpos;
        lineYpos        = inYpos;
        lineLength      = inText.length();
        lineCursor      = 0;
        lineInkColour   = COLOR_WHITE;
        linePaperColour = COLOR_BLACK;

        // copy the text into the line buffer
        lineBuffer.clear();
        std::copy( inText.begin(), inText.end(), std::back_inserter( lineBuffer ) );

        // set the initialised flag
        setInitialized();

        // report that there was no error
        returnError = LibraryError::No_Error;
    }
    return ( returnError );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Sets the parameters, please note init() also needs to be called
                prior to the first time this is called.
    @param      inCursor    cursor position of the line
    @param      inInk       ink colour of the line
    @param      inPaper      paper or background colour of the line
    @return     LibraryError    Error code or LibraryError::No_Error
-----------------------------------------------------------------------------*/
LibraryError IDEEditline::setParams( uint32_t inCursor, uint32_t inInk, uint32_t inPaper )
{
    LibraryError returnError = LibraryError::IDEEditline_InitNotCalled;

    if ( isNotInitialized() == false )
    {
        // check the cursor is within the bounds of the line buffer
        if ( inCursor > lineLength )
        {
            ErrorHandler::getInstance().handleError( ErrorType::Warning, LibraryError::IDEEditline_IncorrectBufferIndex, "IDEEditline::setParams() : cursor out of bounds" );
            inCursor = lineLength - 1;
        }

        lineCursor      = inCursor;
        lineInkColour   = inInk;
        linePaperColour = inPaper;

        returnError     = LibraryError::No_Error;
    }

    return ( returnError );
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file IDEEditline.cpp
//-----------------------------------------------------------------------------
