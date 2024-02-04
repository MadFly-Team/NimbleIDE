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

#include <cstdint>
#include <filesystem>
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
    m_cursorPos = 4;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Destructor for IDEFileDialog class

----------------------------------------------------------------------------*/
IDEFileDialog::~IDEFileDialog()
{
}

// Initialisation -------------------------------------------------------------
/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Initialise the File Dialog
    @param      path        Path to the file
    @param      filename    Filename
    @param      titleDialog Title of the dialog
    @return     LibraryError
----------------------------------------------------------------------------*/
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

    readDirectory( path );
    initDialog( xPos, yPos, width, height, IDE_COL_FG_BLACK, IDE_COL_BG_WHITE );
    title( m_titleDialog );
    status( statusString );

    buttons( getWindow(), "Cancel", "Load" );
    return error;
}

// Display --------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Draw the File Dialog
    @return     LibraryError
----------------------------------------------------------------------------*/
LibraryError IDEFileDialog::drawLoader()
{
    LibraryError error = LibraryError::No_Error;
    // Draw the dialog
    drawDialog();
    // Draw the files in the directory
    uint32_t yPos = 3;
    for ( const auto& entry : m_filesInDirectory )
    {
        if ( yPos < ( getHeight() - 6 ) )
        {
            if ( entry.name == ".." )
            {
                mvwaddnstr( getWindow(), yPos, 3, entry.name.c_str(), 52 );
                mvwchgat( getWindow(), yPos, 3, 52, A_NORMAL, COLOUR_INDEX( IDE_COL_FG_BLUE, IDE_COL_BG_WHITE ), nullptr );
            }
            else
            {
                if ( entry.type == FileType::Directory )
                {
                    mvwaddnstr( getWindow(), yPos, 3, entry.name.c_str(), 52 );
                    mvwchgat( getWindow(), yPos, 3, 52, A_NORMAL, COLOUR_INDEX( IDE_COL_FG_BLUE, IDE_COL_BG_WHITE ), nullptr );
                }
                else
                {
                    mvwaddnstr( getWindow(), yPos, 3, entry.name.c_str(), 52 );
                    mvwchgat( getWindow(), yPos, 3, 52, A_NORMAL, COLOUR_INDEX( IDE_COL_FG_BLACK, IDE_COL_BG_WHITE ), nullptr );
                }
            }
        }
        else
        {
            break;
        }
        yPos++;
    }
    drawCursor();
    draw();
    refresh();
    return error;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Process the File Dialog
    @return     LibraryError
----------------------------------------------------------------------------*/
LibraryError IDEFileDialog::process()
{
    LibraryError error  = LibraryError::No_Error;
    uint32_t     ch     = 0;
    bool         m_done = false;

    processDialog();
    if ( ch != ERR )
    {
        switch ( ch )
        {
            case KEY_UP:
                if ( m_cursorPos > 0 )
                {
                    mvwchgat( getWindow(), m_cursorPos + 3, 3, 52, A_NORMAL, COLOUR_INDEX( IDE_COL_FG_BLACK, IDE_COL_BG_WHITE ), nullptr );
                    m_cursorPos--;
                    drawCursor();
                }
                break;
            case KEY_DOWN:
                if ( m_cursorPos < ( getHeight() - 6 ) )
                {
                    mvwchgat( getWindow(), m_cursorPos + 3, 3, 52, A_NORMAL, COLOUR_INDEX( IDE_COL_FG_BLACK, IDE_COL_BG_WHITE ), nullptr );
                    m_cursorPos++;
                    drawCursor();
                }
                break;
            case 10:
                if ( m_cursorPos == 0 )
                {
                }
                else
                {
                    m_filename  = m_filesInDirectory.at( m_cursorPos ).name;
                    m_path      = m_filesInDirectory.at( m_cursorPos ).name;
                    m_completed = true;
                }
                break;
            case 27:
                m_cancelled = true;
                break;
            default:
                break;
        }
    }

    return error;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Draw the File cursor
    @return     void
----------------------------------------------------------------------------*/
void IDEFileDialog::drawCursor()
{
    mvwchgat( getWindow(), m_cursorPos + 3, 3, 52, A_NORMAL, COLOUR_INDEX( IDE_COL_FG_WHITE, IDE_COL_BG_BLACK ), nullptr );
}

// Getters ------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Get the filename
    @return     std::string
----------------------------------------------------------------------------*/
const std::string& IDEFileDialog::getFilename() const
{
    return m_filename;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Get the path
    @return     std::string
----------------------------------------------------------------------------*/
const std::string& IDEFileDialog::getPath() const
{
    return m_path;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Get the completed flag
    @return     bool
----------------------------------------------------------------------------*/
const bool IDEFileDialog::isCompleted() const
{
    return m_completed;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Get the cancelled flag
    @return     bool
----------------------------------------------------------------------------*/
const bool IDEFileDialog::isCancelled() const
{
    return m_cancelled;
}

// File management ------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Read the directory
    @param      path    Path to the file
    @return     LibraryError
----------------------------------------------------------------------------*/
LibraryError IDEFileDialog::readDirectory( const std::string& path )
{
    LibraryError error = LibraryError::No_Error;
    FileData     fileData;
    fileData.type                     = FileType::Directory;
    fileData.name                     = "..";
    std::filesystem::path currentPath = "c:/";
    m_filesInDirectory.clear();
    m_filesInDirectory.push_back( fileData );
    for ( const auto& entry : std::filesystem::directory_iterator( currentPath ) )
    {
        if ( entry.is_directory() )
        {
            fileData.type = FileType::Directory;
        }
        else
        {
            fileData.type = FileType::File;
        }
        fileData.name = entry.path().filename().string();
        m_filesInDirectory.push_back( fileData );
    }

    return error;
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEFileDialog.cpp
// ----------------------------------------------------------------------------
