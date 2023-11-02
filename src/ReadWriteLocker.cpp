
#include "ReadWriteLocker.h"
#include "ReadWriteLock.h"


namespace mars
{
    namespace utils
    {

        ReadWriteLocker::ReadWriteLocker(ReadWriteLock *readWriteLock, 
                                         ReadWriteLockMode mode)
            : myReadWriteLock(readWriteLock), myMode(mode)
        {
            isLocked = false;
            relock();
        }
  
        ReadWriteLocker::~ReadWriteLocker()
        {
            if (isLocked)
                myReadWriteLock->unlock();
        }

        void ReadWriteLocker::unlock()
        {
            if (isLocked)
            {
                myReadWriteLock->unlock();
                isLocked = false;
            }
        }
   
        void ReadWriteLocker::relock()
        {
            if (!isLocked)
            {
                if (myMode == READWRITELOCK_MODE_READ)
                {
                    myReadWriteLock->lockForRead();
                } else
                {
                    myReadWriteLock->lockForWrite();
                }
                isLocked = true;
            }
        }

    } // end of namepace utils
} // end of namespace mars
