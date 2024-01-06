/**----------------------------------------------------------------------------

    @file       MenuConfig.h
    @defgroup   NimbleMenu Nimble Menu
    @brief      Main entry and control point for the Nimble Menu

    @copyright  Neil Beresford 2023

-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Headers
//-----------------------------------------------------------------------------

#include <stdint.h>
#include <vector>
#include <string>

//-----------------------------------------------------------------------------
// Class Definition
//-----------------------------------------------------------------------------

class MenuConfig
{
  public:
    // Constructor / Destructor --------------------------------------------
    MenuConfig();
    ~MenuConfig();
    // Removal of default copy constructors
    MenuConfig( const MenuConfig& )            = delete;
    MenuConfig& operator=( const MenuConfig& ) = delete;
    MenuConfig( MenuConfig&& )                 = delete;
    MenuConfig& operator=( MenuConfig&& )      = delete;
    // Public Methods -------------------------------------------------------
    void                      MenuConfigInit();
    std::string&              GetMenuDescription( uint32_t item );
    std::vector<std::string>& GetMenuDescriptions();
    std::string&              GetMenuCommand( uint32_t item );
    uint32_t                  GetTotalItems();

  private:
    // Private Members ------------------------------------------------------
    uint32_t                 totalItems = 0;
    std::vector<std::string> menuDescriptions;
    std::vector<std::string> menuCommands;
};

//-----------------------------------------------------------------------------
// End of File: MenuConfig.h
//-----------------------------------------------------------------------------
