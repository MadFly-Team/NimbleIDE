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
#include "IDEDialog.h"

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
    const std::string& GetPath() const;

  private:
    // private member variables -----------------------------------------------
    std::string m_path;
    std::string m_filename;
    std::string m_titleDialog;
};

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEFileDialog.h
// ----------------------------------------------------------------------------
