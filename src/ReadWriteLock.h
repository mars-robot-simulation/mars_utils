#pragma once

namespace mars
{
    namespace utils
    {

        struct PthreadReadWriteLockWrapper;

        class ReadWriteLock
        {
        public:
            ReadWriteLock();
            ~ReadWriteLock();
    
            void lockForRead();
            void lockForWrite();
            bool tryLockForRead();
            bool tryLockForWrite();
            void unlock();
        private:
            // disallow copying
            ReadWriteLock(const ReadWriteLock &);
            ReadWriteLock &operator=(const ReadWriteLock &);

            PthreadReadWriteLockWrapper *myReadWriteLock;

        }; // end of class ReadWriteLock

    } // end of namespace utils
} // end of namespace mars

