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
// Supporting Functionality for ScreenInfo
//-----------------------------------------------------------------------------

void ScreenInfo::RetrieveConsoleInfo()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    width  = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    std::cout << "Console Width: " << width << " columns\n";
    std::cout << "Console Height: " << height << " rows\n";
}

//-----------------------------------------------------------------------------
// End of file: ScreenInfo.cpp
//-----------------------------------------------------------------------------
