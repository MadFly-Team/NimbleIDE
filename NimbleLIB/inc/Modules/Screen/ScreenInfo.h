/**----------------------------------------------------------------------------

    @file       ScreenInfo.h
    @defgroup   NimbleLIBScreen Nimble Library Screen Module
    @brief      Screen information class for the Nimble Library

    @copyright  Neil Beresford 2023

Notes:

Version:

        0.0.1.0   First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <stdint.h>

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
    @brief      Screen information class for the Nimble LIB
  --------------------------------------------------------------------------*/
class ScreenInfo
{
  private:
    // Data --------------------------------------------------------------------

    uint32_t width;  //!< Width of the console
    uint32_t height; //!< Height of the console

    //--------------------------------------------------------------------------

  public:
    // constructors etc --------------------------------------------------------

    /**-------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Default constructor
    --------------------------------------------------------------------------*/
    ScreenInfo()
    {
    }
    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Default destructor
    --------------------------------------------------------------------------*/
    ~ScreenInfo()
    {
    }

    // Getters & Setters -------------------------------------------------------

    /**--------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Returns the character width of the console
        @return     uint32_t - The width of the console
    --------------------------------------------------------------------------*/
    uint32_t GetWidth()
    {
        return width;
    };
    /**--------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Returns the character height of the console
        @return     uint32_t - The height of the console
    --------------------------------------------------------------------------*/
    uint32_t GetHeight()
    {
        return height;
    };

    // Console related ---------------------------------------------------------

    void RetrieveConsoleInfo(); //!< Retrieve the console information
    void SetupConsole();        //!< Setup the console

    //--------------------------------------------------------------------------
};

//-----------------------------------------------------------------------------

} // namespace Screen
} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: ScreenInfo.h
//-----------------------------------------------------------------------------
