/**----------------------------------------------------------------------------

    @file       Logger.cpp
    @defgroup   NimbleLIBLogger Nimble Library Logger Module
    @brief      Logging messages Module
    @copyright  Neil Bereford 2023

Notes:

    Standard logging of messages to the terminal and to a log file.
    This is the base case to the Error Handling module.
    There are four types of messages that can be logged:
    - Information
    - Warning
    - Error
    - Critical Error
    Messages are logged by the the following functions:
    - LogMessage()
    - LogError()

    TODO: Add the ability to log to a file
    TODO: Switch different output methods on and off

Version:

        0.0.1.0     First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include "../../../inc/Modules/ErrorHandling/ErrorHandler.h"
#include "../../../inc/Modules/Logging/Logger.h"

//-----------------------------------------------------------------------------
// Namesapce
//-----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class Support Functions
//-----------------------------------------------------------------------------

// Constructors and Destructors -----------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBLogger Nimble Library Logger Module
    @brief      Constructor for the Logger class
  --------------------------------------------------------------------------*/
Logger::Logger()
{
    outputFile        = false;
    outputTerminal    = false;
    loggerInitialized = false;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBLogger Nimble Library Logger Module
    @brief      Destructor for the Logger class
  --------------------------------------------------------------------------*/
Logger::~Logger()
{
}

void Logger::loggerInitialize()
{
    // defaulted to terminal output
    outputFile     = false;
    outputTerminal = true;

    // set the logger as initialized
    loggerInitialized = true;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBLogger Nimble Library Logger Module
    @brief      Log a message to the log file
    @param      message     Message to log
    @return     LibraryError - Error code
  --------------------------------------------------------------------------*/
LibraryError Logger::LogMessage( const std::string& message )
{
    if ( loggerInitialized == false )
    {
        return LibraryError::Logger_InitializeNotCalled;
    }

    std::time_t       t  = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
    std::tm*          tm = std::localtime( &t );
    std::stringstream ss;

    // build the logged message
    ss << "[" << std::put_time( tm, "%d-%m-%Y %H-%M-%S" ) << "] - " << message << std::endl;

    // Add the message to the log
    loggedInformation.push_back( ss.str() );

    // Output to the terminal if required
    if ( outputTerminal )
    {
        std::cout << ss.str();
    }

    return LibraryError::No_Error;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBLogger Nimble Library Logger Module
    @brief      Log a message to the log file
    @param      error	   Error code
    @param      message     Message to log
    @return     LibraryError - Error code
  --------------------------------------------------------------------------*/
LibraryError Logger::LogError( LibraryError error, const std::string& message )
{
    if ( loggerInitialized == false )
    {
        return LibraryError::Logger_InitializeNotCalled;
    }

    std::time_t       t  = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
    std::tm*          tm = std::localtime( &t );
    std::stringstream ss;

    // build the logged message
    ss << "[" << std::put_time( tm, "%d-%m-%Y %H-%M-%S" ) << "] - "
       << "Error 0x" << std::hex << (uint32_t)error << std::dec << " - " << message << std::endl;

    // Add the message to the log
    loggedInformation.push_back( ss.str() );

    // Output to the terminal if required
    if ( outputTerminal )
    {
        std::cout << ss.str();
    }

    return LibraryError::No_Error;
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: Logger.cpp
//-----------------------------------------------------------------------------
