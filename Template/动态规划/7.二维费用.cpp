/*
背包DP‑二维费用背包（01背包）
【题目：AcWing 8 二维费用的背包问题】
题目描述：
有 n 件物品；背包有两个限制：最大体积V，最大重量M。
每件物品i：占用体积v[i]，占用重量m[i]，价值w[i]。
每件物品只能选一次。求在体积、重量都不超限制的前提下，可拿到的最大总价值。

算法类型：DP，二维费用01背包
状态定义：dp[j][k]：总体积不超过j，总重量不超过k时，最大价值
原始三维状态 dp[i][j][k]：前i件物品，体积j，重量k的最大价值
空间优化：去掉物品i那一维，使用二维数组dp[j][k]
转移方程：
不选第i件：dp[j][k] 保持原值
选第i件：dp[j‑v[i]][k‑m[i]] + w[i]
dp[j][k] = max(dp[j][k], dp[j‑v[i]][k‑m[i]] + w[i])

注意：
1. 01背包，j、k都要倒序循环，防止一件物品被多次选取。
2. 两个费用条件都要满足：j>=v[i] && k>=m[i]。
3. 初始dp全部为0，什么都不选价值为0。
答案：dp[V][M]
时间复杂度 O(n*V*M)，空间 O(V*M)
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

    int n,V,M;
    cin>>n>>V>>M;
    // dp[j][k]：体积j，重量k，最大价值
    vvi dp(V+1, vi(M+1, 0));

    for(int i=1;i<=n;i++)
    {
        int v,m,w;
        cin>>v>>m>>w;
        // 双重倒序！01背包，两种费用都逆序，避免重复选同一件物品
        for(int j=V; j>=v; j--)
        {
            for(int k=M; k>=m; k--)
            {
                // 选或者不选当前物品，取较大价值
                dp[j][k] = max(dp[j][k], dp[j-v][k-m] + w);
            }
        }
    }
    cout<<dp[V][M];
    return 0;
}
