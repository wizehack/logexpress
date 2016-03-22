#ifndef TIMER_H_
#define TIMER_H_

#include <glib-2.0/glib.h>

namespace expr {
    class Timer {
        public:
            Timer();
            ~Timer();
            void set_alarm(int interval);

        public:
            static void alarm_handler(int sig);
            static gpointer _timer_thread(void* data);

        private:
            static int _intval;
    };
}

#endif /*TIMER_H_*/
