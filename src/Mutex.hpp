#pragma once

namespace mars
{
    namespace utils
    {

        class WaitCondition;
        struct PthreadMutexWrapper;

        enum MutexType
        {
            MUTEX_TYPE_NORMAL,
            MUTEX_TYPE_ERRORCHECKED,
            MUTEX_TYPE_RECURSIVE,
        };
  
        enum MutexError
        {
            MUTEX_ERROR_NO_ERROR=0,
            MUTEX_ERROR_NO_VALID_MUTEX,
            MUTEX_ERROR_BUSY,
            MUTEX_ERROR_DEADLOCK,
            MUTEX_ERROR_RECURSIVE_LIMIT,
            MUTEX_ERROR_DONT_OWN,
            MUTEX_ERROR_UNKNOWN,
        };
  
        class Mutex
        {
        public:
            explicit Mutex(const MutexType &mutexType=MUTEX_TYPE_NORMAL);
            ~Mutex();

            /**
             * \brief locks the Mutex
             * \return MUTEX_ERROR_NO_ERROR if the Mutex was successfully locked.
             *         Otherwise depending on the error one of 
             *         MUTEX_ERROR_NO_VALID_MUTEX, MUTEX_ERROR_RECURSIVE_LIMIT,
             *         MUTEX_ERROR_DEADLOCK, or MUTEX_ERROR_UNKNOWN is returned.
             */
            MutexError lock();

            /**
             * \brief tries to lock the mutex.
             * \return MUTEX_ERROR_NO_ERROR if the Mutex was successfully locked.
             *         MUTEX_ERROR_BUSY if the mutex couldn't be locked because it 
             *         is already locked. Otherwise depending on the error one of 
             *         MUTEX_ERROR_NO_VALID_MUTEX, MUTEX_ERROR_RECURSIVE_LIMIT,
             *         or MUTEX_ERROR_UNKNOWN is returned.
             *
             * This method tries to lock the Mutex but does not block to do so.
             * If the mutex is not held by anyone it is locked and MUTEX_ERROR_NO_ERROR
             * is returned. If the mutex is currently in locked state MUTEX_ERROR_BUSY
             * is returned. 
             */
            MutexError tryLock();

            MutexError unlock();
            inline MutexType getMutexType() const
                { return mutexType; }

        private:
            // disallow copying
            Mutex(const Mutex &);
            Mutex &operator=(const Mutex &);

            void* getHandle();

            PthreadMutexWrapper *myMutex;
            MutexType mutexType;

            friend class WaitCondition;

        }; // end of class Mutex
  
    } // end of namespace utils
} // end of namespace mars

