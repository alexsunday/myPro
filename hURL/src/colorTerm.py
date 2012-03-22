#!/usr/bin/env python
# -*- coding: UTF-8 -*-

'''
2010.07.29
''' 

import ctypes
import platform
import sys

# Constants from the Windows API
STD_OUTPUT_HANDLE    = -11
FOREGROUND_BLUE      = 0x0001
FOREGROUND_GREEN     = 0x0002
FOREGROUND_RED       = 0x0004
FOREGROUND_INTENSITY = 0x0008
BACKGROUND_BLUE      = 0x0010
BACKGROUND_GREEN     = 0x0020
BACKGROUND_RED       = 0x0040
BACKGROUND_INTENSITY = 0x0080

ANSI_CODES = {
    "reset"     : "\x1b[0m",
    "bold"      : "\x1b[01m",
    "teal"      : "\x1b[36;06m",
    "turquoise" : "\x1b[36;01m",
    "fuscia"    : "\x1b[35;01m",
    "purple"    : "\x1b[35;06m",
    "blue"      : "\x1b[34;01m",
    "darkblue"  : "\x1b[34;06m",
    "green"     : "\x1b[32;01m",
    "darkgreen" : "\x1b[32;06m",
    "yellow"    : "\x1b[33;01m",
    "brown"     : "\x1b[33;06m",
    "red"       : "\x1b[31;01m",
}

class DbWinColorConsole:
    def __init__(self):
        self.kernel = ctypes.windll.kernel32
        self.handle = self.kernel.GetStdHandle(STD_OUTPUT_HANDLE)
        self.reset = self.get_csbi_attributes()

        self.blue = FOREGROUND_BLUE|FOREGROUND_INTENSITY
        self.green = FOREGROUND_GREEN|FOREGROUND_INTENSITY
        self.red = FOREGROUND_RED|FOREGROUND_INTENSITY
        self.yellow = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY

    def setColor(self, c):
        self.kernel.SetConsoleTextAttribute(self.handle, c)

    def resetColor(self):
        self.kernel.SetConsoleTextAttribute(self.handle, self.reset)

    def get_csbi_attributes(self):
        # Based on IPython's winconsole.py, written by Alexander Belchenko
        import struct
        csbi = ctypes.create_string_buffer(22)
        res = ctypes.windll.kernel32.GetConsoleScreenBufferInfo(self.handle, csbi)
        assert res

        (bufx, bufy, curx, cury, wattr, left, top, right, bottom, 
                maxx, maxy) = struct.unpack("hhhhHhhhhhh", csbi.raw)
        return wattr

class DbLinuxColorConsole:
    def __init__(self):
        self.reset = ANSI_CODES["reset"]
        self.bold = ANSI_CODES["bold"]
        self.teal = ANSI_CODES["teal"]     
        self.turquoise = ANSI_CODES["turquoise"]
        self.fuscia = ANSI_CODES["fuscia"]
        self.purple = ANSI_CODES["purple"]
        self.blue = ANSI_CODES["blue"]
        self.darkblue = ANSI_CODES["darkblue"]
        self.green = ANSI_CODES["green"]
        self.darkgreen = ANSI_CODES["darkgreen"]
        self.yellow = ANSI_CODES["yellow"]
        self.brown = ANSI_CODES["brown"]
        self.red = ANSI_CODES["red"]
    def setColor(self, c):
        sys.stdout.write(c)
    def resetColor(self):
        sys.stdout.write(self.reset)

if platform.system() == 'Windows':
    DCC = DbWinColorConsole()
else:
    DCC = DbLinuxColorConsole()

if __name__ == '__main__':
    DCC.setColor(DCC.blue)
    print "test for color"
    DCC.setColor(DCC.green)
    print "test for color"
    DCC.setColor(DCC.red)
    print "test for color"
    DCC.setColor(DCC.yellow)
    print "test for color"
    DCC.resetColor()
