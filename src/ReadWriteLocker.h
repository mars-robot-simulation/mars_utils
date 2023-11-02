#pragma once

namespace mars
{
    namespace utils
    {

        enum ReadWriteLockMode
        {
            READWRITELOCK_MODE_READ,
            READWRITELOCK_MODE_WRITE,
        };

        class ReadWriteLock;

        class ReadWriteLocker
        {
        public:
            ReadWriteLocker(ReadWriteLock *rwLock, ReadWriteLockMode mode);
            ~ReadWriteLocker();
            void unlock();
            void relock();
        private:
            // disallow copying
            ReadWriteLocker(const ReadWriteLocker &);
            ReadWriteLocker &operator=(const ReadWriteLocker &);

            bool isLocked;
            ReadWriteLock *myReadWriteLock;
            ReadWriteLockMode myMode;
        }; // end of class ReadWriteLocker

    } // end of namespace utils
} // end of namespace mars
