/**----------------------------------------------------------------------------

    @file       CursesColour.cpp
    @defgroup   NimbleLIBCurses Nimble Library Curses Module
    @brief      Curses Colour class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

    This class is a singleton class that provides the ability to set the
    colours used by the curses library. It is a singleton class as there is
    only one set of colours for the whole application.
    The class is initialised by calling the Init() function. This function
    creates a set of colour pairs that can be used by the application. The
    colours are defined by the following:
        Colour 1:    Black
        Colour 2:    Red
        Colour 3:    Green
        Colour 4:    Yellow
        Colour 5:    Blue
        Colour 6:    Magenta
        Colour 7:    Cyan
        Colour 8:    White
    The default colour pairs are defined as follows:
        Colour Pair 0:  White on Black
        Colour Pair 1:  Red on Black
        Colour Pair 2:  Green on Black
        Colour Pair 3:  Yellow on Black
        Colour Pair 4:  Blue on Black
        Colour Pair 5:  Magenta on Black
        Colour Pair 6:  Cyan on Black
        Colour Pair 7:  White on Black
        Colour Pair 8:  Black on Red
        Colour Pair 9:  Red on Red
        Colour Pair 10: Green on Red
        Colour Pair 11: Yellow on Red
        Colour Pair 12: Blue on Red
        Colour Pair 13: Magenta on Red
        Colour Pair 14: Cyan on Red
        Colour Pair 15: White on Red
        Colour Pair 16: Black on Green
        Colour Pair 17: Red on Green
        Colour Pair 18: Green on Green
        Colour Pair 19: Yellow on Green
        Colour Pair 20: Blue on GreenA
    etc. ( 64 colour pairs in total ) using the following formula:
    Colour Pair n: ( n % 8 ) on ( n / 8 )

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include "../../../inc/Modules/Curses/CursesColour.h"

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
    @brief      Default constructor for the curses colour class
  --------------------------------------------------------------------------*/
CursesColour::CursesColour()
{
    // initialise variables
    colourPairs.clear();
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Destructor for the curses colour class
  --------------------------------------------------------------------------*/
CursesColour::~CursesColour()
{
    // Clear the colour pairs
    colourPairs.clear();
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Initialises the colours for the curses colour class
  --------------------------------------------------------------------------*/
LibraryError CursesColour::init()
{
    LibraryError error = LibraryError::No_Error;

    if ( start_color() == ERR )
    {
        // Failed to start colours
        error = LibraryError::CursesColour_CannotStartColour;
        ErrorHandler::getInstance().handleError( ErrorType::Error, error, "Failed to start curses colours for the terminal" );
    }
    else
    {
        // Create the colour pairs
        colourPairs.clear();
        for ( uint32_t i = 0; i < MAX_COLOURS; i++ )
        {
            // Create the colour pair
            ColourPair newColourPair;
            newColourPair.index = i + 1;
            newColourPair.ink   = i % NUUM_BASE_COLORS;
            newColourPair.paper = i / NUUM_BASE_COLORS;
            // Add the colour pair to the list
            colourPairs.push_back( newColourPair );

            // Set the colour pair in the curses library
            init_pair( newColourPair.index, newColourPair.ink, newColourPair.paper );
        }
        // Set the initialized flag
        setInitialized();
    }

    return error;
}

// Setters --------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Sets the curses colour pair
    @param      pair    The colour pair to set
    @param      fg      The foreground colour
    @param      bg      The background colour
    @return     LibraryError    Error code
  --------------------------------------------------------------------------*/
LibraryError CursesColour::setColorPair( uint32_t pair, uint32_t fg, uint32_t bg )
{
    LibraryError error = LibraryError::No_Error;
    if ( pair > MAX_COLOURS )
    {
        error = LibraryError::CursesColour_InvalidColourPair;
    }
    else
    {
        // Set the internal store
        colourPairs[ pair ].ink   = fg;
        colourPairs[ pair ].paper = bg;
        // Set the cursees colour pair
        init_pair( pair, fg, bg );
    }
    return error;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Sets the curses colour pair
    @param      pair    The colour pair to set
    @param      fg      The foreground colour
    @return     LibraryError    Error code
  --------------------------------------------------------------------------*/
LibraryError CursesColour::setInkColourPair( uint32_t pair, uint32_t ink )
{
    LibraryError error = LibraryError::No_Error;
    if ( pair > MAX_COLOURS )
    {
        error = LibraryError::CursesColour_InvalidColourPair;
    }
    else
    {
        // Set the internal store
        colourPairs[ pair ].ink = ink;
        // Set the cursees colour pair
        init_pair( pair, ink, colourPairs[ pair ].paper );
    }
    return error;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Sets the curses colour pair
    @param      pair    The colour pair to set
    @param      bg      The background colour
    @return     LibraryError    Error code
  --------------------------------------------------------------------------*/
LibraryError CursesColour::setPaperColourPair( uint32_t pair, uint32_t paper )
{
    LibraryError error = LibraryError::No_Error;
    if ( pair > MAX_COLOURS )
    {
        error = LibraryError::CursesColour_InvalidColourPair;
    }
    else
    {
        // Set the internal store
        colourPairs[ pair ].paper = paper;
        // Set the cursees colour pair
        init_pair( pair, colourPairs[ pair ].ink, paper );
    }
    return error;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Sets the curses colour pair
    @param      win     The curses window to set the colour pair for
    @param      pair    The colour pair to set
    @return     LibraryError    Error code
-----------------------------------------------------------------------------*/
LibraryError CursesColour::setColour( std::unique_ptr<CursesWin> win, uint32_t pair )
{
    LibraryError error = LibraryError::No_Error;
    if ( pair > MAX_COLOURS )
    {
        error = LibraryError::CursesColour_InvalidColourPair;
    }
    else
    {
        win->setColour( pair );
    }
    return error;
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: CursesColour.cpp
// ----------------------------------------------------------------------------
