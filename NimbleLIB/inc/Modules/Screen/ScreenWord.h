/**----------------------------------------------------------------------------

    @file       ScreenWord.h
    @defgroup   NimbleLIBScreen Nimble Library Screen Module
    @brief      Basde class for screen objects

    @copyright  Neil Beresford 2023

Notes:

Version:

        0.0.1.0   First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include <stdint.h>
#include <string>

//-----------------------------------------------------------------------------
// Namespace access
//-----------------------------------------------------------------------------

namespace Nimble
{
namespace Screen
{

//-----------------------------------------------------------------------------
// Class Definition
//-----------------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBScreen Nimble Library Screen Module
    @brief      enum Effect used to define the word effects
  --------------------------------------------------------------------------*/
enum Effect
{
    None      = 0,  //!< Effect None to apply to the word
    Italic    = 1,  //!< Effect Italic to apply to the word
    Bold      = 2,  //!< Effect Bold to apply to the word
    Underline = 4,  //!< Effect Underline to apply to the word
    Strike    = 8,  //!< Effect Strike to apply to the word
    Blink     = 16, //!< Effect Blink to apply to the word
    Reverse   = 32  //!< Effect Reverse to apply to the word
};

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBScreen Nimble Library Screen Module
    @brief      enum eState used to define the word effects
  --------------------------------------------------------------------------*/
enum eState
{
    Off = 0, //!< Effect Off to apply to the word
    On  = 1  //!< Effect On to apply to the word
};

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBScreen Nimble Library Screen Module
    @brief      union struct WORD_EFFECR used to define the word effects
  --------------------------------------------------------------------------*/
union WORD_EFFECT
{
    struct
    {
        uint8_t Italic    : 1; //!< Effect Italic to apply to the word
        uint8_t Bold      : 1; //!< Effect Bold to apply to the word
        uint8_t Underline : 1; //!< Effect Underline to apply to the word
        uint8_t Strike    : 1; //!< Effect Strike to apply to the word
        uint8_t Blink     : 1; //!< Effect Blink to apply to the word
        uint8_t Reverse   : 1; //!< Effect Reverse to apply to the word
    };
    uint8_t value; //!< Effect value to apply to the word
};

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBScreen Nimble Library Screen Module
    @brief      class ScreenWord for the Nimble LIB
  --------------------------------------------------------------------------*/
class ScreenWord
{
  private:
    // Data --------------------------------------------------------------------
    WORD_EFFECT effect;   //!< Effect to apply to the word
    uint32_t    xPos;     //!< X position of the word
    uint32_t    yPos;     //!< Y position of the word
    uint32_t    fgColour; //!< Foreground colour of the word
    uint32_t    bgColour; //!< Background colour of the word
    std::string word;     //!< Pointer to the word

    //--------------------------------------------------------------------------
  public:
    // constructors etc --------------------------------------------------------
    /**-------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Default constructor
    --------------------------------------------------------------------------*/
    ScreenWord()
    {
        effect.value = 0;
        xPos         = 0;
        yPos         = 0;
        fgColour     = 0;
        bgColour     = 0;
        word         = "";
    }
    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Default destructor
    --------------------------------------------------------------------------*/
    ~ScreenWord()
    {
    }
    //-----------------------------------------------------------------------------
    // Accessors
    //-----------------------------------------------------------------------------
    /**-------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Set the X position of the word
        @param      x X position of the word
    --------------------------------------------------------------------------*/
    void SetXPos( uint32_t x )
    {
        xPos = x;
    }
    /**-------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Set the Y position of the word
        @param      y Y position of the word
    --------------------------------------------------------------------------*/
    void SetYPos( uint32_t y )
    {
        yPos = y;
    }
    /**-------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Set the foreground colour of the word
        @param      fg Foreground colour of the word
    --------------------------------------------------------------------------*/
    void SetFGColour( uint32_t fg )
    {
        fgColour = fg;
    }
    /**-------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Set the background colour of the word
        @param      bg Background colour of the word
    --------------------------------------------------------------------------*/
    void SetBGColour( uint32_t bg )
    {
        bgColour = bg;
    }

    /**-------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Set the word
        @param      w Word
    --------------------------------------------------------------------------*/
    void SetWord( std::string w )
    {
        word = w;
    }
    /**-------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Set the word effect
        @param      e Word effect to apply to the word
    --------------------------------------------------------------------------*/
    void SetEffect( uint8_t e )
    {
        effect.value = e;
    }
    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Returns the word string
        @return     std::string Word string
      --------------------------------------------------------------------------*/
    std::string GetWord() const
    {
        return word;
    }
    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Returns the X position of the word
        @return     uint32_t X position of the word
      --------------------------------------------------------------------------*/
    uint32_t GetXPos() const
    {
        return xPos;
    }
    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Returns the Y position of the word
        @return     uint32_t Y position of the word
      --------------------------------------------------------------------------*/
    uint32_t GetYPos() const
    {
        return yPos;
    }
    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Returns the foreground colour of the word
        @return     uint32_t Foreground colour of the word
      --------------------------------------------------------------------------*/
    uint32_t GetFGColour() const
    {
        return fgColour;
    }
    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Returns the background colour of the word
        @return     uint32_t Background colour of the word
      --------------------------------------------------------------------------*/
    uint32_t GetBGColour() const
    {
        return bgColour;
    }
    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Returns the effect of the word
        @return     WORD_EFFECT Effect of the word
      --------------------------------------------------------------------------*/
    WORD_EFFECT GetEffect() const
    {
        return effect;
    }
};

//-----------------------------------------------------------------------------

} // namespace Screen
} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: ScreenWord.h
//-----------------------------------------------------------------------------
