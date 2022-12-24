#ifndef _CRONJOB_H
#define _CRONJOB_H

#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

namespace cron {
typedef unsigned long long SECONDS;
typedef std::function<void(void)> PassFunction;

struct CronTime {
    int hour { 0 };
    int min { 0 };
    int sec { 0 };

    CronTime(int _hour, int _min, int _sec)
        : hour(_hour)
        , min(_min)
        , sec(_sec)
    {
    }
};

class cronjob {
private:
    std::thread cron_thread;
    SECONDS seconds { 0 };

    /**
     * @param function execudeable function. Use lambda function
     */
    void add_cron(PassFunction function);

public:
    /**
     * init cron job
     *
     * @param function execudeable function. Use lambda function
     * @param time cron time in struct
     */
    cronjob(CronTime time, PassFunction function);
    /**
     * parsing time form string
     */
    SECONDS parse_string_time(CronTime time);

    std::thread& get_thread();
    /**
     * waiting for execude successfuly.
     */
    void wait();
};

cronjob::cronjob(CronTime time, PassFunction function)
{
    seconds = parse_string_time(time);
    if (seconds <= 0) {
        std::cerr << "second must be not null, char or 0" << std::endl;
    } else {
        cron_thread = std::thread(&cronjob::add_cron, this, function);
    }
}

SECONDS cronjob::parse_string_time(CronTime time)
{
    SECONDS temp_sec { 0 };

    if (time.hour > 0) {
        temp_sec += time.hour * 60 * 60;
    }
    if (time.min > 0) {
        temp_sec += time.min * 60;
    }
    if (time.sec > 0) {
        temp_sec += time.sec;
    }

    return temp_sec;
}

void cronjob::add_cron(PassFunction function)
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
        function();
    }
}

std::thread& cronjob::get_thread() { return this->cron_thread; }

void cronjob::wait() { return this->cron_thread.join(); }
}

#endif //_CRONJOB_H
