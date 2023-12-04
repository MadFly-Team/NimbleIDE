/**----------------------------------------------------------------------------

    @file       CursesKeyboard.h
    @defgroup   NimbleLIBCurses Nimble Library Curses Module
    @brief      Curses keyboard class for the Nimble Library

    @copyright  Neil Bereford 2023

Notes:

        please see CursesKeyboard.cpp for full details.

Version:

        0.0.1.0     First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include <cinttypes>
#include <cstdint>

extern "C"
{
#include "../../../../ExternalLibraries/PDCurses/curses.h"
}

#include "../ErrorHandling/ErrorHandler.h"
#include "../Utilities/StatusCtrl.h"

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Nimble
{

//-----------------------------------------------------------------------------
// Class definitions
// ----------------------------------------------------------------------------

typedef void ( *pKeyFunction )( int32_t key ); //!< Keymap Function pointer type

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
    // Other --------------------------------------------------------------------
    void addKeyMap( const std::string& name, const std::vector<uint32_t>& keys, pKeyFunction function );
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
