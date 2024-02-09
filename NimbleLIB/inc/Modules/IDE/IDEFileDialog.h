/**----------------------------------------------------------------------------

    @file       IDEFileDialog.h
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEFileDialog class for the Nimble Library

    @copyright  Neil Bereford 2023

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include <filesystem>
#include <vector>
#include "IDEDialog.h"
#include "IDEButton.h"

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
    @brief      File Dialog, allowing selection of files and directories

-----------------------------------------------------------------------------*/
class IDEFileDialog : public IDEDialog
{
  public:
    // constructor & destructor -----------------------------------------------
    IDEFileDialog();
    ~IDEFileDialog();
    // constants --------------------------------------------------------------
    static const uint32_t m_kDialogWidth  = 60;
    static const uint32_t m_kDialogHeight = 25;
    // initialisation ---------------------------------------------------------
    LibraryError initLoader( const std::string& path, const std::string& filename, const std::string titleDialog );
    // Getters functions ------------------------------------------------------
    const std::string& getFilename() const;
    const std::string& getPath() const;
    const bool         isCompleted() const;
    const bool         isCancelled() const;
    // Process ----------------------------------------------------------------
    LibraryError processKeyPress( uint32_t ch );
    // File Management --------------------------------------------------------
    LibraryError readDirectory( const std::string& path );
    // Draw -------------------------------------------------------------------
    LibraryError drawLoader();

  private:
    // enums and structs -----------------------------------------------------

    enum class FileType
    {
        Directory,
        File
    };

    struct FileData
    {
        FileType    type;
        std::string name;
    };

    // cursor control ---------------------------------------------------------
    KeyMap m_keyMapCursorControl = {
        "CursorControl", {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT},
         std::bind( &IDEFileDialog::cursorControl, this, std::placeholders::_1 )
    };

    KeyMap m_keyMapDialogControl = {
        "DialogControl", {KEY_ESC, KEY_ENTER},
         std::bind( &IDEFileDialog::dialogControl, this, std::placeholders::_1 )
    };

    // private member variables -----------------------------------------------
    std::string           m_path;             // !< Path
    std::string           m_filename;         //!< Filename
    std::string           m_titleDialog;      //!< Title of the dialog
    std::vector<FileData> m_filesInDirectory; //!< Files in the directory
    uint32_t              m_cursorPos;        //!< Cursor position
    uint32_t              m_fileStartPos;     //!< start of first shown file
    bool                  m_completed;        //!< Completed
    bool                  m_cancelled;        //!< Cancelled
    // private functions -------------------------------------------------------
    void drawCursor();
    void cursorControl( uint32_t key );
    void dialogControl( uint32_t key );
    //-------------------------------------------------------------------------
};

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEFileDialog.h
// ----y-----------------------------------------------------------------------
