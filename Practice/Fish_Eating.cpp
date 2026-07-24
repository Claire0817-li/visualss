//     /ᐠ˶˶ᐟ\
//   (=•ㅅ < )
//  |￣∪∪￣|
//  |＿求AC＿|
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
const int N=250005;
int fa[N],sz[N];
ll w[N],mx[N];
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
int find(int x)
{
    if(fa[x]!=x)
    {
        int pre=fa[x];
        int rt=find(fa[x]);
        fa[x]=rt;
        mx[x]=max(mx[x],mx[pre]);
    }
    return fa[x];
}
int merge(int a,int b,ll val)
{
    int ra=find(a),rb=find(b);
    if(ra==rb) return ra;
    w[rb]=val;
    mx[rb]=max(mx[rb],w[rb]-1ll*sz[rb]+1);
    sz[ra]+=sz[rb];
    fa[rb]=ra;
    return ra;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m,q;cin>>n>>m>>q;
    int sum=n*m;
    for(int i=1;i<=sum;i++)
    {
        fa[i]=i;
        sz[i]=1;
        w[i]=0;
        mx[i]=0;
    }
    vi siz(sum+5,-1);
    ll last=0;
    while(q--)
    {
        int op;
        cin>>op;
        if(op==1)
        {
            int xp,yp;ll v;
            cin>>xp>>yp>>v;
            int x=xp^last;
            int y=yp^last;
            int id=(x-1)*m+y;
            siz[id]=v;
            
            for(int d=0;d<4;d++)
            {
                int nx=x+dx[d];
                int ny=y+dy[d];
                if(nx<1||nx>n||ny<1||ny>m) continue;
                int nid=(nx-1)*m+ny;
                if(siz[nid]!=-1)
                {
                    int r1=find(id);
                    int r2=find(nid);
                    if(r1!=r2) {merge(r1,r2,v);}
                }
            }
            
            int rt=find(id);
            last=sz[rt]-1;
            cout<<last<<'\n';
        }
        else
        {
            int xp,yp;
            cin>>xp>>yp;
            int x=xp^last;
            int y=yp^last;
            int id=(x-1)*m+y;
            ll v0=siz[id]; 
            find(id);
            ll need=mx[id];
            last=max(0LL,need-v0);
            cout<<last<<'\n';
        }
    }
    return 0;
}