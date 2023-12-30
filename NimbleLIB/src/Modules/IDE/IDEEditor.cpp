/**----------------------------------------------------------------------------

    @file       IDEEditor.h
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEEditor class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:


Version:

        0.0.1.0     First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include "../../../inc/Modules/IDE/IDEEditor.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

// Constructors and Destructors -----------------------------------------------

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEEditor Constructor
-----------------------------------------------------------------------------*/
IDEEditor::IDEEditor()
{
    m_currentLine   = 0;
    m_currentColumn = 0;
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEEditor Destructor
-----------------------------------------------------------------------------*/
IDEEditor::~IDEEditor()
{
}

// Initialisation --------------------------------------------------------------

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Initialise the IDEEditor class
    @param      width   width of the editor
    @param      height  height of the editor
    @param      x       x position of the editor
    @param      y       y position of the editor
    @return     LibraryError    error code, if any
-----------------------------------------------------------------------------*/
LibraryError IDEEditor::init( uint32_t width, uint32_t height, uint32_t x, uint32_t y )
{
    LibraryError error = LibraryError::No_Error;

    if ( isNotInitialized() == false )
    {
        error = LibraryError::IDEEditor_AlreadyInitialized;
    }
    else
    {
        m_width  = width;
        m_height = height;
        m_xStart = x;
        m_yStart = y;

        // create the curses window
        m_editorWin = std::make_unique<CursesWin>( m_width, m_height + 1, m_xStart, m_yStart, COLOR_WHITE, COLOR_BLACK );
        setInitialized();
    }

    return error;
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Start the IDEEditor class
    @param      filename    filename to open
    @return     LibraryError    error code, if any
-----------------------------------------------------------------------------*/
LibraryError IDEEditor::start( std::string& filename )
{
    LibraryError error = LibraryError::No_Error;
    if ( isNotInitialized() )
    {
        error = LibraryError::IDEEditor_NotInitialized;
    }
    else
    {
        error = openFile( filename );
        if ( error == LibraryError::No_Error )
        {
            displayEditor();
        }
    }
    return error;
}

// display functions -----------------------------------------------------------

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      display the editor
    @return     LibraryError    error code
-----------------------------------------------------------------------------*/
LibraryError IDEEditor::displayEditor()
{
    LibraryError error   = LibraryError::No_Error;

    uint32_t     curline = 0;
    uint32_t     curcol  = m_currentColumn;

    std::string  blankline( m_width, ' ' );

    while ( curline < ( m_height ) && ( curline < ( m_height + m_editlines.size() - 1 ) ) )
    {
        std::string line;

        line = blankline;
        if ( ( curline + m_currentLine ) < m_editlines.size() )
        {
            line = m_editlines[ curline + m_currentLine ].getLineString();
        }

        // move to the current column, blanking if off screen
        if ( line.length() > 0 && line.length() >= curcol )
        {
            line = line.substr( curcol, m_width );
        }
        else
        {
            line = blankline;
        }

        // pad the line to the correct length
        if ( line.length() < m_width )
        {
            line += blankline.substr( curcol, m_width - line.length() );
        }
        else if ( line.length() > m_width )
        {
            line = line.substr( 0, m_width );
        }

        // print the line
        m_editorWin->print( 0, curline, line );
        curline++;
    }

    m_editorWin->draw();

    return error;
}

// getters --------------------------------------------------------------------

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      get the current line
    @return     uint32_t    current line
-----------------------------------------------------------------------------*/
uint32_t IDEEditor::getCurrentLine() const
{
    return m_currentLine;
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      get the current column
    @return     uint32_t    current column
-----------------------------------------------------------------------------*/
uint32_t IDEEditor::getCurrentColumn() const
{
    return m_currentColumn;
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      get the total lines
    @return     uint32_t    total lines
------------------------------------------------------------------------------*/
uint32_t IDEEditor::getTotalLines() const
{
    return m_editlines.size();
}

// control functions ----------------------------------------------------------

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      process the keys presses
    @param      key     key pressed
    @return     bool    true if display changed
------------------------------------------------------------------------------*/
bool IDEEditor::processKey( uint32_t key )
{
    bool displayChanged = false;

    if ( key != ERR )
    {
        switch ( key )
        {
            case 259: // up
            {
                if ( m_currentLine > 0 )
                {
                    m_currentLine--;
                    displayEditor();
                    displayChanged = true;
                }
                break;
            }
            case 258: // down
            {
                if ( m_currentLine < m_editlines.size() - 1 )
                {
                    m_currentLine++;
                    displayEditor();
                    displayChanged = true;
                }
                break;
            }
            case 339: // page up
            {
                m_currentLine -= m_height;
                if ( m_currentLine < 0 )
                {
                    m_currentLine = 0;
                }
                displayEditor();
                displayChanged = true;
                break;
            }
            case 338: // page down
            {
                m_currentLine += m_height;
                if ( m_currentLine > m_editlines.size() - 1 )
                {
                    m_currentLine = m_editlines.size() - 1;
                }
                displayEditor();
                displayChanged = true;
                break;
            }
            case 260: // left
            {
                if ( m_currentColumn > 0 )
                {
                    m_currentColumn--;
                    displayEditor();
                    displayChanged = true;
                }
                break;
            }
            case 261: // right
            {
                if ( m_currentColumn < 10000 )
                {
                    m_currentColumn++;
                    displayEditor();
                    displayChanged = true;
                }
                break;
            }
            default:
            {
                break;
            }
        }
    }
    return displayChanged;
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEEditor.h
// ----------------------------------------------------------------------------
