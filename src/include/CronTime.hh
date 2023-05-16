#ifndef _CRONTIME_H
#define _CRONTIME_H

namespace Cron {
class CronTime {
private:
    int weaks { 0 };
    int days { 0 };
    int hours { 0 };
    int mins { 0 };
    int secs { 0 };

public:
    CronTime& SetWeaks(int _weaks);
    CronTime& SetDays(int _days);
    CronTime& SetHours(int _hours);
    CronTime& SetMinutes(int _mins);
    CronTime& SetSeconds(int _secs);

    int GetWeaks();
    int GetDays();
    int GetHours();
    int GetMinutes();
    int GetSeconds();
};

CronTime& CronTime::SetWeaks(int _weaks)
{
    this->weaks = _weaks;
    return *this;
}

CronTime& CronTime::SetDays(int _days)
{
    this->days = _days;
    return *this;
}

CronTime& CronTime::SetHours(int _hours)
{
    this->hours = _hours;
    return *this;
}

CronTime& CronTime::SetMinutes(int _mins)
{
    this->mins = _mins;
    return *this;
}

CronTime& CronTime::SetSeconds(int _secs)
{
    this->secs = _secs;
    return *this;
}

int CronTime::GetWeaks()
{
    return weaks + (days * 7) + (hours / 24) + (mins / 60) + (secs / (60 * 60));
}

int CronTime::GetDays()
{
    return (weaks * 7) + days + (hours / 24) + (mins / 60) + (secs / (60 * 60));
}

int CronTime::GetHours()
{
    return (weaks * 7 * 24) + (days * 24) + hours + (mins / 60) + (secs / (60 * 60));
}

int CronTime::GetMinutes()
{
    return (weaks * 7 * 24 * 60) + (days * 24 * 60) + (hours * 60) + mins + (secs / 60);
}

int CronTime::GetSeconds()
{
    return (weaks * 7 * 24 * 60 * 60) + (days * 24 * 60 * 60) + (hours * 60 * 60 * 60) + (mins * 60) + secs;
}

}

#endif //_CRONTIME_H