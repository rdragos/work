c = "0000 aaaa 0000 bbbb 0000 cccc 0000 dddd"
bX = "dbb1 f04f 2d5a 42e1 a554 4916 51af a669"
bY = "13ae d689 294a a168 bbf3 57a2 522b 3be9"

BIT = 1

def convert(x):
	acc = 0
	for item in x.split(' '):
		acc = acc * (2**16) + int(item, 16)
	return acc

c =  convert(c)
bX = convert(bX)
bY = convert(bY)

print len(bin(bX))-2
sX = bX ^ c
sY = bY ^ c

import random

random.seed(21321313)

def get_bin(x):
	return bin(x)[2:][::-1]

def safe_retrieve(basis, Y):
	while 1:
		j = 0
		for b in range(7):
			take = random.randint(0, 1)
			j += (2**b)*take

		k = j ^ basis

		r = int(Y[basis]) ^ int(Y[j]) ^ BIT
		if r != int(Y[k]):
			print "try again"
			continue
		else:
			return j, k


def decode(Y):
	# Y is in bit form
	# print "decoding:"
	# print(Y)
	X = [0] * 8

	while len(Y) < 128:
		Y += "0"
	for i in range(128):
		for j in range(128):
			k = (i ^ j)
			s = int(Y[i]) ^ int(Y[j]) ^ BIT
			if s != int(Y[k]):
				print "omg ", i, j, k

	for i in range(7):
		ei = 2**i
		j, k = safe_retrieve(ei, Y)
		Yj = int(Y[j])
		Yk = int(Y[k])

		X[i] = (Yj ^ Yk)

	X[7] = BIT
	return X

class Solver(object):
	def __init__(self):
		self.result = 0

	def extend(self, posbit, curlist, kbin):
		if posbit == 8:
			tmp = 0
			nr = 0
			for i in range(8):
				tmp ^= curlist[7-i] * kbin[i]
			self.result += (2**self.hits)*tmp
			self.hits += 1
		else:
			for k in range(2):
				curlist[posbit] = k
				self.extend(posbit+1, curlist, kbin)

	def encode(self, klist):
		self.result = 0
		self.hits = 0

		clist = [0] * 8
		clist[0] = BIT

		self.extend(1, clist, klist)
		return self.result


def diff(a, b):
	a = get_bin(a)
	b = get_bin(b)
	while len(a) < 128:
		a += "0"
	while(len(b)) < 128:
		b += "0"

	differ = 0
	for i in range(128):
		if a[i] != b[i]:
			differ += 1

	return differ

print "sX: ", sX
Encoder = Solver()

k1 = decode(get_bin(sX))
k2 = decode(get_bin(sY))

ext1 = Encoder.encode(k1)
ext2 = Encoder.encode(k2)

print "Difference with actual key:"
print diff(ext1 ^ c, bX)
print diff(ext2 ^ c, bY)

md1 = 10000
md2 = 10000


key1 = key2 = None

for k in range(2**7):
	bk = get_bin(k)
	#convert chars to integers
	bk1 = [int(_) for _ in bk]
	while len(bk1) < 7:
		bk1 += [0]
	bk1 = bk1 + [BIT]
	ext = Encoder.encode(bk1)

	assert decode(get_bin(ext)) == bk1
	# print "differences\n"
	d1 = diff((ext ^ c), bX)
	d2 = diff((ext ^ c), bY)

	if d1 < md1:
		md1 = d1
		print md1
		key1 = bk1
	if d2 < md2:
		md2 = d2
		key2 = bk1

print md1, key1
print md2, key2

# actual_key = [1, 1, 0, 1, 1, 0, 1, 1]

# print(key1)

# def pbin(v):
# 	v2 = get_bin(v)
# 	while len(v2) < 128:
# 		v2 += "0"
# 	return v2

# ext1 = Encoder.encode(key1)
# print(hex(ext1^c))
# print(hex(bX))

# a1 = pbin(ext1 ^ c)
# b1 = pbin(bX)

# print(pbin(ext1 ^ c))
# print(pbin(bX))

# res = ""
# for i in range(128):
# 	if a1[i] != b1[i]:
# 		res += "1"
# 	else:
# 		res += "0"
# print(res)
	# print diff( (ext ^ c), bY)

# print(hex(Encoder.encode(k1)))

# extend(1, [0] * 8, 
# print(decode(bin(sX)[2:]))
# print(decode(bin(sY)[2:]))

# print(c, bX, bY)