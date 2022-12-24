#ifndef _SCHEDULE_H
#define _SCHEDULE_H

#include "cronjob.hh"
#include <cstddef>
#include <vector>

namespace cron {
namespace schedule {
    struct ScheduleCron {
        SECONDS second;
        PassFunction function;

        ScheduleCron(SECONDS _second, PassFunction _function)
        {
            second = _second;
            function = _function;
        }
    };

    class schedule {
    private:
        cronjob cron;
        int intreval { 1 };
        std::vector<ScheduleCron> schedules;
        std::vector<SECONDS> schedules_temp;

    public:
        schedule()
            : cron(CronTime(0, 0, 1),
                [this](void) { this->schedule_checker(); }) {};

        void schedule_checker();

        void add(CronTime time, PassFunction function);

        void wait();
    };

    void schedule::schedule_checker()
    {
        for (size_t i = 0; i < schedules.size(); i++) {
            // std::cout << schedules[i].second << "\n";

            schedules[i].second -= 1;

            if (schedules[i].second == 0) {
                schedules[i].function();
                schedules[i].second = schedules_temp[i];
            }
        }
    }

    void schedule::add(CronTime time, PassFunction function)
    {
        SECONDS second = cron.parse_string_time(time);

        if (second == 0)
            second = 1;

        ScheduleCron new_cron = ScheduleCron(second, function);

        schedules.push_back(new_cron);
        schedules_temp.push_back(new_cron.second);
    }

    void schedule::wait() { return this->cron.get_thread().join(); }
}
}

#endif //_SCHEDULE_H
