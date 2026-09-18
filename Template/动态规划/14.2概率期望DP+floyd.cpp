/*
题目：P1850 换教室 NOIP2016 D1T2
算法：Floyd全源最短路 + 概率期望DP
限制：n,m<=2000，v<=300，e<=90000
状态定义：
dp[i][j][0]：上完第i节课，累计提交j次申请，第i节课【没有申请换教室】，最小期望体力
dp[i][j][1]：上完第i节课，累计提交j次申请，第i节课【申请了换教室】，最小期望体力
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
const int N=2005;
int n,m,v,e;          // n节课，最多m次申请；v教室数量，e道路数量
int dis[N][N];        // dis[u][v]：教室u到v的最短路
double dp[N][N][2];   // dp[i][j][0/1] 期望DP数组

// Floyd求任意两点最短路，v<=300，O(v^3)可过
void floyd()
{
    for(int k=1;k<=v;k++)         // 中转点k
    {
        for(int i=1;i<=v;i++)     // 起点i
        {
            for(int j=1;j<=v;j++) // 终点j
            {
                if(dis[i][j]>dis[i][k]+dis[k][j])
                {
                    dis[i][j]=dis[i][k]+dis[k][j];
                }
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m>>v>>e;
    vi c(n+1),d(n+1);             // c[i]：i时段默认教室；d[i]：申请成功后换到的教室
    vector<double> k(n+1);        // k[i]：第i节课申请通过的概率
    for(int i=1;i<=n;i++)   cin>>c[i];
    for(int i=1;i<=n;i++)   cin>>d[i];
    for(int i=1;i<=n;i++)   cin>>k[i];

    memset(dis,0x3f,sizeof(dis)); // 距离初始无穷大
    for(int i=1;i<=v;i++) dis[i][i]=0; // 自己到自己距离0
    for(int i=0;i<e;i++)
    {
        int a,b,w;  cin>>a>>b>>w;
        dis[a][b]=min(dis[a][b],w);
        dis[b][a]=min(dis[b][a],w); // 无向双向边
    }
    floyd();

    // DP初始化，全部置极大浮点数（代表不可达）
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dp[i][j][0]=dp[i][j][1]=1e18;
        }
    }
    // 初始状态：第1节课，0次申请，不申请换教室，期望体力0
    dp[1][0][0]=0;
    if(m>=1)    dp[1][1][1]=0; // 第1节课，1次申请，申请换教室，期望体力0

    // 从第2节课依次向后DP
    for(int i=2;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            // dp[i][j][0]：当前i课【不申请】，j次申请总数不变
            // 两种来源：i-1课没申请；i-1课申请了
            dp[i][j][0]=min(
                // i-1没申请：上节课一定在c[i-1]，直接走到c[i]
                dp[i-1][j][0]+dis[c[i-1]][c[i]],
                // i-1申请了：(1-k[i-1])留在c[i-1]，k[i-1]成功到d[i-1]，求期望距离
                dp[i-1][j][1]+dis[c[i-1]][c[i]]*(1-k[i-1])+dis[d[i-1]][c[i]]*k[i-1]
            );
            // dp[i][j][1]：当前i课【申请换教室】，消耗1次申请，j>=1
            if(j>=1)
            {
                dp[i][j][1]=min(
                    // 情况1：i-1课没有申请；i课申请
                    // i-1固定在c[i-1]；i有(1-k[i])留在c[i]，k[i]到d[i]
                    dp[i-1][j-1][0]+dis[c[i-1]][d[i]]*k[i]+dis[c[i-1]][c[i]]*(1-k[i]),
                    // 情况2：i-1课申请了；i课也申请
                    // i-1有两种位置，i有两种位置，四个独立事件，全部概率加权求和
                    dp[i-1][j-1][1]+
                    dis[c[i-1]][c[i]]*((1-k[i-1])*(1-k[i]))+
                    dis[d[i-1]][c[i]]*(k[i-1]*(1-k[i]))+
                    dis[c[i-1]][d[i]]*((1-k[i-1])*k[i])+
                    dis[d[i-1]][d[i]]*(k[i-1]*k[i])
                );
            }
        }
    }
    // 在所有申请次数0~m里面，找最小期望
    double ans=1e18;
    for(int i=0;i<=m;i++)
    {
        ans=min({dp[n][i][0],dp[n][i][1],ans});
    }
    // 保留2位小数输出
    cout<<fixed<<setprecision(2)<<ans;
    return 0;
}
