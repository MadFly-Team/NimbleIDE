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
};

// ----------------------------------------------------------------------------

} // end namespace Nimble

//-----------------------------------------------------------------------------
// End of file: Errors.h
// ----------------------------------------------------------------------------
