/**----------------------------------------------------------------------------

    @file       ErrorHandler.cpp
    @defgroup   NimbleLIBError Nimble Library Error Module
    @brief      Handles error messages for the USB tool.

    @copyright  Neil Bereford 2023

Notes:

    Error handling is done by the ErrorHandler class. This class is used to
    store and report errors that occur during the execution of the USB HID
    Console Application.
    Logging of errors is done by the Logger class. This class is used to
    store and report errors that occur during the execution of the USB HID
    Console Application.
    To report an error, the ErrorHandler::handleError() function is called.
    This function takes three parameters:

    - ErrorType - Type of error
    - LibraryError - Error number
    - std::string - Error message

    The ErrorHandler::handleError() function creates a new ErrorInformation
    structure and adds it to the errorList vector. This vector is used to
    report the errors to the console terminal if needed, and log them.
    The ErrorHandler::reportErrors() function is used to report the errors
    to the console terminal. This function loops through the errorList vector
    and calls the ErrorHandler::displayMessage() function to display the
    error to the console terminal.
    The ErrorHandler::displayMessage() function displays the error to the
    console terminal. This function takes one parameter:

    - ErrorInformation - Error structure

    Please also note, functionality for ErrorStatus is included in this file.

-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include <iomanip>
#include <iostream>
#include "../../../inc/Modules/ErrorHandling/ErrorHandler.h"

//-----------------------------------------------------------------------------
// Namespace
//-----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class support functions
// ----------------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBError Nimble Library Error Module
    @brief      Constructor for the ErrorHandler class
    @return     bool - true if successful
  --------------------------------------------------------------------------*/
ErrorHandler::ErrorHandler()
{
    errorList.clear();

    // Initialize the logger
    loggerInitialize();
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBError Nimble Library Error Module
    @brief      Destructor for the ErrorHandler class
    @return     bool - true if successful
  --------------------------------------------------------------------------*/
ErrorHandler::~ErrorHandler()
{
    errorList.clear();
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBError Nimble Library Error Module
    @brief      Handles the error message, storing and reporting
    @param      errorType - Type of error
    @param      errorNumber - Error number
    @param      message - Error message
  --------------------------------------------------------------------------*/
void ErrorHandler::handleError( ErrorType errorType, LibraryError errorNumber, const std::string& message )
{
    // Create a new error
    ErrorInformation info;
    info.type    = errorType;
    info.number  = errorNumber;
    info.message = message;
    info.time    = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() ); // Add the error to the list
    errorList.push_back( info );

    // log error message
    LogError( errorNumber, message );
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBError Nimble Library Error Module
    @brief      Clears the error list
  --------------------------------------------------------------------------*/
void ErrorHandler::clearErrors()
{
    errorList.clear();
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBError Nimble Library Error Module
    @brief      Support function that reports the errors to the console terminal
 --------------------------------------------------------------------------*/
void ErrorHandler::reportErrors()
{
    if ( errorList.empty() )
    {
        std::cout << "No errors to report" << std::endl;
        return;
    }
    else
    {
        std::cout << "Errors reported:" << std::endl;
        for ( auto& error : errorList )
        {
            displayMessage( error );
        }
    }
}

/**---------------------------------------------------------------------------
    @ingroup    USBHIDConsoleApplication USB HID Console Application
    @brief      Returns the current status of the error handler
                This is used for Unit Tests
    @return     TS_ERRORHANDLER_STATUS - Status of the error handler
  --------------------------------------------------------------------------*/
ErrorStatus ErrorHandler::getStatusInformation()
{
    ErrorStatus info;

    info.Clear();

    for ( auto& error : errorList )
    {
        switch ( error.type )
        {
            case ErrorType::Status:
            {
                info.numStatus++;
                break;
            }
            case ErrorType::Warning:
            {
                info.numWarnings++;
                break;
            }
            case ErrorType::Critical:
            {
                info.numCritical++;
                break;
            }
            default:
            {
                info.numErrors++;
                break;
            }
        }
    }
    info.totalErrors = info.numErrors + info.numWarnings + info.numStatus + info.numCritical;
    return info;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBError Nimble Library Error Module
    @brief      Displays the passed in error to the console terminal
    @param      error - Error structure
  --------------------------------------------------------------------------*/
void ErrorHandler::displayMessage( const ErrorInformation& error )
{
    // Standard report to terminal
    // TODO: Add logging to file
    std::tm* tm = std::localtime( &error.time );

    std::cout << std::put_time( tm, "%d-%m-%Y %H-%M-%S" ) << " - ";
    switch ( error.type )
    {
        case ErrorType::Status:
        {
            std::cout << "Status: ";
            break;
        }
        case ErrorType::Warning:
        {
            std::cout << "Warning: ";
            break;
        }
        case ErrorType::Critical:
        {
            std::cout << "Critical: ";
            break;
        }
        default:
        {
            std::cout << "Error: ";
            break;
        }
    }
    // continue to display the error message
    std::cout << error.message << " (" << std::hex << (uint32_t)error.number << ")" << std::dec << std::endl;
}

//-----------------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBError Nimble Library Error Module
    @brief      Clears all the members of ErrorStatus
  --------------------------------------------------------------------------*/
void ErrorStatus::Clear()
{
    numErrors   = 0;
    numWarnings = 0;
    numStatus   = 0;
    numCritical = 0;
    totalErrors = 0;
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: ErrorHandler.cpp
// ----------------------------------------------------------------------------
