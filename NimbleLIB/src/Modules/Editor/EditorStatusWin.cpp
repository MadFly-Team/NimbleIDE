/**----------------------------------------------------------------------------

    @file       EditorStatusWin.cpp
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      EditorStatusWin class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include "../../../inc/Modules/Editor/EditorStatusWin.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class functions
// ----------------------------------------------------------------------------

// constructors & destructors -------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Constructor for EditorStatusWin class
----------------------------------------------------------------------------*/
EditorStatusWin::EditorStatusWin()
{
    // create the status window
    CursesWin::init( WIN_WIDTH, WIN_HEIGHT, WIN_X, WIN_Y, WIN_INK_COLOUR, WIN_PAPER_COLOUR );
    colourWindow( COLOUR_INDEX( WIN_INK_COLOUR, WIN_PAPER_COLOUR ), true );
    print( WIN_TITLE_X, WIN_TITLE_Y, WIN_TITLE );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Destructor for EditorStatusWin class
----------------------------------------------------------------------------*/
EditorStatusWin::~EditorStatusWin()
{
}

// display --------------------------------------------------------------------

void EditorStatusWin::display()
{
    if ( m_editor != nullptr )
    {
        std::stringstream strStream = std::stringstream();
        strStream << "Lines: " << m_editor->getTotalLines() << " Cursor: " << m_editor->getCursorX() << "," << m_editor->getCursorY();
        std::string linesString = strStream.str();
        linesString.resize( 34, ' ' );
        mvwprintw( getWindow(), 1, COLS - 35, linesString.c_str() );
        mvwchgat( getWindow(), 1, COLS - 28, 5, A_NORMAL, COLOUR_INDEX( IDE_COL_FG_GREEN, IDE_COL_BG_WHITE ), nullptr );
        mvwchgat( getWindow(), 1, COLS - 15, 13, A_NORMAL, COLOUR_INDEX( IDE_COL_FG_GREEN, IDE_COL_BG_WHITE ), nullptr );
        mvwprintw( getWindow(), 2, COLS - 35, "Mouse: %d, %d    ", m_editor->getMouseX(), m_editor->getMouseY() );
        draw();
    }
}

// setters --------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Store the reference to the IDEEditor class
    @param      editor      pointer to the IDEEditor class
----------------------------------------------------------------------------*/
void EditorStatusWin::setIDEEditor( IDEEditor* editor )
{
    m_editor = editor;
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: EditorStatusWin.cpp
// ----------------------------------------------------------------------------
