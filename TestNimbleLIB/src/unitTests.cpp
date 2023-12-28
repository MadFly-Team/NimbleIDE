/**----------------------------------------------------------------------------

    @file       unitTests.cpp
    @defgroup   NimbleLIB Nimble LIB
    @brief      Unit Tests for the Nimble LIB

    @copyright  Neil Beresford 2023

Notes:

Version:

        0.0.1.0   First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

// doctest unit testing framework setup
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../doctest/doctest/doctest.h"
#include "../../NimbleLIB/inc/NimbleLib.h"

//-----------------------------------------------------------------------------
// Namespace access
//-----------------------------------------------------------------------------

using namespace Nimble;
using namespace Nimble::Screen;

//-----------------------------------------------------------------------------
// Unit Tests
//-----------------------------------------------------------------------------
// clang-format off
TEST_SUITE( "Nimble LIB Test Suite" )
{
    //-----------------------------------------------------------------------------
    TEST_CASE( "Testing ScreenInfo" )
    //-----------------------------------------------------------------------------
    {
        SUBCASE( "Testing getWidth() and getHeight()" )
        {
            ScreenInfo screenInfo;
            screenInfo.RetrieveConsoleInfo();
            CHECK( screenInfo.GetWidth() != 0 );
            CHECK( screenInfo.GetHeight() != 0 );
        }
    }
    //-----------------------------------------------------------------------------
    // Test the Screen Module
    //-----------------------------------------------------------------------------

    #include "../inc/unitTests_Screen.h"

    //-----------------------------------------------------------------------------
    // Test the Error Handler Module
    //-----------------------------------------------------------------------------

    #include "../inc/unitTests_ErrorHandler.h"

    //-----------------------------------------------------------------------------
    // Test the IDE Module
    //-----------------------------------------------------------------------------

    #include "../inc/unitTests_IDEEdit.h"


} // TEST_SUITE( "Nimble LIB Test Suite" )
// clang-format on
//-----------------------------------------------------------------------------
// End of file: unitTests.cpp
//-----------------------------------------------------------------------------
