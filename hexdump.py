#!/usr/bin/env python
# encoding: utf-8

import sys


def main():
    content = file(sys.argv[1]).read()
    res = 'static unsigned char file_content[] = {'
    for pos, bit in enumerate(content):
        if pos % 16 == 0:
            res += '\n'
        res += '0x%02x, ' % ord(bit)
    res += "};"
    with open(sys.argv[2], 'wt') as f1:
        f1.write(res)
    print 'Over~'


if __name__ == '__main__':
    main()
