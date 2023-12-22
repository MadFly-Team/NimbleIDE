/**----------------------------------------------------------------------------

    @file       IDEEditline.cpp
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEEditline class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

        please see CursesColour.cpp for full details.

Version:

        0.0.1.0     First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include "../../../inc/Modules/IDE/IDEEditline.h"

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

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file IDEEditline.cpp
//-----------------------------------------------------------------------------
