/**----------------------------------------------------------------------------

    @file       ScreenBox.h
    @defgroup   NimbleIDEScreen Nimble IDE Screen Module
    @brief      ScreenBox class for the Nimble IDE

    @copyright  Neil Bereford 2023

Notes:

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
//  includes
//-----------------------------------------------------------------------------

#include "../../../inc/Modules/Screen/ScreenPrint.h"
#include "../../../inc/Modules/Screen/ScreenBox.h"

//-----------------------------------------------------------------------------
// Namespace access
//-----------------------------------------------------------------------------

namespace Nimble
{
namespace Screen
{

//-----------------------------------------------------------------------------
// Class definitions
//-----------------------------------------------------------------------------

/**----------------------------------------------------------------------------
    @ingroup    NimbleIDEScreen Nimble IDE Screen Module
    @brief      Print box on screen
    @param      x       x position
    @param      y       y position
    @param      width   width of box
    @param      height  height of box
    @return     void
-----------------------------------------------------------------------------*/
void ScreenBox::PrintBox( uint32_t x, uint32_t y, uint32_t width, uint32_t height )
{
    uint32_t i;

    // Get the instance of the global class
    Globals& global = Globals::getInstance();
    // Print the top edge
    std::string str;
    std::string strTitleLine;

    str = strEdgeSingle[ eBoxEdge_TopLeft ];
    for ( i = 0; i < width - 2; i++ )
    {
        str += strEdgeSingle[ eBoxEdge_Top ];
    }
    str += strEdgeSingle[ eBoxEdge_TopRight ];
    global.PrintAdd( x, y++, str );
    global.Print();

    str          = strEdgeSingle[ eBoxEdge_Left ];
    strTitleLine = strEdgeSingle[ eBoxEdge_CrossLeft ];
    for ( i = 0; i < width - 2; i++ )
    {
        strTitleLine += strEdgeSingle[ eBoxEdge_Top ];
    }
    str += std::string( width - 2, ' ' );
    str += strEdgeSingle[ eBoxEdge_Right ];
    strTitleLine += strEdgeSingle[ eBoxEdge_CrossRight ];
    global.PrintAdd( x, y++, str );
    global.Print();
    global.PrintAdd( x, y++, strTitleLine );
    global.Print();
    for ( i = 0; i < height - 4; i++ )
    {
        global.PrintAdd( x, y++, str );
        global.Print();
    }

    str = strEdgeSingle[ eBoxEdge_BottomLeft ];
    for ( i = 0; i < width - 2; i++ )
    {
        str += strEdgeSingle[ eBoxEdge_Bottom ];
    }
    str += strEdgeSingle[ eBoxEdge_BottomRight ];
    global.PrintAdd( x, y, str );
    global.Print();
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleIDEScreen Nimble IDE Screen Module
    @brief      Print double box on screen
    @param      x       x position
    @param      y       y position
    @param      width   width of box
    @param      height  height of box
    @return     void
-----------------------------------------------------------------------------*/
void ScreenBox::PrintBoxDouble( uint32_t x, uint32_t y, uint32_t width, uint32_t height )
{
    uint32_t i;

    // Get the instance of the global class
    Globals& global = Globals::getInstance();
    // Print the top edge
    std::string str;
    std::string strTitleLine;

    str = strEdgeDouble[ eBoxEdgeDouble_TopLeft ];
    for ( i = 0; i < width - 2; i++ )
    {
        str += strEdgeDouble[ eBoxEdgeDouble_Top ];
    }
    str += strEdgeDouble[ eBoxEdgeDouble_TopRight ];
    global.PrintAdd( x, y++, str );
    global.Print();

    str          = strEdgeDouble[ eBoxEdgeDouble_Left ];
    strTitleLine = strEdgeDouble[ eBoxEdgeDouble_CrossLeft ];
    for ( i = 0; i < width - 2; i++ )
    {
        strTitleLine += strEdgeDouble[ eBoxEdge_Top ];
    }
    str += std::string( width - 2, ' ' );
    str += strEdgeDouble[ eBoxEdgeDouble_Right ];
    strTitleLine += strEdgeDouble[ eBoxEdgeDouble_CrossRight ];
    global.PrintAdd( x, y++, str );
    global.Print();
    global.PrintAdd( x, y++, strTitleLine );
    global.Print();
    for ( i = 0; i < height - 4; i++ )
    {
        global.PrintAdd( x, y++, str );
        global.Print();
    }

    str = strEdgeDouble[ eBoxEdgeDouble_BottomLeft ];
    for ( i = 0; i < width - 2; i++ )
    {
        str += strEdgeDouble[ eBoxEdgeDouble_Bottom ];
    }
    str += strEdgeDouble[ eBoxEdgeDouble_BottomRight ];
    global.PrintAdd( x, y, str );
    global.Print();
}

/**----------------------------------------------------------------------------
    @ingroup    NimbleIDEScreen Nimble IDE Screen Module
    @brief      Add vertical line to box
    @param      x       x position
    @param      y       y position
    @param      height  height of box
    @return     void
-----------------------------------------------------------------------------*/
void ScreenBox::AddVertLine( uint32_t x, uint32_t y, uint32_t height )
{
    uint32_t i;
    // Get the instance of the global class
    Globals& global = Globals::getInstance();
    global.PrintAdd( x, y++, strEdgeSingle[ eBoxEdge_CrossTop ] );
    global.Print();

    for ( i = 0; i < height - 1; i++ )
    {
        global.PrintAdd( x, y++, strEdgeSingle[ eBoxEdge_Left ] );
        global.Print();
    }

    global.PrintAdd( x, y, strEdgeSingle[ eBoxEdge_CrossBottom ] );
    global.Print();
}

//-----------------------------------------------------------------------------

} // namespace Screen
} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: ScreenPrint.h
//-----------------------------------------------------------------------------
