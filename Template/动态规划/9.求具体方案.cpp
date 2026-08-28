#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

/*
算法题型：分组背包 机器分配
题目：n个分公司，m台机器。给第i家公司分配k台机器可以获得a[i][k]盈利。
求总盈利最大值；多组最优解时，让靠后的公司分得尽可能多的机器（字典序最大方案）
dp[i][j]：前 i 家公司，一共分配 j 台机器，能获得的最大总盈利
*/
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    cin>>n>>m;

    // a[i][k]：第 i 号公司分配 k 台机器对应的盈利
    vvi a(n+1,vi(m+1));
    for(int i=1;i<=n;i++)
    {
        a[i][0]=0;       // 分配0台机器，盈利为0
        for(int j=1;j<=m;j++)
        {
            cin>>a[i][j];
        }
    }

    // dp[i][j]：前i家公司，总共分配j台机器的最大盈利
    vvi dp(n+1,vi(m+1,0));

    // i：处理第 i 家公司（分组背包，每家就是一组）
    for(int i=1;i<=n;i++)
    {
        // j：给前i家公司，总共分配 j 台机器
        for(int j=0;j<=m;j++)
        {
            // k：给第 i 家公司分配 k 台机器
            // k取值0~j：第i家可以分0台、1台……最多j台
            for(int k=0;k<=j;k++)
            {
                // dp[i‑1][j‑k]：前i‑1家一共分配 j‑k 台
                // a[i][k]：第i家分配k台的收益
                dp[i][j]=max(dp[i][j], dp[i-1][j-k] + a[i][k]);
            }
        }
    }
    // 前n家，一共分配m台机器，最大总盈利
    cout<<dp[n][m]<<"\n";


    // =========回溯，求出每家分配多少台机器=========
    int re=m;           // re：剩余还可以分配的机器数量
    vi ans(n+1);        // ans[i]：保存第i家公司分到的机器台数

    // 倒着遍历公司：从最后一家n，向前到第1家
    for(int i=n;i>=1;i--)
    {
        // k从大到小枚举：优先尝试给当前i分配尽可能多机器
        // 目的：多组最优解时，得到字典序最大的分配方案
        for(int k=re;k>=0;k--)
        {
            // 判断状态等式：dp[i][re]这个最优结果，是不是来自：
            // 第i家拿k台，剩下 re‑k 台交给前i‑1家处理
            if(dp[i][re] == dp[i-1][re-k] + a[i][k])
            {
                ans[i]=k;        // 确定第i家分配k台
                re -= k;         // 剩余机器减去k台
                break;           // 找到合法k就跳出，处理上一家公司
            }
        }
    }

    // 按1~n顺序输出每家公司编号与分配机器数量
    for(int i=1;i<=n;i++)
    {
        cout<<i<<" "<<ans[i]<<'\n';
    }

    return 0;
}
