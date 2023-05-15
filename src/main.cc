#include <iostream>

#include "include/CronTime.hh"
#include "include/cronjob.hh"
#include "include/schedule.hh"

int main(int argc, char const* argv[])
{

    Cron::CronTime time;

    time.SetSeconds(3);

    std::cout << "Seconds: " << time.GetSeconds() << std::endl;

    Cron::Schedule::Schedule sch;

    sch.add(time, [](void) {
        std::cout << "Cron executed! - 1" << std::endl;
    });

    time.SetSeconds(2);

    sch.add(time, [](void) {
        std::cout << "Cron executed! - 2" << std::endl;
    });

    sch.wait();

    return 0;
}
