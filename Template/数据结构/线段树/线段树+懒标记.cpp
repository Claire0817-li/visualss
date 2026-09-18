#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
#define lc p<<1
#define rc p<<1|1
const int N=100005;
int n;
ll a[N];
struct node
{
    int l,r;
    ll sum,add;
}tr[4*N];
void pushup(int p)
{
    tr[p].sum=tr[lc].sum+tr[rc].sum;
}
void pushdown(int p)
{
    if(tr[p].add)   
    {
        tr[lc].sum+=tr[p].add*(tr[lc].r-tr[lc].l+1);
        tr[rc].sum+=tr[p].add*(tr[rc].r-tr[rc].l+1);
        tr[lc].add+=tr[p].add;
        tr[rc].add+=tr[p].add;
        tr[p].add=0;
    }
}
void build(int p,int x,int y)
{
    tr[p].l=x;
    tr[p].r=y;
    tr[p].add=0;
    if(x==y)    {tr[p].sum=a[x];return;}
    int m=x+y>>1;
    build(lc,x,m);
    build(rc,m+1,y);
    pushup(p);
}
ll query(int p,int x,int y)
{
    if(x<=tr[p].l&&y>=tr[p].r)  return tr[p].sum;
    ll sum=0;
    int m=tr[p].l+tr[p].r>>1;
    pushdown(p);
    if(x<=m)    sum+=query(lc,x,y);
    if(y>m)     sum+=query(rc,x,y);
    return sum;
}
void update(int p,int x,int y,ll k)
{
    if(x<=tr[p].l&&y>=tr[p].r)
    {
        tr[p].sum+=(tr[p].r-tr[p].l+1)*k;
        tr[p].add+=k;
        return;
    }
    int m=tr[p].l+tr[p].r>>1;
    pushdown(p);
    if(x<=m)    update(lc,x,y,k);
    if(y>m)     update(rc,x,y,k);
    pushup(p);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m;  cin>>n>>m;
    for(int i=1;i<=n;i++)   cin>>a[i];
    build(1,1,n);
    while(m--)
    {
        int o;  cin>>o;
        if(o==1)
        {
            int x,y;ll k;  cin>>x>>y>>k;
            update(1,x,y,k);
        }
        if(o==2)
        {
            int x,y;    cin>>x>>y;
            cout<<query(1,x,y)<<"\n";
        }
    }
    return 0;
}