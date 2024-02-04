/**----------------------------------------------------------------------------

    @file       EditorHexWin.cpp
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      EditorHexWin class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include <cstdint>
#include <iomanip>
#include "../../../inc/Modules/Editor/EditorHexWin.h"

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
    @brief      Constructor for EditorHexWin class
----------------------------------------------------------------------------*/
EditorHexWin::EditorHexWin()
{
    // create the status window
    CursesWin::init( WIN_WIDTH, WIN_HEIGHT, WIN_X, WIN_Y, WIN_INK_COLOUR, WIN_PAPER_COLOUR );
    colourWindow( COLOUR_INDEX( WIN_INK_COLOUR, WIN_PAPER_COLOUR ), true );
    print( WIN_TITLE_X, WIN_TITLE_Y, WIN_TITLE );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Destructor for EditorHexWin class
----------------------------------------------------------------------------*/
EditorHexWin::~EditorHexWin()
{
}

// display --------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Display the status window
----------------------------------------------------------------------------*/
void EditorHexWin::display()
{
    if ( m_editor != nullptr )
    {
        // clear the window
        clear();
        // display the title
        print( WIN_TITLE_X, WIN_TITLE_Y, WIN_TITLE );
        // display the data
        int      line   = 1;
        int      col    = 0;
        uint8_t* offset = (uint8_t*)getWindow();

        while ( line < WIN_HEIGHT - 1 )
        {
            // display the offset
            mvwprintw( getWindow(), line, 2, "%08X", offset );
            // display the data
            col = 0;
            while ( col < 16 )
            {
                mvwprintw( getWindow(), line, 13 + ( col * 3 ), "%02X", offset[ line * 16 + col ] );
                col++;
                offset++;
            }
            line++;
        }

        // display the window
        draw();
    }
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Display the status window
----------------------------------------------------------------------------*/
void EditorHexWin::redrawBackground()
{
    if ( m_editor != nullptr )
    {
        colourWindow( COLOUR_INDEX( WIN_INK_COLOUR, WIN_PAPER_COLOUR ), true );
        print( WIN_TITLE_X, WIN_TITLE_Y, WIN_TITLE );
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
void EditorHexWin::setIDEEditor( IDEEditor* editor )
{
    m_editor = editor;
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: EditorHexWin.cpp
// ----------------------------------------------------------------------------
