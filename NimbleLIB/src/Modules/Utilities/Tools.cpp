/**----------------------------------------------------------------------------

    @file       Tools.cpp
    @defgroup   NimbleLIBTools Nimble Library Tools Module
    @brief      Handles error messages for the USB tool.

    @copyright  Neil Bereford 2023

Notes:


-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include "../../../inc/Modules/Utilities/Tools.h"

//-----------------------------------------------------------------------------
// Namespace
//-----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class support functions
// ----------------------------------------------------------------------------

// Constructor and destructor  -------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBTools Nimble Library Tools Module
    @brief      Constructor for the Tools class

  --------------------------------------------------------------------------*/
Tools::Tools()
{
}
//-----------------------------------------------------------------------------
/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBTools Nimble Library Tools Module
    @brief      Destructor for the Tools class

  --------------------------------------------------------------------------*/
Tools::~Tools()
{
}

//-----------------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBTools Nimble Library Tools Module
    @brief      Calculates the CRC for the data
    @param      pData - Pointer to the data
    @param      len - Length of the data to calculate the CRC for
    @return     uint16_t - CRC16 value
  --------------------------------------------------------------------------*/
uint16_t Tools::crc16( uint8_t* pData, uint32_t len ) const
{
    uint16_t crc = CRC_START;
    uint8_t  i;

    while ( len-- )
    {
        crc ^= *pData++;
        for ( i = 0; i < CRC_BITS; i++ )
        {
            if ( crc & CRC_MASK )
            {
                crc >>= CRC_SHIFT;
                crc ^= CRC_POLY;
            }
            else
            {
                crc >>= CRC_SHIFT;
            }
        }
    }
    return crc;
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: Tools.cpp
// ----------------------------------------------------------------------------
