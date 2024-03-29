/**----------------------------------------------------------------------------

    @file       IDEFileHandler.h
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEFileHandler class for the Nimble Library

    @copyright  Neil Bereford 2023

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include <cinttypes>
#include <cstdint>
#include <memory>
#include <vector>
#include <sstream>

#include "../ErrorHandling/ErrorHandler.h"
#include "../Utilities/StatusCtrl.h"
#include "IDEEditline.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------
/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      File handler class for the Nimble Library
-----------------------------------------------------------------------------*/
class IDEFileHandler : public StatusCtrl
{
  public:
    // typedefs and enums ------------------------------------------------------
    typedef struct _EditLineAttributes
    {
        uint16_t MarkStart; //!< Mark start (highlight)
        uint16_t MarkEnd;   //!< Mark end (highlight)

        /**-------------------------------------------------------------------------
            @ingroup    NimbleLIBIDE Nimble Library IDE Module
            @brief      EditLineAttributes - Clear the attributes
            @return     void
        ----------------------------------------------------------------------------*/
        void clear()
        {
            MarkStart = 0;
            MarkEnd   = 0;
        }
        /**-------------------------------------------------------------------------
            @ingroup    NimbleLIBIDE Nimble Library IDE Module
            @brief      EditLineAttributes - Get the length
            @return     Length of the marked text
        ----------------------------------------------------------------------------*/
        uint32_t length()
        {
            return ( MarkEnd - MarkStart );
        }

    } EditLineAttributes, *pEditLineAttributes; //!< Editline attributes

    /**-------------------------------------------------------------------------
        @ingroup    NimbleLIBIDE Nimble Library IDE Module
        @brief      File handler flags, used with StatusCtrl class
    ----------------------------------------------------------------------------*/
    enum class FileHandlerFlags : uint32_t
    {
        None         = 0x00000000,
        Open         = 0x00000001,
        Save         = 0x00000002,
        SaveAs       = 0x00000004,
        Close        = 0x00000008,
        Quit         = 0x00000010,
        New          = 0x00000020,
        Undo         = 0x00000040,
        Redo         = 0x00000080,
        Cut          = 0x00000100,
        Copy         = 0x00000200,
        Paste        = 0x00000400,
        SelectAll    = 0x00000800,
        Find         = 0x00001000,
        FindNext     = 0x00002000,
        FindPrevious = 0x00004000,
        Replace      = 0x00008000,
        Goto         = 0x00010000,
        Compile      = 0x00020000,
        Build        = 0x00040000,
        Run          = 0x00080000,
        Debug        = 0x00100000,
        StepInto     = 0x00200000,
        StepOver     = 0x00400000,
        StepOut      = 0x00800000,
        Breakpoint   = 0x01000000,
        Watch        = 0x02000000,
        Settings     = 0x04000000,
        Help         = 0x08000000,
        About        = 0x10000000,
        All          = 0xFFFFFFFF
    };
    // public functions --------------------------------------------------------
    // constructors & destructors ----------------------------------------------
    IDEFileHandler();
    ~IDEFileHandler();
    // setters -----------------------------------------------------------------
    void setFlags( uint32_t flags );
    void setStatus( std::string status );
    // getters -----------------------------------------------------------------
    std::string getStatus();
    uint32_t    getFlags();
    // file functions ----------------------------------------------------------
    LibraryError openFile( std::string& filename );
    LibraryError saveFile( std::string& filename );
    //--------------------------------------------------------------------------
  private:
    // private variables -------------------------------------------------------
    uint32_t      m_flags;    //!< File handler flags
    std::string   m_filename; //!< Filename
    std::string   m_status;   //!< Status string
    std::ofstream m_fileOut;  //!< File stream - output
    std::ifstream m_fileIn;   //!< File stream - input
  protected:
    std::vector<std::string>                  m_editlines;          //!< Edit lines
    std::vector<EditLineAttributes>           m_editlineAttributes; //!< Edit line attributes
    std::vector<std::unique_ptr<IDEEditline>> m_test;               //!< Test for class insertion
    //--------------------------------------------------------------------------
};

//-----------------------------------------------------------------------------
} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEFileHandler.h
// ----------------------------------------------------------------------------
