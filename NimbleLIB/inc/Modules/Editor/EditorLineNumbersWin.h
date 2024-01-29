/**----------------------------------------------------------------------------

    @file       EditorLineNumbersWin.h
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      EditorLineNumbersWin class for the Nimble Library

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
    @brief      EditorLineNumbersWin class for the Nimble Library
                Please note that CursesMouse is inherited privately, so that the
                the EditorLineNumbersWin can control the mouse events.
    @return     none
-----------------------------------------------------------------------------*/
class EditorLineNumbersWin : public IDEWindow
{
  public:
    // Enuums -----------------------------------------------------------------
    const uint32_t WIN_HEIGHT       = LINES - 8;        //!< height of the Project window
    const uint32_t WIN_WIDTH        = 9;                //!< width of the Project window
    const uint32_t WIN_X            = 0;                //!< x position of the Project window
    const uint32_t WIN_Y            = 4;                //!< y position of the Project window
    const uint32_t WIN_INK_COLOUR   = IDE_COL_FG_BLACK; //!< ink colour of the Project window
    const uint32_t WIN_PAPER_COLOUR = IDE_COL_BG_WHITE; //!< paper colour of the Project window
    // Constructor & destructor -----------------------------------------------
    EditorLineNumbersWin();
    ~EditorLineNumbersWin();
    // Public functions -------------------------------------------------------
    // setters ----------------------------------------------------------------
    void setIDEEditor( IDEEditor* editor );
    // display ----------------------------------------------------------------
    void         display();
    LibraryError displayLineNumbers( uint32_t nLine, uint32_t nTotalLines );
    void         redrawBackground();

  private:
    // Private constants ------------------------------------------------------
    // Private functions ------------------------------------------------------
    // Private members --------------------------------------------------------
    IDEEditor* m_editor = nullptr; //!< refernece to the editor/IDE
};

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: EditorLineNumbersWin.h
// ----------------------------------------------------------------------------
