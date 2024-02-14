/**----------------------------------------------------------------------------

    @file       IDEManager.cpp
    @defgroup   NimbleLIBIDE Nimble Library IDE Module
    @brief      IDEManager class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

-----------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include "../../../inc/Modules/Curses/CursesColour.h"
#include "../../../inc/Modules/IDE/IDEManager.h"
#include "../../../inc/Modules/IDE/IDEDialog.h"
#include "../../../inc/Modules/IDE/IDEFileDialog.h"
#include "../../../inc/Modules/Global/Globals.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

// constructor and destructor --------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief     IDEManager constructor
    @return    none
-----------------------------------------------------------------------------*/
IDEManager::IDEManager()
{
    // initial member variables
    activeControls.clear();
    activeControlIDs.clear();
    m_bRedrawNeeded = false;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief     IDEManager destructor
    @return    none
-----------------------------------------------------------------------------*/
IDEManager::~IDEManager()
{
    // free any active Control
    for ( auto& control : activeControls )
    {
        control.reset();
    }
}

//-----------------------------------------------------------------------------

// Control ---------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Add control to the IDEManager
    @param      dialogID - ManagerControlID
    @return     none
-----------------------------------------------------------------------------*/
void IDEManager::addControl( ManagerControlID dialogID )
{
    m_controls[ static_cast<int>( dialogID ) ].eState = ManagerControlState::NotActive;
    activeControlIDs.push_back( dialogID );
    switch ( dialogID )
    {
        case ManagerControlID::ID_LoadFile:
        {
            activeControls.push_back( std::make_unique<IDEFileDialog>() );
            while ( getch() != ERR )
                ;
            break;
        }
        case ManagerControlID::ID_SaveFile:
        {
            activeControls.push_back( std::make_unique<IDEFileDialog>() );
            while ( getch() != ERR )
                ;
            break;
        }
        default:
        {
            break;
        }
    }
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Process the IDEManager
    @return     none
-----------------------------------------------------------------------------*/
void IDEManager::process( uint32_t key )
{
    if ( activeControls.size() > 0 )
    {
        uint32_t index = activeControls.size() - 1;
        activeControls[ index ].get()->setKeytoProcess( key );
        m_controls[ static_cast<int>( activeControlIDs[ index ] ) ].controlCB();
 
        Screen::Globals::getInstance().setManagerComponents( activeControls.size() );
    }
}

// getters and setters --------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Checks to see number of active controls
    @return     bool - true if there are active controls
-----------------------------------------------------------------------------*/
const bool IDEManager::areControlsActive() const
{
    return activeControls.size() > 0;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Checks to see if a redraw is needed
    @return     bool - true if a redraw is needed
-----------------------------------------------------------------------------*/
const bool IDEManager::redrawNeeded() const
{
    return m_bRedrawNeeded;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Clears the redraw flag
    @return     void
-----------------------------------------------------------------------------*/
void IDEManager::clearRedrawNeeded()
{
    m_bRedrawNeeded = false;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Get the number of active controls
    @return     uint32_t - number of active controls/
-----------------------------------------------------------------------------*/
uint32_t IDEManager::getActiveControlCount() const
{
    return activeControls.size();
}

// Controller callbacks -------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Load file callback
    @return     none
-----------------------------------------------------------------------------*/
void IDEManager::LoadFileCallback()
{
    IDEManagerControl* pControl = &m_controls[ static_cast<int>( ManagerControlID::ID_LoadFile ) ];
    uint32_t           index    = activeControls.size() - 1;
    IDEFileDialog*     pDialog  = (IDEFileDialog*)activeControls[ index ].get();

    switch ( pControl->eState )
    {
        case ManagerControlState::NotActive:
        {
            pControl->eState = ManagerControlState::Start;
            break;
        }
        case ManagerControlState::Start:
        {
            pDialog->initLoader( "./", "TEST.TXT", "File Loader" );
            uint32_t colour = COLOUR_INDEX( activeControls[ index ]->getInkColour(), activeControls[ index ]->getPaperColour() );
            pDialog->colourWindow( colour, true );
            pDialog->setVerticalScroll();
            pDialog->drawLoader();
            pControl->eState = ManagerControlState::Running;
            break;
        }
        case ManagerControlState::Running:
        {
            uint32_t key = pDialog->getKeytoProcess();
            pDialog->processKeyPress( key );
            uint32_t colour = COLOUR_INDEX( activeControls[ index ]->getInkColour(), activeControls[ index ]->getPaperColour() );
            pDialog->colourWindow( colour, true );
            pDialog->setVerticalScroll();
            pDialog->drawLoader();
            if ( pDialog->isCancelled() )
            {
                pControl->eState = ManagerControlState::Cancel;
            }
            if ( pDialog->isCompleted() )
            {
                pControl->eState = ManagerControlState::Confirm;
            }
            break;
        }
        case ManagerControlState::Cancel:
        case ManagerControlState::Confirm:
        {
            delwin( pDialog->getWindow() );
            activeControls[ index ].reset();
            activeControls.pop_back();
            activeControlIDs.pop_back();
            m_bRedrawNeeded = true;
            break;
        }
        default:
        {
            break;
        }
    }
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBIDE Nimble Library IDE Module
    @brief      Save file callback
    @return     none
-----------------------------------------------------------------------------*/
void IDEManager::SaveFileCallback()
{
    IDEManagerControl* pControl = &m_controls[ static_cast<int>( ManagerControlID::ID_SaveFile ) ];

    // load file callback
    switch ( pControl[ static_cast<int>( ManagerControlID::ID_SaveFile ) ].eState )
    {
        case ManagerControlState::NotActive:
        {
            pControl->eState = ManagerControlState::Start;
            break;
        }
        case ManagerControlState::Start:
        {
            break;
        }
        case ManagerControlState::Running:
        {
            break;
        }
        case ManagerControlState::Error:
        {
            break;
        }
        case ManagerControlState::Close:
        {
            break;
        }
        case ManagerControlState::Cancel:
        {
            break;
        }
        case ManagerControlState::Confirm:
        {
            break;
        }
        default:
        {
            break;
        }
    }
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: IDEManager.cpp
// ----------------------------------------------------------------------------
