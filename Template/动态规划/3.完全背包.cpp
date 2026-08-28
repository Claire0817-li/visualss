/*
背包DP 完全背包模板
【题目：AcWing 3 完全背包问题 / P1616 疯狂的采药】
题目描述：
一共有 m 种草药，每种草药可以无限采摘。
每种草药采摘需要消耗时间 a[i]，可以获得价值 b[i]。
总可用时间 t，求不超过总时间，能获得的最大价值。

算法类型：完全背包DP
状态定义：dp[j] 代表总消耗不超过 j 时间时，可以拿到的最大价值。
转移方程：dp[j] = max(dp[j], dp[j‑a[i]] + b[i])
区别于01背包：j循环从小到大正序遍历，允许物品被多次选取。
01背包是逆序，防止重复选；完全背包正序，允许重复选取。
初始化：dp数组全部初始0，不选任何物品价值为0。
时间复杂度 O(m*t)，空间 O(t) 一维滚动数组优化。
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

    ll t,m;
    cin>>t>>m;
    // a[i]:采摘第i种草药耗费时间；b[i]:第i种草药价值
    vl a(m+1),b(m+1);
    for(ll i=1;i<=m;i++)
        cin>>a[i]>>b[i];

    // dp[j]:花费不超过j时间，可以得到的最大价值
    vl dp(t+1);
    // 初始全部0，什么都不选价值为0

    //遍历每一种物品
    for(ll i=1;i<=m;i++)
    {
        // 完全背包：体积j从小到大正序循环，可以重复选取同一个物品
        for(ll j=0;j<=t;j++)
        {
            // j >= a[i]：当前时间足够采该草药
            if(j>=a[i])
            {
                // 两种选择：不采，保持dp[j]；采，dp[j‑a[i]]+b[i]
                dp[j]=max(dp[j], dp[j-a[i]] + b[i]);
            }
        }
    }
    //总时间t下最大价值
    cout<<dp[t];

    return 0;
}
