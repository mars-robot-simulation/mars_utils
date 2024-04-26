#pragma once

#ifdef WIN32
#  ifndef EIGEN_DONT_ALIGN
#    define EIGEN_DONT_ALIGN
#  endif
#endif

#include <Eigen/Core>


/* define M_PI if it is not defined (M_PI is *not* part of any standard) */
#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif


namespace mars
{
    namespace utils
    {

        typedef Eigen::Matrix<double, 3, 1, Eigen::DontAlign> Vector;
        typedef Eigen::Matrix<double, 3, 3, Eigen::DontAlign> Tensor;

    } // end of namespace utils
} // end of namespace mars

