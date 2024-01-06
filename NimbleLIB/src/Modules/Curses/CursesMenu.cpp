/**----------------------------------------------------------------------------

    @file       CursesMenu.cpp
    @defgroup   NimbleLIBCurses Nimble Library Curses Module
    @brief      Curse Menu class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:


-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include "../../../inc/Modules/Curses/CursesMenu.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class Support Functions
// ----------------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Constructor for the CursesMenu class.
-----------------------------------------------------------------------------*/
CursesMenu::CursesMenu()
{
    // add the keyboard handlers to the keyboard
    addKeyMapArray( menuKeys );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Destructor for the CursesMenu class.
-----------------------------------------------------------------------------*/
CursesMenu::~CursesMenu()
{
}

// Setters --------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Set the menu title.
    @param      title       Menu title
-----------------------------------------------------------------------------*/
void CursesMenu::setMenuTitle( std::string& title )
{
    menuTitle = title;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Set the menu subtitle.
    @param      subtitle    Menu subtitle
------------------------------------------------------------------------------*/
void CursesMenu::setMenuSubTitle( std::string& subtitle )
{
    menuSubTitle = subtitle;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Set the menu footer.
    @param      footer      Menu footer
-----------------------------------------------------------------------------*/
void CursesMenu::setMenuFooter( std::string& footer )
{
    menuFooter = footer;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Set the menu options.
    @param      options     Menu options
-----------------------------------------------------------------------------*/
void CursesMenu::setMenuOptions( std::vector<std::string>& options )
{
    menuItems      = options;
    menuMaxOptions = menuItems.size();
}

// Getters --------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Get the menu option.
    @return     Menu option, or -1 if menu terminated
-----------------------------------------------------------------------------*/
uint32_t CursesMenu::getMenuOption() const noexcept
{
    return ( menuTerminated ? MENU_INVALID_OPTION : menuOption );
}

// Display --------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Display the menu.
-----------------------------------------------------------------------------*/
void CursesMenu::displayMenu()
{
    uint32_t menuHeight = 0;
    uint32_t menuWidth  = 0;
    uint32_t option     = 0;

    // calculate the menu width
    getmaxyx( stdscr, menuHeight, menuWidth );

    uint32_t yPos = ( menuHeight / 2 ) - ( menuMaxOptions / 2 );

    mvaddstr( yPos - 3, ( menuWidth / 2 ) - ( menuTitle.length() / 2 ), menuTitle.c_str() );
    mvaddstr( yPos - 2, ( menuWidth / 2 ) - ( menuSubTitle.length() / 2 ), menuSubTitle.c_str() );
    for ( auto& item : menuItems )
    {
        attroff( A_REVERSE );
        if ( option == menuOption )
        {
            attron( A_REVERSE );
        }
        mvaddstr( yPos, ( menuWidth / 2 ) - ( item.length() / 2 ), item.c_str() );
        yPos++;
        option++;
    }
    attroff( A_REVERSE );
    mvaddstr( yPos + 1, ( menuWidth / 2 ) - ( menuFooter.length() / 2 ), menuFooter.c_str() );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Display the menu options.
 -----------------------------------------------------------------------------*/
void CursesMenu::displayMenuOptions()
{
    uint32_t menuHeight = 0;
    uint32_t menuWidth  = 0;
    uint32_t option     = 0;

    // calculate the menu width
    getmaxyx( stdscr, menuHeight, menuWidth );

    uint32_t yPos = ( menuHeight / 2 ) - ( menuMaxOptions / 2 );

    for ( auto& item : menuItems )
    {
        attroff( A_REVERSE );
        if ( option == menuOption )
        {
            attron( A_REVERSE );
        }
        mvaddstr( yPos, ( menuWidth / 2 ) - ( item.length() / 2 ), item.c_str() );
        yPos++;
        option++;
    }
    attroff( A_REVERSE );
}

// Control --------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Process the menu key control.
    @return     Menu option, or -1 if menu terminated
-----------------------------------------------------------------------------*/
int32_t CursesMenu::processMenu()
{
    // get the key
    int32_t key        = getch();

    menuTerminated     = false;
    menuOption         = 0;
    menuOptionSelected = false;

    while ( ( menuTerminated == false ) && ( menuOptionSelected == false ) )
    {
        // display the menu
        displayMenu();

        // process the key
        processKey( key );

        // get the key
        key = getch();
    }

    return ( getMenuOption() );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Process the key.
    @param      key         Key code
-----------------------------------------------------------------------------*/
void CursesMenu::processKey( int32_t key )
{
    // process the key
    for ( auto& keyMap : menuKeys )
    {
        for ( auto& inKey : keyMap.keys )
        {
            if ( inKey == key )
            {
                keyMap.function( key );
            }
        }
    }
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Controller for the navigation of the menu.
    @param      key         Key code
-----------------------------------------------------------------------------*/
void CursesMenu::fnMenuNavigation( int32_t key )
{
    switch ( key )
    {
        case KEY_UP:
        {
            if ( menuOption > 0 )
            {
                menuOption--;
            }
            break;
        }
        case KEY_DOWN:
        {
            if ( menuOption < ( menuMaxOptions - 1 ) )
            {
                menuOption++;
            }
            break;
        }
        case (uint32_t)ExtraKeys::KEY_RETURN:
        {
            menuOptionSelected = true;
            break;
        }
        default:
        {
            break;
        }
    }
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Controller for the menu control.
    @param      key         Key code
-----------------------------------------------------------------------------*/
void CursesMenu::fnMenuControl( int32_t key )
{
    switch ( key )
    {
        case 'Q':
        case 'q':
        case (uint32_t)ExtraKeys::KEY_ESC:
        {
            menuTerminated = true;
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
// End of file: CursesMenu.cpp
// ----------------------------------------------------------------------------
