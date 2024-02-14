/**----------------------------------------------------------------------------

    @file       CursesWin.cpp
    @defgroup   NimbleLIBCurses Nimble Library Curses Module
    @brief      Curse window class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

        Curses window class for the Nimble Library. This class provides a curses
        window for the Nimble Library. The curses window is a sub-window of the
        curses screen. The curses window is created using the curses subwin()
        function. The curses window is used to display text and graphics. The
        curses window is used by the curses text and graphics classes.

        The following have getters and setters
           winWidth    - width of window
           winheight   - height if window
           winX        - left screen positiom of window
           winY        - Top position for the window
           inkColour   - ink colour of the window
           paperColour - paper colour of the window

        The ColourWindow() function is used to set the colour of the window. The
        colour of the window is set using the curses wattron() function.
        The print() function is used to print text to the window.

        Example of usage:

            std::unique_ptr<CursesWin> winTitle;

            winTitle  = std::make_unique<CursesWin>( COLS, 1, 0, 0, COLOR_WHITE, COLOR_BLUE );
            winTitle->colourWindow( TITLECOLOR, false );
            winTitle->print( 2, 0, "Nimble IDE : Version 0.0.1" );


-----------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include <memory>
#include "../../../inc/Modules/Curses/CursesWin.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class Support Functions
// ----------------------------------------------------------------------------

// Constructors and destructors ------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Default constructor for the curses window class

  --------------------------------------------------------------------------*/
CursesWin::CursesWin()
{
    // initialise variables
    winWidth       = 0;
    winHeight      = 0;
    winX           = 0;
    winY           = 0;
    winInkColour   = 0;
    winPaperColour = 0;
    win            = nullptr;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Constructor for the curses window class
    @param      width       The width of the window
    @param      height      The height of the window
    @param      x           The x position of the window
    @param      y           The y position of the window
    @param      inkColour   The ink colour of the window
    @param      paperColour The paper colour of the window

  --------------------------------------------------------------------------*/
CursesWin::CursesWin( uint32_t width, uint32_t height, uint32_t x, uint32_t y, uint32_t inkColour, uint32_t paperColour )
{
    // initialise variables
    winWidth       = width;
    winHeight      = height;
    winX           = x;
    winY           = y;
    winInkColour   = inkColour;
    winPaperColour = paperColour;

    // create the window
    win = subwin( stdscr, winHeight, winWidth, winY, winX );
    if ( win == nullptr )
    {
        ErrorHandler::getInstance().handleError( ErrorType::Error, LibraryError::CursesWin_FailedToCreateWindow, "Failed to create the curses window" );
    }
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Destructor for the curses window class

  --------------------------------------------------------------------------*/
CursesWin::~CursesWin()
{
}

// display ---------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Prints text to the curses window
    @param      x       The x position of the text
    @param      y       The y position of the text
    @param      text    The text to print
    @return     The error code
  --------------------------------------------------------------------------*/
LibraryError CursesWin::print( uint32_t x, uint32_t y, const std::string& text )
{
    LibraryError error = LibraryError::No_Error;

    if ( mvwaddstr( win, y, x, text.c_str() ) == ERR )
    {
        error = LibraryError::CursesWin_FailedToPrintToWindow;
        ErrorHandler::getInstance().handleError( ErrorType::Error, error, "Failed to print to the curses window" );
    }

    return error;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Prints text to the curses window
    @param      x       The x position of the text
    @param      y       The y position of the text
    @param      markStart The start of the text to highlight
    @param      markEnd   The end of the text to highlight
    @param      markAll   Highlight all the text
    @return     The error code
--------------------------------------------------------------------------*/
LibraryError CursesWin::displayHighlight( uint32_t x, uint32_t y, uint32_t markStart, uint32_t markEnd )
{
    LibraryError error = LibraryError::No_Error;
    if ( mvwchgat( win, y, x + markStart, markEnd - markStart, A_REVERSE, 0, nullptr ) == ERR )
    {
        error = LibraryError::CursesWin_FailedToPrintToWindow;
        ErrorHandler::getInstance().handleError( ErrorType::Error, error, "Failed to print to the curses window" );
    }
    return error;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Prints text to the curses window
    @param      x       The x position of the text
    @param      y       The y position of the text
    @param      text    The text to print
    @return     The error code
  --------------------------------------------------------------------------*/
LibraryError CursesWin::eraseChar( uint32_t x, uint32_t y )
{
    LibraryError error = LibraryError::No_Error;

    if ( mvwdelch( win, y, x ) == ERR )
    {
        error = LibraryError::CursesWin_FailedToEraseChar;
        ErrorHandler::getInstance().handleError( ErrorType::Error, error, "Failed to erase char from the curses window" );
    }

    return error;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Prints text to the curses window
    @param      colour   The collour of the window
    @param      hasBox   Does the window have a box
    @return     The error code
  --------------------------------------------------------------------------*/
LibraryError CursesWin::colourWindow( uint32_t colour, bool hasBox )
{
    LibraryError error = LibraryError::No_Error;

    if ( colourBox( colour, hasBox ) == false )
    {
        error = LibraryError::CursesWin_FailedToColourWindow;
        ErrorHandler::getInstance().handleError( ErrorType::Error, error, "Failed to colour the curses window" );
    }

    return error;
}

// Control ---------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Initialises the curses window
    @return     The error code
  --------------------------------------------------------------------------*/
LibraryError CursesWin::init()
{
    LibraryError error = LibraryError::No_Error;

    return error;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Initialises the curses window
    @param      width       The width of the window
    @param      height      The height of the window
    @param      x           The x position of the window
    @param      y           The y position of the window
    @param      inkColour   The ink colour of the window
    @param      paperColour The paper colour of the window
    @return     LibraryError  LibraryError::No_Error if ok
  --------------------------------------------------------------------------*/
LibraryError CursesWin::init( uint32_t width, uint32_t height, uint32_t x, uint32_t y, uint32_t inkColour, uint32_t paperColour )
{
    LibraryError error = LibraryError::No_Error;

    // initialise variables
    winWidth       = width;
    winHeight      = height;
    winX           = x;
    winY           = y;
    winInkColour   = inkColour;
    winPaperColour = paperColour;

    // create the window
    win = subwin( stdscr, winHeight, winWidth, winY, winX );
    if ( win == nullptr )
    {
        ErrorHandler::getInstance().handleError( ErrorType::Error, LibraryError::CursesWin_FailedToCreateWindow, "Failed to create the curses window" );
        error = LibraryError::CursesWin_FailedToCreateWindow;
    }

    return ( error );
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Draws the curses window
    @return     The error code
  --------------------------------------------------------------------------*/
LibraryError CursesWin::draw()
{
    LibraryError error = LibraryError::No_Error;

    // update the mouse
    processMouse();
    drawMouse( win );

    // update the window.
    touchwin( win );
    wrefresh( win );

    return error;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Draws a vertyical line in the curses window
    @param      x       The x position of the line
    @param      y       The y position of the line
    @param      length  The length of the line
    @return     The error code
  --------------------------------------------------------------------------*/
LibraryError CursesWin::drawVerticalLine( uint32_t x, uint32_t y, uint32_t length )
{
    LibraryError error = LibraryError::No_Error;
    if ( mvwvline( win, y, x, ACS_VLINE, length ) == ERR )
    {
        error = LibraryError::CursesWin_FailedToDrawVerticalLine;
        ErrorHandler::getInstance().handleError( ErrorType::Error, error, "Failed to draw vertical line in the curses window" );
    }
    return error;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Draws a horizontal line in the curses window
    @param      x       The x position of the line
    @param      y       The y position of the line
    @param      length  The length of the line
    @return     The error code
  --------------------------------------------------------------------------*/
LibraryError CursesWin::drawHorizontalLine( uint32_t x, uint32_t y, uint32_t length )
{
    LibraryError error = LibraryError::No_Error;
    if ( mvwhline( win, y, x, ACS_HLINE, length ) == ERR )
    {
        error = LibraryError::CursesWin_FailedToDrawHorizontalLine;
        ErrorHandler::getInstance().handleError( ErrorType::Error, error, "Failed to draw horizontal line in the curses window" );
    }
    return error;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Clears the curses window
    @return     The error code
  --------------------------------------------------------------------------*/
LibraryError CursesWin::clear()
{
    LibraryError error = LibraryError::No_Error;

    return error;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Refreshes the curses window
    @return     The error code
  --------------------------------------------------------------------------*/
LibraryError CursesWin::refresh()
{
    LibraryError error = LibraryError::No_Error;
    wrefresh( win );
    return error;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Hides the curses window
    @return     The error code
  --------------------------------------------------------------------------*/
LibraryError CursesWin::hideWindow()
{
    LibraryError error = LibraryError::No_Error;
    mvwin( win, -1, -1 );
    return error;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Shows the curses window
    @return     The error code
  --------------------------------------------------------------------------*/
LibraryError CursesWin::showWindow()
{
    LibraryError error = LibraryError::No_Error;
    mvwin( win, winY, winX );
    return error;
}

// Getters ---------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Gets the width of the window
    @return     The width of the window
  --------------------------------------------------------------------------*/
uint32_t CursesWin::getWidth() const noexcept
{
    return winWidth;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Gets the height of the window
    @return     The height of the window
  --------------------------------------------------------------------------*/
uint32_t CursesWin::getHeight() const noexcept
{
    return winHeight;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Gets the x position of the window
    @return     The x position of the window
  --------------------------------------------------------------------------*/
uint32_t CursesWin::getX() const noexcept
{
    return winX;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Gets the y position of the window
    @return     The y position of the window
  --------------------------------------------------------------------------*/
uint32_t CursesWin::getY() const noexcept
{
    return winY;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Gets the ink colour of the window
    @return     The ink colour of the window
  --------------------------------------------------------------------------*/
uint32_t CursesWin::getInkColour() const noexcept
{
    return winInkColour;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Gets the paper colour of the window
    @return     The paper colour of the window
  --------------------------------------------------------------------------*/
uint32_t CursesWin::getPaperColour() const noexcept
{
    return winPaperColour;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Gets the curses window
    @return     The curses window
  --------------------------------------------------------------------------*/
WINDOW* CursesWin::getWindow() const noexcept
{
    return win;
}

// Setters ---------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Sets the width of the window
    @param      width   The width of the window
    @return     void
  --------------------------------------------------------------------------*/
void CursesWin::setWidth( uint32_t width )
{
    winWidth = width;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Sets the height of the window
    @param      height  The height of the window
    @return     void
  --------------------------------------------------------------------------*/
void CursesWin::setHeight( uint32_t height )
{
    winHeight = height;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Sets the x position of the window
    @param      x       The x position of the window
    @return     void
  --------------------------------------------------------------------------*/
void CursesWin::setX( uint32_t x )
{
    winX = x;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Sets the y position of the window
    @param      y       The y position of the window
    @return     void
  --------------------------------------------------------------------------*/
void CursesWin::setY( uint32_t y )
{
    winY = y;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Sets the ink colour of the window
    @param      inkColour   The ink colour of the window
    @return     void
  --------------------------------------------------------------------------*/
void CursesWin::setInkColour( uint32_t inkColour )
{
    winInkColour = inkColour;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Sets the paper colour of the window
    @param      paperColour The paper colour of the window
    @return     void
  --------------------------------------------------------------------------*/
void CursesWin::setPaperColour( uint32_t paperColour )
{
    winPaperColour = paperColour;
}

// Other Functions ------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Colours the window, adding box around the window if needed
    @param      colour  The colour of the box
    @param      hasBox  Whether the box should be drawn
    @return     bool    true if the box was drawn, false otherwise
  --------------------------------------------------------------------------*/
bool CursesWin::colourBox( uint32_t colour, bool hasBox )
{
    bool     drawn = false;
    uint32_t maxY;
    chtype   attr = colour & A_ATTR;

    // set the colour of the window
    setColour( colour );
    if ( wbkgd( win, COLOR_PAIR( colour & A_CHARTEXT ) | ( attr & ~A_REVERSE ) ) == ERR )
    {
        ErrorHandler::getInstance().handleError( ErrorType::Error, LibraryError::CursesWin_FailedToColourBackground, "Failed to colour the background of the window" );
        return drawn;
    }

    if ( werase( win ) == ERR )
    {
        ErrorHandler::getInstance().handleError( ErrorType::Error, LibraryError::CursesWin_FailedToClearWindow, "Failed to clear the window" );
        return drawn;
    }

    // draw the box if needed
    maxY = getmaxy( win );
    if ( hasBox && ( maxY > MIN_WIN_SIZE ) )
    {
        box( win, 0, 0 );
    }

    // update the window
    touchwin( win );
    wrefresh( win );

    drawn = true;
    return ( drawn );
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Sets the colour of the window
    @param      colour   The colour of the window
    @return     void
  --------------------------------------------------------------------------*/
void CursesWin::setColour( uint32_t colour )
{
    wattrset( win, COLOR_PAIR( colour & A_CHARTEXT ) | ( colour & A_ATTRIBUTES ) );
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: CursesWin.cpp
// ----------------------------------------------------------------------------
