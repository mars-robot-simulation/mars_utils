#pragma once

#include <cstddef> // for std::size_t
#include <list>

#include "Mutex.h"

namespace mars
{
    namespace utils
    {

        struct PthreadThreadWrapper;

        class Thread
        {
        public:
            Thread();
            virtual ~Thread();

            /**
             * \brief Starts the execution of this Thread.
             * This will start new thread in which the run method will be executed.
             * This method will return as soon as the thread has been set up.
             * \see run(), wait(), wait(unsigned long)
             */
            void start();

            /**
             * \brief Tries to cancel the Thread.
             * \param block If \c true cancel will only return when the 
             *              Thread stopped.
             * The Thread can only be canceled at certain cancellation points.
             * Many IO related system calls are cancellation points and so 
             * is Thread::wait.  You can manually add cancellation points to 
             * you run method by calling Thread::setCancelationPoint().
             * \see setCancellationPoint()
             */
            void cancel(bool block=false);

            /**
             * \brief Adds a cancellation point to your run method.
             * \see cancel
             */
            void setCancellationPoint();

            /**
             * \brief stops execution until the thread has finished.
             * \see wait(unsigned long), cancel()
             */
            bool wait();
            bool join();

            /**
             * \brief puts the Thread to sleep for a specified amount of time.
             * \param timeoutMilliseconds The time the Thread shall sleep in 
             *                            milliseconds
             * \see wait(), cancel()
             */
            bool wait(unsigned long timeoutMilliseconds);

            /**
             * \brief returns \c true if the Thread is running.
             * returns \c true if the Thread was \link start started \endlink and
             * has not terminated (i.e. the run method has not returned yet) and
             * was not canceled. returns \c false otherwise.
             * \see isFinished()
             */
            bool isRunning() const;

            /**
             * \see isRunning()
             */
            bool isFinished() const;
            void setStackSize(std::size_t stackSize);
            std::size_t getStackSize() const;
            bool isCurrentThread() const;
            static Thread* getCurrentThread();

            static void cancelAll(bool block=false);

        protected:
            /**
             * \brief The thread will execute this method once it has been 
             *        \link start() started \endlink.
             * \see start(), cancel(), wait(), wait(unsigned long)
             */
            virtual void run() = 0;

            /**
             * causes the current thread to sleep for \arg msec millisecond.
             */
            static void msleep(unsigned long msec);

        private:
            // disallow copying
            Thread(const Thread &);
            Thread &operator=(const Thread &);
    
            static void* runHelper(void *context);
            static void cleanupHandler(void *context);

            PthreadThreadWrapper *myThread;

            std::size_t myStackSize;
            bool running;
            bool finished;
            static Mutex threadListMutex;
            static std::list<Thread*> threads;
        }; // end of class Thread

    } // end of namespace utils
} // end of namespace mars
