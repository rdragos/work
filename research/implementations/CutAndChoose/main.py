import math
import sys

nbits = int(sys.argv[1])
upper_bound_c = int(sys.argv[2])
upper_bound_b = int(sys.argv[3])
sec_param = int(sys.argv[4])
n_parties = int(sys.argv[5])

# Usage: python main.py nbits_per_loop max_c mac_b stat_sec n_parties

# convention is n_parties / field_size / stat sec
def get_key(prefix, n_parties, field_size, stat_sec):
    return prefix + str(n_parties) + ";" + str(field_size) + ";" + str(stat_sec)

def add_comm_cost(cost_table, n_parties,
        field_size, stat_sec, cost):
    key = get_key("comm", n_parties, field_size, stat_sec)
    if key not in cost_table:
        cost_table.update({key:cost})

def add_time_cost(cost_table, n_parties,
        field_size, stat_sec, cost):
    key = get_key("time", n_parties, field_size, stat_sec)
    if key not in cost_table:
        cost_table.update({key:cost})

class LowGear(object):

    def add_known_costs(self):
        self.input_cost = dict()
        self.triple_cost = dict()
        # 2 parties
        # time: 36361
        # comm: 13.1711kb
        # \log{p} = 128, sec = 40
        add_comm_cost(self.triple_cost, 2, 128, 40, 26.3422)
        add_time_cost(self.triple_cost, 2, 128, 40, 0.0275019)

        add_comm_cost(self.input_cost, 2, 128, 64, 1.792)
        add_time_cost(self.input_cost, 2, 128, 40, 0.0018)

        # \log{p} = 128, sec = 64
        # 540056 inputs per second
        add_comm_cost(self.input_cost, 2, 128, 64, 2.048)
        add_time_cost(self.input_cost, 2, 128, 64, 0.0018)

        add_comm_cost(self.triple_cost, 2, 128, 64, 30.146)
        add_time_cost(self.triple_cost, 2, 128, 64, 0.033)

        # for -s 128 -f 128 numbers are computed using ESAT computers
        # \log{p} = 128, sec = 128
        add_comm_cost(self.input_cost, 2, 128, 128, 2.304)
        # 364238 inputs per second
        add_time_cost(self.input_cost, 2, 128, 128, 0.0028)

        add_comm_cost(self.triple_cost, 2, 128, 128, 33.38)
        add_time_cost(self.triple_cost, 2, 128, 128, 0.027)

        # \log{p} = 64, sec = 40
        # 705859 inputs per second
        add_comm_cost(self.input_cost, 2, 64, 40, 1.15209)
        add_time_cost(self.input_cost, 2, 64, 40, 0.0014)

        add_comm_cost(self.triple_cost, 2, 64, 40, 18.00)
        add_time_cost(self.triple_cost, 2, 64, 40, 0.0169)

        # from now on only communication costs
        # 3 parties
        add_comm_cost(self.input_cost, 3, 128, 64, 5.888)
        add_comm_cost(self.triple_cost, 3, 128, 64, 89.67)
        # 4 parties
        add_comm_cost(self.input_cost, 4, 128, 64, 11.520)
        add_comm_cost(self.triple_cost, 4, 128, 64, 178.572)
        # 5 parties
        add_comm_cost(self.input_cost, 5, 128, 64, 18.94)
        add_comm_cost(self.triple_cost, 5, 128, 64, 296.85)


    def __init__(self, n_parties, lgp, stat_sec):
        self.add_known_costs();
        self.n = n_parties
        self.lgp = lgp
        self.stat_sec = stat_sec

    def get_input(self, prefix, n_inputs):
        key = get_key(prefix, self.n, self.lgp, self.stat_sec)
        return self.input_cost[key] * n_inputs

    def get_triple(self, prefix, n_triples):
        key = get_key(prefix, self.n, self.lgp, self.stat_sec)
        return self.triple_cost[key] * n_triples

class MASCOT(object):

    def add_known_costs(self):
        self.input_cost = dict()
        self.triple_cost = dict()

        # 2 parties
        add_comm_cost(self.input_cost, 2, 128, 40, 0.384)
        add_comm_cost(self.triple_cost, 2, 128, 40, 360.44)

        add_comm_cost(self.input_cost, 2, 128, 64, 0.384)
        add_comm_cost(self.triple_cost, 2, 128, 64, 360.44)

        add_time_cost(self.triple_cost, 2, 128, 65, 0.2065)
        # 3 parties
        add_comm_cost(self.input_cost, 3, 128, 64, 1.024)
        add_comm_cost(self.triple_cost, 3, 128, 64, 1081.32)
        # 4 parties
        add_comm_cost(self.input_cost, 4, 128, 64, 1.92)
        add_comm_cost(self.triple_cost, 4, 128, 64, 2162.64)
        # 5 parties
        add_comm_cost(self.input_cost, 5, 128, 64, 3.072)
        add_comm_cost(self.triple_cost, 5, 128, 64, 3604.4)


    def __init__(self, n_parties, lg2, stat_sec):
        self.add_known_costs();
        self.n = n_parties
        self.lg2 = lg2
        self.stat_sec = stat_sec

    def get_input(self, prefix, n_inputs):
        key = get_key(prefix, self.n, self.lg2, self.stat_sec)
        return self.input_cost[key] * n_inputs

    def get_triple(self, prefix, n_triples):
        key = get_key(prefix, self.n, self.lg2, self.stat_sec)
        return self.triple_cost[key] * n_triples

class DABit(object):
    def __init__(self, cnc_param, bucket_size, num_parties, size_fp, size_f2):
        self.num_inputs_p = cnc_param * bucket_size * nbits
        self.num_inputs_2 = cnc_param * bucket_size * nbits
        self.num_inputs_p *= num_parties
        self.num_inputs_2 *= num_parties

        self.num_triples_p = (num_parties - 1) * bucket_size * nbits
        self.num_triples_p += (bucket_size - 1) * nbits
        self.num_triples_2 = 0

        self.mascot = MASCOT(num_parties, size_f2, 64)
        self.low_gear = LowGear(num_parties, size_fp, 64)

        self.num_parties = num_parties

        self.internalize_cost()

    def internalize_cost(self):
        mascot = self.mascot
        low_gear = self.low_gear

        cost2k = 0
        cost2k += mascot.get_input("comm", self.num_inputs_2)
        cost2k += mascot.get_triple("comm", self.num_triples_2)

        self.cost2k = cost2k

        costp = 0
        costp += low_gear.get_input("comm", self.num_inputs_p)
        costp += low_gear.get_triple("comm", self.num_triples_p)

        self.costp = costp

        costp_time = 0
        costp_time = low_gear.get_input("time", self.num_inputs_p)
        costp_time += low_gear.get_triple("time", self.num_triples_p)

        self.costp_time = costp_time


    def get_comm(self):
        cost = self.cost2k + self.costp;
        return cost

    def print_cost_per_dab(self):
        print "inputs_p: ", self.num_inputs_p / (1.0 * nbits),
        print "triples_p: ", self.num_triples_p / (1.0 * nbits)

    def __str__(self):
        # prints cost per party
        cost2k = self.cost2k
        cost2k /= 1.0 * self.num_parties * nbits
        costp = self.costp
        costp /= 1.0 * self.num_parties * nbits
        costp_time = self.costp_time
        costp_time /= 1.0 * nbits

        cost2k = str(cost2k)
        costp = str(costp)
        costp_time = str(costp_time)
        serialized = "cost2k: " + cost2k + " "
        serialized += "costp: " + costp + " "
        serialized += "costp_time: " + costp_time
        return serialized



def choose(n, k):
    fact = [1] * (n-k+1)
    for i in range(1, n-k+1):
        fact[i] = fact[i - 1] * i

    nominator = 1
    for i in range(k+1, n+1):
        nominator *= i

    return nominator / fact[n - k]

def kbits_to_MBytes(x):
    return x * 0.000125

def main():
    # stick with 64 bit statistical security
    allcosts = list()
    for c in range(2, upper_bound_c):
        for b in range(upper_bound_b):
            cb = math.pow(c, b)
            sec_bound = long(cb * choose(b * nbits, b))
            if sec_bound >= 2**sec_param:
                dabit = DABit(c, b, n_parties, 128, 128)
                allcosts.append((dabit.get_comm(), (c, b) ))

    allcosts.sort()
    for item in allcosts[:2]:
        c = item[1][0]
        b = item[1][1]

        print "######################"
        print "total comm: ", item[0] / (nbits * 1.0), " kbits", " c = ", item[1][0], " b = ", item[1][1]
        dabit = DABit(c, b, n_parties, 128, 128)
        dabit.print_cost_per_dab()
        print(dabit)
        print ""



if __name__=="__main__":
    main()
