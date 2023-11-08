
/**----------------------------------------------------------------------------

    @file       main.cpp
    @defgroup   NimbleIDE Nimble IDE
    @brief      Main entry and control point for the Nimble IDE

    @copyright  Neil Beresford 2023

Notes:

Version:

        0.0.1.0   First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Headers
//-----------------------------------------------------------------------------

#include <iostream>
#include <windows.h>

#include "../inc/Modules/Screen/ScreenInfo.h"

//-----------------------------------------------------------------------------
// External Functions
//-----------------------------------------------------------------------------

void setColor( int textCol, int backgroundCol )
{
    int color = textCol + ( backgroundCol * 16 );
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), color );
}

int main()
{
    ScreenInfo screenInfo;

    // Clear the screen
    system( "cls" );

    // Text color: Yellow (14), Background color: Blue (1)
    setColor( 14, 1 );

    // Output colored text
    std::cout << "Text with Yellow foreground and Blue background\n";

    // Restoring default color (white text on black background)
    setColor( 15, 0 );

    screenInfo.RetrieveConsoleInfo();

    std::cout << "Hello, World!" << std::endl;

    return 0;
}

//-----------------------------------------------------------------------------
// End of file: main.cpp
//-----------------------------------------------------------------------------
