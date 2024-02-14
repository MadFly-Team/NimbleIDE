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
#include "../../../inc/Modules/Global/Globals.h"

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

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Display the status window
----------------------------------------------------------------------------*/
void EditorStatusWin::display( bool bRedraw /*= false*/ )
{
    if ( m_editor != nullptr )
    {
        if ( bRedraw == true )
        {
            colourWindow( COLOUR_INDEX( WIN_INK_COLOUR, WIN_PAPER_COLOUR ), true );
            print( WIN_TITLE_X, WIN_TITLE_Y, WIN_TITLE );
        }
        // display the line position and total lines, also the mosue position
        std::stringstream strStream = std::stringstream();
        strStream << "Lines: " << m_editor->getTotalLines() << " Cursor: " << m_editor->getCursorX() << "," << m_editor->getCursorY();
        std::string linesString = strStream.str();
        linesString.resize( STATUS_EDITORXOFFSET - 1, ' ' );
        mvwprintw( getWindow(), STATUS_EDITORLINE, COLS - STATUS_EDITORXOFFSET, linesString.c_str() );
        mvwchgat( getWindow(), STATUS_EDITORLINE, COLS - STATUS_EDITORCOLOFFSET1, STATUS_EDITORCOLOFFSET1SZ, A_NORMAL, COLOUR_INDEX( IDE_COL_FG_GREEN, IDE_COL_BG_WHITE ), nullptr );
        mvwchgat( getWindow(), STATUS_EDITORLINE, COLS - STATUS_EDITORCOLOFFSET2, STATUS_EDITORCOLOFFSET2SZ, A_NORMAL, COLOUR_INDEX( IDE_COL_FG_GREEN, IDE_COL_BG_WHITE ), nullptr );
        mvwprintw( getWindow(), STATUS_EDITORMOUSE, COLS - STATUS_EDITORXOFFSET, "Mouse: %d, %d    ", GControl.getMouseX(), GControl.getMouseY() );
        mvwprintw( getWindow(), STATUS_EDITORMOUSE, 4, "Componets active - %d", GControl.getManagerComponents() );
        // display the window
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
