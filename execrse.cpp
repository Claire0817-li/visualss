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
const int N=50005;
int fa[N],d[N];
int find(int x)
{
    if(fa[x]!=x)
    {
        int rt=find(fa[x]);
        d[x]+=d[fa[x]];
        d[x]%=3;
        fa[x]=rt;
    }
    return fa[x];
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,k;    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        fa[i]=i;d[i]=0;
    }
    int ans=0;
    while(k--)   
    {
        int num,x,y;    cin>>num>>x>>y;
        if((x>n||y>n)||(num==2&&x==y))    {ans++;continue;}
        int rx=find(x),ry=find(y);
        if(rx==ry)
        {
            if(num==1&&d[x]%3!=d[y]%3)   {ans++;}
            if(num==2&&(d[x]+1)%3!=d[y]%3)  {ans++;}
        }
        else
        {
            fa[rx]=ry;
            if(num==1)
            {
                d[rx]=(d[y]-d[x]+3)%3;
            }
            else    {d[rx]=(d[y]-d[x]-1+3)%3;}
        }
    }
    cout<<ans;
    return 0;
}