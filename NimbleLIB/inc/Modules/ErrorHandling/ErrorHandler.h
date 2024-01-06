/**----------------------------------------------------------------------------

    @file       ErrorHandler.h
    @defgroup   NimbleLIBError Nimble Library Error Module
    @brief      Handles error messages for the USB tool.

    @copyright  Neil Bereford 2023

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include <string>
#include <chrono>
#include <ctime>
#include <vector>

#include "../Logging/Logger.h"
#include "Errors.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBError Nimble Library Error Module
    @brief      Error types for the Nimble Library
  --------------------------------------------------------------------------*/
enum class ErrorType
{
    Status = 0, //!< Reporting general status of module
    Warning,    //!, Reporting a warning erorr
    Error,      //!< Reporting an error
    Critical,   //!< Reporting a critical error, Library will terminate
};

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBError Nimble Library Error Module
    @brief      Stored errors, used for Reporting
  --------------------------------------------------------------------------*/
struct ErrorInformation
{
    std::string  message; //!< Error message
    std::time_t  time;    //!< Time of error
    ErrorType    type;    //!< Error type
    LibraryError number;  //!< Error code
};

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBError Nimble Library Error Module
    @brief      Status of the error handler
  --------------------------------------------------------------------------*/
struct ErrorStatus
{
    uint32_t numErrors;   //!< Number of errors
    uint32_t numWarnings; //!< Number of warnings
    uint32_t numStatus;   //!< Number of status messages
    uint32_t numCritical; //!< Number of critical errors
    uint32_t totalErrors; //!< Total number of errors

    // General Functionality -------------------------------------------------
    void Clear();
};

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBError Nimble Library Error Module
    @brief      Error handler class for the Nimble Library
  --------------------------------------------------------------------------*/
class ErrorHandler : public Logger
{
  public:
    // Function to access the singleton -----------------------------------------
    static ErrorHandler& getInstance()
    {
        static ErrorHandler instance; // Created only once
        return instance;
    }
    // Error handling functions ------------------------------------------------
    void handleError( ErrorType type, LibraryError error, const std::string& message );
    void reportErrors();
    void clearErrors();

    // Unit Test functions -----------------------------------------------------
    ErrorStatus getStatusInformation();

  private:
    // Singleton constructor and destructor ------------------------------------
    ErrorHandler();
    ~ErrorHandler();
    ErrorHandler( const ErrorHandler& )            = delete;
    ErrorHandler& operator=( const ErrorHandler& ) = delete;

    // Private Data -------------------------------------------------------------
    std::vector<ErrorInformation> errorList; //!< List of errors

    // Private functions --------------------------------------------------------
    void displayMessage( const ErrorInformation& error );

}; // end class Singleton ErrorHandler

//-----------------------------------------------------------------------------

} // end namespace Nimble

//-----------------------------------------------------------------------------
// End of file: ErrorHandler.h
// ----------------------------------------------------------------------------
