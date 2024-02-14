/**----------------------------------------------------------------------------

    @file       EditorStatusWin.h
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      EditorStatusWin class for the Nimble Library

    @copyright  Neil Bereford 2023

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include "../IDE/IDEWindow.h"
#include "../IDE/IDEEditor.h"
#include "../Curses/CursesColour.h"

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
    @brief      EditorStatusWin class for the Nimble Library
                Please note that CursesMouse is inherited privately, so thatthe
                the EditorStatusWin can control the mouse events.
    @return     none
-----------------------------------------------------------------------------*/
class EditorStatusWin : public IDEWindow
{
  public:
    // Enuums -----------------------------------------------------------------
    const uint32_t    WIN_HEIGHT       = 4;                                  //!< height of the status window
    const uint32_t    WIN_WIDTH        = COLS;                               //!< width of the status window
    const uint32_t    WIN_X            = 0;                                  //!< x position of the status window
    const uint32_t    WIN_Y            = LINES - WIN_HEIGHT;                 //!< y position of the status window
    const uint32_t    WIN_INK_COLOUR   = IDE_COL_FG_BLACK;                   //!< ink colour of the status window
    const uint32_t    WIN_PAPER_COLOUR = IDE_COL_BG_WHITE;                   //!< paper colour of the status window
    const std::string WIN_TITLE        = " Status Bar : Press 'q' to quit "; //!< title of the status window
    const uint32_t    WIN_TITLE_X      = 2;                                  //!< x position of the title of the status window
    const uint32_t    WIN_TITLE_Y      = 0;                                  //!< y position of the title of the status window
    // Constructor & destructor -----------------------------------------------
    EditorStatusWin();
    ~EditorStatusWin();
    // Public functions -------------------------------------------------------
    // setters ----------------------------------------------------------------
    void setIDEEditor( IDEEditor* editor );
    // display ----------------------------------------------------------------
    void display( bool bRedraw = false );

  private:
    // Private constants ------------------------------------------------------
    const uint32_t STATUS_EDITORLINE         = 1;                         //!< line number for editor status
    const uint32_t STATUS_EDITORMOUSE        = 2;                         //!< mouse status for editor status
    const uint32_t STATUS_EDITORXOFFSET      = 35;                        //!< x offset for editor status
    const uint32_t STATUS_EDITORCOLOFFSET1   = STATUS_EDITORXOFFSET - 7;  //!< colour offset for editor lines
    const uint32_t STATUS_EDITORCOLOFFSET1SZ = 5;                         //!< colour offset size for editor lines
    const uint32_t STATUS_EDITORCOLOFFSET2   = STATUS_EDITORXOFFSET - 20; //!< colour offset for editor cursor position
    const uint32_t STATUS_EDITORCOLOFFSET2SZ = 13;                        //!< colour offset size for editor cursor position
    // Private functions ------------------------------------------------------
    // Private members --------------------------------------------------------
    IDEEditor* m_editor = nullptr; //!< refernece to the editor/IDE
};

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: EditorStatusWin.h
// ----------------------------------------------------------------------------
