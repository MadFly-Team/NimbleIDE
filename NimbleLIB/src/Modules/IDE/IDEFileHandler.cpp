/**----------------------------------------------------------------------------

    @file       IDEFileHandler.cpp
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEFileHandler class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:


Version:

        0.0.1.0     First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include "../../../inc/Modules/IDE/IDEFileHandler.h"
#include <cstdint>

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

// Constructor & Destructor -----------------------------------------------------

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEFileHandler Constructor
------------------------------------------------------------------------------*/
IDEFileHandler::IDEFileHandler()
{
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEFileHandler Destructor
------------------------------------------------------------------------------*/
IDEFileHandler::~IDEFileHandler()
{
}

// getters ---------------------------------------------------------------------

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      retrieve the flags of the IDEFileHandler class
    @return     uint32_t    FileHandlerFlags full set of flags
------------------------------------------------------------------------------*/
uint32_t IDEFileHandler::getFlags()
{
    return m_flags;
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      retrieve the status string of the IDEFileHandler class
    @return     std::string   status string
------------------------------------------------------------------------------*/
std::string IDEFileHandler::getStatus()
{
    return m_status;
}

// setters ---------------------------------------------------------------------

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      set the flags of the IDEFileHandler class
    @param      flags   FileHandlerFlags full set of flags
------------------------------------------------------------------------------*/
void IDEFileHandler::setFlags( uint32_t flags )
{
    m_flags = flags;
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      set the status string of the IDEFileHandler class
    @param      status  std::string   status string
------------------------------------------------------------------------------*/
void IDEFileHandler::setStatus( std::string status )
{
    m_status = status;
}

// file functions ---------------------------------------------------------------

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      open a file
    @param      filename    std::string filename to open
    @return     LibraryError    error code
------------------------------------------------------------------------------*/
LibraryError IDEFileHandler::openFile( std::string& filename )
{
    LibraryError error = LibraryError::No_Error;

    // open the file
    m_fileIn.open( filename );
    if ( !m_fileIn.is_open() )
    {
        error = LibraryError::IDEFileHandler_FailedToOpenFile;
    }
    else
    {
        // prep for the file read
        m_editlines.clear();
        m_filename = filename;
        m_status   = "File Opened : ";
        m_status += m_filename;

        // read the file
        std::string line;
        while ( getline( m_fileIn, line ) )
        {
            m_editlines.push_back( line );
        }
        m_fileIn.close();
        m_flags |= (uint32_t)FileHandlerFlags::Open;
        m_flags &= -(uint32_t)FileHandlerFlags::Save;
    }

    return error;
}

/**-----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      save a file
    @param      filename    std::string filename to save
    @return     LibraryError    error code
------------------------------------------------------------------------------*/
LibraryError IDEFileHandler::saveFile( std::string& filename )
{
    LibraryError error = LibraryError::No_Error;

    if ( m_flags & (uint32_t)FileHandlerFlags::Open )
    {
        // save the file
        m_fileOut.open( filename );
        if ( !m_fileOut.is_open() )
        {
            error = LibraryError::IDEFileHandler_FailedToOpenFile;
        }
        else
        {
            for ( auto& editline : m_editlines )
            {
                m_fileOut << editline << std::endl;
            }
            m_fileOut.close();
            m_flags |= (uint32_t)FileHandlerFlags::Save;
            m_flags &= -(uint32_t)FileHandlerFlags::Open;
            m_filename = filename;
            m_status   = "File Saved : ";
            m_status += m_filename;
        }
    }
    else
    {
        error = LibraryError::IDEFileHandler_FileNotOpen;
    }
    return error;
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEFileHandler.cpp
// ----------------------------------------------------------------------------
