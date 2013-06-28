#!/usr/bin/env python

try:
    from time import monotonic
except ImportError:
    print('Please use Python 3.3 or better for this script.')
    raise SystemExit(1)


class timing(object):
    def __enter__(self):
        self._start = monotonic()

    def __exit__(self, type_, value, traceback):
        end = monotonic()
        elapsed_nano = (end - self._start) * 1e6
        print('{0} ns'.format(elapsed_nano))


class bench(object):
    _benches = []

    def __init__(self, func):
        self._benches.append(func)
        self._func = func

    def __call__(self):
        self._func()


@bench
def put():
    d = {}
    with timing():
        for i in range(1000000):
            d[i] = i


@bench
def get():
    d = dict([(i, i) for i in range(1000000)])
    with timing():
        for i in range(1000000):
            d[i]


def main():
    print('''Python 3.3 dictionary benchmark
All times are elapsed monotonic time.
''')
    for func in bench._benches:
        print(func.__name__, end=': ')
        func()

    print()


if __name__ == '__main__':
    raise SystemExit(main())
