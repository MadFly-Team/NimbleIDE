/**----------------------------------------------------------------------------

    @file       ScreenInfo.cpp
    @defgroup   NimbleIDEScreen Nimble IDE Screen Module
    @brief      ScreenInfo class for the Nimble IDE

    @copyright  Neil Beresford 2023

Notes:

Version:

        0.0.1.0   First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Headers
//-----------------------------------------------------------------------------

#if defined( WIN32 ) || defined( _WIN32 )
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#endif

#include <iostream>

#include "../../../inc/Modules/Screen/ScreenInfo.h"
#include "../../../inc/Modules/Global/Globals.h"
#include "../../../inc/Modules/ErrorHandling/ErrorHandler.h"

//-----------------------------------------------------------------------------
// Namespace access
//-----------------------------------------------------------------------------

namespace Nimble
{
namespace Screen
{

//-----------------------------------------------------------------------------
// Supporting Functionality for ScreenInfo
//-----------------------------------------------------------------------------
/**---------------------------------------------------------------------------
    @ingroup    NimbleIDEScreen Nimble IDE Screen Module
    @brief      Interogate the console for the screen information
  --------------------------------------------------------------------------*/
void ScreenInfo::RetrieveConsoleInfo()
{
#if defined( WIN32 ) || defined( _WIN32 )
    CONSOLE_SCREEN_BUFFER_INFO csbi; //!< Local: Console screen buffer information

    // Retrieve the console information
    if ( GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi ) == false )
    {
        ErrorHandler::getInstance().LogError( LibraryError::Screen_ConsoleInfoFailed, "Failed to retrieve console information" );
        return;
    }

    // Set the width and height
    width  = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else

#ifdef TIOCGSIZE
    struct ttysize ts;
    ioctl( STDIN_FILENO, TIOCGSIZE, &ts );
    width  = ts.ts_cols;
    height = ts.ts_lines;
#elif defined( TIOCGWINSZ )
    struct winsize ts;
    ioctl( STDIN_FILENO, TIOCGWINSZ, &ts );
    width  = ts.ws_col;
    height = ts.ws_row;
#endif /* TIOCGSIZE */

#endif

    // Store the new values globally
    Globals::getInstance().setScreenWidth( width );
    Globals::getInstance().setScreenHeight( height );
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleIDEScreen Nimble IDE Screen Module
    @brief      Setup console for the NimbleIDE Screen
    --------------------------------------------------------------------------*/
void ScreenInfo::SetupConsole()
{
#if defined( WIN32 ) || defined( _WIN32 )
    if ( SetConsoleOutputCP( CP_UTF8 ) == false )
    {
        ErrorHandler::getInstance().LogError( LibraryError::Screen_SetupConsoleFailed, "Failed to set console output code page" );
        return;
    }
    if ( SetConsoleCP( CP_UTF8 ) == false )
    {
        ErrorHandler::getInstance().LogError( LibraryError::Screen_SetupConsoleFailed, "Failed to set console code page" );
        return;
    }

    // Enable VT processing on stdout and stdin
    auto  stdout_handle = GetStdHandle( STD_OUTPUT_HANDLE );

    DWORD out_mode      = 0;
    if ( GetConsoleMode( stdout_handle, &out_mode ) == false )
    {
        ErrorHandler::getInstance().LogError( LibraryError::Screen_SetupConsoleFailed, "Failed to get console mode" );
        return;
    }

    // https://docs.microsoft.com/en-us/windows/console/setconsolemode
    const int enable_virtual_terminal_processing = 0x0004;
    const int disable_newline_auto_return        = 0x0008;
    out_mode |= enable_virtual_terminal_processing;
    out_mode |= disable_newline_auto_return;

    if ( SetConsoleMode( stdout_handle, out_mode ) == false )
    {
        ErrorHandler::getInstance().LogError( LibraryError::Screen_SetupConsoleFailed, "Failed to set console mode" );
        return;
    }

#endif
}

//-----------------------------------------------------------------------------

} // namespace Screen
} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: ScreenInfo.cpp
//-----------------------------------------------------------------------------
//
