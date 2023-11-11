
/**----------------------------------------------------------------------------

    @file       Globals.h
    @defgroup   NimbleLIBScreen Nimble Library Screen Module
    @brief      Globals class for the Nimble LIB

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
// GLass definitions
//-----------------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBScreen Nimble Library Screen Module
    @brief      Global Singleton class for the Nimble Library
                This class is a singleton and is used to store global variables
                and functions for the Nimble Library

  --------------------------------------------------------------------------*/
class Global
{
  public:
    // Function to get the instance of the Global
    static Global& getInstance()
    {
        static Global instance; // Guaranteed to be destroyed, instantiated on first use
        return instance;
    }

    //-----------------------------------------------------------------------------
    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Get the screen width
        @return     uint32_t - screen width
      --------------------------------------------------------------------------*/
    uint32_t getScreenWidth() const
    {
        return m_screenWidth;
    }
    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Get the screen height
        @return     uint32_t - screen height
      --------------------------------------------------------------------------*/
    uint32_t getScreenHeight() const
    {
        return m_screenHeight;
    }

    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Set the screen width
        @param      uint32_t - screen width
      --------------------------------------------------------------------------*/
    void setScreenWidth( uint32_t width )
    {
        m_screenWidth = width;
    }
    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Set the screen height
        @param      uint32_t - screen height
      --------------------------------------------------------------------------*/
    void setScreenHeight( uint32_t height )
    {
        m_screenHeight = height;
    }
    //-----------------------------------------------------------------------------

  private:
    // Private constructor to prevent instantiation
    Global()
    {
    }

    // Private copy constructor and copy assignment operator to prevent duplication
    Global( const Global& )            = delete;
    Global& operator=( const Global& ) = delete;

    //-----------------------------------------------------------------------------
    // GLobal variables
    uint32_t m_screenWidth  = 0; //!< Screen width
    uint32_t m_screenHeight = 0; //!< Screen height

    //-----------------------------------------------------------------------------
};

//-----------------------------------------------------------------------------

} // namespace Screen
} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: Globals.h
//-----------------------------------------------------------------------------
