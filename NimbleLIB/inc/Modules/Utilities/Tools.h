/**----------------------------------------------------------------------------

    @file       Tools.h
    @defgroup   NimbleLIBTools Nimble Library Tools Module
    @brief      Handles error messages for the USB tool.

    @copyright  Neil Bereford 2023

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include <string>
#include <chrono>
#include <ctime>
#include <vector>

#include "../Logging/Logger.h"
#include "../ErrorHandling/Errors.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBTools Nimble Library Tools Module
    @brief      Tools class (Support functionality) for the Nimble Library
  --------------------------------------------------------------------------*/
class Tools
{
  public:
    // Function to access the singleton -----------------------------------------
    static Tools& getInstance()
    {
        static Tools instance; // Created only once
        return instance;
    }

    uint16_t crc16( uint8_t* pData, uint32_t len ) const;

  private:
    // Singleton constructor and destructor ------------------------------------
    Tools();
    ~Tools();

    Tools( const Tools& )            = delete;
    Tools& operator=( const Tools& ) = delete;

    // Constants ---------------------------------------------------------------
    // crc16 constants ----------------------------------------------------------
    const uint16_t CRC_START = 0xFFFF; //<! Const values for the crc16 - CRC start value
    const uint16_t CRC_POLY  = 0xA001; //<! Const values for the crc16 - CRC polynomial
    const uint16_t CRC_MASK  = 0x0001; //<! Const values for the crc16 - CRC mask
    const uint16_t CRC_SHIFT = 1;      //<! Const values for the crc16 - CRC shift
    const uint16_t CRC_BITS  = 8;      //<! Const values for the crc16 - CRC bits

}; // end class Singleton Tools

//-----------------------------------------------------------------------------

} // end namespace Nimble

//-----------------------------------------------------------------------------
// End of file: Tools.h
// ----------------------------------------------------------------------------
