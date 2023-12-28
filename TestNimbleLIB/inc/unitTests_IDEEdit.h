/**-----------------------------------------------------------------------------

    @file       unitTests_IDEEdit.h
    @defgroup   NimbleLIB Nimble LIB
    @brief      Unit Tests for the IDE Edit section of the module

    @copyright  Neil Beresford 2023

Notes:

    This file contains the unit tests for
    IDEEditline class in the IDE Module, in the Nimble Library

    Tests the IDE Edit functionality within the IDE Module

    Parameters are passed to the test functions and the results are checked
    against the expected values.

    Editing of  the IDEEditline is also tested.

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

//-----------------------------------------------------------------------------
// Tests
//-----------------------------------------------------------------------------
TEST_CASE( "Testing the IDE Edit functionality within the IDE Module" )
{
    // Editline tests ---------------------------------------------------------
    SUBCASE( "IDEEditline core functionality" )
    {
        // Test the Editline core functionality
        std::string testString = "test string";
        std::string returnString;
        IDEEditline editline;

        CHECK( editline.setParams( 1, 10, 10 ) == LibraryError::IDEEditline_InitNotCalled );  //!< test set parameters function, should fail as init not called
        CHECK( editline.init( testString, 1, 2 ) == LibraryError::No_Error );                 //!< test the init function, string and position 1,2
        CHECK( editline.setParams( 0, COLOR_WHITE, COLOR_BLACK ) == LibraryError::No_Error ); //!< test set parameters function, should pass as init called
        CHECK( editline.getLineXpos() == 1 );                                                 //!< test get cursor x position
        CHECK( editline.getLineYpos() == 2 );                                                 //!< test get cursor y position
        CHECK( editline.getLineLength() == testString.size() );                               //!< test get line length
        CHECK( editline.getLineString() == testString );                                      //!< test get line string
        CHECK( editline.getLineCursor() == 0 );                                               //!< test get cursor position
        CHECK( editline.getLineBufferChar( 1 ) == 'e' );                                      //!< test get buffer char
        CHECK( editline.getLineInkColour() == COLOR_WHITE );                                  //!< test get ink colour
        CHECK( editline.getLinePaperColour() == COLOR_BLACK );                                //!< test get paper colour
        editline.setHilightStart( 1 );                                                        //!< set hilight start
        editline.setHilightEnd( 2 );                                                          //!< set hilight end
        CHECK( editline.getHilightStart() == 1 );                                             //!< test set hilight start
        CHECK( editline.getHilightEnd() == 2 );                                               //!< test set hilight end
        editline.setLineXpos( 4 );                                                            //!< set line x position
        CHECK( editline.getLineXpos() == 4 );                                                 //!< test set line x position
        editline.setLineYpos( 5 );                                                            //!< set line y position
        CHECK( editline.getLineYpos() == 5 );                                                 //!< test set line y position
        editline.setLineInkColour( COLOR_GREEN );                                             //!< set ink colour
        CHECK( editline.getLineInkColour() == COLOR_GREEN );                                  //!< test ink colour
        editline.setLinePaperColour( COLOR_GREEN );                                           //!< set paper colour
        CHECK( editline.getLinePaperColour() == COLOR_GREEN );                                //!< test paper colour
        editline.setLineCursor( 7 );                                                          //!< set cursor position
        CHECK( editline.getLineCursor() == 7 );                                               //!< test set cursor position
    }
    // Editline editing string functionality -----------------------------------
    SUBCASE( "IDEEditline edit functionality" )
    {
        // Test the Editline edit functionality
        std::string testString = "test string";
        std::string returnString;
        IDEEditline editline;

        CHECK( editline.init( testString, 1, 2 ) == LibraryError::No_Error ); //!< test the init function, string and position 1,2
        CHECK( editline.addChar( 'a' ) == LibraryError::No_Error );           //!< test add char
        CHECK( editline.getLineString() == "atest string" );                  //!< test get line string
        editline.setLineCursor( editline.getLineLength() );                   //!< set cursor to end of line
        testString = "bc";                                                    //!< set test string
        CHECK( editline.addString( testString ) == LibraryError::No_Error );  //!< test add string
        CHECK( editline.getLineString() == "atest stringbc" );                //!< test get line string
        CHECK( editline.deleteChar() == LibraryError::No_Error );             //!< test delete char
        CHECK( editline.getLineString() == "atest stringb" );                 //!< test get line string
        CHECK( editline.deleteChars( 2 ) == LibraryError::No_Error );         //!< test delete chars
        CHECK( editline.getLineString() == "atest string" );                  //!< test get line string
    }
    // check the user flags ----------------------------------------------------
    SUBCASE( "IDEEditline check user flags" )
    {
        // Test the Editline user flags functionality
        std::string testString = "test string";
        IDEEditline editline;
        CHECK( editline.init( testString, 1, 2 ) == LibraryError::No_Error );                                         //!< test the init function, string and position 1,2
        CHECK( editline.setEditlineFlag( IDEEditline::EditlineFlags::CursorActive ) == LibraryError::No_Error );      //!< test set flag
        CHECK( editline.isEditlineFlagSet( IDEEditline::EditlineFlags::CursorActive ) == true );                      //!< test get flag
        CHECK( editline.clearEditlineFlag( IDEEditline::EditlineFlags::CursorActive ) == LibraryError::No_Error );    //!< test clear flag
        CHECK( editline.isEditlineFlagSet( IDEEditline::EditlineFlags::CursorActive ) == false );                     //!< test get flag
        CHECK( editline.setEditlineFlag( IDEEditline::EditlineFlags::FormatWhenPrint ) == LibraryError::No_Error );   //!< test set flag
        CHECK( editline.isEditlineFlagSet( IDEEditline::EditlineFlags::FormatWhenPrint ) == true );                   //!< test get flag
        CHECK( editline.clearEditlineFlag( IDEEditline::EditlineFlags::FormatWhenPrint ) == LibraryError::No_Error ); //!< test clear flag
        CHECK( editline.isEditlineFlagSet( IDEEditline::EditlineFlags::FormatWhenPrint ) == false );                  //!< test get flag
    }
}

// end of TEST_CASE
//-----------------------------------------------------------------------------
// End of File unitTests_IDEEdit.h
// ----------------------------------------------------------------------------
