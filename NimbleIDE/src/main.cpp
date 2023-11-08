
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

#include <stdint.h>
#include <iostream>
#include <sstream>
#include "../inc/Modules/Screen/ScreenInfo.h"

#define COLOUR_TEXT( colour, bgcolour, text )  ( "\033[38;5;"  #colour  "m\033[48;5;" #bgcolour "m"  text )
#define COLOUR_RESET                           ( "\033[0m" )
#define SCREEN_CLEAR                           ( "\033[2J" )
#define SCREEN_HOME                            ( "\033[H" )
#define CHAR_FLASH                             ( "\033[5m" )
#define CHAR_UNDERLINE                         ( "\033[4m" )
#define CHAR_ITALIC                            ( "\033[3m" )
#define CHAR_INVERSE                           ( "\033[7m" )
#define CHAR_RESET                             ( "\033[0m" )
#define CHAR_BOLD                              ( "\033[1m" )
#define SCREEN_BOTTOM_LEFT                     ( "\033[999;999H" )
#define COLOUR_WHITE                           ( "\033[38;5;15m" )
#define COLOUR_BLACK                           ( "\033[38;5;0m" )
#define COLOUR_RED                             ( "\033[38;5;1m" )
#define COLOUR_GREEN                           ( "\033[38;5;2m" )
#define COLOUR_YELLOW                          ( "\033[38;5;3m" )
#define COLOUR_BLUE                            ( "\033[38;5;4m" )
#define COLOUR_MAGENTA                         ( "\033[38;5;5m" )
#define COLOUR_CYAN                            ( "\033[38;5;6m" )
#define COLOUR_BRIGHT_WHITE                    ( "\033[38;5;7m" )
#define COLOUR_BRIGHT_BLACK                    ( "\033[38;5;8m" )
#define COLOUR_BRIGHT_RED                      ( "\033[38;5;9m" )
#define COLOUR_BRIGHT_GREEN                    ( "\033[38;5;10m" )
#define COLOUR_BRIGHT_YELLOW                   ( "\033[38;5;11m" )
#define COLOUR_BRIGHT_BLUE                     ( "\033[38;5;12m" )
#define COLOUR_BRIGHT_MAGENTA                  ( "\033[38;5;13m" )
#define COLOUR_BRIGHT_CYAN                     ( "\033[38;5;14m" )
#define COLOUR_BRIGHT_WHITE                    ( "\033[38;5;15m" )
#define COLOUR_BG_WHITE                        ( "\033[38;5;15m" )
#define COLOUR_BG_BLACK                        ( "\033[38;5;0m" )
#define COLOUR_BG_RED                          ( "\033[38;5;1m" )
#define COLOUR_BG_GREEN                        ( "\033[38;5;2m" )
#define COLOUR_BG_YELLOW                       ( "\033[38;5;3m" )
#define COLOUR_BG_BLUE                         ( "\033[38;5;4m" )
#define COLOUR_BG_MAGENTA                      ( "\033[38;5;5m" )
#define COLOUR_BG_CYAN                         ( "\033[38;5;6m" )
#define COLOUR_BG_BRIGHT_WHITE                 ( "\033[38;5;7m" )
#define COLOUR_BG_BRIGHT_BLACK                 ( "\033[38;5;8m" )
#define COLOUR_BG_BRIGHT_RED                   ( "\033[38;5;9m" )
#define COLOUR_BG_BRIGHT_GREEN                 ( "\033[38;5;10m" )
#define COLOUR_BG_BRIGHT_YELLOW                ( "\033[38;5;11m" )
#define COLOUR_BG_BRIGHT_BLUE                  ( "\033[38;5;12m" )
#define COLOUR_BG_BRIGHT_MAGENTA               ( "\033[38;5;13m" )
#define COLOUR_BG_BRIGHT_CYAN                  ( "\033[38;5;14m" )
#define COLOUR_BG_BRIGHT_WHITE                 ( "\033[38;5;15m" )

//-----------------------------------------------------------------------------
// External Functionality
//-----------------------------------------------------------------------------

std::string ScreenPosition( uint32_t x, uint32_t y )
{
    std::stringstream ss;
    ss << "\033[" << y << ";" << x << "H";
    return ss.str();
}

int main( int argc, char* argv[] )
{
    ScreenInfo screenInfo;
    uint32_t xPos = 1;
    uint32_t yPos = 5;

    screenInfo.SetupConsole();
   
   // Print out the welcome message
    std::cout << SCREEN_CLEAR << SCREEN_HOME << ScreenPosition( 5, 10 );
    std::cout << "Welcome to the " << CHAR_FLASH << CHAR_BOLD << CHAR_ITALIC << "Nimble" << CHAR_RESET << " IDE" << std::endl;
    std::cout << ScreenPosition( 1,4 );
    screenInfo.RetrieveConsoleInfo();

    std::cout << ScreenPosition( 1,15 );
    std::cout << "This is "
              << "\033[38;5;226m"
              << "\033[48;5;100m"
              << " YELLOW "
              << "\033[0m"
              << " text" << std::endl;

    std::cout << "This is again "
              << COLOUR_TEXT( 226,72, " YELLOW " )
              << COLOUR_RESET << " text" << std::endl;

    xPos = (screenInfo.GetWidth() / 2) - 9;
    yPos = (screenInfo.GetHeight() / 2);

    std::cout << ScreenPosition( xPos, yPos )  << CHAR_FLASH << "This is flashing text" << CHAR_RESET << std::endl;
    std::cout << SCREEN_BOTTOM_LEFT << std::endl;

    // Return success
    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
// End of file: main.cpp
//-----------------------------------------------------------------------------
