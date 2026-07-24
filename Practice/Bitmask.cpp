#include<bits/stdc++.h>
using namespace std;
using ll=long long;
void solve()
{
    int n;cin>>n;
    int ct[30][4]{},pct[30][4]{};
    for(int i=1;i<=n;i++)
    {
        int a;cin>>a;
        ct[0][(a>>0)&1]++;
        for(int j=1;j<30;j++) pct[j][((a>>j)&1)+(((a>>(j-1))&1)<<1)]++;
    }
    auto sum=[&]()
    {
        ll res=ct[0][1];
        for(int i=1;i<30;i++) res+=pct[i][2];
        return res;
    };
    int m;cin>>m;while(m--)
    {
    int f,g;cin>>f>>g;
    int d=(g>>0)&1;
    if(f==1&&!d) ct[0][1]=0;
    if(f==2&&d) ct[0][1]=n;
    if(f==3&&d) ct[0][1]=n-ct[0][1];

    for(int i=1;i<30;i++)
    {
        int dx=(g>>i)&1,dy=(g>>(i-1))&1;
        int wd[4]={};
        for(int j=0;j<4;j++)
        {
            int nx=((j>>1)&1),ny=(j&1);
            int cx,cy;
            if(f==1) cx=nx&dx,cy=ny&dy;
            if(f==2) cx=nx|dx,cy=ny|dy;
            if(f==3) cx=nx^dx,cy=ny^dy;
            wd[(cx<<1)+cy]+=pct[i][j];
        }
        for(int hj=0;hj<4;hj++) pct[i][hj]=wd[hj];
    }
    cout<<sum()<<'\n';
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}