#!/usr/bin/python3

with open("/proc/1930/mem", 'r') as mem:
    mem.seek(0x00eb2000)
    heap = mem.read(0x00ed3000 - 0x00eb2000)
    print heap

