#!/usr/bin/python3

import sys


def get_heap(pid):
    """Identify the start and end addresses for the heap of a process."""
    # TODO: handle any io errors?
    with open("/proc/{pid}/maps".format(pid=pid), 'r') as maps:
            while True:
                mapping = maps.readline()
                if not mapping:
                    # EOF presumably reached
                    sys.exit(
                        "ERROR: Could not identify heap in /proc/{pid}/maps."
                        .format(pid=pid)
                    )

                if mapping[-8:] == ' [heap]\n':
                    mapping = mapping.split('-')
                    heap_start = int(mapping[0], 16)
                    heap_end = int(mapping[1].split(' ')[0], 16)
                    return (heap_start, heap_end)


def main():
    """Replace a string in heap of given process."""
    pid = sys.argv[1]
    search = sys.argv[2]
    replace = sys.argv[3]

    heap_start, heap_end = get_heap(pid)

    with open("/proc/{pid}/mem".format(pid=pid), 'r+b') as mem:
        mem.seek(heap_start)
        # heap = mem.read(heap_end - heap_start).decode("utf-")
        heap = mem.read(heap_end - heap_start).decode("ISO-8859-1")
        i = heap.find(search)
        if i == -1:
            sys.exit("ERROR: '{search}' not found in heap."
                     .format(search=search))

        mem.seek(heap_start + i)
        mem.write(replace.encode("ISO-8859-1"))

main()
