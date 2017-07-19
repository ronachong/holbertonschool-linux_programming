#!/usr/bin/python3

with open("/proc/2440/mem", 'r') as mem:
    mem.seek(0x020d0000)
    heap = mem.read(0x020d0000 - 0x020d0000)
    print heap

