/**----------------------------------------------------------------------------

    @file       CursesMenu.h
    @defgroup   NimbleLIBCurses Nimble Library Curses Module
    @brief      Curse Menu class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

        please see CursesMenu.cpp for full details.

Version:

        0.0.1.0     First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include <cinttypes>
#include <cstdint>
#include <functional>

extern "C"
{
#include "../../../../ExternalLibraries/PDCurses/curses.h"
}

#include "CursesKeyboard.h"
#include "../ErrorHandling/ErrorHandler.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Menu structure for the CursesMenu class.
-----------------------------------------------------------------------------*/
class CursesMenu : public CursesKeyboard
{
  public:
    const uint32_t MENU_INVALID_OPTION = -1; //!< Invalid menu option

    /**----------------------------------------------------------------------------
        @ingroup    NimbleLIBCurses Nimble Library Curses Module
        @brief      Exra keys for the CursesMenu class.
    -----------------------------------------------------------------------------*/
    enum class ExtraKeys
    {
        KEY_ESC    = 27, //!< Escape key
        KEY_RETURN = 10, //!< Enter key
    };

    // Constructors and destructors ---------------------------------------------
    CursesMenu();
    ~CursesMenu();

    // Member functions ---------------------------------------------------------
    // Getters ------------------------------------------------------------------
    uint32_t getMenuOption() const noexcept;
    // Setters ------------------------------------------------------------------
    void setMenuTitle( std::string& title );
    void setMenuSubTitle( std::string& subtitle );
    void setMenuFooter( std::string& footer );
    void setMenuOptions( std::vector<std::string>& options );

    // Control ------------------------------------------------------------------
    int32_t processMenu();
    void    processKey( int32_t key );

    // display functions --------------------------------------------------------
    void displayMenu();
    void displayMenuOptions();

  private:
    // Preset for the menu ------------------------------------------------------
    std::vector<KeyMap> menuKeys = {
        {"Menu navigation", { KEY_UP, KEY_DOWN, (uint32_t)ExtraKeys::KEY_RETURN }, std::bind( &CursesMenu::fnMenuNavigation, this, std::placeholders::_1 )},
        { "Menu control",   { 'Q', 'q', (uint32_t)ExtraKeys::KEY_ESC },            std::bind( &CursesMenu::fnMenuControl,    this, std::placeholders::_1 )}
    };
    // Menu variables -----------------------------------------------------------
    std::vector<std::string> menuItems;                  //!< Menu items
    std::string              menuTitle          = "";    //!< Menu title
    std::string              menuSubTitle       = "";    //!< Menu subtitle
    std::string              menuFooter         = "";    //!< Menu footer
    uint32_t                 menuOption         = 0;     //!< Menu option
    uint32_t                 menuMaxOptions     = 0;     //!< Maximum number of menu options
    bool                     menuTerminated     = false; //!< Menu terminated flag
    bool                     menuOptionSelected = false; //!< Menu option selected flag

    // Constants ----------------------------------------------------------------
    // Member variables ---------------------------------------------------------
    // Member functions ---------------------------------------------------------
    void fnMenuNavigation( int32_t key );
    void fnMenuControl( int32_t key );
};

//-----------------------------------------------------------------------------
} // namespace Nimble

// End of file: CursesMenu.h
// ----------------------------------------------------------------------------
