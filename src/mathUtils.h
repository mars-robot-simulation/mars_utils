#pragma once

#include "Vector.h"
#include "Quaternion.h"
#include <configmaps/ConfigData.h>

namespace mars
{
    namespace utils
    {

        // approximation functions

        enum ApproximationFunction
        {
            FUNCTION_PIPE,
            FUNCTION_POLYNOM2,
            FUNCTION_POLYNOM3,
            FUNCTION_POLYNOM4,
            FUNCTION_POLYNOM5,
            FUNCTION_GAUSSIAN, /*
                                 FUNCTION_BETA_DISTRIBUTION,
                                 FUNCTION_GAMMA_DISTRIBUTION*/
            FUNCTION_UNKNOWN
        };

        enum ApproximationFunction2D
        {
            FUNCTION_UNKNOWN2D,
            FUNCTION_POLYNOM2D1,
            FUNCTION_POLYNOM2D2,
            //FUNCTION_POLYNOM2D3
        };


        ApproximationFunction getApproximationFunctionFromString(std::string s);
        ApproximationFunction2D getApproximationFunction2DFromString(std::string s);
        const double SQRT2PI = 2.5066282746310002;

        double pipe(double* x, std::vector<double>* c);
        double polynom2(double* x, std::vector<double>* c);
        double polynom3(double* x, std::vector<double>* c);
        double polynom4(double* x, std::vector<double>* c);
        double polynom5(double* x, std::vector<double>* c);
        double gaussian(double* x, std::vector<double>* c);
        double beta_distribution(double* x, std::vector<double>* c);
        double gamma_distribution(double* x, std::vector<double>* c);
        double polynom2D1(double* x, double* y, std::vector<double>* c);
        double polynom2D2(double* x, double* y, std::vector<double>* c);

        const double EPSILON = Eigen::NumTraits<double>::epsilon();

        inline bool isNormalized(const Vector &vec)
        { return (fabs(vec.squaredNorm() - 1.) < EPSILON*EPSILON); }

        inline Vector scaleVectorToLength(const Vector &vec, const double &length)
        { return vec * length / vec.norm(); }
        

        /**
         * Angle between two vectors
         * \param[in] v Vector to which we want to know the angle
         * \param[out] axis If axis != NULL the axis of rotation will be stored here.
         * \return The angle between \c this and v in radian.
         */
        double angleBetween(const Vector &v1, const Vector &v2, Vector *axis=NULL);

        double getYaw(const mars::utils::Quaternion &);

        inline Quaternion angleAxisToQuaternion(double angle, const Vector &axis) {
            return Quaternion(Eigen::AngleAxis<double>(angle, axis));
        }

        Quaternion eulerToQuaternion(const Vector &euler_v);
        inline Quaternion eulerToQuaternion(const sRotation &rot)
        { return eulerToQuaternion(Vector(rot.alpha, rot.beta, rot.gamma)); }

        sRotation quaternionTosRotation(const Quaternion &value);

        Vector lerp(const Vector &from, const Vector &to, double t);
        Vector slerp(const Vector &from, const Vector &to, double t);

        inline double distanceSquaredBetween(const Vector &v1, const Vector &v2)
        { return (v2.array() - v1.array()).square().sum(); }
        inline double distanceBetween(const Vector &v1, const Vector &v2)
        { return sqrt(distanceSquaredBetween(v1, v2)); }

        void vectorToSpherical(const Vector &v, double *r, double *theta, double *phi);

        Vector getProjection(const Vector &v1, const Vector &v2);

        /** \brief Projects a vector to a plane defined by the direction vectors pln1 and pln2.
         * \param vec: Vector to project
         * \param pln1: a vector that lies in the plane
         * \param pln2: another linear independent vector that lies in the plane
         * \return The projected vector
         */
        Vector projectVectorToPlane(Vector vec, Vector pln1, Vector pln2);

        Vector vectorFromSpherical(double r, double theta, double phi);

        bool vectorFromConfigItem(configmaps::ConfigItem *item, Vector *v);
        void vectorToConfigItem(configmaps::ConfigItem *item, const Vector *v);
        configmaps::ConfigItem vectorToConfigItem(const Vector &v);

        bool quaternionFromConfigItem(configmaps::ConfigItem *item, Quaternion *q);
        void quaternionToConfigItem(configmaps::ConfigItem *item, const Quaternion *q, bool add_euler_angles = false);
        configmaps::ConfigItem quaternionToConfigItem(const Quaternion &q, bool add_euler_angles = false);

        template <typename T>
        Quaternion quaternionFromMembers(T q)
        {
            return Quaternion(q.w, q.x, q.y, q.z);
        }

        template <typename T>
        Quaternion quaternionFromXYZWArray(T q)
        {
            return Quaternion(q[3], q[0], q[1], q[2]);
        }

        template <typename T>
        Quaternion quaternionFromWXYZArray(T q)
        {
            return Quaternion(q[0], q[1], q[2], q[3]);
        }

        double random_normal_number(double mean, double std, double min, double max);
        double random_number(double min, double max, int digits);

    }; // end of namespace utils
}; // end of namespace mars
