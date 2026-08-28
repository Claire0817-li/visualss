#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
const double eps=1e-8;
inline int dcmp(double a,double b)
{
    if(fabs(a-b)<eps)   return 0;
    return a>b?1:-1;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;  cin>>t;
    while(t--)
    {
        int n,m;    cin>>n>>m;
        vector<pair<double,double>> p(n);
        for(int i=0;i<n;i++)    cin>>p[i].first>>p[i].second;

        vvi line(n,vi(n,0));
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i==j)    continue;
                double x1=p[i].first,y1=p[i].second;
                double x2=p[j].first,y2=p[j].second;
                double a=(y2/x2-y1/x1)/(x2-x1);
                double b=y1/x1-a*x1;
                if(dcmp(a,0)>=0)    continue;
                int mask=0;
                for(int k=0;k<n;k++)
                {
                    double x=p[k].first,y=p[k].second;
                    if(dcmp(x*x*a+b*x,y)==0)    mask|=(1<<k);
                }
                line[i][j]=mask;
            }
        }
        
        vi dp(1<<n,0x3f3f3f3f);
        dp[0]=0;
        for(int s=0;s<(1<<n);s++)
        {
            if(dp[s]==0x3f3f3f3f) continue;
            int f;
            for(f=0;f<n;f++)
            {
                if(!(s&(1<<f)))    break;
            }
            if(f>=n)    continue;

            dp[s|(1<<f)]=min(dp[s|(1<<f)],dp[s]+1);
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<n;j++)
                {
                    if(i==j)    continue;
                    if(line[f][j]==0)  continue;
                    dp[s|line[i][j]]=min(dp[s|line[i][j]],dp[s]+1);
                }
            }
        }
        cout<<dp[(1<<n)-1]<<'\n';
    }
    return 0;
}