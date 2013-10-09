
import sys

R = raw_input

while (1):
    try:
        m, n = map(int, R().split())
    except EOFError:
        break
    print abs(m - n)



