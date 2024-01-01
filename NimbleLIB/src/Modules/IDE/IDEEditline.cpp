/**----------------------------------------------------------------------------

    @file       IDEEditline.cpp
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEEditline class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:


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
    lineBufferLimit = 27;
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

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Get the start of the hilight
    @return     uint32_t    start of the hilight
-----------------------------------------------------------------------------*/
uint32_t IDEEditline::getHilightStart() const
{
    return hilightStart;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Get the end of the hilight
    @return     uint32_t    end of the hilight
-----------------------------------------------------------------------------*/
uint32_t IDEEditline::getHilightEnd() const
{
    return hilightEnd;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Get the line buffer as a string
    @return     std::string line buffer as a string
-----------------------------------------------------------------------------*/
std::string IDEEditline::getLineString() const
{
    return std::string( lineBuffer.begin(), lineBuffer.end() );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Get the line buffer limit
    @return     uint32 line buffer limit
-----------------------------------------------------------------------------*/
uint32_t IDEEditline::getLineBufferLimit() const
{
    return lineBufferLimit;
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

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Set the start of the hilight
    @param      start   start of the hilight
-----------------------------------------------------------------------------*/
void IDEEditline::setHilightStart( uint32_t start )
{
    hilightStart = start;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Set the end of the hilight
    @param      end     value for the highlight end
-----------------------------------------------------------------------------*/
void IDEEditline::setHilightEnd( uint32_t end )
{
    hilightEnd = end;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Set the line buffer limit
    @param      limit     line buffer limit
-----------------------------------------------------------------------------*/
void IDEEditline::setLineBufferLimit( uint32_t limit )
{
    lineBufferLimit = limit;
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
            inCursor = lineLength;
        }

        lineCursor      = inCursor;
        lineInkColour   = inInk;
        linePaperColour = inPaper;

        returnError     = LibraryError::No_Error;
    }

    return ( returnError );
}

// Editing ---------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Inserts a character at the cursor position
    @param      inChar  character to insert
    @return     LibraryError    Error code or LibraryError::No_Error
-----------------------------------------------------------------------------*/
LibraryError IDEEditline::addChar( uint8_t inChar )
{
    LibraryError returnError = LibraryError::IDEEditline_InitNotCalled;
    if ( isNotInitialized() == false )
    {
        // check the cursor is within the bounds of the line buffer
        if ( lineCursor > lineLength )
        {
            ErrorHandler::getInstance().handleError( ErrorType::Warning, LibraryError::IDEEditline_IncorrectBufferIndex, "IDEEditline::insertChar() : cursor out of bounds" );
            lineCursor = lineLength;
        }
        // insert the character at the cursor position
        lineBuffer.insert( lineBuffer.begin() + lineCursor, inChar );
        // increment the line length
        lineLength++;
        lineBufferLimit++;
        // increment the cursor position
        lineCursor++;
        returnError = LibraryError::No_Error;
    }
    return ( returnError );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Deletes a character at the cursor position
    @return     LibraryError    Error code or LibraryError::No_Error
-----------------------------------------------------------------------------*/
LibraryError IDEEditline::deleteChar( void )
{
    LibraryError returnError = LibraryError::IDEEditline_InitNotCalled;
    if ( isNotInitialized() == false )
    {
        if ( lineLength > 0 )
        {
            // delete the character at the cursor position
            if ( lineCursor > 0 )
            {
                lineCursor--;
            }
            // check the cursor is within the bounds of the line buffer
            if ( lineCursor >= lineLength )
            {
                ErrorHandler::getInstance().handleError( ErrorType::Warning, LibraryError::IDEEditline_IncorrectBufferIndex, "IDEEditline::deleteChar() : cursor out of bounds" );
                lineCursor = lineLength - 1;
            }
            lineBuffer[ lineLength - 1 ] = 0;
            lineBuffer.erase( lineBuffer.begin() + lineCursor );
            // decrement the line length
            lineLength--;
            lineBufferLimit--;
        }
        returnError = LibraryError::No_Error;
    }
    return ( returnError );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      adds a string at the cursor position
    @return     LibraryError    Error code or LibraryError::No_Error
-----------------------------------------------------------------------------*/
LibraryError IDEEditline::addString( std::string& inString )
{
    LibraryError returnError = LibraryError::IDEEditline_InitNotCalled;
    if ( isNotInitialized() == false )
    {
        // check the cursor is within the bounds of the line buffer
        if ( lineCursor > lineLength )
        {
            ErrorHandler::getInstance().handleError( ErrorType::Warning, LibraryError::IDEEditline_IncorrectBufferIndex, "IDEEditline::insertString() : cursor out of bounds" );
            lineCursor = lineLength;
        }
        // insert the string at the cursor position
        lineBuffer.insert( lineBuffer.begin() + lineCursor, inString.begin(), inString.end() );
        // increment the line length
        lineLength += inString.length();
        // increment the cursor position
        lineCursor += inString.length();
        returnError = LibraryError::No_Error;
    }
    return ( returnError );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Deletes a numver of char starting at the cursor position
    @return     LibraryError    Error code or LibraryError::No_Error
-----------------------------------------------------------------------------*/
LibraryError IDEEditline::deleteChars( uint32_t numChars )
{
    LibraryError returnError = LibraryError::IDEEditline_InitNotCalled;
    if ( isNotInitialized() == false )
    {
        // check the cursor is within the bounds of the line buffer
        if ( lineCursor >= lineLength )
        {
            ErrorHandler::getInstance().handleError( ErrorType::Warning, LibraryError::IDEEditline_IncorrectBufferIndex, "IDEEditline::deleteChars() : cursor out of bounds" );
            lineCursor = lineLength - 1;
        }
        // delete the character at the cursor position
        lineBuffer.erase( lineBuffer.begin() + lineCursor );
        // decrement the line length
        lineLength--;
        returnError = LibraryError::No_Error;
    }
    return ( returnError );
}

// Navigation ------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Moves the cursor to the left
    @return     LibraryError    Error code or LibraryError::No_Error
-----------------------------------------------------------------------------*/
LibraryError IDEEditline::moveCursorLeft( void )
{
    LibraryError returnError = LibraryError::IDEEditline_InitNotCalled;
    if ( isNotInitialized() == false )
    {
        // check the cursor is within the bounds of the line buffer
        if ( lineCursor > lineLength )
        {
            ErrorHandler::getInstance().handleError( ErrorType::Warning, LibraryError::IDEEditline_IncorrectBufferIndex, "IDEEditline::moveCursorLeft() : cursor out of bounds" );
            lineCursor = lineLength;
        }
        // decrement the cursor position
        if ( lineCursor > 0 )
        {
            lineCursor--;
        }
        returnError = LibraryError::No_Error;
    }
    return ( returnError );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Moves the cursor to the right
    @return     LibraryError    Error code or LibraryError::No_Error
-----------------------------------------------------------------------------*/
LibraryError IDEEditline::moveCursorRight( void )
{
    LibraryError returnError = LibraryError::IDEEditline_InitNotCalled;
    if ( isNotInitialized() == false )
    {
        // check the cursor is within the bounds of the line buffer
        if ( lineCursor > lineLength )
        {
            ErrorHandler::getInstance().handleError( ErrorType::Warning, LibraryError::IDEEditline_IncorrectBufferIndex, "IDEEditline::moveCursorRight() : cursor out of bounds" );
            lineCursor = lineLength;
        }
        // increment the cursor position
        if ( lineCursor < lineLength )
            lineCursor++;

        returnError = LibraryError::No_Error;
    }
    return ( returnError );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Moves the cursor to the start of the line
    @return     LibraryError    Error code or LibraryError::No_Error
-----------------------------------------------------------------------------*/
LibraryError IDEEditline::moveCursorHome( void )
{
    LibraryError returnError = LibraryError::IDEEditline_InitNotCalled;
    if ( isNotInitialized() == false )
    {
        lineCursor  = 0;
        returnError = LibraryError::No_Error;
    }
    return ( returnError );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Moves the cursor to the end of the line
    @return     LibraryError    Error code or LibraryError::No_Error
-----------------------------------------------------------------------------*/
LibraryError IDEEditline::moveCursorEnd( void )
{
    LibraryError returnError = LibraryError::IDEEditline_InitNotCalled;
    if ( isNotInitialized() == false )
    {
        lineCursor  = lineLength;
        returnError = LibraryError::No_Error;
    }
    return ( returnError );
}

// FLag control ----------------------------------------------------------------
/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Sets the Editline flags
    @param      inFlag     Flag to set
    @return     LibraryError    Error code or LibraryError::No_Error

-----------------------------------------------------------------------------*/
LibraryError IDEEditline::setEditlineFlag( EditlineFlags inFlag )
{
    LibraryError returnError = LibraryError::IDEEditline_InitNotCalled;
    if ( isNotInitialized() == false )
    {
        setUserFlag( (uint32_t)inFlag );
        returnError = LibraryError::No_Error;
    }
    return ( returnError );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Clears the Editline flags
    @param      inFlag     Flag to clear
    @return     LibraryError    Error code or LibraryError::No_Error
-----------------------------------------------------------------------------*/
LibraryError IDEEditline::clearEditlineFlag( EditlineFlags inFlag )
{
    LibraryError returnError = LibraryError::IDEEditline_InitNotCalled;
    if ( isNotInitialized() == false )
    {
        clearUserFlag( (uint32_t)inFlag );
        returnError = LibraryError::No_Error;
    }
    return ( returnError );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Gets the Editline flag
    @param      inFlag     Flag to get
    @return     bool    true if flag is set

-----------------------------------------------------------------------------*/
bool IDEEditline::isEditlineFlagSet( EditlineFlags inFlag ) const noexcept
{
    bool returnFlag = false;
    if ( isNotInitialized() == false )
    {
        returnFlag = isUserFlagSet( (uint32_t)inFlag );
    }
    return ( returnFlag );
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file IDEEditline.cpp
//-----------------------------------------------------------------------------
