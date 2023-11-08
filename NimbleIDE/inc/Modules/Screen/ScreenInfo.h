#include <stdint.h>

class ScreenInfo
{
  private:
    /* data */
    uint32_t width;
    uint32_t height;

  public:
    ScreenInfo(){};
    ~ScreenInfo(){};
    uint32_t getWidth()
    {
        return width;
    };
    uint32_t getHeight()
    {
        return height;
    };

    void RetrieveConsoleInfo();
};
