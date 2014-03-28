
#include <cstdio>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cstring>
#include <string>
#include <set>

#define pb push_back
#define mp make_pair
#define f first
#define s second
#define ll long long

using namespace std;

#include "automat.h"


class node_regex {

private:
    automat val;
    char op;
    node_regex* l;
    node_regex*	r;
    int mark;

public:
    node_regex(string a = "", char b = 0 ,  node_regex* c = NULL, node_regex* d = NULL) :
        val(a) , op(b) , l(c), r(d), mark(0) {
    }
    node_regex* getleft()  const {
        return l;
    }
    node_regex* getright() const {
        return r;
    }
    automat getval() const {
        return val;
    }
    char getop() const {
        return op;
    }
    void regex_mark_on() {
        mark = 1;
    }
    int get_mark() {
        return mark;
    }

};

class Parse {
    node_regex* Tree;
    char *A;
    const int LMAX;
    char *OP[4];

private:
    node_regex* get(int lev) {
        node_regex *x, *y;

        if (lev == LMAX) {
            if (*A == '(') {
                A++;
                x = get(0);
                A++;
            } else {
                string val = "";
                for (; *A <= 'z' && *A >= 'a' ; ++A)
                    val += *A;
                x = new node_regex(val);
                //				cerr << x -> getval() << " " ;
            }
        } else {

            for (x = get(lev + 1); strchr(OP[lev], *A); ) {
                if (*A == '*') {
                    x -> regex_mark_on();
                    ++A;
                    continue;
                }
                y = new node_regex("", *A++, x, get(lev + 1));
                x = y;
            }

        }

        return x;
    }

    automat eval(node_regex *x) const {
        char op = x -> getop();


        if(op == 0) {
            automat L = x -> getval();
            if (x -> get_mark()) {
                L.star();
            }
            return L;
        }

        automat L = eval(x -> getleft());
        automat R = eval(x -> getright());

        if (op == '+') {
            L.concat(R);
        }
        if (op == '|') {
            L.unite(R);
        }

        if (x -> get_mark())
            L.star();
        return L;
    }


public:
    Parse(char *B) : A(B), LMAX(3) {
        OP[0] = "+";
        OP[1] = "|";
        OP[2] = "*";
    }
    automat get_things_done() {
        Tree = get(0);
        return eval(Tree);
    }


};
int main() {


    char *P = new char[1000];
    cout << "Rules a* -> a^(n) n >= 0\n(a+b) -> (ab), (a|b) -> a or b\n";
    cout << "Prints - You're the Boss -  if the word gave was matched to te regular expression you gave first time\n";

    cout << "Give me a valid regular expresion:\n";
    fgets(P, 1000, stdin);
    Parse T(P);

    automat A = T.get_things_done();
    string str;

    while(cin >> str) {
        if(A.See(str)) {
            cout << "You're the Boss\n";
        } else {
            cout << "Try again\n";
        }
    }

    return 0;
}
