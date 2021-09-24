import random
from math import log

a = random.randint(0, 2**63)
b = random.randint(0, 2**63)
#a = 2**64-1
#b = 1

def bit_and(x, y):
    assert len(x) == len(y)
    return [x[i] & y[i] for i in range(len(x))]


def bit_xor(x, y):
    assert len(x) == len(y)
    return [x[i] ^ y[i] for i in range(len(x))]


def get64(x):
    return [ (x >> i) & 1 for i in range(64) ]


def getint(x):
    assert len(x) == 64
    return sum(2 ** i * x[i] for i in range(len(x)))

def to_str(x):
    assert len(x) == 64
    return "".join(str(x[63-i]) for i in range(64))

def bit_adder(a, b):
#    print("Adding ", str(a), " ", str(b))
    a_bin = bin(a)[2:][::-1]
    b_bin = bin(b)[2:][::-1] 
    a_bin = [int(_) for _ in a_bin]
    b_bin = [int(_) for _ in b_bin]

    n = 64

    while len(a_bin) < n:
        a_bin.append(0)
    
    while len(b_bin) < n:
        b_bin.append(0)

    print(f"a = \n{to_str(a_bin)}")
    print(f"b = \n{to_str(b_bin)}")

    N = int(log(n, 2))

    G = bit_and(a_bin, b_bin)
    P = bit_xor(a_bin, b_bin)

    for i in range(N):
        G1 = getint(G) << (2 ** i)
        P1 = getint(P) << (2 ** i)
        P1 = P1 + (2**(2**i) - 1)

        G = bit_xor(G, bit_and(P, get64(G1)))
        P = bit_and(P, get64(P1))

    C = getint(G) << 1
#    print("Carry: ", C, to_str(get64(C)))
#    print("Carry bit: ", get64(C)[-1])
    P = bit_xor(a_bin, b_bin)
    z = bit_xor(get64(C), P)

    # G[i,j] = G[i,k+1] xor (P[i,k+1] and G[k,j])
    # P[i,j] = P[i,k+1] and P[k,j]

#    print(z)
    return z


for i in range(1):
    a = random.randint(0, 2**64)
    b = random.randint(0, 2**64)
    assert(getint(bit_adder(a, b)) == (a+b) % 2**64)
