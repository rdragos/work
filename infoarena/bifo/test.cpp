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
#include <stack>
#define pb push_back

#define mp make_pair
#define f first
#define ll long long

using namespace std;

int N;
string A, B;
int* fib[500];
int* sfib[500];
inline void sub(int *A, int *B)
{
      int i, t = 0;
      for (i = 1; i <= A[0]; i++) {
              A[i] -= ((i <= B[0]) ? B[i] : 0) + t;
              A[i] += (t = A[i] < 0) * 10;
      }
      for (; A[0] > 1 && !A[A[0]]; A[0]--);
}
inline void add(int *A, int *B)
{
      int i, t = 0;
      for (i=1; i<=A[0] || i<=B[0] || t; i++, t/=10)
              A[i] = (t += A[i] + B[i]) % 10;
      A[0] = i - 1;
}
inline int* decompose(int x) {
    int *v = new int[10];
    
    while(x > 0) {
        v[++v[0]] = x % 10;
        x /= 10;
    }
    return v;
}
inline int toInt(int *t) {
    int x = 0;
    for (int i = t[0] ; i > 0; --i) {
        x = x * 10 + t[i];
    }
    return x;
}
inline int compare(int *a, int *b, int ok = 0) {
    if (a[0] == b[0]) {
        for (int i = a[0]; i > 0; --i) {
            if (a[i] == b[i]) {
                continue;
            }
            return a[i] > b[i];
        }
    } 
    if (ok) {
        return a[0] >= b[0];
    }
    return a[0] > b[0];
}
char solve(int* t, int G) {
    
    if (G == 1) {
        return B[toInt(t) - 1];
    } else if(G == 0) {
        return A[toInt(t) - 1];
    }
    //fib[G] = fib[G - 2] fib[G - 1]
    if (compare(t, fib[G - 2])) {
        //t > fib[G - 2]
        sub(t, fib[G - 2]);
        return solve(t, G - 1);
    }
    return solve(t, G - 2);
}
void print(int *t) {
    for (int i = t[0]; i > 0; --i) {
        cout << t[i];
    }
    cout << "\n";
}
void copy(int *a, int *b) {
    for (int i = 0; i <= b[0]; ++i) {
        a[i] = b[i];
    }
}
int main() {
    ifstream cin("bifo.in");
    ofstream cout("bifo.out");
    /*
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    */
    cin >> A >> B;

    for (int i = 0; i < 500; ++i) {
        fib[i] = new int[200];
        sfib[i] = new int[200];
    }
    //fib[0] = len(A)
    copy(fib[0], decompose(A.length()));
    
    //fib[1] = len(B);
    copy(fib[1], decompose(B.length()));   

    //sfib[0] = fib[0];
    copy(sfib[0], fib[0]);

    //sfib[1] = fib[0] + fib[1];
    copy(sfib[1], fib[0]);
    add(sfib[1], fib[1]);
/*
    print(sfib[0]);
    print(sfib[1]); 
*/ 
    for (int i = 2; fib[i - 1][0] < 101; ++i) {
        //fib[i] = fib[i - 1] + fib[i];
        add(fib[i], fib[i - 1]);
        add(fib[i], fib[i - 2]);
        
        //sfib[i] = sfib[i - 1] + fib[i];
        add(sfib[i], fib[i]);
        add(sfib[i], sfib[i - 1]);

        N += 1;
    }
    cerr << N << "\n";

    int M;
    cin >> M;
    
    for (int i = 1; i <= M; ++i) {
        string s;
        cin >> s;

        // copy reversed(s) in t;

        int m = s.length();
        reverse(s.begin(), s.end());
        int *t = new int[200];
        t[0] = m;
        for (int i = 0; i < m; ++i)
            t[i + 1] = (s[i] - '0');
        
        int go = 0;
        
        for (int j = 0; j < N; ++j) {
            if (compare(sfib[j], t, 1)) {
//                cout << "substraction\n";

                go = j;
                if (j > 0) {
//                    print(t);
//                    print(sfib[j - 1]);
                    sub(t, sfib[j - 1]);
                }
//                cout << "end substraction\n";
                break;
            }
        }
        /* 
        cout << "this is t\n"; 
        cout << go << " " ; print(t); 
        cout << "end with t\n";
        */
        cout << solve(t, go);
        delete[]t;
    }
    return 0;
}
