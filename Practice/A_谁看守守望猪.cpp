//     /ᐠ˶˶ᐟ\
//   (=•ㅅ < )
//  |￣∪∪￣|
//  |＿求AC＿|
// 猫神大人请赐我本世纪最难得的运气[^]_[^]
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;
const int INF = 0x3f3f3f3f;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while(T--)
    {
        int n,k;
        string s;
        cin>>n>>k>>s;
        int mx=n;
        vvi f(n+2,vi(mx+2,INF));
        for(int x=0;x<=mx;x++)
            f[n+1][x]=(x==0?0:INF);

        for(int i=n;i>=1;i--)
        {
            char c=s[i-1];
            int cl=(c=='L'?0:1);
            int cr =(c=='R'?0:1);
            for(int x=0;x<=mx;x++)
            {
                int tL=cl+f[i+1][max(x-1,0)];
                int tR=cr+f[i+1][x];
                f[i][x]=min(tL,tR);
            }
        }

        vvi dp(n+2,vi(n+2,INF));
        dp[1][0]=0;
        for(int i=1;i<=n;i++)
        {
            for(int r=0;r<i;r++)
            {
                if(dp[i][r]==INF) continue;
                char c=s[i-1];
                int cl=(c=='L'?0:1);
                if(r>=k)
                {
                    dp[i+1][r]=min(dp[i+1][r],dp[i][r]+cl);
                }
                int cr=(c=='R'?0:1);
                if(f[i+1][k]!=INF)
                {
                    dp[i+1][r+1]=min(dp[i+1][r+1],dp[i][r]+cr);
                }
            }
        }

        int res=INF;
        for(int r=0;r<=n;r++)
        {
            res=min(res,dp[n+1][r]);
        }
        if(res==INF)    cout<<"-1\n";
        else    cout<<res<<"\n";
    }
    return 0;
}