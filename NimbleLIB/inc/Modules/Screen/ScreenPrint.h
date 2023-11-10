/**----------------------------------------------------------------------------

    @file       ScreenPrint.h
    @defgroup   NimbleIDEScreen Nimble IDE Screen Module
    @brief      ScreenPrint class for the Nimble IDE

    @copyright  Neil Bereford 2023

Notes:

Version:

        0.0.1.0     First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
//  includes
//-----------------------------------------------------------------------------

#include <stdint.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include "../../../inc/Modules/Screen/ScreenWord.h"

//-----------------------------------------------------------------------------
// Namespace access
//-----------------------------------------------------------------------------

namespace Nimble
{
namespace Screen
{

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

#define COLOUR_TEXT( colour, bgcolour, text ) ( "\033[38;5;" #colour "m\033[48;5;" #bgcolour "m" text )
#define COLOUR_RESET                          ( "\033[0m" )
#define SCREEN_CLEAR                          ( "\033[2J" )
#define SCREEN_HOME                           ( "\033[H" )
#define CHAR_FLASH                            ( "\033[5m" )
#define CHAR_UNDERLINE                        ( "\033[4m" )
#define CHAR_ITALIC                           ( "\033[3m" )
#define CHAR_INVERSE                          ( "\033[7m" )
#define CHAR_RESET                            ( "\033[0m" )
#define CHAR_BOLD                             ( "\033[1m" )
#define CHAR_STRIKETHROUGH                    ( "\033[9m" )
#define SCREEN_BOTTOM_LEFT                    ( "\033[999;999H" )
#define COLOUR_WHITE                          ( "\033[38;5;55m" )
#define COLOUR_BLACK                          ( "\033[38;5;40m" )
#define COLOUR_RED                            ( "\033[38;5;41m" )
#define COLOUR_GREEN                          ( "\033[38;5;42m" )
#define COLOUR_YELLOW                         ( "\033[38;5;43m" )
#define COLOUR_BLUE                           ( "\033[38;5;44m" )
#define COLOUR_MAGENTA                        ( "\033[38;5;45m" )
#define COLOUR_CYAN                           ( "\033[38;5;46m" )
#define COLOUR_BRIGHT_WHITE                   ( "\033[38;5;7m" )
#define COLOUR_BRIGHT_BLACK                   ( "\033[38;5;8m" )
#define COLOUR_BRIGHT_RED                     ( "\033[38;5;9m" )
#define COLOUR_BRIGHT_GREEN                   ( "\033[38;5;10m" )
#define COLOUR_BRIGHT_YELLOW                  ( "\033[38;5;1m" )
#define COLOUR_BRIGHT_BLUE                    ( "\033[38;5;2m" )
#define COLOUR_BRIGHT_MAGENTA                 ( "\033[38;5;3m" )
#define COLOUR_BRIGHT_CYAN                    ( "\033[38;5;4m" )
#define COLOUR_BG_WHITE                       ( "\033[38;5;45m" )
#define COLOUR_BG_BLACK                       ( "\033[48;5;40m" )
#define COLOUR_BG_RED                         ( "\033[48;5;41m" )
#define COLOUR_BG_GREEN                       ( "\033[48;5;42m" )
#define COLOUR_BG_YELLOW                      ( "\033[48;5;43m" )
#define COLOUR_BG_BLUE                        ( "\033[48;5;44m" )
#define COLOUR_BG_MAGENTA                     ( "\033[48;5;45m" )
#define COLOUR_BG_CYAN                        ( "\033[48;5;46m" )
#define COLOUR_BG_BRIGHT_WHITE                ( "\033[48;5;7m" )
#define COLOUR_BG_BRIGHT_BLACK                ( "\033[48;5;8m" )
#define COLOUR_BG_BRIGHT_RED                  ( "\033[48;5;9m" )
#define COLOUR_BG_BRIGHT_GREEN                ( "\033[48;5;10m" )
#define COLOUR_BG_BRIGHT_YELLOW               ( "\033[48;5;11m" )
#define COLOUR_BG_BRIGHT_BLUE                 ( "\033[48;5;12m" )
#define COLOUR_BG_BRIGHT_MAGENTA              ( "\033[48;5;13m" )
#define COLOUR_BG_BRIGHT_CYAN                 ( "\033[48;5;14m" )
#define COLOUR_BG_START                       ( "\033[48;5;" )
#define COLOUR_START                          ( "\033[38;5;" )
#define COLOUR_END                            ( "m" )

//-----------------------------------------------------------------------------
// Class definitions
//-----------------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleIDEScreen Nimble IDE Screen Module
    @brief      ScreenPrint class for the Nimble IDE
  --------------------------------------------------------------------------*/
class ScreenPrint
{
  private:
    /**------------------------------------------------------------------------
        @brief      Data for the ScreenPrint class
     ------------------------------------------------------------------------*/
    std::stringstream m_ss; //!< String stream for the screen print class

    /**------------------------------------------------------------------------
        @brief      Constructor
     ------------------------------------------------------------------------*/
    ScreenPrint( const ScreenPrint& ) = delete;
    /**------------------------------------------------------------------------
        @brief      Constructor
     ------------------------------------------------------------------------*/
    ScreenPrint& operator=( const ScreenPrint& ) = delete;

  public:
    /**------------------------------------------------------------------------
        @brief      Constructor
     ------------------------------------------------------------------------*/
    ScreenPrint();
    /**------------------------------------------------------------------------
        @brief      Destructor
     ------------------------------------------------------------------------*/
    ~ScreenPrint();
    /**---------------------------------------------------------------------------
        @ingroup    NimbleIDEScreen Nimble IDE Screen Module
        @brief      Adds a ScreenWord to the string stream
      --------------------------------------------------------------------------*/
    void Add( const ScreenWord& word )
    {
        WORD_EFFECT effect = word.GetEffect();

        // send the position to the string stream
        if ( word.GetXPos() != 0 )
            m_ss << "\033[" << word.GetYPos() << ";" << word.GetXPos() << "H";

        // send the formatted colour and effecr to the string stream
        m_ss << COLOUR_BG_START << word.GetBGColour() << COLOUR_END << COLOUR_START << word.GetFGColour() << COLOUR_END;
        if ( effect.Reverse == eState::On )
            m_ss << CHAR_INVERSE;
        if ( effect.Italic == eState::On )
            m_ss << CHAR_ITALIC;
        if ( effect.Bold == eState::On )
            m_ss << CHAR_BOLD;
        if ( effect.Underline == eState::On )
            m_ss << CHAR_UNDERLINE;
        if ( effect.Strike == eState::On )
            m_ss << CHAR_STRIKETHROUGH;
        if ( effect.Blink == eState::On )
            m_ss << CHAR_FLASH;

        // send the word to the string stream
        m_ss << word.GetWord() << CHAR_RESET;
    }
};

//-----------------------------------------------------------------------------

} // namespace Screen
} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: ScreenPrint.h
//-----------------------------------------------------------------------------
