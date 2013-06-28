#!/usr/bin/env python

try:
    from time import monotonic
except ImportError:
    print('Please use Python 3.3 or better for this script.')
    raise SystemExit(1)


def main():
    d = {}
    start = monotonic()
    for i in range(1000000):
        d[i] = i
    end = monotonic()
    elapsed_nano = (end - start) * 1e6
    print('Elapsed monotonic time: {0} ns'.format(elapsed_nano))


if __name__ == '__main__':
    raise SystemExit(main())
