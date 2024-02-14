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
#include <algorithm>
#include "../../../inc/Modules/ErrorHandling/ErrorHandler.h"
#include "../../../inc/Modules/Curses/CursesColour.h"
#include "../../../inc/Modules/Curses/CursesKeyboard.h"
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
    m_cursorPos    = 4;
    m_cancelled    = false;
    m_completed    = false;
    m_fileStartPos = 0;
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

    addKeyMap( m_keyMapCursorControl );
    addKeyMap( m_keyMapDialogControl );

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
    uint32_t    yPos      = 3;
    uint32_t    fileCount = 0;
    std::string nameStr   = "";
    for ( const auto& entry : m_filesInDirectory )
    {
        if ( fileCount++ < m_fileStartPos )
            continue;

        if ( yPos < ( getHeight() - 6 ) )
        {
            nameStr = entry.name;
            nameStr.resize( 52, ' ' );

            mvwaddstr( getWindow(), yPos, 3, nameStr.c_str() );

            if ( entry.name == ".." )
            {
                mvwchgat( getWindow(), yPos, 3, 52, A_NORMAL, COLOUR_INDEX( IDE_COL_FG_BLUE, IDE_COL_BG_WHITE ), nullptr );
            }
            else
            {
                if ( entry.type == FileType::Directory )
                {
                    mvwchgat( getWindow(), yPos, 3, 52, A_NORMAL, COLOUR_INDEX( IDE_COL_FG_BLUE, IDE_COL_BG_WHITE ), nullptr );
                }
                else
                {
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
    @ingroup   NimbleLIBIDE Nimble Library IDE Module
    @brief     Process the File Dialog
    @param     ch      Key pressed returned or ERR
    @return    LibraryError
----------------------------------------------------------------------------*/
LibraryError IDEFileDialog::processKeyPress( uint32_t ch )
{
    LibraryError error = LibraryError::No_Error;

    processDialog( ch );
    // check the button presses by the mouse...
    if ( isLeftButtonPressed() )
    {
        m_cancelled = true;
    }
    if ( isRightButtonPressed() )
    {
        m_completed = true;
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

// Control --------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Control the File Dialog
    @param      ch  Character to process
    @return     void
----------------------------------------------------------------------------*/
void IDEFileDialog::cursorControl( uint32_t ch )
{
    switch ( ch )
    {
        case KEY_UP:
        {

            if ( m_cursorPos == 0 && m_fileStartPos > 0 )
            {
                m_fileStartPos--;
            }
            else if ( m_cursorPos > 0 )
            {
                mvwchgat( getWindow(), m_cursorPos + 3, 3, 52, A_NORMAL, COLOUR_INDEX( IDE_COL_FG_BLACK, IDE_COL_BG_WHITE ), nullptr );
                m_cursorPos--;
                drawCursor();
            }
            setVerticalScrollPos( ( (float)( m_fileStartPos + m_cursorPos ) / (float)m_filesInDirectory.size() ) * 100 );
            break;
        }
        case KEY_DOWN:
        {
            if ( m_cursorPos < ( getHeight() - 10 ) )
            {
                mvwchgat( getWindow(), m_cursorPos + 3, 3, 52, A_NORMAL, COLOUR_INDEX( IDE_COL_FG_BLACK, IDE_COL_BG_WHITE ), nullptr );
                if ( m_cursorPos < m_filesInDirectory.size() )
                    m_cursorPos++;
                drawCursor();
            }
            else
            {
                if ( m_cursorPos + m_fileStartPos < m_filesInDirectory.size() - 1 )
                    m_fileStartPos++;
            }
            setVerticalScrollPos( ( (float)( m_fileStartPos + m_cursorPos ) / (float)m_filesInDirectory.size() ) * 100 );
            break;
        }
        default:
        {

            break;
        }
    }
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Process the File Dialog
    @param      ch  Character to process
    @return     void
----------------------------------------------------------------------------*/
void IDEFileDialog::dialogControl( uint32_t ch )
{
    switch ( ch )
    {
        case KEY_ESC:
        {
            m_cancelled = true;
            break;
        }
        case KEY_ENTER:
        {
            m_completed = true;
            break;
        }
        default:
        {
            break;
        }
    }
}

// Getters --------------------------------------------------------------------

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
    @brief      Read the directory, sorting the results alphabetically
    @param      path    Path to the file
    @return     LibraryError
----------------------------------------------------------------------------*/
LibraryError IDEFileDialog::readDirectory( const std::string& path )
{
    LibraryError error = LibraryError::No_Error;
    FileData     fileData;
    fileData.type = FileType::Directory;
    fileData.name = "..";

#if ( _WIN32_ )
    std::filesystem::path currentPath = "c:/";
#else
    std::filesystem::path currentPath = "/";
#endif
    m_filesInDirectory.clear();
    m_filesInDirectory.push_back( fileData );

    // Read the directory, storing the files and directories
    for ( const auto& entry : std::filesystem::directory_iterator( currentPath ) )
    {
        // special case for system files and directories that mess up the sort, and are not needed.
        if ( entry.path().filename().string()[ 0 ] == '$' )
        {
            continue;
        }
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

    // Sort the files and directories alphabetically (directories first)
    std::sort( m_filesInDirectory.begin(), m_filesInDirectory.end(),
               []( const FileData& a, const FileData& b ) -> bool
               {
                   if ( a.type != b.type )
                   {
                       return a.type < b.type;
                   }
                   return a.name < b.name;
               } );

    // setup the dialog, with new file list
    m_cursorPos    = 0;
    m_fileStartPos = 0;
    return error;
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEFileDialog.cpp
// ----------------------------------------------------------------------------
