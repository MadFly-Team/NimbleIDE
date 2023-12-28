/**----------------------------------------------------------------------------

    @file       IDEEditBox.cpp
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEEditBox class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:


Version:

        0.0.1.0     First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include "..\..\..\inc\Modules\IDE\IDEEditbox.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

// constructors & destructors -------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Constructor for IDEEditBox class
----------------------------------------------------------------------------*/
IDEEditBox::IDEEditBox()
{
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Destructor for IDEEditBox class
----------------------------------------------------------------------------*/
IDEEditBox::~IDEEditBox()
{
}

// initialisation -----------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Initialise the IDEEditBox class
    @param      x       x position of the window
    @param      y       y position of the window
    @param      width   width of the window
    @param      height  height of the window
    @param      ink     ink colour of the window
    @param      paper   paper colour of the window
    @return     LibraryError     Any errors generated, otherwise No_Error
----------------------------------------------------------------------------*/
LibraryError IDEEditBox::initBox( int16_t x, int16_t y, int16_t width, int16_t height, int16_t ink, int16_t paper )
{
    LibraryError error = LibraryError::IDEEditBox_InitAlreadyCalled;

    if ( isInitialized() == false )
    {
        // initialise the base class Editline
        std::string edittext = "Edit text here";
        error                = IDEEditline::init( edittext, 1, 2 );

        if ( error == LibraryError::No_Error )
        {
            // set the editline as editable
            setParams( 0, ink, paper );

            // and initialise the curses window
            error = CursesWin::init( width, height, x, y, ink, paper );
            if ( error == LibraryError::No_Error )
            {
                draw();
                // set as initialised
                setInitialized();
            }
            else
            {
                ErrorHandler::getInstance().handleError( ErrorType::Error, LibraryError::IDEEditBox_FailedToCreateWindow, "IDEEditBox - init() failed to create window" );
            }
        }
    }
    else
    {
        ErrorHandler::getInstance().handleError( ErrorType::Warning, LibraryError::IDEEditBox_InitAlreadyCalled, "IDEEditBox - init() already called, ignored" );
    }

    return ( error );
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEEditBox.cpp
// ----------------------------------------------------------------------------
