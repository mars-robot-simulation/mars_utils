#pragma once

#ifdef WIN32
#  ifndef EIGEN_DONT_ALIGN
#    define EIGEN_DONT_ALIGN
#  endif
#endif

#include <Eigen/Core>
#include <Eigen/Geometry>

/* define M_PI if it is not defined (M_PI is *not* part of any standard) */
#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

namespace mars
{
    namespace utils
    {

        //rotation structure
        struct sRotation
        {
            double alpha;
            double beta;
            double gamma;
        };

        inline void ZERO_ROTATION(sRotation &a)
        { a.alpha = a.beta = a.gamma = 0.; }


        typedef Eigen::Quaternion<double, Eigen::DontAlign> Quaternion;


    } // end of namespace utils 
} // end of namespace mars
