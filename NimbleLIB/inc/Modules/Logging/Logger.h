/**----------------------------------------------------------------------------

    @file       Logger.h
    @defgroup   NimbleLIBLogger Nimble Library Logger Module
    @brief      Logging Manager Module
    @copyright  Neil Bereford 2023

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <fstream>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "../ErrorHandling/Errors.h"

//-----------------------------------------------------------------------------
// Namesapce
//-----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Clsss Definitions
//-----------------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBLogger Nimble Library Logger Module
    @brief      Logging Manager Class manages the logging of errors
                and messages

  --------------------------------------------------------------------------*/
class Logger
{
  public:
    // Public Methods -------------------------------------------------------
    // Constructor / Destructor ---------------------------------------------
    Logger();
    ~Logger();

    // intialization --------------------------------------------------------
    void loggerInitialize();

    // Logging messages -----------------------------------------------------
    LibraryError LogMessage( const std::string& message );
    LibraryError LogError( LibraryError error, const std::string& message );

    // Control of log data --------------------------------------------------
    void clearLog();
    void saveLog();

  private:
    // Private Data ---------------------------------------------------------
    std::vector<std::string> loggedInformation; //!< Internal store of all logged messaages
    bool                     loggerInitialized; //!< True, if the logger has been initialized
    bool                     outputTerminal;    //!< True, will display on stdout to the terminal
    bool                     outputFile;        //!< True, will log directly to file, not need to save log
};

//---------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: Logger.h
//-----------------------------------------------------------------------------
