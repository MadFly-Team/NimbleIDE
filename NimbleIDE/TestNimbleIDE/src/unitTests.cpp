/**----------------------------------------------------------------------------

    @file       unitTests.cpp
    @defgroup   NimbleIDE Nimble IDE
    @brief      Unit Tests for the Nimble IDE

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
#include "../../../doctest/doctest/doctest.h"
#include "../../inc/Modules/Screen/ScreenInfo.h"
//-----------------------------------------------------------------------------
// Unit Tests
//-----------------------------------------------------------------------------

TEST_SUITE( "Nimble IDE Test Suite" )
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
    //-----------------------------------------------------------------------------
} // TEST_SUITE( "Nimble IDE Test Suite" )

//-----------------------------------------------------------------------------
// End of file: unitTests.cpp
//-----------------------------------------------------------------------------
