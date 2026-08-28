/*
区间dp
【题目：P1775 石子合并（弱化版）】
题目描述：
有 n 堆石子排成一条直线，每堆石子有若干颗。
每次操作可以合并相邻的两堆石子，合并的代价 = 两堆石子的总数量。
求将所有石子合并成一堆，需要的最小总代价。

数据范围：n ≤ 100

*/

#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>>n;

    vi m(n+1);      // m[1~n]：每堆石子的数量，下标从1开始
    vi pre(n+1,0);  // pre前缀和数组，pre[0]=0
    // dp[l][r]表示合并[l,r]的最小代价，全部初始化为无穷大1e9
    vvi dp(n+1, vi(n+1, 1e9));

    for(int i=1;i<=n;i++)
    {
        cin>>m[i];
        dp[i][i] = 0;          // 只有一堆石子，无需合并，代价0
        pre[i] = pre[i-1] + m[i];  // 维护前缀和
    }

    // len：当前处理的区间长度，从2开始（长度1已经初始化完毕）
    for(int len=2; len<=n; len++)
    {
        // l：区间左端点，保证右端 r=l+len-1 不超过n
        for(int l=1; l + len -1 <= n; l++)
        {
            int r = l + len - 1;  // 当前区间的右端点

            // k是分割点，把[l,r]切 [l,k] 和 [k+1,r]
            for(int k=l; k<r; k++)
            {
                // dp[l][k]：合并左边；dp[k+1][r]：合并右边
                // pre[r]-pre[l-1]：最后把左右两大堆合并的代价
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k+1][r] + pre[r] - pre[l-1]);
            }
        }
    }

    // 答案：合并 1~n 全部石子的最小代价
    cout << dp[1][n];

    return 0;
}