#include <iostream>

#include "include/cronjob.hh"
#include "include/schedule.hh"

int main(int argc, char const* argv[])
{
    cron::CronTime time(0, 0, 2);

    cron::schedule::schedule sch;

    sch.add(time, [] { std::cout << "Hello\n"; });
    sch.add(cron::CronTime(0, 0, 4), [] { std::cout << "Hello - 4\n"; });

    sch.wait();

    return 0;
}
