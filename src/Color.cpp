#include "Color.h"

using namespace configmaps;

namespace mars
{
    namespace utils
    {

        bool Color::fromConfigItem(ConfigItem *item)
        {
            a = (*item)["a"];
            r = (*item)["r"];
            g = (*item)["g"];
            b = (*item)["b"];
            return true;
        }

        void Color::toConfigItem(ConfigItem *item)
        {
            (*item)["a"] = a;
            (*item)["r"] = r;
            (*item)["g"] = g;
            (*item)["b"] = b;
        }
    
    } // end of namespace base

} // end of namespace mars

