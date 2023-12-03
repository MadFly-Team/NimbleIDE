/**----------------------------------------------------------------------------

    @file       Errors.h
    @defgroup   NimbleLIBError Nimble Library Error Module
    @brief      Error numbers - please add erorrs here.

    @copyrighr  Neil Bereford 2023


Notes:

    Error numbers are defined here. Please add new errors here.
    Each module has a base error number. This is used to identify the module
    that the error came from. The error number is then offset by the module
    offset number. This is used to identify the error within the module.

    Currently the module offset is set to 0x00001000. This means that each
    module can have 4096 errors. This should be more than enough for each
    module.

    Supported Modules:
    - Logger


Version:

        0.0.1.0     First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Define constants
// ----------------------------------------------------------------------------

#define LIBRARY_ERROR_BASE ( 0x10000000 ) //!< Base error number reference
#define MODULE_OFFSET      ( 0x00001000 ) //!< Offset for each module

//-----------------------------------------------------------------------------
// Enum definitions
// ----------------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBError Nimble Library Error Module
    @brief      Error numbers for the Nimble Library
  --------------------------------------------------------------------------*/
enum class LibraryError
{
    // General Errors
    No_Error = 0, //!< 0x00000000 No error

    // Logger Errors
    Logger_base_error = LIBRARY_ERROR_BASE, //!< 0x10001000 Base error for the Logger
    Logger_InitializeNotCalled,             //!< 0x10001001 Failed to initialise the Logger

    // Curses Errors
    Curses_base_error = Logger_base_error + MODULE_OFFSET, //!< 0x10002000 Base error for the Curses module
    CursesColour_AlreadyInitialised,                       //!< 0x10002001 Curses Colour class already initialised

    // File Handling Errors
    FileHandlding_base_error = Curses_base_error + MODULE_OFFSET, //!< 0x10003000 Base error for the File Handling module

    // ErrorHandling Errors
    ErrorHandler_base_error = FileHandlding_base_error + MODULE_OFFSET, //!< 0x10004000 Base error for the Error Handling module

    // Screen Errors
    Screen_base_error = FileHandlding_base_error + MODULE_OFFSET, //!< 0x10005000 Base error for the Screen module

    // Utllities Errors
    Utilities_base_error = Screen_base_error + MODULE_OFFSET, //!< 0x10006000 Base error for the Utilities module
};

// ----------------------------------------------------------------------------

} // end namespace Nimble

//-----------------------------------------------------------------------------
// End of file: Errors.h
// ----------------------------------------------------------------------------
