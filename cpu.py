#!/usr/bin/env python
# encoding: utf-8

import time
import json
import requests


DB_INFLUXDB = "db1"
USER_INFLUXDB = "user1"
PWD_INFLUXDB = "pwd1"
HOST_INFLUXDB = "192.168.0.192:8086"

def main():
    while True:
        timestamp = int(time.time())
        with open('/proc/loadavg', 'rb') as proc_fd:
            loadavg = proc_fd.read().split(' ')[:3]
            cpu_load = [float(el) for el in loadavg]
            print cpu_load
            obj = [{"name": "cpu_load",
                        "columns": ["time", "l1", "l5", "l15"],
                        "points": [
                            [timestamp, cpu_load[0], cpu_load[1], cpu_load[2]]
                        ]
                    }, ]
            url = "/db/%s/series?u=%s&p=%s" % (DB_INFLUXDB, USER_INFLUXDB, PWD_INFLUXDB)
            api_url = "http://%s%s" % (HOST_INFLUXDB, url)
            rsp = requests.post(api_url, data=json.dumps(obj))
        time.sleep(5)

if __name__ == '__main__':
    main()
