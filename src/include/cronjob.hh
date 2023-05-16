#ifndef _CRONJOB_H
#define _CRONJOB_H

#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

#include "CronTime.hh"

namespace Cron {
typedef std::function<void(void)> PassFunction;

class Cronjob {
private:
    std::thread cron_thread;

    /**
     * @param function execudeable function. Use lambda function
     */
    void add_cron(PassFunction function, CronTime time);

    std::thread& get_thread();

public:
    Cronjob();
    /**
     * init cron job
     *
     * @param function execudeable function. Use lambda function
     * @param time cron time in struct
     */
    Cronjob(CronTime time, PassFunction function);

    /**
     * waiting for execude successfuly.
     */
    void wait();
};

Cronjob::Cronjob(CronTime time, PassFunction function)
{
    if (time.GetSeconds() <= 0) {
        std::cerr << "second must be not null, char or 0" << std::endl;
    } else {
        cron_thread = std::thread(&Cronjob::add_cron, this, function, time);
    }
}

void Cronjob::add_cron(PassFunction function, CronTime time)
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(time.GetSeconds()));
        function();
    }
}

std::thread& Cronjob::get_thread() { return this->cron_thread; }

void Cronjob::wait() { return this->cron_thread.join(); }
}

#endif //_CRONJOB_H
