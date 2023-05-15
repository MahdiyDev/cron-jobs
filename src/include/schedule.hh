#ifndef _SCHEDULE_H
#define _SCHEDULE_H

#include "cronjob.hh"
#include <cstddef>
#include <vector>

namespace Cron {
namespace Schedule {
    struct ScheduleCron {
        PassFunction function;
        CronTime time;

        ScheduleCron(CronTime _time, PassFunction _function)
        {
            time = _time;
            function = _function;
        }
    };

    class Schedule {
    private:
        int intreval { 1 };
        std::vector<ScheduleCron> schedules;
        std::vector<CronTime> schedules_temp;

        void schedule_checker();

    public:
        void add(CronTime time, PassFunction function);

        void wait();
    };

    void Schedule::schedule_checker()
    {
        size_t i { 0 };
        for (; i < schedules.size(); i++) {
            auto& time = schedules[i].time;
            auto& function = schedules[i].function;

            time.SetSeconds(time.GetSeconds() - 1);

            if (time.GetSeconds() == 0) {
                function();
                time = schedules_temp[i];
            }
        }
    }

    void Schedule::add(CronTime time, PassFunction function)
    {
        auto second = time.GetSeconds();

        if (second == 0)
            time.SetSeconds(1);

        ScheduleCron new_cron = ScheduleCron(time, function);

        schedules.push_back(new_cron);
        schedules_temp.push_back(new_cron.time);
    }

    void Schedule::wait()
    {
        CronTime time;
        time.SetSeconds(1);
        Cronjob newCron(time, [this](void) { this->schedule_checker(); });
        newCron.wait();
    }
}
}

#endif //_SCHEDULE_H
