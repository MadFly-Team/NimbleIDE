/**----------------------------------------------------------------------------

    @file       IDEEditline.h
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEEditline class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

        please see IDEEditline.cpp for full details.

Version:

        0.0.1.0     First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include <cinttypes>
#include <cstdint>
#include <memory>
#include <vector>
#include <sstream>

extern "C"
{
#include "../../../../ExternalLibraries/PDCurses/curses.h"
}

#include "../ErrorHandling/ErrorHandler.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

class IDEEditline
{
  public:
    // constructors & destructors ----------------------------------------------
    IDEEditline();
    ~IDEEditline();
    // public functions --------------------------------------------------------
    // getters -----------------------------------------------------------------
    uint32_t getLineXpos() const;
    uint32_t getLineYpos() const;
    uint32_t getLineLength() const;
    uint32_t getLineInkColour() const;
    uint32_t getLinePaperColour() const;
    uint32_t getLineCursor() const;
    uint8_t  getLineBufferChar( uint32_t index ) const;
    // setters -----------------------------------------------------------------
    void setLineXpos( uint32_t xpos );
    void setLineYpos( uint32_t ypos );
    void setLineLength( uint32_t length );
    void setLineInkColour( uint32_t inkColour );
    void setLinePaperColour( uint32_t paperColour );
    void setLineCursor( uint32_t cursor );
    void setLineBufferChar( uint32_t index, int8_t value );

  private:
    // private variables --------------------------------------------------------
    uint32_t            lineXpos;        //!< X position of line
    uint32_t            lineYpos;        //!< Y position of line
    uint32_t            lineLength;      //!< Length of line
    uint32_t            lineInkColour;   //!< Ink colour of line
    uint32_t            linePaperColour; //!< Paper colour of line
    uint32_t            lineCursor;      //!< X position of cursor
    std::vector<int8_t> lineBuffer;      //!< Buffer for line
};

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEEditline.h
// ----------------------------------------------------------------------------
