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

#include <windows.h>
#include <iostream>

#include "../../../inc/Modules/Screen/ScreenInfo.h"

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
    CONSOLE_SCREEN_BUFFER_INFO csbi; //!< Local: Console screen buffer information

    // Retrieve the console information
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );

    // Set the width and height
    width  = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    // Report the console information
    std::cout << "Console Width: " << width << " columns\n";
    std::cout << "Console Height: " << height << " rows\n";
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleIDEScreen Nimble IDE Screen Module
    @brief      Setup console for the NimbleIDE Screen
    --------------------------------------------------------------------------*/
void ScreenInfo::SetupConsole()
{
    SetConsoleOutputCP( CP_UTF8 );
    SetConsoleCP( CP_UTF8 );

    // Enable VT processing on stdout and stdin
    auto  stdout_handle = GetStdHandle( STD_OUTPUT_HANDLE );

    DWORD out_mode      = 0;
    GetConsoleMode( stdout_handle, &out_mode );

    // https://docs.microsoft.com/en-us/windows/console/setconsolemode
    const int enable_virtual_terminal_processing = 0x0004;
    const int disable_newline_auto_return        = 0x0008;
    out_mode |= enable_virtual_terminal_processing;
    out_mode |= disable_newline_auto_return;

    SetConsoleMode( stdout_handle, out_mode );
}

//-----------------------------------------------------------------------------

} // namespace Screen
} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: ScreenInfo.cpp
//-----------------------------------------------------------------------------
