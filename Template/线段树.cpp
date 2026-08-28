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
int n,m;
int a[N];
struct node
{
    int l,r,sum;
}tr[N*4];

void pushup(int p)
{
    tr[p].sum=tr[lc].sum+tr[rc].sum;
}
void build(int p,int x,int y)
{
    tr[p]={x,y,0};
    if(x==y)    {tr[p].sum=a[x];return;}
    int m=x+y>>1;
    build(lc,x,m);
    build(rc,m+1,y);
    pushup(p);
}
void update(int p,int x,int k)
{
    if(tr[p].l==x&&tr[p].r==x)  {tr[p].sum+=k;return;}
    int m=tr[p].l+tr[p].r>>1;
    if(x<=m)    update(lc,x,k);
    if(x>m) update(rc,x,k);
    pushup(p);
}
int query(int p,int x,int y)
{
    if(x<=tr[p].l&&y>=tr[p].r)  return tr[p].sum;
    int m=tr[p].l+tr[p].r>>1;
    int sum=0;
    if(x<=m)    sum+=query(lc,x,y);
    if(y>m) sum+=query(rc,x,y);
    return sum; 
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;i++)   cin>>a[i];
    build(1,1,n);
    while(m--)
    {
        int o,x,y;  cin>>o>>x>>y;
        if(o==1)
        {
            update(1,x,y);
        }
        else
        {
            cout<<query(1,x,y)<<"\n";
        }
    }
    return 0;
}