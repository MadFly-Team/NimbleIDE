/**----------------------------------------------------------------------------

    @file       EditorTitleWin.h
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      EditorTitleWin class for the Nimble Library

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
    @brief      EditorTitleWin class for the Nimble Library
                Please note that CursesMouse is inherited privately, so that the
                the EditorTitleWin can control the mouse events.
    @return     none
-----------------------------------------------------------------------------*/
class EditorTitleWin : public IDEWindow
{
  public:
    // Enuums -----------------------------------------------------------------
    const uint32_t    WIN_HEIGHT       = 4;                              //!< height of the Project window
    const uint32_t    WIN_WIDTH        = COLS;                           //!< width of the Project window
    const uint32_t    WIN_X            = 0;                              //!< x position of the Project window
    const uint32_t    WIN_Y            = 0;                              //!< y position of the Project window
    const uint32_t    WIN_INK_COLOUR   = IDE_COL_FG_BLACK;               //!< ink colour of the Project window
    const uint32_t    WIN_PAPER_COLOUR = IDE_COL_BG_WHITE;               //!< paper colour of the Project window
    const std::string WIN_TITLE        = " Nimble IDE : Version 0.0.1 "; //!< title of the Project window
    const uint32_t    WIN_TITLE_X      = 2;                              //!< x position of the title of the Project window
    const uint32_t    WIN_TITLE_Y      = 0;                              //!< y position of the title of the Project window
    // Constructor & destructor -----------------------------------------------
    EditorTitleWin();
    ~EditorTitleWin();
    // Public functions -------------------------------------------------------
    // setters ----------------------------------------------------------------
    void setIDEEditor( IDEEditor* editor );
    // display ----------------------------------------------------------------
    void display( bool bRedraw = false );

  private:
    // Private constants ------------------------------------------------------
    // Private functions ------------------------------------------------------
    std::string returnTimeDate();
    // Private members --------------------------------------------------------
    IDEEditor* m_editor = nullptr; //!< refernece to the editor/IDE
};

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: EditorTitleWin.h
// ----------------------------------------------------------------------------
