/**----------------------------------------------------------------------------

    @file       unitTests_ErrorHandler.h
    @defgroup   NimbleLIB Nimble LIB
    @brief      Unit Tests for the Nimble LIB

    @copyright  Neil Beresford 2023

Notes:

Version:

        0.0.1.0   First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <string>
#include "../../NimbleLIB/inc/NimbleLib.h"

//-----------------------------------------------------------------------------
// Namespace access
//-----------------------------------------------------------------------------

using namespace Nimble;
using namespace Nimble::Screen;

//-----------------------------------------------------------------------------
// Tests
//-----------------------------------------------------------------------------
TEST_CASE( "Testing the Error Handler Module" )
{
    // Test the Erorr Handler at initialization
    SUBCASE( "Testing Error Handler Initialization" )
    {
        ErrorHandler::getInstance().clearErrors();
        ErrorStatus errorStatus = ErrorHandler::getInstance().getStatusInformation();
        CHECK( errorStatus.totalErrors == 0 );
    }
    // Test the Error Handler with a single error
    SUBCASE( "Testing Error Handler with a single error" )
    {
        ErrorHandler::getInstance().clearErrors();
        ErrorHandler::getInstance().handleError( ErrorType::Error, LibraryError::Logger_InitializeNotCalled, "Test Error" );
        ErrorStatus errorStatus = ErrorHandler::getInstance().getStatusInformation();
        CHECK( errorStatus.totalErrors == 1 );
    }
    // test the Erorr Handler clear errors
    SUBCASE( "Testing Error Handler clear errors" )
    {
        ErrorHandler::getInstance().clearErrors();
        ErrorHandler::getInstance().handleError( ErrorType::Error, LibraryError::Logger_InitializeNotCalled, "Test another Error" );
        ErrorHandler::getInstance().clearErrors();
        ErrorStatus errorStatus = ErrorHandler::getInstance().getStatusInformation();
        CHECK( errorStatus.totalErrors == 0 );
    }
    // Test the Error Handler with multiple errors
    SUBCASE( "Testing Error Handler with multiple errors" )
    {
        ErrorHandler::getInstance().clearErrors();
        ErrorHandler::getInstance().handleError( ErrorType::Error, LibraryError::Logger_InitializeNotCalled, "Test Error 1" );
        ErrorHandler::getInstance().handleError( ErrorType::Error, LibraryError::Logger_InitializeNotCalled, "Test Error 2" );
        ErrorHandler::getInstance().handleError( ErrorType::Error, LibraryError::Logger_InitializeNotCalled, "Test Error 3" );
        ErrorHandler::getInstance().handleError( ErrorType::Error, LibraryError::Logger_InitializeNotCalled, "Test Error 4" );
        ErrorHandler::getInstance().handleError( ErrorType::Error, LibraryError::Logger_InitializeNotCalled, "Test Error 5" );
        ErrorStatus errorStatus = ErrorHandler::getInstance().getStatusInformation();
        CHECK( errorStatus.totalErrors == 5 );
    }
    // Test the Error Handler with multiple different errors and check the error codes
    SUBCASE( "Testing Error Handler with multiple different errors" )
    {
        ErrorHandler::getInstance().clearErrors();
        ErrorHandler::getInstance().handleError( ErrorType::Error, LibraryError::Logger_InitializeNotCalled, "Test Error 1" );
        ErrorHandler::getInstance().handleError( ErrorType::Critical, LibraryError::Logger_InitializeNotCalled, "Test Critical 2" );
        ErrorHandler::getInstance().handleError( ErrorType::Warning, LibraryError::Logger_InitializeNotCalled, "Test Warning 3" );
        ErrorHandler::getInstance().handleError( ErrorType::Status, LibraryError::Logger_InitializeNotCalled, "Test Status 4" );
        ErrorStatus errorStatus = ErrorHandler::getInstance().getStatusInformation();
        CHECK( errorStatus.totalErrors == 4 );
        CHECK( errorStatus.numErrors == 1 );
        CHECK( errorStatus.numCritical == 1 );
        CHECK( errorStatus.numWarnings == 1 );
        CHECK( errorStatus.numStatus == 1 );
        ErrorHandler::getInstance().clearErrors();
    }
}

//-----------------------------------------------------------------------------
// End of file: unitTests_ErrorHandler.h
//-----------------------------------------------------------------------------
