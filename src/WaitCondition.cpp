#include "WaitCondition.h"
#include "Mutex.h"

#include <pthread.h>
#include <errno.h>

namespace mars
{
    namespace utils
    {

        struct PthreadConditionWrapper
        {
            pthread_cond_t c;
        };

        WaitCondition::WaitCondition() 
            : myWaitCondition(new PthreadConditionWrapper)
        {
            pthread_cond_init(&myWaitCondition->c, NULL);
        }

        WaitCondition::~WaitCondition()
        {
            pthread_cond_destroy(&myWaitCondition->c);
            delete myWaitCondition;
        }
  
        WaitConditionError WaitCondition::wait(Mutex *mutex)
        {
            pthread_mutex_t *m = static_cast<pthread_mutex_t*>(mutex->getHandle());
            int rc = pthread_cond_wait(&myWaitCondition->c, m);
            switch(rc)
            {
            case 0:
                return WAITCOND_NO_ERROR;
            case EINVAL:
                return WAITCOND_UNSPECIFIED;
            default:
                return WAITCOND_UNKNOWN;
            }
        }

        WaitConditionError WaitCondition::wait(Mutex *mutex,
                                               unsigned long timeoutMilliseconds)
        {
            struct timespec t;
            t.tv_sec = timeoutMilliseconds / 1000;
            t.tv_nsec = (timeoutMilliseconds % 1000) * 1000000;
            pthread_mutex_t *m = static_cast<pthread_mutex_t*>(mutex->getHandle());
            int rc = pthread_cond_timedwait(&myWaitCondition->c, m, &t);
            switch(rc)
            {
            case 0:
                return WAITCOND_NO_ERROR;
            case ETIMEDOUT:
                return WAITCOND_TIMEOUT;
            case EINVAL:
                return WAITCOND_UNSPECIFIED;
            default:
                return WAITCOND_UNKNOWN;
            }
        }

        WaitConditionError WaitCondition::wakeOne()
        {
            int rc = pthread_cond_signal(&myWaitCondition->c);
            switch(rc)
            {
            case 0:
                return WAITCOND_NO_ERROR;
            case EINVAL:
                return WAITCOND_INTERNAL_ERROR;
            default:
                return WAITCOND_UNKNOWN;
            }
        }

        WaitConditionError WaitCondition::wakeAll()
        {
            int rc = pthread_cond_broadcast(&myWaitCondition->c);
            switch(rc)
            {
            case 0:
                return WAITCOND_NO_ERROR;
            case EINVAL:
                return WAITCOND_INTERNAL_ERROR;
            default:
                return WAITCOND_UNKNOWN;
            }
        }

    } // end of namespace utils
} // end of namespace mars
