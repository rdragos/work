def myf2(P1):
    P2 = (1 - P1)
    return 10000.0 * P1 * (2.0 * P2 + 1.0)

def myf(P1):
    P2 = float(1 - P1)
    return 10000.0 * P1 * (2.0 * P2 + 1.0)


test = input()
for i in range(test):
    x = input()
    print float(max(myf(x), myf(1-x)))

    
