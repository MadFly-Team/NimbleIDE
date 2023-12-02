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

  private:
    // Typedefs and Enumerations -----------------------------------------------
    /**----------------------------------------------------------------------------
        @ingroup    NimbleLIBStatus Nimble Library Status Module
        @brief      Status Control Union
    -----------------------------------------------------------------------------*/
    typedef union
    {
        uint8_t statusByte; //!< status byte
        struct
        {
            uint8_t notInitialized : 1; //!< not initialized
            uint8_t initialized    : 1; //!< initialized
            uint8_t ready          : 1; //!< ready
            uint8_t error          : 1; //!< error
            uint8_t busy           : 1; //!< busy
            uint8_t reserved       : 3; //!< reserved
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
