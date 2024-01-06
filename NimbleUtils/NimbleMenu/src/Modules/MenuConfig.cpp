/**----------------------------------------------------------------------------

    @file       MenuConfig.cpp
    @defgroup   NimbleMenu Nimble Menu
    @brief      Main entry and control point for the Nimble Menu

    @copyright  Neil Beresford 2023

Notes:

-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Headers
//-----------------------------------------------------------------------------

#include <fstream>
#include "../../../../NimbleLIB/inc/NimbleLib.h"

#include "../../inc/Modules/MenuConfig.h"

//-----------------------------------------------------------------------------
// Namespace access
// -----------------------------------------------------------------------------

using namespace Nimble;

//-----------------------------------------------------------------------------
// Class Definition
//-----------------------------------------------------------------------------

// Constructor / Destructor ---------------------------------------------------
/**---------------------------------------------------------------------------
    @ingroup    NimbleMenu Nimble Menu
    @brief      Constructor for the MenuConfig class
  --------------------------------------------------------------------------*/
MenuConfig::MenuConfig()
{
    // initialize the menu config
    totalItems = 0;
    menuCommands.clear();
    menuDescriptions.clear();
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleMenu Nimble Menu
    @brief      Destructor for the MenuConfig class
  --------------------------------------------------------------------------*/
MenuConfig::~MenuConfig()
{
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleMenu Nimble Menu
    @brief      Initialize the MenuConfig class
  --------------------------------------------------------------------------*/
void MenuConfig::MenuConfigInit()
{
    // load the menu config file
    std::ifstream menuConfigFile;
    menuConfigFile.open( "./NimbleMenu.cfg" );
    if ( menuConfigFile.is_open() )
    {
        // read the file
        std::stringstream buffer;
        buffer << menuConfigFile.rdbuf();
        std::string              menuConfigString = buffer.str();

        std::vector<std::string> menuConfigLines;
        std::string              strLine = "";

        // read the file line by line
        while ( std::getline( buffer, strLine ) )
        {
            // parse the line
            // add the line to the vector
            menuConfigLines.push_back( strLine );
        }

        // find the menu items
        uint32_t curLine = 0;
        while ( curLine < menuConfigLines.size() )
        {
            if ( menuConfigLines[ curLine ].find( "Items = ", 0 ) != std::string::npos )
            {
                // found the items
                totalItems = std::stoi( menuConfigLines[ curLine ].substr( 8 ) );
                break;
            }
            curLine++;
        }
        curLine++;
        while ( curLine < menuConfigLines.size() )
        {
            std::vector<std::string> splitStrings;
            std::stringstream        refString( menuConfigLines[ curLine ] );
            std::string              tmpString;

            if ( menuConfigLines[ curLine ].empty() == false )
            {
                while ( std::getline( refString, tmpString, '^' ) )
                {
                    splitStrings.push_back( tmpString );
                }

                menuCommands.push_back( splitStrings[ 2 ] + "\n" );
                menuDescriptions.push_back( splitStrings[ 1 ] );
            }
            curLine++;
        }

        // close the file
        menuConfigFile.close();
    }
    else
    {
        // log error
        ErrorHandler::getInstance().handleError( ErrorType::Error, LibraryError::Logger_base_error, "NimbleMenu.cfg not found" );
    }
}

// Getters -------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    NimbleMenu Nimble Menu
    @brief      Get the total number of menu items
    @return     uint32_t - total number of menu items
  --------------------------------------------------------------------------*/
uint32_t MenuConfig::GetTotalItems()
{
    return totalItems;
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleMenu Nimble Menu
    @brief      Get the menu command for the specified item
    @param      item - menu item to get the command
    @return     std::string - menu command
  --------------------------------------------------------------------------*/
std::string& MenuConfig::GetMenuCommand( uint32_t item )
{
    return menuCommands[ item ];
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleMenu Nimble Menu
    @brief      Get the menu description for the specified item
    @param      item - menu item to get the description
    @return     std::string - menu description
  --------------------------------------------------------------------------*/
std::string& MenuConfig::GetMenuDescription( uint32_t item )
{
    return menuDescriptions[ item ];
}

/**---------------------------------------------------------------------------
    @ingroup    NimbleMenu Nimble Menu
    @brief      Get the menu descriptions
    @return     std::vector<std::string> - vector of menu descriptions
  --------------------------------------------------------------------------*/
std::vector<std::string>& MenuConfig::GetMenuDescriptions()
{
    return menuDescriptions;
}

//-----------------------------------------------------------------------------
// End of File: MenuConfig.cpp
//-----------------------------------------------------------------------------
