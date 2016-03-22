#include <signal.h>
#include <unistd.h>
#include <iostream>
#include "timer.h"
#include "confData.h"
#include "messageQueue.h"

int expr::Timer::_intval = -1;

expr::Timer::Timer(){}
expr::Timer::~Timer(){}

void expr::Timer::set_alarm(int interval)
{
    if(interval > 0)
    {
        Timer::_intval = interval;

        signal(SIGALRM, Timer::alarm_handler); // Install handler first,
        alarm(Timer::_intval); 
        while(Timer::_intval > 0){};
    }
}

void expr::Timer::alarm_handler(int sig)
{
    /*
    static int count = 0;
    std::cout << "alarm: " << count << std::endl;
    count++;
    */

    char* msg = g_strdup("sync");
    g_async_queue_push(expr::MessageQueue::getInstance()->get_listenerQueue(), static_cast<gpointer>(msg)); 
    alarm(Timer::_intval);
}

gpointer expr::Timer::_timer_thread(void* data)
{
    expr::Timer timer;
    timer.set_alarm(expr::ConfData::getInstance()->get_export_period());
    return NULL;
}
