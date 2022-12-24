# Cron Jobs scheduler

install command

```bash
make install
```

### Cron jobs overview.

Single usege of cron job:

```c++
cron::cronjob single_cron(
	cron::CronTime(0, 0, 1),
	[](void) {
		std::cout << "cron executed" << std::endl;
	});

// your code...

single_cron.wait();
```

CronTime struct overview: `CronTime(hour, minute, second)`. The `wait` function waits for cron to shut down.

Usege of cron jobs scheduler:

```c++
cron::schedule::schedule sch;

sch.add(
	cron::CronTime(0, 0, 4),
	[](void) {
		std::cout << "schedule executed" << std::endl;
	});

// your code...

sch.wait();
```

Alawys use lambda function.
