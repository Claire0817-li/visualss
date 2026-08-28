#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
const int N=200005;
ll n,m; 
vl fa(N),siz(N,1);
ll find(ll x)
{
    if(fa[x]==x)    return x;
    return fa[x]=find(fa[x]);
}
void unionset(ll x,ll y)
{
    ll a=find(x),b=find(y);
    if(siz[a]>siz[b])   swap(a,b);
    fa[a]=b;
    siz[b]+=siz[a];
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(ll i=0;i<n;i++) fa[i]=i;
    while(m--)
    {
        ll z,x,y;   cin>>z>>x>>y;
        if(z==1)
        {
            unionset(x,y);
        }
        else
        {
            if(find(x)==find(y))    cout<<"Y\n";
            else    cout<<"N\n";
        }
    }
    return 0;
}