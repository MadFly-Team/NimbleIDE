/**----------------------------------------------------------------------------

    @file       StatusCtrl.cpp
    @defgroup   NimbleLIBStatus Nimble Library Status Module
    @brief      Status Control Module Header File

    @copyright  Neil Bereford 2023

Notes:

    StatusCtrl is a class that provides a simple status control for the
    Nimble Library. It is used to track the status of the Modules.
    The followinbg states are tracked:

        Initialized - true if the module is initialized
        Ready       - true if the module is ready
        Busy        - true if the module is busy
        Error       - true if the module is in error

    On startup, the module is in the not initialized state. The module
    must be initialized before it can be used. Once initialized, the module
    is ready to be used. The module can be set to busy if it is in the
    ready state. The module can be set to error from any state. The module
    can be set to ready from any state.

    User flags are also provided to allow the user to set flags as required.
    A total of 8 user flags are provided.
    The following functions support this;

        void  setUserFlag( uint32_t userFlag );
        void  clearUserFlag( uint32_t userFlag );
        bool  isUserFlagSet( uint32_t userFlag ) const noexcept;

-----------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include "../../../inc/Modules/Utilities/StatusCtrl.h"

//-----------------------------------------------------------------------------
// Namespace
//-----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class Methods
//-----------------------------------------------------------------------------

// Constructors and Destructors -----------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBStatus Nimble Library Status Module
    @brief      Status Control Constructor
 -----------------------------------------------------------------------------*/
StatusCtrl::StatusCtrl()
{
    // Startup state - not initialized
    status.statusData     = 0;
    status.notInitialized = ON;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBStatus Nimble Library Status Module
    @brief      Status Control Destructor
 -----------------------------------------------------------------------------*/
StatusCtrl::~StatusCtrl()
{
}

// Getters --------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBStatus Nimble Library Status Module
    @brief      Check to see if the module is not initialized
    @return     bool true if not initialized, false otherwise
 -----------------------------------------------------------------------------*/
bool StatusCtrl::isNotInitialized() const noexcept
{
    return status.notInitialized == ON;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBStatus Nimble Library Status Module
    @brief      Check if the module is initialized
    @return     true if initialized, false otherwise
 -----------------------------------------------------------------------------*/
bool StatusCtrl::isInitialized() const noexcept
{
    return status.initialized == ON;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBStatus Nimble Library Status Module
    @brief      Check if the module is reafy
    @return     true if initialized, false otherwise
 -----------------------------------------------------------------------------*/
bool StatusCtrl::isReady() const noexcept
{
    return status.ready == ON;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBStatus Nimble Library Status Module
    @brief      Check if the module is busy
    @return     true if initialized, false otherwise
 -----------------------------------------------------------------------------*/
bool StatusCtrl::isBusy() const noexcept
{
    return status.busy == ON;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBStatus Nimble Library Status Module
    @brief      Check if the module is errored
    @return     true if initialized, false otherwise
 -----------------------------------------------------------------------------*/
bool StatusCtrl::isError() const noexcept
{
    return status.error == ON;
}

// Setters --------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBStatus Nimble Library Status Module
    @brief      Sets the erorr flag
 -----------------------------------------------------------------------------*/
void StatusCtrl::setError()
{
    status.error = ON;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBStatus Nimble Library Status Module
    @brief      Clear the error flag
 -----------------------------------------------------------------------------*/
void StatusCtrl::clearError()
{
    status.error = OFF;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBStatus Nimble Library Status Module
    @brief      Sets the busy flag
 -----------------------------------------------------------------------------*/
void StatusCtrl::setBusy()
{
    status.busy = ON;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBStatus Nimble Library Status Module
    @brief      Clear the busy flag
    @return     true if initialized, false otherwise
 -----------------------------------------------------------------------------*/
void StatusCtrl::clearBusy()
{
    status.busy = OFF;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBStatus Nimble Library Status Module
    @brief      Sets the ready flag
 -----------------------------------------------------------------------------*/
void StatusCtrl::setReady()
{
    status.ready = ON;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBStatus Nimble Library Status Module
    @brief      Clear the ready flag
 -----------------------------------------------------------------------------*/
void StatusCtrl::clearReady()
{
    status.ready = OFF;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBStatus Nimble Library Status Module
    @brief      Sets the initialized flag
 -----------------------------------------------------------------------------*/
void StatusCtrl::setInitialized()
{
    status.notInitialized = OFF;
    status.initialized    = ON;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBStatus Nimble Library Status Module
    @brief      Clear the inialized flag
 -----------------------------------------------------------------------------*/
void StatusCtrl::clearInitialized()
{
    status.initialized = OFF;
}
// user status ----------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBStatus Nimble Library Status Module
    @brief      Sets the user status flag, up to 8 flags can be set
    @param      userFlag - user status to clear
 -----------------------------------------------------------------------------*/
void StatusCtrl::setUserFlag( uint32_t userFlag )
{
    if ( userFlag >= TOTAL_USER_FLAGS )
    {
        userFlag = TOTAL_USER_FLAGS - 1;
    }

    uint16_t mskFlag = 1 << ( userFlag + START_USER_FLAGS );
    status.statusData |= mskFlag;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBStatus Nimble Library Status Module
    @brief      Clears the user status flag, up to 8 flags can be cleared
    @param      userFlag - user status to clear
 -----------------------------------------------------------------------------*/
void StatusCtrl::clearUserFlag( uint32_t userFlag )
{
    if ( userFlag >= TOTAL_USER_FLAGS )
    {
        userFlag = TOTAL_USER_FLAGS - 1;
    }
    uint16_t mskFlag = 1 << ( userFlag + START_USER_FLAGS );
    status.statusData &= ~mskFlag;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBStatus Nimble Library Status Module
    @brief      Check if the user status flag is set
    @param      userFlag - user status to check
    @return     true if set, false otherwise
 -----------------------------------------------------------------------------*/
bool StatusCtrl::isUserFlagSet( uint32_t userFlag ) const noexcept
{
    if ( userFlag >= TOTAL_USER_FLAGS )
    {
        userFlag = TOTAL_USER_FLAGS - 1;
    }
    uint16_t mskFlag = 1 << ( userFlag + START_USER_FLAGS );
    return ( status.statusData & mskFlag ) != 0;
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: StatusCtrl.h
//-----------------------------------------------------------------------------
