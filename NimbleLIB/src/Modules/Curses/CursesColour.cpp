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

Version:

        0.0.1.0     First Release, development phase. Draft copy

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
LibraryError CursesColour::Init()
{
    LibraryError error = LibraryError::No_Error;

    if ( isInitialized() )
    {
        error = LibraryError::CursesColour_AlreadyInitialised;
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
        }
        // Set the initialized flag
        setInitialized();
    }

    return error;
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: CursesColour.cpp
// ----------------------------------------------------------------------------
