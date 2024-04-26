#include "ReadWriteLock.hpp"

#include <pthread.h>

namespace mars
{
    namespace utils
    {

        struct PthreadReadWriteLockWrapper
        {
            pthread_rwlock_t rw;
        };

        ReadWriteLock::ReadWriteLock()
            : myReadWriteLock(new PthreadReadWriteLockWrapper)
        {
            // TODO error checking?
            pthread_rwlock_init(&myReadWriteLock->rw, NULL);
        }

        ReadWriteLock::~ReadWriteLock()
        {
            // TODO error checking?
            pthread_rwlock_destroy(&myReadWriteLock->rw);
            delete myReadWriteLock;
        }

        void ReadWriteLock::lockForRead()
        {
            // TODO error checking?
            pthread_rwlock_rdlock(&myReadWriteLock->rw);
        }
        void ReadWriteLock::lockForWrite()
        {
            // TODO error checking?
            pthread_rwlock_wrlock(&myReadWriteLock->rw);
        }
        bool ReadWriteLock::tryLockForRead()
        {
            return (pthread_rwlock_tryrdlock(&myReadWriteLock->rw) == 0);
        }
        bool ReadWriteLock::tryLockForWrite()
        {
            return (pthread_rwlock_trywrlock(&myReadWriteLock->rw) == 0);
        }
        void ReadWriteLock::unlock()
        {
            pthread_rwlock_unlock(&myReadWriteLock->rw);
        }

    } // end of namespace utils
} // end of namespace mars
