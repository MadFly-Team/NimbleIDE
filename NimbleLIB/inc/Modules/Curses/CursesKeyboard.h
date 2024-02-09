/**----------------------------------------------------------------------------

    @file       CursesKeyboard.h
    @defgroup   NimbleLIBCurses Nimble Library Curses Module
    @brief      Curses keyboard class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

        please see CursesKeyboard.cpp for full details.

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

#include "../ErrorHandling/ErrorHandler.h"
#include "../Utilities/StatusCtrl.h"

//-----------------------------------------------------------------------------
// Definitions
// ----------------------------------------------------------------------------

constexpr uint32_t KEY_ESC = 27; //!< Escape key code

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

using pKeyFunction = std::function<void( uint32_t )>; //!< Keymap Function pointer type

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Key map structure for the Nimble Library
   --------------------------------------------------------------------------*/
typedef struct
{
    std::string           name;     //!< Name of the key mapping
    std::vector<uint32_t> keys;     //!< List of keys
    pKeyFunction          function; //!< Function pointer callback

} KeyMap, *pKeyMap; //!< Key map structure

/**----------------------------------------------------------------------------
    @ingroup    NimbleLIBCurses Nimble Library Curses Module
    @brief      Curses keyboard class for the Nimble Library
   --------------------------------------------------------------------------*/
class CursesKeyboard
{
  public:
    // Constructors and destructors ---------------------------------------------
    CursesKeyboard();
    CursesKeyboard( const CursesKeyboard& other );
    CursesKeyboard( const std::string name, const std::vector<uint32_t> keys, pKeyFunction function );
    ~CursesKeyboard();

    // Member functions ---------------------------------------------------------
    // Getters ------------------------------------------------------------------
    uint32_t getLastKey() const noexcept;
    uint32_t getKey() const noexcept;
    // Setters ------------------------------------------------------------------
    void setKey( uint32_t key ) noexcept;
    // Other --------------------------------------------------------------------
    void addKeyMap( const std::string& name, const std::vector<uint32_t>& keys, pKeyFunction function );
    void addKeyMap( const KeyMap& keyMap );
    void addKeyMapArray( const std::vector<KeyMap>& keyMapArray );
    void clearKeyMaps();
    void processKeyMaps();
    //---------------------------------------------------------------------------
  private:
    // Private data members
    std::vector<KeyMap> keyMaps; //!< List of key maps
    uint32_t            lastKey; //!< Last key pressed
    uint32_t            key;     //!< Current key pressed
    // --------------------------------------------------------------------------
};

//-----------------------------------------------------------------------------

} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: CursesKeyboard.h
// ----------------------------------------------------------------------------
