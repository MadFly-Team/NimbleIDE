/**----------------------------------------------------------------------------

    @file       CursesKeyboard.cpp
    @defgroup   NimbleLIBCurses Nimble Library Curses Module
    @brief      Curses keyboard class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

    This class is used to process keyboard input for the Nimble Library.
    It is designed to be used with the Curses module, but can be used
    independently if required.
    The keyboard is processed using a key map. A key map is a list of
    keys that are tested against the keyboard input. If a key is pressed
    that matches one of the keys in the key map, then the function
    pointer callback is called.
    The key map is a list of keys that are tested against the keyboard
    input. If a key is pressed that matches one of the keys in the key
    map, then the function pointer callback is called.

    The kry codes are defined in the curses.h header file. The following
    are the most common keys:
        LEFT        260
        RIGHT       261
        UP          259
        DOWN        258
        ENTER       10
        ESCAPE      27
        SPACE       32
        TAB         9
        BACKSPACE   8
        DELETE      330
        F1          265
        F12         276
        Q           113
        q           81

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include "../../../inc/Modules/Curses/CursesKeyboard.h"
#include <cstdint>
#include <string>

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

// Constructors and destructors ---------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Curses keyboard constructor
--------------------------------------------------------------------------*/
CursesKeyboard::CursesKeyboard()
{
    keyMaps.clear();
    lastKey = 0;
    key     = 0;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Curses keyboard copy constructor
    @param      other   Curses keyboard to copy
  --------------------------------------------------------------------------*/
CursesKeyboard::CursesKeyboard( const CursesKeyboard& other )
{
    keyMaps = other.keyMaps;
    lastKey = 0;
    key     = 0;
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Curses keyboard assignment operator
    @param      name        Name of the key mapping
    @param      keys        List of keys
    @param      function    Function pointer callback
    --------------------------------------------------------------------------*/
CursesKeyboard::CursesKeyboard( const std::string name, const std::vector<uint32_t> keys, pKeyFunction function )
{
    addKeyMap( name, keys, function );
}
/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Curses keyboard destructor
--------------------------------------------------------------------------*/
CursesKeyboard::~CursesKeyboard()
{
    keyMaps.clear();
}

// Getters ------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Get the last key pressed
    @return     uint32_t   Last key pressed
--------------------------------------------------------------------------*/
uint32_t CursesKeyboard::getLastKey() const noexcept
{
    return ( lastKey );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Get the key pressed
    @return     uint32_t   key pressed
--------------------------------------------------------------------------*/
uint32_t CursesKeyboard::getKey() const noexcept
{
    return ( key );
}

// Others ------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Add a key map
    @param      name        Name of the key mapping
    @param      keys        List of keys
    @param      function    Function pointer callback
    --------------------------------------------------------------------------*/
void CursesKeyboard::addKeyMap( const std::string& name, const std::vector<uint32_t>& keys, pKeyFunction function )
{
    KeyMap keyMap;

    keyMap.name     = name;
    keyMap.keys     = keys;
    keyMap.function = function;

    keyMaps.push_back( keyMap );
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Add a key map array
    @param      keyMapArray     Key map array
    --------------------------------------------------------------------------*/
void CursesKeyboard::addKeyMapArray( const std::vector<KeyMap>& keyMapArray )
{
    for ( auto& keyMap : keyMapArray )
    {
        keyMaps.push_back( keyMap );
    }
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Clear all key maps
    --------------------------------------------------------------------------*/
void CursesKeyboard::clearKeyMaps()
{
    keyMaps.clear();
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Process the keyboard
    --------------------------------------------------------------------------*/
void CursesKeyboard::processKeyMaps()
{
    for ( auto& keyMap : keyMaps )
    {
        for ( auto keyToTest : keyMap.keys )
        {
            if ( key == keyToTest )
            {
                if ( keyMap.function != nullptr )
                {
                    keyMap.function( key );
                }
                lastKey = key;
                break;
            }
        }
    }
}

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: CursesKeyboard.cpp
// ----------------------------------------------------------------------------
