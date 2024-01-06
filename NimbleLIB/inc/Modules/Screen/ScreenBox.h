/**----------------------------------------------------------------------------

    @file       ScreenBox.h
    @defgroup   NimbleIDEScreen Nimble IDE Screen Module
    @brief      ScreenBox class for the Nimble IDE

    @copyright  Neil Bereford 2023

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
//  includes
//-----------------------------------------------------------------------------

#include <stdint.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "../../../inc/Modules/Screen/ScreenWord.h"
#include "../../../inc/Modules/Screen/ScreenPrint.h"
#include "../../../inc/Modules/Global/Globals.h"

//-----------------------------------------------------------------------------
// Namespace access
//-----------------------------------------------------------------------------

namespace Nimble
{
namespace Screen
{

//-----------------------------------------------------------------------------
// Class definations
//-----------------------------------------------------------------------------

enum eBoxEdgeSingle
{
    eBoxEdge_Top = 0,
    eBoxEdge_Bottom,
    eBoxEdge_Left,
    eBoxEdge_Right,
    eBoxEdge_TopLeft,
    eBoxEdge_TopRight,
    eBoxEdge_BottomLeft,
    eBoxEdge_BottomRight,
    eBoxEdge_Cross,
    eBoxEdge_CrossTop,
    eBoxEdge_CrossBottom,
    eBoxEdge_CrossLeft,
    eBoxEdge_CrossRight,
    eBoxEdge_SingleTotal
};

enum eBoxEdgeDouble
{
    eBoxEdgeDouble_Top         = 0,
    eBoxEdgeDouble_Bottom      = 1,
    eBoxEdgeDouble_Left        = 2,
    eBoxEdgeDouble_Right       = 3,
    eBoxEdgeDouble_TopLeft     = 4,
    eBoxEdgeDouble_TopRight    = 5,
    eBoxEdgeDouble_BottomLeft  = 6,
    eBoxEdgeDouble_BottomRight = 7,
    eBoxEdgeDouble_Cross       = 8,
    eBoxEdgeDouble_CrossTop    = 9,
    eBoxEdgeDouble_CrossBottom = 10,
    eBoxEdgeDouble_CrossLeft   = 11,
    eBoxEdgeDouble_CrossRight  = 12,
    eBoxEdge_DoubleTotal
};

enum eBoxEdge
{
    eBoxEdge_Single = 0,
    eBoxEdge_Double = 1,
};

class ScreenBox
{
  private:
    std::string strEdgeSingle[ eBoxEdge_SingleTotal ] = { "─", "─", "│", "│", "┌", "┐", "└", "┘", "┼", "┬", "┴", "├", "┤" };
    std::string strEdgeDouble[ eBoxEdge_DoubleTotal ] = { "═", "═", "║", "║", "╔", "╗", "╚", "╝", "╬", "╦", "╩", "╠", "╣" };

  public:
    void PrintBox( uint32_t x, uint32_t y, uint32_t width, uint32_t height );
    void PrintBoxDouble( uint32_t x, uint32_t y, uint32_t width, uint32_t height );
    void AddVertLine( uint32_t x, uint32_t y, uint32_t height );
    // void PrintBox( uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t colour );
    // void PrintBox( uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t colour, uint32_t background );
    // void PrintBox( uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t colour, uint32_t background, eBoxEdge edge );
};

//-----------------------------------------------------------------------------

} // namespace Screen
} // namespace Nimble

//-----------------------------------------------------------------------------
// End of file: ScreenBox.h
//-----------------------------------------------------------------------------
