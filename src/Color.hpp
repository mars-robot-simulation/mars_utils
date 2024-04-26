#pragma once

#include <configmaps/ConfigData.h>

namespace mars
{
    namespace utils
    {

        class Color
        {
        public:
            void setZero()
            {
                a = 1;
                r = 0;
                g = 0;
                b = 0;
            }
            Color()
            {
                setZero();
            }
            Color(double r, double g, double b, double a):
                r(r),g(g),b(b),a(a)
            {
            }

            double  r;
            double  g;
            double  b;
            double  a;

            /** Compare with other color (usually compared with default color) */
            bool operator==(const Color &other) const
            {
                /* warning: comparing (double) float values */
                return (a == other.a) && (r == other.r) && (g == other.g) && (b == other.b);
            }

            bool operator!=(const Color& other) const
            {
                /* warning: comparing (double) float values */
                return !(*this == other);
            }

            bool fromConfigItem(configmaps::ConfigItem *item);
            void toConfigItem(configmaps::ConfigItem *item);

        }; // end of class Color

    } // end of namespace utils
} // end of namespace mars
