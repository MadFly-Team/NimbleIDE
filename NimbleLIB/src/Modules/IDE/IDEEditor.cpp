/**----------------------------------------------------------------------------

    @file       IDEEditor.h
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEEditor class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:


-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include "../../../inc/Modules/IDE/IDEEditor.h"
#include "../../../inc/Modules/Curses/CursesColour.h"
#include "../../../inc/Modules/Global/Globals.h"
#include <cstdint>
#include <memory>

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
    // default the editor values
    m_currentLine   = 0;
    m_currentColumn = 0;
    m_cursorX       = 0;
    m_cursorY       = 0;
    m_oldCursorX    = 0;
    m_oldCursorY    = 0;

    // set up the Editor flags
    clearUserFlag( (uint32_t)EditorFlags::FormatWhenPrint );
    clearUserFlag( (uint32_t)EditorFlags::MarkedTextActive );
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
        m_editorWin = std::make_unique<CursesWin>( m_width, m_height + 1, m_xStart, m_yStart, IDE_COL_FG_BLACK, IDE_COL_BG_WHITE );
        m_editorWin->colourWindow( COLOUR_INDEX( IDE_COL_FG_BLACK, IDE_COL_BG_WHITE ), true );
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
            // TODO: sort out settins properly
            Screen::sEditorSettings* pSettings = Screen::Globals::getInstance().getEditorSettings();
            pSettings->Theme                   = Screen::eEditorTheme::Dark;
            pSettings->LineNumbers             = true;

            displayEditor();
            enableMouse();
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
    LibraryError error         = LibraryError::No_Error;

    uint32_t     curline       = 0;
    uint32_t     curcol        = m_currentColumn;
    uint32_t     displayWidth  = m_width - 2;
    uint32_t     displayHeight = m_height - 1;

    std::string  blankline( displayWidth, ' ' );

    while ( curline < ( displayHeight ) && ( curline < ( displayHeight + m_editlines.size() - 1 ) ) )
    {
        std::string line;

        line = "¬";
        if ( ( curline + m_currentLine ) < m_editlines.size() )
        {
            line = m_editlines[ curline + m_currentLine ];
        }

        // move to the current column, blanking if off screen
        if ( line.length() > 0 && line.length() >= curcol )
        {
            line = line.substr( curcol, displayWidth );
        }
        else
        {
            line = "¬";
        }

        if ( line.length() > displayWidth )
        {
            line = line.substr( 0, displayWidth );
        }

        // print the line, blanking first
        m_editorWin->print( 1, curline + 1, blankline );
        if ( line != "¬" )
        {
            m_editorWin->print( 1, curline + 1, line );
        }

        // attribute the line
        updateHighlighting( curline );
        curline++;
    }

    m_editorWin->draw();

    return error;
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      print to the editor window
    @param      x     x position
    @param      y     y position
    @param      text  text to print
    @return     LibraryError    error code
-----------------------------------------------------------------------------*/
LibraryError IDEEditor::print( uint32_t x, uint32_t y, const std::string& text )
{
    LibraryError error = LibraryError::IDEEditor_NotInitialized;

    if ( isInitialized() )
    {
        m_editorWin->print( x, y, text );
        m_editorWin->draw();
        error = LibraryError::No_Error;
    }
    return error;
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      redraws the background and also the border
    @return     void
-----------------------------------------------------------------------------*/
void IDEEditor::redrawBackground()
{
    m_editorWin->colourWindow( COLOUR_INDEX( IDE_COL_FG_BLACK, IDE_COL_BG_WHITE ), true );
    displayEditor();
    m_editorWin->draw();
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

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      get the cursor X position
    @return     uint32_t    cursor X position
------------------------------------------------------------------------------*/
uint32_t IDEEditor::getCursorX() const
{
    return m_cursorX + m_currentColumn + 1;
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      get the cursor Y position
    @return     uint32_t    cursor Y position
------------------------------------------------------------------------------*/
uint32_t IDEEditor::getCursorY() const
{
    return m_cursorY + m_currentLine + 1;
}
/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      returns the curses window
    @return     WINDOW* Curses window.
------------------------------------------------------------------------------*/
WINDOW* IDEEditor::getWindow() const
{
    return m_editorWin->getWindow();
}

// setters --------------------------------------------------------------------

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      set the cursor position from x,y
    @param      x     x position
    @param      y     y position
    @return     void
------------------------------------------------------------------------------*/
void IDEEditor::setCursorPosition( uint32_t x, uint32_t y )
{
    if ( x > m_xStart && x < m_xStart + m_width && y > m_yStart && y < m_yStart + m_height )
    {
        m_cursorX = x - m_xStart - 1;
        m_cursorY = y - m_yStart - 1;

        if ( m_cursorX + m_currentColumn > m_editlines[ m_currentLine + m_cursorY ].length() )
            placeCursorinLine( m_currentLine );
    }
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Scrool the winodow up or down one line
    @param      upIfTrue     true if up, false if down
    @return     void
------------------------------------------------------------------------------*/
void IDEEditor::scrollEditor( bool upIfTrue )
{
    m_currentLine += ( upIfTrue ) ? -1 : 1;

    if ( m_currentLine < 0 )
        m_currentLine = 0;
    if ( m_currentLine > m_editlines.size() )
        m_currentLine = m_editlines.size();

    if ( m_cursorX + m_currentColumn > m_editlines[ m_currentLine + m_cursorY ].length() )
        placeCursorinLine( m_currentLine );
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

    // save the old cursor position
    // m_oldCursorX = m_cursorX;
    // m_oldCursorY = m_cursorY;

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
    if ( ( m_frameCount & 0x1f ) == 0 )
    {
        m_cursorDrawn = m_cursorDrawn ? false : true;
    }

    mvwchgat( m_editorWin->getWindow(), m_oldCursorY + 1, m_oldCursorX + 1, 1, A_REVERSE, 0, nullptr );

    m_oldCursorX = m_cursorX;
    m_oldCursorY = m_cursorY;

    if ( m_cursorDrawn )
    {
        mvwchgat( m_editorWin->getWindow(), m_cursorY + 1, m_cursorX + 1, 1, A_NORMAL, 0, nullptr );
    }

    drawMouse( m_editorWin->getWindow() );
    m_editorWin->draw();
    return displayChanged;
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      show the curses window
    @return     LibraryError    error code
-----------------------------------------------------------------------------*/
LibraryError IDEEditor::showWindow()
{
    LibraryError error = LibraryError::No_Error;
    m_editorWin->showWindow();
    redrawBackground();
    return error;
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      hide the curses window
    @return     LibraryError    error code
-----------------------------------------------------------------------------*/
LibraryError IDEEditor::hideWindow()
{
    LibraryError error = LibraryError::No_Error;
    m_editorWin->hideWindow();
    return error;
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
                if ( m_cursorX + m_currentColumn > m_editlines[ m_currentLine + m_cursorY ].length() )
                    placeCursorinLine( m_currentLine );
                displayChanged = true;
            }
            else
            {
                if ( m_currentLine > 0 )
                {
                    m_currentLine--;
                    if ( m_cursorX + m_currentColumn > m_editlines[ m_currentLine + m_cursorY ].length() )
                        placeCursorinLine( m_currentLine );
                    displayChanged = true;
                }
            }
            break;
        }
        case 258: // down
        {
            if ( m_cursorY < m_height - 2 )
            {
                if ( m_cursorY + m_currentLine < m_editlines.size() - 1 )
                {
                    m_cursorY++;
                    if ( m_cursorX + m_currentColumn > m_editlines[ m_currentLine + m_cursorY ].length() )
                        placeCursorinLine( m_currentLine );
                }
                displayChanged = true;
            }
            else
            {
                if ( m_currentLine + m_cursorY < m_editlines.size() - 1 )
                {
                    m_currentLine++;
                    if ( m_cursorX + m_currentColumn > m_editlines[ m_currentLine + m_cursorY ].length() )
                        placeCursorinLine( m_currentLine );
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
            if ( m_cursorX < m_width - 3 )
            {
                if ( m_cursorX < m_editlines[ m_currentLine + m_cursorY ].length() )
                {
                    m_cursorX++;
                    displayChanged = true;
                }
            }
            else
            {
                moveTextRight();
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
                m_cursorX--;
                eraseCharFromEditor( m_cursorX, m_cursorY );
                displayChanged = true;
            }
            else if ( m_currentLine + m_cursorY > 0 )
            {
                m_cursorX = m_editlines[ m_currentLine + m_cursorY - 1 ].length();
                m_editlines[ m_currentLine + m_cursorY - 1 ] += m_editlines[ m_currentLine + m_cursorY ];
                m_editlines.erase( m_editlines.begin() + m_currentLine + m_cursorY );
                m_editlineAttributes.erase( m_editlineAttributes.begin() + m_currentLine + m_cursorY );
                m_cursorY--;
                displayChanged = true;
            }
            break;
        }
        case 10: // enter
        {
            m_cursorY++;
            insertLineIntoEditor( m_cursorY );
            if ( m_cursorY > m_height - 3 )
            {
                m_cursorY = m_height - 3;
                m_currentLine++;
            }
            m_cursorX      = 0;
            displayChanged = true;
            break;
        }
        case 9: // tab
        {
            // spaces to add to string...
            uint32_t spaces = 4 - ( m_cursorX & 0x3 );
            for ( uint32_t i = 0; i < spaces; i++ )
            {
                m_editlines[ m_currentLine + m_cursorY ].insert( m_cursorX, " " );
            }
            m_cursorX += spaces;

            if ( m_cursorX > m_width - 3 )
            {
                moveTextRight();
            }
            displayChanged = true;
            break;
        }
        case 127: // delete
        {
            break;
        }
        case 330: // delete
        {
            if ( m_cursorX != m_editlines[ m_currentLine + m_cursorY ].length() && m_editlines[ m_currentLine + m_cursorY ].length() > 0 )
            {
                eraseCharFromEditor( m_cursorX, m_cursorY );
            }
            else if ( m_currentLine + m_cursorY < m_editlines.size() - 1 )
            {
                m_editlines[ m_currentLine + m_cursorY ] += m_editlines[ m_currentLine + m_cursorY + 1 ];
                m_editlines.erase( m_editlines.begin() + m_currentLine + m_cursorY + 1 );
                m_editlineAttributes.erase( m_editlineAttributes.begin() + m_currentLine + m_cursorY + 1 );
            }
            displayChanged = true;
            break;
        }
        case 338: // page down
        {
            m_currentLine += m_height - 2;
            if ( m_currentLine + m_cursorY > m_editlines.size() - 1 )
            {
                m_currentLine = m_editlines.size() - 1 - m_cursorY;
            }
            placeCursorinLine( m_currentLine + m_cursorY );
            displayChanged = true;
            break;
        }
        case 339: // page up
        {
            m_currentLine -= m_height - 2;
            if ( m_currentLine < 0 )
            {
                m_currentLine = 0;
            }
            placeCursorinLine( m_currentLine + m_cursorY );
            displayChanged = true;
            break;
        }
        case 262: // homeKey:
        {
            m_cursorX       = 0;
            m_currentColumn = 0;
            displayChanged  = true;
            break;
        }
        case 358: // endKey:
        {
            m_currentColumn = m_editlines[ m_currentLine + m_cursorY ].length() - m_width + 3;
            if ( m_currentColumn < 0 )
            {
                m_currentColumn = 0;
            }
            m_cursorX      = m_editlines[ m_currentLine + m_cursorY ].length() - m_currentColumn;
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
                // check if we need to move the text right
                if ( m_cursorX >= m_width - 2 )
                {
                    moveTextRight();
                }
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
        if ( x < m_editlines[ m_currentLine + y ].length() )
        {
            ch = m_editlines[ m_currentLine + y ][ x ];
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
    @return     void
-----------------------------------------------------------------------------*/
void IDEEditor::insertCharIntoEditor( uint32_t x, uint32_t y, uint8_t ch )
{
    x += m_currentColumn;
    y += m_currentLine;

    if ( y < m_editlines.size() )
    {
        // pad with spaces if less then x position
        if ( m_editlines[ y ].length() < x )
        {
            uint32_t nCursorPos = m_editlines[ y ].length();
            while ( nCursorPos <= x )
            {
                m_editlines[ y ].insert( nCursorPos, 1, ' ' );
                nCursorPos++;
            }
        }
        m_editlines[ y ].insert( x, 1, ch );
    }
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      erases a character from the editor
    @param      x  x position
    @param      y  y position
    @return     void
------------------------------------------------------------------------------*/
void IDEEditor::eraseCharFromEditor( uint32_t x, uint32_t y )
{
    x += m_currentColumn;
    y += m_currentLine;

    if ( y < m_editlines.size() )
    {
        if ( m_editlines[ y ].length() > x )
        {
            m_editlines[ y ].erase( x, 1 );
        }
    }
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      inserts a line into the editor
    @param      y  y position
    @return     void
------------------------------------------------------------------------------*/
void IDEEditor::insertLineIntoEditor( uint32_t y )
{
    y += m_currentLine;
    std::string newText = m_editlines[ y - 1 ].substr( m_cursorX, m_editlines[ y - 1 ].length() - m_cursorX );
    m_editlines[ y - 1 ].erase( m_cursorX, m_editlines[ y - 1 ].length() - m_cursorX );
    m_editlines.insert( m_editlines.begin() + y, newText );
    EditLineAttributes attr;
    attr.clear();
    m_editlineAttributes.insert( m_editlineAttributes.begin() + y, attr );
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      places the cursor in the line
    @param      y  y position
    @return     void
------------------------------------------------------------------------------*/
void IDEEditor::placeCursorinLine( uint32_t y )
{
    y += m_cursorY;

    if ( y < m_editlines.size() )
    {
        if ( m_cursorX > m_editlines[ y ].length() )
        {
            m_cursorX = m_editlines[ y ].length();
        }
        m_currentColumn = m_editlines[ y ].length() - m_width + 3;
        if ( m_currentColumn < 0 )
        {
            m_currentColumn = 0;
        }
    }
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      moves the text right - 16 characters
    @return     void
------------------------------------------------------------------------------*/
void IDEEditor::moveTextRight()
{
    // if ( m_cursorX != m_editlines[ m_currentLine + m_cursorY ].length() - m_currentColumn )
    {
        m_currentColumn += 16;
        if ( m_currentColumn > m_editlines[ m_currentLine + m_cursorY ].length() - m_width + 3 )
        {
            m_currentColumn = m_editlines[ m_currentLine + m_cursorY ].length() - m_width + 3;
        }
        if ( m_cursorX + m_currentColumn > m_editlines[ m_currentLine + m_cursorY ].length() )
        {
            m_cursorX = m_editlines[ m_currentLine + m_cursorY ].length() - m_currentColumn;
        }
        else
        {
            m_cursorX -= 16;
            if ( m_cursorX + m_currentColumn > m_editlines[ m_currentLine + m_cursorY ].length() )
            {
                m_cursorX = m_editlines[ m_currentLine + m_cursorY ].length() - m_currentColumn;
            }
        }
    }
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      does the hightlighting for the editor line that is to be displayed
    @param      curline  current line
    @return     void
------------------------------------------------------------------------------*/
void IDEEditor::updateHighlighting( uint32_t curline )
{
    int32_t nStart = (int32_t)m_editlineAttributes[ curline ].MarkStart - m_currentColumn;
    int32_t nEnd   = (int32_t)m_editlineAttributes[ curline ].MarkEnd - m_currentColumn;

    if ( nStart < 0 )
    {

        nStart = 0;
    }
    if ( nStart < m_width )
    {
        if ( nEnd > 0 )
        {
            if ( nEnd > m_width )
            {
                nEnd = m_width;
            }
            if ( ( nEnd - nStart ) > 0 )
            {
                m_editorWin->displayHighlight( 0, curline, nStart, nEnd );
            }
        }
    }
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEEditor.h
// ----------------------------------------------------------------------------
