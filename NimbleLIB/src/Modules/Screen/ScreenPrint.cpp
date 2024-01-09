/**----------------------------------------------------------------------------

    @file       ScreenPrint.h
    @defgroup   NimbleIDEScreen Nimble IDE Screen Module
    @brief      ScreenPrint class for the Nimble IDE

    @copyright  Neil Bereford 2023

Notes:

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
//  includes
//-----------------------------------------------------------------------------

#include "../../../inc/Modules/Screen/ScreenPrint.h"

//-----------------------------------------------------------------------------
// Namespace access
//-----------------------------------------------------------------------------

namespace Nimble
{
namespace Screen
{

//-----------------------------------------------------------------------------
// Class definitions
//-----------------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleIDEScreen Nimble IDE Screen Module
    @brief      ScreenPrint constructor

  --------------------------------------------------------------------------*/
ScreenPrint::ScreenPrint()
{
    m_ss.str( "" );
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleIDEScreen Nimble IDE Screen Module
    @brief      ScreenPrint destructor

  --------------------------------------------------------------------------*/
ScreenPrint::~ScreenPrint()
{
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleIDEScreen Nimble IDE Screen Module
    @brief      Adds a ScreenWord to the string stream
    @param      word    ScreenWord to add
    return      void
    --------------------------------------------------------------------------*/
void ScreenPrint::Add( const ScreenWord& word )
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

/**---------------------------------------------------------------------------
    @ingroup    NimbleIDEScreen Nimble IDE Screen Module
    @brief      Adds the text to the string stream, no formatting.
    @param      inText - string to add to the string stream
    return      void
  --------------------------------------------------------------------------*/
void ScreenPrint::Add( const std::string& inText )
{
    // just pipe the text to the string stream
    m_ss << inText;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleIDEScreen Nimble IDE Screen Module
    @brief      Adds the text to the string stream, no formatting.
    @param      x - x position to add the text
    @param      y - y position to add the text
    @param      inText - string to add to the string stream
    return      void
  --------------------------------------------------------------------------*/
void ScreenPrint::Add( uint32_t x, uint32_t y, const std::string& inText )
{
    // send the position to the string stream
    m_ss << "\033[" << y << ";" << x << "H";

    // just pipe the text to the string stream
    m_ss << inText;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleIDEScreen Nimble IDE Screen Module
    @brief      Displays the string stream to the screen
    @param      inText - string to add to the string stream
    return      void
  --------------------------------------------------------------------------*/
void ScreenPrint::Display()
{
    // send the string stream to the screen
    std::cout << m_ss.str();
    // clear the string stream
    m_ss.str( "" );
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleIDEScreen Nimble IDE Screen Module
    @brief      Displays the ScreenWord straight to the screen
    @param      word - ScreenWord to display
    return      void
  --------------------------------------------------------------------------*/
void ScreenPrint::DisplayWord( const ScreenWord& word )
{
    // clear the string stream
    m_ss.str( "" );

    // send the word to be formatted and displayed
    Add( word );
    Display();
}

// Unit test functionality ----------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleIDEScreen Nimble IDE Screen Module
    @brief      Returns the string stream
    @return     string stream
  --------------------------------------------------------------------------*/
std::string ScreenPrint::GetStreamString() const
{
    return m_ss.str();
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleIDEScreen Nimble IDE Screen Module
    @brief      Clears the string stream
    return      void
  --------------------------------------------------------------------------*/
void ScreenPrint::ClearStream()
{
    m_ss.str( "" );
}

//-----------------------------------------------------------------------------

} // namespace Screen
} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: ScreenPrint.h
//-----------------------------------------------------------------------------
