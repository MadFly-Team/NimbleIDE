/**----------------------------------------------------------------------------

    @file 		CFrameworkObject.hpp
    @defgroup   HardwareEmulationFramwork Hardware Emulation Framework
    @brief      Main Framework object

    @copyright	Neil Bereford 2023

-----------------------------------------------------------------------------*/

class CFrameworkObject
{
  public:
    // virtual functions
    virtual void Init()          = 0;
    virtual void Process()       = 0;
    virtual void LoadResources() = 0;
};

class CTest : public CFrameworkObject
{
  public:
    void Init()
    {
    }
    void Process()
    {
    }
    void LoadResources()
    {
    }
};

//-----------------------------------------------------------------------------
// End if file CFrameworkObject.hpp
//-----------------------------------------------------------------------------
