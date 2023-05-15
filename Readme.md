# Cron Jobs scheduler

install command

```bash
make install
```

### Cron jobs overview.

Usege of `CronTime`:
```cpp
CronTime time;

time.SetMinutes(10) // sets by minutes

time.GetSeconds() // return converts to seconds
```
Units of CronTime:
- weak
- day
- hour
- minute
- second

Single usege of cron job:

```cpp
CronTime time;

time.SetMinutes(10) 

cron::cronjob single_cron(
	time,
	[](void) {
		std::cout << "cron executed" << std::endl;
	});

// your code...

single_cron.wait();
```

The `wait` function waits for cron to shut down.

Usege of cron jobs scheduler:

```cpp
cron::schedule::schedule sch;

CronTime time;

time.SetMinutes(10) 

sch.add(
    time,
    [](void) {
        std::cout << "schedule executed" << std::endl;
    });

// your code...

sch.wait();
```

Alawys use lambda function.
