/**----------------------------------------------------------------------------

    @file       ScreenInfo.h
    @defgroup   NimbleIDEScreen Nimble IDE Screen Module
    @brief      Screen information class for the Nimble IDE

    @copyright  Neil Beresford 2023

Notes:

Version:

        0.0.1.0   First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <stdint.h>

//-----------------------------------------------------------------------------
// Class Definition
//-----------------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleIDEScreen Nimble IDE Screen Module
    @brief      Screen information class for the Nimble IDE
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
        @ingroup    NimbleIDEScreen Nimble IDE Screen Module
        @brief      Default constructor
    --------------------------------------------------------------------------*/
    ScreenInfo()
    {
    }
    /**---------------------------------------------------------------------------
        @ingroup    NimbleIDEScreen Nimble IDE Screen Module
        @brief      Default destructor
    --------------------------------------------------------------------------*/
    ~ScreenInfo()
    {
    }

    // Getters & Setters -------------------------------------------------------

    /**--------------------------------------------------------------------------
        @ingroup    NimbleIDEScreen Nimble IDE Screen Module
        @brief      Returns the character width of the console
        @return     uint32_t - The width of the console
    --------------------------------------------------------------------------*/
    uint32_t GetWidth()
    {
        return width;
    };
    /**--------------------------------------------------------------------------
        @ingroup    NimbleIDEScreen Nimble IDE Screen Module
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
// End of file: ScreenInfo.h
//-----------------------------------------------------------------------------
