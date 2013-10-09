wsw
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define ll long long


const int MAXN = 100005;
const int mod = 1000000007;

using namespace std;

ll pw[MAXN];
string S;
ll compute_pow(ll A, ll B) {
    //return (A ^ B) % mod

    ll res = 1;
    for (ll i = 0; i < 40; ++i) {
        if (B & (1LL << i)) {
            res = (res * A) % mod;
        }
        A = (A * A) % mod;
    }
    return res;
}
int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);

    int n;
    ll M;

    cin >> S; 
    cin >> M;
    
    n = S.length();

    pw[0] = 1;
    for (int i = 1; i < n; ++i) {
        pw[i] = (1LL * pw[i - 1] * 2) % mod;
    }
    
    ll s = 0, p = 0, cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (S[i] == '0' || S[i] == '5') {
            s += pw[i] - 1;
            
            if (s >= mod) {
                s %= mod;
            }
            
            cnt += 1;
            
            p = (p + pw[i]) % mod;
            cerr << "2 la " << i << "\n";
        }
    }
 
    if (S[n - 1] == '0' || S[n - 1] == '5') {
        s += M;
    }
    if (M == 0) {
        cout << s << "\n";
        return 0;
    }
    cerr << n + M - 1 << "\n";
    p = p * pw[n];
    p %= mod;
    // 2^A1 + 2^A2 + .. + 2^Ak
    // 
    p = p * (compute_pow(2, M-1) - 2);
    p = (p - cnt * (M-1)) % mod;
    p = (p + mod) % mod;
    p %=  mod;
    cout << (s + p + mod) % mod;
    
    return 0;
}
