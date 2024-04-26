#pragma once

namespace mars
{
    namespace utils
    {

        class Mutex;
  
        class MutexLocker
        {
        public:
            explicit MutexLocker(Mutex *mutex);
            ~MutexLocker();
    
            void unlock();
            void relock();
        private:
            // disallow copying
            MutexLocker(const MutexLocker &);
            MutexLocker &operator=(const MutexLocker &);

            Mutex *myMutex;
            bool isLocked;
        }; // end of class MutexLocker

    } // end of namespace utils
} // end of namespace mars

