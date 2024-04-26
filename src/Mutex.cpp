#include "Mutex.hpp"

#include <errno.h>

#include <pthread.h>


namespace mars
{
    namespace utils
    {

        struct PthreadMutexWrapper
        {
            pthread_mutex_t m;
        };

        Mutex::Mutex(const MutexType &mutexType_) 
            : myMutex(new PthreadMutexWrapper),
              mutexType(mutexType_)
        {
            pthread_mutexattr_t mutexAttributes;
            pthread_mutexattr_init(&mutexAttributes);
            switch(mutexType)
            {
            case MUTEX_TYPE_NORMAL:
                pthread_mutexattr_settype(&mutexAttributes, PTHREAD_MUTEX_NORMAL);
                break;
            case MUTEX_TYPE_RECURSIVE:
                pthread_mutexattr_settype(&mutexAttributes, PTHREAD_MUTEX_RECURSIVE);
                break;
            case MUTEX_TYPE_ERRORCHECKED:
            default:
                pthread_mutexattr_settype(&mutexAttributes, PTHREAD_MUTEX_ERRORCHECK);
                break;
            }
            pthread_mutex_init(&myMutex->m, &mutexAttributes);
            pthread_mutexattr_destroy(&mutexAttributes);
        }

        Mutex::~Mutex()
        {
            pthread_mutex_destroy(&myMutex->m);
            delete myMutex;
        }
  
        MutexError Mutex::lock()
        {
            int rc = pthread_mutex_lock(&myMutex->m);
            switch(rc)
            {
            case 0:
                return MUTEX_ERROR_NO_ERROR;
            case EINVAL:
                return MUTEX_ERROR_NO_VALID_MUTEX;
            case EAGAIN:
                return MUTEX_ERROR_RECURSIVE_LIMIT;
            case EDEADLK:
                return MUTEX_ERROR_DEADLOCK;
            default:
                return MUTEX_ERROR_UNKNOWN;
            }
        }

        MutexError Mutex::unlock()
        {
            int rc = pthread_mutex_unlock(&myMutex->m);
            switch(rc)
            {
            case 0:
                return MUTEX_ERROR_NO_ERROR;
            case EINVAL:
                return MUTEX_ERROR_NO_VALID_MUTEX;
            case EAGAIN:
                return MUTEX_ERROR_RECURSIVE_LIMIT;
            case EPERM:
                return MUTEX_ERROR_DONT_OWN;
            default:
                return MUTEX_ERROR_UNKNOWN;
            }
        }

        MutexError Mutex::tryLock()
        {
            int rc = pthread_mutex_trylock(&myMutex->m);
            switch(rc)
            {
            case 0:
                return MUTEX_ERROR_NO_ERROR;
            case EBUSY:
                return MUTEX_ERROR_BUSY;
            case EINVAL:
                return MUTEX_ERROR_NO_VALID_MUTEX;
            case EAGAIN:
                return MUTEX_ERROR_RECURSIVE_LIMIT;
            default:
                return MUTEX_ERROR_UNKNOWN;
            }
        }

        void* Mutex::getHandle()
        {
            return &myMutex->m;
        }

    } // end of namespace utils
} // end of namespace mars
