/**----------------------------------------------------------------------------

    @file       EditorTitleWin.cpp
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      EditorTitleWin class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include <iomanip>
#include "../../../inc/Modules/Editor/EditorTitleWin.h"

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
    @brief      Constructor for EditorTitleWin class
----------------------------------------------------------------------------*/
EditorTitleWin::EditorTitleWin()
{
    // create the status window
    CursesWin::init( WIN_WIDTH, WIN_HEIGHT, WIN_X, WIN_Y, WIN_INK_COLOUR, WIN_PAPER_COLOUR );
    colourWindow( COLOUR_INDEX( WIN_INK_COLOUR, WIN_PAPER_COLOUR ), true );
    print( WIN_TITLE_X, WIN_TITLE_Y, WIN_TITLE );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Destructor for EditorTitleWin class
----------------------------------------------------------------------------*/
EditorTitleWin::~EditorTitleWin()
{
}

// display --------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Display the status window
----------------------------------------------------------------------------*/
void EditorTitleWin::display()
{
    if ( m_editor != nullptr )
    {
        // display the time and  date
        std::string streamString = returnTimeDate();
        print( COLS - 2 - streamString.length(), 1, streamString );
        mvwchgat( getWindow(), 1, COLS - 2 - streamString.length(), streamString.length(), A_NORMAL, COLOUR_INDEX( IDE_COL_FG_YELLOW, IDE_COL_BG_WHITE ), nullptr );
        draw();

        // display the file name
        print( 2, 1, "EDITING MODE: ./Test.txt " );

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
void EditorTitleWin::setIDEEditor( IDEEditor* editor )
{
    m_editor = editor;
}

// Private functions ----------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Function to return the current time and date as a string
    @return     std::string
 *----------------------------------------------------------------------------*/
std::string EditorTitleWin::returnTimeDate()
{
    auto              now       = std::chrono::system_clock::now();
    auto              in_time_t = std::chrono::system_clock::to_time_t( now );

    std::stringstream ss;
    ss << std::put_time( std::localtime( &in_time_t ), "%Y-%m-%d %X" );
    return ss.str();
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: EditorTitleWin.cpp
// ----------------------------------------------------------------------------
