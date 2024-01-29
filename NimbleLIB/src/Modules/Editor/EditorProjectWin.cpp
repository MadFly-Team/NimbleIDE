/**----------------------------------------------------------------------------

    @file       EditorProjectWin.cpp
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      EditorProjectWin class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include "../../../inc/Modules/Editor/EditorProjectWin.h"

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
    @brief      Constructor for EditorProjectWin class
----------------------------------------------------------------------------*/
EditorProjectWin::EditorProjectWin()
{
    // create the status window
    CursesWin::init( WIN_WIDTH, WIN_HEIGHT, WIN_X, WIN_Y, WIN_INK_COLOUR, WIN_PAPER_COLOUR );
    colourWindow( COLOUR_INDEX( WIN_INK_COLOUR, WIN_PAPER_COLOUR ), true );
    print( WIN_TITLE_X, WIN_TITLE_Y, WIN_TITLE );

    // update the buttons
    m_button.initButton( 3, 1, 24, 3, IDE_COL_FG_BLUE, IDE_COL_BG_WHITE );
    m_button.setButtonText( "Button" );
    m_button.setWindowHandle( getWindow() );
    m_button2.initButton( 3, 4, 24, 7, IDE_COL_FG_GREEN, IDE_COL_BG_WHITE );
    m_button2.setButtonText( "Big Button" );
    m_button2.setWindowHandle( getWindow() );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Destructor for EditorProjectWin class
----------------------------------------------------------------------------*/
EditorProjectWin::~EditorProjectWin()
{
}

// display --------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Display the status window
----------------------------------------------------------------------------*/
void EditorProjectWin::display()
{
    if ( m_editor != nullptr )
    {
        // display the window
        draw();
        m_button.drawButton();
        m_button.processClick( m_editor->getMouseX(), m_editor->getMouseY() );
        m_button2.drawButton();
        m_button2.processClick( m_editor->getMouseX(), m_editor->getMouseY() );
    }
}

// setters --------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Store the reference to the IDEEditor class
    @param      editor      pointer to the IDEEditor class
----------------------------------------------------------------------------*/
void EditorProjectWin::setIDEEditor( IDEEditor* editor )
{
    m_editor = editor;
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: EditorProjectWin.cpp
// ----------------------------------------------------------------------------
