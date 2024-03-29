/**----------------------------------------------------------------------------

    @file       FileManager.cpp
    @defgroup   NimbleLIBFile Nimble Library File Module
    @brief      File Manager Module
    @copyright  Neil Bereford 2023

Notes:

-----------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include "../../../inc/Modules/FileHandling/FileManager.h"

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
    @ingroup    NimbleLIBFile Nimble Library File Module
    @brief      Constructor for the FileManager class

  --------------------------------------------------------------------------*/
FileManager::FileManager()
{
    fileCount  = 0;
    nextFileID = 0;
    fileList.clear();
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBFile Nimble Library File Module
    @brief      Destructor for the FileManager class

  --------------------------------------------------------------------------*/
FileManager::~FileManager()
{
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: FileManager.cpp
//-----------------------------------------------------------------------------
