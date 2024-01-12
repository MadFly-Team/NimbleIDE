/**----------------------------------------------------------------------------

    @file       IDEFileDialog.cpp
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEFileDialog class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

-----------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include "../../../inc/Modules/ErrorHandling/ErrorHandler.h"
#include "../../../inc/Modules/Curses/CursesColour.h"
#include "../../../inc/Modules/IDE/IDEFileDialog.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

// constructors & destructors -------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Constructor for IDEFileDialog class

----------------------------------------------------------------------------*/
IDEFileDialog::IDEFileDialog()
{
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Destructor for IDEFileDialog class

----------------------------------------------------------------------------*/
IDEFileDialog::~IDEFileDialog()
{
}

// Initialisation -------------------------------------------------------------

LibraryError IDEFileDialog::initLoader( const std::string& path, const std::string& filename, const std::string titleDialog )
{
    LibraryError error        = LibraryError::No_Error;
    std::string  statusString = "Select file to load";
    uint32_t     width        = m_kDialogWidth;
    uint32_t     height       = m_kDialogHeight;
    uint32_t     xPos         = ( COLS / 2 ) - ( width / 2 );
    uint32_t     yPos         = ( LINES / 2 ) - ( height / 2 );

    m_titleDialog             = titleDialog;
    m_path                    = path;
    m_filename                = filename;

    initDialog( xPos, yPos, width, height, IDE_COL_FG_BLACK, IDE_COL_BG_WHITE );
    title( m_titleDialog );
    status( statusString );

    return error;
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEFileDialog.cpp
// ----------------------------------------------------------------------------
