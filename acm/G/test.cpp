#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>
#define Nmax 2001
using namespace std;
long long T,N,M,K,l,r,sol;
long long ARB[Nmax*4];
vector< pair<long long,long long> > G;

long long query(long long nod,long long left,long long right)
{
    if(l<=left && right<=r)
        return ARB[nod];

    if(left>=right)return 0;

    long long mid = left+(right-left)/2;
    long long a = 0,b = 0;
    if(l<=mid)
        a = query(2*nod, left, mid);
    if(r>mid)
        b = query(2*nod+1, mid+1,right);

    return a + b;
}
void update(long long nod, long long left, long long right)
{
    if(left == right && l == left)
        ++ARB[nod];

    if(left >= right)return;

    long long mid = left+(right-left)/2;

    if(l<=mid)
        update(2*nod,left,mid);
    if(r>mid)
        update(2*nod+1,mid+1,right);

    ARB[nod] = ARB[nod*2] + ARB[nod*2+1];
}
void init_all()
{
    sol = 0;
    G.clear();
    for(long long i=0;i<4*Nmax;++i)
        ARB[i] = 0;
}
int main()
{
//    ifstream cin("test.in");
    cin>>T;
    long long x,y;
    for(long long j=1;j<=T;++j)
    {
        cin>>N>>M>>K;
        init_all();
        for(long long i=0;i<K;++i)
        {
            cin>>x>>y;
            G.push_back( make_pair(x,y) );
        }
        sort(G.begin(), G.end());
//        G.resize(unique(G.begin(), G.end()) - G.begin());
        for(vector< pair<long long,long long> >::iterator it=G.begin();it!=G.end();++it)
        {
            l        = it->second+1;
            r        = M;
            sol += query(1,1,M);

            l = r = it->second;
            update(1,1,M);
        }
        cout<<"Test case "<<j<<": "<<sol<<"\n";
    }
    return 0;
}
