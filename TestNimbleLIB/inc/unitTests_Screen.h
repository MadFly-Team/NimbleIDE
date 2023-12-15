/**----------------------------------------------------------------------------

    @file       unitTests_Screen.h
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

#include <string>
#include "../../NimbleLIB/inc/NimbleLib.h"

//-----------------------------------------------------------------------------
// Namespace access
//-----------------------------------------------------------------------------

using namespace Nimble;
using namespace Nimble::Screen;

//-----------------------------------------------------------------------------
// Tests
//-----------------------------------------------------------------------------
TEST_CASE( "Testing the Screen Module" )
{
    // Test the Screen core functionality
    SUBCASE( "Testing ScreenInfo" )
    {
        ScreenInfo screenInfo;
        screenInfo.RetrieveConsoleInfo();
        CHECK( screenInfo.GetWidth() != 0 );
        CHECK( screenInfo.GetHeight() != 0 );
    }
    SUBCASE( "Testing ScreenControl" )
    {
        ErrorHandler::getInstance().clearErrors();
        ScreenControl screenControl;
        ErrorStatus   errorStatus = ErrorHandler::getInstance().getStatusInformation();
        CHECK( errorStatus.totalErrors == 0 );
    }
    SUBCASE( "Testong ScreenWord" )
    {
        // test parameters
        std::string testString = "TestString";
        uint32_t    testInt    = 10;
        uint8_t     testByte   = 0x55;

        // test the getters and setters
        ScreenWord screenWord;
        screenWord.SetWord( testString );
        CHECK( screenWord.GetWord() == testString );
        screenWord.SetWord( testString.c_str() );
        CHECK( screenWord.GetWord() == testString );
        screenWord.SetXPos( testInt );
        CHECK( screenWord.GetXPos() == testInt );
        screenWord.SetYPos( testInt );
        CHECK( screenWord.GetYPos() == testInt );
        screenWord.SetFGColour( testInt );
        CHECK( screenWord.GetFGColour() == testInt );
        screenWord.SetBGColour( testInt );
        CHECK( screenWord.GetBGColour() == testInt );
        screenWord.SetEffect( testByte );
        CHECK( screenWord.GetEffect().value == testByte );
        CHECK( screenWord.GetEffect().Italic == (uint8_t)Screen::eState::On );
        CHECK( screenWord.GetEffect().Bold == (uint8_t)Screen::eState::Off );
        CHECK( screenWord.GetEffect().Underline == (uint8_t)Screen::eState::On );
        CHECK( screenWord.GetEffect().Strike == (uint8_t)Screen::eState::Off );
        CHECK( screenWord.GetEffect().Blink == (uint8_t)Screen::eState::On );
        CHECK( screenWord.GetEffect().Reverse == (uint8_t)Screen::eState::Off );
    }
    SUBCASE( "Testing ScreenPrint" )
    {
        // test parameters
        std::string       testString = "TestString";
        std::stringstream ss;
        ScreenWord        blankWord;
        ScreenWord        testWord;
        ScreenPrint       screenPrint;

        // setup the result string as expected, fromn the formatted return string
        ss << COLOUR_BG_START << blankWord.GetBGColour() << COLOUR_END << COLOUR_START << blankWord.GetFGColour() << COLOUR_END;
        ss << blankWord.GetWord() << CHAR_RESET;

        // test the 'add' functionality, with string and ScreenWord classes
        screenPrint.Add( testString );
        CHECK( screenPrint.GetStreamString() == testString );
        screenPrint.ClearStream();
        CHECK( screenPrint.GetStreamString() != testString );
        CHECK( screenPrint.GetStreamString() == "" );
        screenPrint.Add( blankWord );
        CHECK( screenPrint.GetStreamString() == ss.str() );
        testWord.SetWord( testString );
        ss.clear();
        ss << COLOUR_BG_START << testWord.GetBGColour() << COLOUR_END << COLOUR_START << testWord.GetFGColour() << COLOUR_END;
        ss << testWord.GetWord() << CHAR_RESET;
        screenPrint.Add( testWord );
        CHECK( screenPrint.GetStreamString() == ss.str() );
    }
}

//-----------------------------------------------------------------------------
// End of file: unitTests_Screen.h
//-----------------------------------------------------------------------------
