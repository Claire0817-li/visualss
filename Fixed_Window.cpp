#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
const int N=500005;
#define lc p<<1
#define rc p<<1|1
int n,L;
ll k;
ll a[N],w[N];
vl b;
struct node
{
    int l,r;
    ll mx;
}tr[N*4];
void pushup(int p)
{
    tr[p].mx=max(tr[lc].mx,tr[rc].mx);
}
void build(int p,int x,int y,vl &val)
{
    tr[p]={x,y,0};
    if(x==y)
    {
        tr[p].mx=val[x];
        return;
    }
    int m=x+y>>1;
    build(lc,x,m,val);
    build(rc,m+1,y,val);
    pushup(p);
}
void update(int p,int x,ll k)
{
    if(tr[p].l==x&&tr[p].r==x)
    {
        tr[p].mx+=k;
        return;
    }
    int m=tr[p].l+tr[p].r>>1;
    if(x<=m)    update(lc,x,k);
    if(x>m) update(rc,x,k);
    pushup(p);
}
int getid(ll x)
{
    return lower_bound(b.begin(),b.end(),x)-b.begin()+1;
}
void add(int i)
{
    ll x=a[i];
    int id1=getid(x);
    int id2=getid(x+k);
    update(1,id1,-w[i]);
    update(1,id2,w[i]);
}
void remove(int i)
{
    ll x=a[i];
    int id1=getid(x);
    int id2=getid(x+k);
    update(1,id1,w[i]);
    update(1,id2,-w[i]);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>L>>k;
    for(int i=1;i<=n;i++)   cin>>a[i];
    for(int i=1;i<=n;i++)   cin>>w[i];
    for(int i=1;i<=n;i++)
    {
        b.push_back(a[i]);
        b.push_back(a[i]+k);
    }
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    int sz=b.size();
    vl val(sz+1,0);
    for(int i=1;i<=n;i++)
    {
        int id=getid(a[i]);
        val[id]+=w[i];
    }
    build(1,1,sz,val);
    ll ans=tr[1].mx;
    for(int i=1;i<=L;i++)   add(i);
    ans=max(ans,tr[1].mx);
    for(int r=L+1;r<=n;r++)
    {
        remove(r-L);
        add(r);
        ans=max(ans,tr[1].mx);
    }
    cout<<ans<<"\n";
    return 0;
}