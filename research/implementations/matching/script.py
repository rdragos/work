

f = open("parties.in", "r")
all_lines = f.readlines();
res = list()

for line in all_lines:
    item = line.rstrip('\n').split(' ')
    litem = [int(_) for _ in item]
    res.append(sum( 2**(temp - 1) for temp in litem))
    #print(item)

print "{" + ",".join(str(_) for _ in res) + "}"
