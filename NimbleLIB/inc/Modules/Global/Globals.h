/**----------------------------------------------------------------------------

    @file       Globals.h
    @defgroup   NimbleLIBScreen Nimble Library Screen Module
    @brief      Globals class for the Nimble LIB

    @copyright  Neil Bereford 2023

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
//  includes
//-----------------------------------------------------------------------------

#include <cstdint>
#include <stdint.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
extern "C"
{
#include "../../../../ExternalLibraries/PDCurses/curses.h"
}
#include "../../../inc/Modules/Screen/ScreenWord.h"
#include "../../../inc/Modules/Screen/ScreenPrint.h"

//-----------------------------------------------------------------------------
// Defines
// -----------------------------------------------------------------------------

#define GControl Nimble::Screen::Globals::getInstance()

//-----------------------------------------------------------------------------
// Namespace access
//-----------------------------------------------------------------------------

namespace Nimble
{
namespace Screen
{

//-----------------------------------------------------------------------------
// GLass definitions
//-----------------------------------------------------------------------------

enum class eEditorTheme
{
    Dark,  //!< Dark theme
    Light, //!< Light theme
    Total  //!< Total number of themes
};

enum class eEditorSettings
{
    LineNumbers, //!< Show line numbers
    Theme,       //!< Theme selected

    Total //!< Total number of settings
};

struct sEditorSettings
{
    bool         LineNumbers;
    eEditorTheme Theme;
};

/**---------------------------------------------------------------------------
    @ingroup    NimbleLIBScreen Nimble Library Screen Module
    @brief      Global Singleton class for the Nimble Library
                This class is a singleton and is used to store global variables
                and functions for the Nimble Library

  --------------------------------------------------------------------------*/
class Globals
{
  public:
    // Function to get the instance of the Global
    static Globals& getInstance()
    {
        static Globals instance; // Guaranteed to be destroyed, instantiated on first use
        return instance;
    }

    //-----------------------------------------------------------------------------
    //  Public Functions
    void PrintAdd( uint32_t x, uint32_t y, const std::string& text )
    {
        m_print.Add( x, y, text );
    }
    void PrintAdd( const std::string& text )
    {
        m_print.Add( text );
    }

    void Print()
    {
        m_print.Display();
    }

    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Get the screen width
        @return     uint32_t - screen width
      --------------------------------------------------------------------------*/
    uint32_t getScreenWidth() const
    {
        return m_screenWidth;
    }
    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Get the screen height
        @return     uint32_t - screen height
      --------------------------------------------------------------------------*/
    uint32_t getScreenHeight() const
    {
        return m_screenHeight;
    }

    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Set the screen width
        @param      uint32_t - screen width
      --------------------------------------------------------------------------*/
    void setScreenWidth( uint32_t width )
    {
        m_screenWidth = width;
    }
    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Set the screen height
        @param      uint32_t - screen height
      --------------------------------------------------------------------------*/
    void setScreenHeight( uint32_t height )
    {
        m_screenHeight = height;
    }

    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Set the number of manager components
        @param      uint32_t - number of manager components
    --------------------------------------------------------------------------*/
    void setManagerComponents( uint32_t nDialogs )
    {
        m_managerComponents = nDialogs;
    }

    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Get the number of manager components
        @return     uint32_t - number of manager components
    --------------------------------------------------------------------------*/
    uint32_t getManagerComponents()
    {
        return m_managerComponents;
    }

    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Get the editor settings

        TODO: This needs complete rework to protect the settings

        @return     sEditorSettings - editor settings
    ---------------------------------------------------------------------------*/
    sEditorSettings* getEditorSettings()
    {
        return &m_editorSettings;
    }

    // Editor Settings -----------------------------------------------------------
    void ProcessMouse()
    {
        if ( getmouse( &mouseEvent ) == OK )
        {
            m_mouseX            = mouseEvent.x;
            m_mouseY            = mouseEvent.y;
            m_mouseButtonStates = mouseEvent.bstate;
        }
    }
    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Get the mouse y position
        @return     uint32_t - mouse y position
    ---------------------------------------------------------------------------*/
    uint32_t getMouseY()
    {
        return ( m_mouseY );
    }

    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Get the mouse x position
        @return     uint32_t - mouse x position
    ----------------------------------------------------------------------------*/
    uint32_t getMouseX()
    {
        return ( m_mouseX );
    }

    /**---------------------------------------------------------------------------
        @ingroup    NimbleLIBScreen Nimble Library Screen Module
        @brief      Get the mouse button states
        @return     uint32_t - mouse button states
    ----------------------------------------------------------------------------*/
    uint32_t getMouseButtonStates()
    {
        return ( m_mouseButtonStates );
    }

    //-----------------------------------------------------------------------------

  private:
    // Private constructor to prevent instantiation
    Globals()
    {
    }

    // Private copy constructor and copy assignment operator to prevent duplication
    Globals( const Globals& )            = delete;
    Globals& operator=( const Globals& ) = delete;

    //-----------------------------------------------------------------------------
    // GLobal variables
    uint32_t        m_screenWidth       = 0; //!< Screen width
    uint32_t        m_screenHeight      = 0; //!< Screen height
    uint32_t        m_managerComponents = 0; //!< Number of manager components
    ScreenPrint     m_print;                 //!< Screen print class
    sEditorSettings m_editorSettings;        //!< Editor settings
    uint32_t        m_mouseX            = 0; //!< Mouse x position
    uint32_t        m_mouseY            = 0; //!< Mouse y position
    uint32_t        m_mouseButtonStates = 0; //!< Mouse button
    MEVENT          mouseEvent;              //!< Mouse event
    //-----------------------------------------------------------------------------
};

//-----------------------------------------------------------------------------

} // namespace Screen
} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: Globals.h
//-----------------------------------------------------------------------------
