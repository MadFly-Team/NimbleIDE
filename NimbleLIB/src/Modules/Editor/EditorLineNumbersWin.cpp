/**----------------------------------------------------------------------------

    @file       EditorLineNumbersWin.cpp
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      EditorLineNumbersWin class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include "../../../inc/Modules/Editor/EditorLineNumbersWin.h"

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
    @brief      Constructor for EditorLineNumbersWin class
----------------------------------------------------------------------------*/
EditorLineNumbersWin::EditorLineNumbersWin()
{
    // create the status window
    CursesWin::init( WIN_WIDTH, WIN_HEIGHT, WIN_X, WIN_Y, WIN_INK_COLOUR, WIN_PAPER_COLOUR );
    colourWindow( COLOUR_INDEX( WIN_INK_COLOUR, WIN_PAPER_COLOUR ), true );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Destructor for EditorLineNumbersWin class
----------------------------------------------------------------------------*/
EditorLineNumbersWin::~EditorLineNumbersWin()
{
}

// display --------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Display the status window
----------------------------------------------------------------------------*/
void EditorLineNumbersWin::display()
{
    if ( m_editor != nullptr )
    {
        displayLineNumbers( m_editor->getCurrentLine() + 1, m_editor->getTotalLines() );
        // display the window
        draw();
    }
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Display the line numbers
    @param      nLine       current line number
    @param      nTotalLines total number of lines
    @return     LibraryError enum
----------------------------------------------------------------------------*/
LibraryError EditorLineNumbersWin::displayLineNumbers( uint32_t nLine, uint32_t nTotalLines )
{
    LibraryError error = LibraryError::IDEWindow_InitNotCalled;

    if ( m_editor != nullptr )
    {
        uint32_t nAmount = getHeight() - 2;
        for ( uint32_t i = 0; i < nAmount; i++ )
        {
            std::stringstream strStream;
            strStream << std::setw( 6 ) << std::setfill( ' ' ) << nLine + i;
            std::string line = strStream.str();
            if ( nLine + i > nTotalLines )
            {
                line = "      ";
            }
            print( 1, i + 1, line );
        }
        draw();
        error = LibraryError::No_Error;
    }

    return error;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Display the status window
----------------------------------------------------------------------------*/
void EditorLineNumbersWin::redrawBackground()
{
    if ( m_editor != nullptr )
    {
        colourWindow( COLOUR_INDEX( WIN_INK_COLOUR, WIN_PAPER_COLOUR ), true );
        // display the window
        display();
    }
}

// setters --------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Store the reference to the IDEEditor class
    @param      editor      pointer to the IDEEditor class
----------------------------------------------------------------------------*/
void EditorLineNumbersWin::setIDEEditor( IDEEditor* editor )
{
    m_editor = editor;
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: EditorLineNumbersWin.cpp
// ----------------------------------------------------------------------------
