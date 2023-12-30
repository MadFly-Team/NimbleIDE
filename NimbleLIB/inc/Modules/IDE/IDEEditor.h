/**----------------------------------------------------------------------------

    @file       IDEEditor.h
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEEditor class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

        please see IDEEditor.cpp for full details.

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

#include "../Curses/CursesWin.h"
#include "../ErrorHandling/ErrorHandler.h"
#include "../Utilities/StatusCtrl.h"
#include "IDEEditline.h"
#include "IDEFileHandler.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

class IDEEditor : protected IDEFileHandler
{
  public:
    // constructor & destructor -------------------------------------------------
    IDEEditor();
    ~IDEEditor();
    // initialisation ----------------------------------------------------------
    LibraryError init( uint32_t width, uint32_t height, uint32_t x, uint32_t y );
    LibraryError start( std::string& filename );
    // public functions --------------------------------------------------------
    // getters -----------------------------------------------------------------
    uint32_t getCurrentLine() const;
    uint32_t getCurrentColumn() const;
    uint32_t getTotalLines() const;
    // display functions -------------------------------------------------------
    LibraryError displayEditor();
    // control functions -------------------------------------------------------
    bool processKey( uint32_t key );

  private:
    // private variables -------------------------------------------------------
    uint32_t                   m_width;         //!< width of the editor window
    uint32_t                   m_height;        //!< height of the editor window
    uint32_t                   m_xStart;        //!< x position of the editor window
    uint32_t                   m_yStart;        //!< y position of the editor window
    int32_t                    m_currentLine;   //!< current line number
    int32_t                    m_currentColumn; //!< current column number
    std::unique_ptr<CursesWin> m_editorWin;     //!< editor window
};

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEEditor.h
// ----------------------------------------------------------------------------
