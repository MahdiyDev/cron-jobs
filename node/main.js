'use strict'

const { Cronjob, CronTime } = require("./build/Release/Cronjob.node")


const time = new CronTime()

const a = time.SetWeaks(3);

console.log(a.GetSeconds());

const cron = new Cronjob(time)

console.log(cron.time);