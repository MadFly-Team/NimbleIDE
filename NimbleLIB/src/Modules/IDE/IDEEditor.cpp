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
#include <cstdint>

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
    m_cursorX       = 0;
    m_cursorY       = 0;
    m_oldCursorX    = 0;
    m_oldCursorY    = 0;
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
        m_editorWin  = std::make_unique<CursesWin>( m_width, m_height + 1, m_xStart, m_yStart, COLOR_WHITE, COLOR_BLACK );
        m_overlayWin = std::make_unique<CursesWin>( m_width, m_height + 1, m_xStart, m_yStart, COLOR_WHITE, COLOR_BLACK );
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
            uint32_t nPad = m_width - line.length();
            line += blankline.substr( 0, nPad );
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
    @brief      process the keys presses for EDIT mode
    @param      key     key pressed
    @return     bool    true if display changed
------------------------------------------------------------------------------*/
bool IDEEditor::processKeyEdit( uint32_t key )
{
    bool displayChanged = false;

    if ( key != ERR )
    {

        displayChanged = checkCursorKeys( key );
        if ( displayChanged == false )
        {
            displayChanged = checkEditKeys( key );
        }
    }

    return displayChanged;
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      process the keys presses
    @param      key     key pressed
    @return     bool    true if display changed
------------------------------------------------------------------------------*/
bool IDEEditor::processKeyViewOnly( uint32_t key )
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
                    displayChanged = true;
                }
                break;
            }
            case 258: // down
            {
                if ( m_currentLine < m_editlines.size() - 1 )
                {
                    m_currentLine++;
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
                displayChanged = true;
                break;
            }
            case 260: // left
            {
                if ( m_currentColumn > 0 )
                {
                    m_currentColumn--;
                    displayChanged = true;
                }
                break;
            }
            case 261: // right
            {
                if ( m_currentColumn < 10000 )
                {
                    m_currentColumn++;
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

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      process the dispay
    @return     bool    true if display changed
-----------------------------------------------------------------------------*/
bool IDEEditor::processDisplay()
{
    bool        displayChanged = false;
    std::string charStr        = " ";

    // flash the cursor...
    m_frameCount++;
    if ( ( m_frameCount & 0x7 ) == 0 )
    {
        m_cursorDrawn = m_cursorDrawn ? false : true;
    }

    charStr[ 0 ] = getCharFromEditor( m_oldCursorX, m_oldCursorY );
    m_overlayWin->print( m_oldCursorX, m_oldCursorY, charStr );

    if ( m_cursorDrawn )
    {
        m_overlayWin->print( m_cursorX, m_cursorY, "\xDB" );
    }
    m_overlayWin->draw();
    return displayChanged;
}

// private functions ----------------------------------------------------------

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      check the cursor keys
    @param      key     key pressed
    @return     bool    true if display changed
-----------------------------------------------------------------------------*/
bool IDEEditor::checkCursorKeys( uint32_t key )
{
    bool displayChanged = false;

    switch ( key )
    {
        case 259: // up
        {
            if ( m_cursorY > 0 )
            {
                m_cursorY--;
                displayChanged = true;
            }
            else
            {
                if ( m_currentLine > 0 )
                {
                    m_currentLine--;
                    displayChanged = true;
                }
            }
            break;
        }
        case 258: // down
        {
            if ( m_cursorY < m_height - 1 )
            {
                m_cursorY++;
                displayChanged = true;
            }
            else
            {
                if ( m_currentLine <= m_editlines.size() - 1 )
                {
                    m_currentLine++;
                    displayChanged = true;
                }
            }
            break;
        }
        case 260: // left
        {
            if ( m_cursorX > 0 )
            {
                m_cursorX--;
                displayChanged = true;
            }
            else
            {
                if ( m_currentColumn > 0 )
                {
                    uint32_t adj = ( m_currentColumn > 16 ) ? 16 : m_currentColumn;
                    m_currentColumn -= adj;
                    m_cursorX += adj;
                    displayChanged = true;
                }
            }
            break;
        }
        case 261: // right
        {
            if ( m_cursorX < m_width - 1 )
            {
                m_cursorX++;
                displayChanged = true;
            }
            else
            {
                m_currentColumn += 16;
                m_cursorX -= 16;
                displayChanged = true;
            }
            break;
        }
        default:
        {
            break;
        }
    }

    return displayChanged;
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      check the edit keys
    @param      key     key pressed
    @return     bool    true if display changed
-----------------------------------------------------------------------------*/
bool IDEEditor::checkEditKeys( uint32_t key )
{
    bool displayChanged = false;

    switch ( key )
    {
        case 8: // backspace
        {
            if ( m_cursorX > 0 )
            {
                eraseCharFromEditor( m_cursorX, m_cursorY );
                m_cursorX--;
                displayChanged = true;
            }
            break;
        }
        case 10: // enter
        {

            break;
        }
        case 127: // delete
        {
            break;
        }
        case 330: // delete
        {
            eraseCharFromEditor( m_cursorX, m_cursorY );
            displayChanged = true;
            break;
        }
        default:
        {
            if ( key >= 32 && key <= 126 )
            {
                displayChanged = true;
                insertCharIntoEditor( m_cursorX, m_cursorY, key );
                m_cursorX++;
            }
            break;
        }
    }

    return displayChanged;
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      returns the character at the current cursor position
    @param      x  x position
    @param      y  y position
    @return     uint8_t    character or space
-----------------------------------------------------------------------------*/
uint8_t IDEEditor::getCharFromEditor( uint32_t x, uint32_t y )
{
    uint8_t ch = ' ';

    if ( ( y + m_currentLine ) <= m_editlines.size() - 1 )
    {
        x += m_currentColumn;
        if ( x < m_editlines[ m_currentLine + y ].getLineString().length() )
        {
            ch = m_editlines[ m_currentLine + y ].getLineString()[ x ];
        }
    }
    return ch;
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      inserts a character into the editor
    @param      x  x position
    @param      y  y position
    @param      ch character to insert
-----------------------------------------------------------------------------*/
void IDEEditor::insertCharIntoEditor( uint32_t x, uint32_t y, uint8_t ch )
{
    x += m_currentColumn;
    y += m_currentLine;

    if ( y < m_editlines.size() )
    {
        // pad with spaces if less then x position
        if ( m_editlines[ y ].getLineString().length() < x )
        {
            uint32_t nCursorPos = m_editlines[ y ].getLineString().length();
            m_editlines[ y ].setLineCursor( nCursorPos );
            while ( nCursorPos <= x )
            {
                m_editlines[ y ].addChar( ' ' );
                nCursorPos++;
                m_editlines[ y ].setLineCursor( nCursorPos );
            }
        }
        m_editlines[ y ].setLineCursor( x );
        m_editlines[ y ].addChar( ch );
    }
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      erases a character from the editor
    @param      x  x position
    @param      y  y position
------------------------------------------------------------------------------*/
void IDEEditor::eraseCharFromEditor( uint32_t x, uint32_t y )
{
    x += m_currentColumn;
    y += m_currentLine;

    if ( y < m_editlines.size() )
    {
        if ( m_editlines[ y ].getLineString().length() > x )
        {
            m_editlines[ y ].setLineCursor( x );
            m_editlines[ y ].deleteChar();
        }
    }
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEEditor.h
// ----------------------------------------------------------------------------
