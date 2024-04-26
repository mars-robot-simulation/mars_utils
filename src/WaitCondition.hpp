#pragma once


namespace mars
{
    namespace utils
    {

        struct PthreadConditionWrapper;
        class Mutex;

        enum WaitConditionError
        {
            WAITCOND_NO_ERROR=0,
            WAITCOND_TIMEOUT,
            WAITCOND_UNSPECIFIED,
            WAITCOND_INTERNAL_ERROR,
            WAITCOND_UNKNOWN,
        };
  
        class WaitCondition
        {
        public:
            explicit WaitCondition();
            ~WaitCondition();

            /**
             */
            WaitConditionError wait(Mutex *mutex);
            WaitConditionError wait(Mutex *mutex, unsigned long timeoutMilliseconds);

            /**
             */
            WaitConditionError wakeOne();

            WaitConditionError wakeAll();

        private:
            // disallow copying
            WaitCondition(const WaitCondition &);
            WaitCondition &operator=(const WaitCondition &);

            PthreadConditionWrapper *myWaitCondition;

        }; // end of class WaitCondition
  
    } // end of namespace utils
} // end of namespace mars

