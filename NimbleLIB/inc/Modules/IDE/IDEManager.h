/**----------------------------------------------------------------------------

    @file       IDEManager.h
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEManager class for the Nimble Library

    @copyright  Neil Bereford 2023

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include <cinttypes>
#include <cstdint>
#include <functional>
#include <vector>

#include "../ErrorHandling/ErrorHandler.h"
#include "IDEDialog.h"
#include "IDEWindow.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      ID for each control
-----------------------------------------------------------------------------*/
enum class ManagerControlID
{
    ID_LoadFile = 0, //!< Load file ID
    ID_SaveFile,     //!< Save file ID
    ID_Total         //!< Total number of controls
};

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      State for each control
-----------------------------------------------------------------------------*/
enum class ManagerControlState
{
    NotActive = 0, //!< Not active state
    Start,         //!< Start state
    Running,       //!< Running state
    Error,         //!< Error state
    Close,         //!< Close state
    Cancel,        //!< Cancel state
    Confirm,       //!< Confirm state
    TotalStates    //!< Total number of states
};

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEManagerControl struct
-----------------------------------------------------------------------------*/
struct IDEManagerControl
{
    ManagerControlID      eID;       //!< Control ID
    std::function<void()> controlCB; //!< Control callback
    std::string           label;     //!< Control label
    ManagerControlState   eState;    //!< Control state
};

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief     IDEManager class
-----------------------------------------------------------------------------*/
class IDEManager : public IDEWindow
{
  public:
    // enums ---------------------------------------------------------------------
    enum class IDEManagerControls
    {
        Dialog_LoaadFile = 0, //!< Load file dialog
        Dialog_SaveFile,      //!< Save file dialog
        TotalControls         //!< Total number of controls
    };
    // constructors & destructors --------------------------------------------
    IDEManager();
    ~IDEManager();
    // initialisation ----------------------------------------------------------
    // process and control -----------------------------------------------------
    void addControl( ManagerControlID diaalogID );
    void process( uint32_t key );
    // general access ----------------------------------------------------------
    const bool areControlsActive() const;
    const bool redrawNeeded() const;
    void       clearRedrawNeeded();
    uint32_t   getActiveControlCount() const;

  private:
    // variables ---------------------------------------------------------------
    // clang-format off
    IDEManagerControl m_controls[ static_cast<uint32_t>( ManagerControlID::ID_Total ) ] = //!< Controls
    {
        { ManagerControlID::ID_LoadFile, [ this ]() { this->LoadFileCallback(); }, "Load File", ManagerControlState::NotActive },
        { ManagerControlID::ID_SaveFile, [ this ]() { this->SaveFileCallback(); }, "Save File", ManagerControlState::NotActive }
    };
    // clang-format on
    std::vector<std::unique_ptr<IDEDialog>> activeControls;
    std::vector<ManagerControlID>           activeControlIDs;
    bool                                    m_bRedrawNeeded;
    // functions ---------------------------------------------------------------
    void LoadFileCallback(); //!< Load file callback
    void SaveFileCallback(); //!< Save file callback
};

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEManager.h
// ---------------------------------------------------------------------------/-
