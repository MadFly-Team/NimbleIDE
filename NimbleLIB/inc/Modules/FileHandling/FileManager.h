/**----------------------------------------------------------------------------

    @file       FileManager.h
    @defgroup   NimbleLIBFile Nimble Library File Module
    @brief      File Manager Module
    @copyright  Neil Bereford 2023

-----------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <fstream>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

//-----------------------------------------------------------------------------
// Namesapce
//-----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Clsss Definitions
//-----------------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBFile Nimble Library File Module
    @brief      File state machine states
  --------------------------------------------------------------------------*/
typedef enum
{
    IDLE = 0,    //!< 0 - structure is idle and free for use
    OPENED,      //!< 1 - File has been opened
    READ,        //!< 2 - File has been read
    ERROR,       //!< 3 - Errored state
    TOTAL_STATES //!< 4 - Total States

} TE_FILE_STATE;

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBFile Nimble Library File Module
    @brief      FILE_DATA structure stores the file data
                and the file state machine

  --------------------------------------------------------------------------*/
typedef struct
{
    std::string          fileName;   //!< Full File Name
    std::ifstream        fileHandle; //!< File Handle, when opened
    std::vector<uint8_t> fileData;   //!< File Data, stored as bytes
    TE_FILE_STATE        fileState;  //!< File State Machine
    uint32_t             fileSize;   //!< File Size in bytes
    uint32_t             fileID;     //!< Unique File ID

} TS_FILE_DATA, *PTS_FILE_DATA;

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBFile Nimble Library File Module
    @brief      File Manager Class manages the files with their data
  --------------------------------------------------------------------------*/
class FileManager
{
  public:
    // Public Methods -------------------------------------------------------
    // Constructor / Destructor ---------------------------------------------
    FileManager();
    ~FileManager();
    // File Handling --------------------------------------------------------
    uint32_t openFile( const std::string& fileName );

  private:
    // Private Data -------------------------------------------------------
    std::vector<TS_FILE_DATA> fileList;   //!< List of files
    uint32_t                  nextFileID; //!< Unique File ID used for next file
    uint32_t                  fileCount;  //!< Total number of files handled
};

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: FileManager.h
//-----------------------------------------------------------------------------
