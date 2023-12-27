/**----------------------------------------------------------------------------

    @file       StatusCtrl.h
    @defgroup   NimbleLIBStatus Nimble Library Status Module
    @brief      Status Control Module Header File

    @copyright  Neil Bereford 2023

Notes:

Version:

        0.0.1.0     First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------

#include <cinttypes>

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// class StatusCtrl
// ----------------------------------------------------------------------------

class StatusCtrl
{
  public:
    // Constructors and Destructors -------------------------------------------
    StatusCtrl();
    ~StatusCtrl();
    // Methods -----------------------------------------------------------------
    bool isNotInitialized() const noexcept;
    bool isInitialized() const noexcept;
    bool isReady() const noexcept;
    bool isBusy() const noexcept;
    bool isError() const noexcept;
    void setError();
    void clearError();
    void setBusy();
    void clearBusy();
    void setReady();
    void clearReady();
    void setInitialized();
    void clearInitialized();
    // user flags --------------------------------------------------------------
    void setUserFlag( uint32_t userFlag );
    void clearUserFlag( uint32_t userFlag );
    bool isUserFlagSet( uint32_t userFlag ) const noexcept;

    // constants ---------------------------------------------------------------
    const uint32_t TOTAL_USER_FLAGS = 8;
    const uint32_t START_USER_FLAGS = 8;

  private:
    // Typedefs and Enumerations -----------------------------------------------
    /**----------------------------------------------------------------------------
        @ingroup    NimbleLIBStatus Nimble Library Status Module
        @brief      Status Control Union
    -----------------------------------------------------------------------------*/
    typedef union
    {
        uint16_t statusData; //!< status data
        struct
        {
            uint8_t notInitialized : 1; //!< not initialized  SYSYTEM only
            uint8_t initialized    : 1; //!< initialized
            uint8_t ready          : 1; //!< ready
            uint8_t error          : 1; //!< error
            uint8_t busy           : 1; //!< busy
            uint8_t reserved       : 3; //!< reserved
            uint8_t user1          : 1; //!< user1             USER definable
            uint8_t user2          : 1; //!< user2
            uint8_t user3          : 1; //!< user3
            uint8_t user4          : 1; //!< user4
            uint8_t user5          : 1; //!< user5
            uint8_t user6          : 1; //!< user6
            uint8_t user7          : 1; //!< user7
            uint8_t user8          : 1; //!< user8
        };

    } InternalStatus;

    // constants ---------------------------------------------------------------
    const uint8_t OFF = 0x00; //!< Off state
    const uint8_t ON  = 0x01; //!< On state

    // Variables ---------------------------------------------------------------
    InternalStatus status;

}; // end class StatusCtrl

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: StatusCtrl.h
//-----------------------------------------------------------------------------
