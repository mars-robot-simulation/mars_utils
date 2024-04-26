#include "MutexLocker.hpp"
#include "Mutex.hpp"


namespace mars
{
    namespace utils
    {

        MutexLocker::MutexLocker(Mutex *mutex)
            : myMutex(mutex)
        {
            myMutex->lock();
            isLocked = true;
        }

        MutexLocker::~MutexLocker()
        {
            if (isLocked)
                myMutex->unlock();
        }

        void MutexLocker::unlock()
        {
            if (isLocked)
            {
                myMutex->unlock();
                isLocked = false;
            }
        }

        void MutexLocker::relock()
        {
            if (!isLocked)
            {
                myMutex->lock();
                isLocked = true;
            }
        }

    } // end of namespace utils
} // end of namespace mars
