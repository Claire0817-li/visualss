/*
背包DP‑分组背包
【题目：洛谷P1757 通天之分组背包】
题目描述：
背包容量为m，共有n件物品。每件物品有重量x，价值y，所属组别z。
同一组的物品最多只能选一件，也可以整组不选。
在总重量不超过背包容量m的前提下，求能获得的最大价值。

算法类型：DP 分组背包，01背包的变种
状态定义：dp[j]：背包容量为j时，可以取得的最大价值
思路：
1. a[z]保存第z组内全部物品，pair{重量，价值}
2. 外层循环遍历每一个组k
3. 容量j必须倒序循环（从m往下），避免同一组选出多件物品
4. 内层遍历当前组内每一件物品：
   dp[j] = max(不选本组物品，选本组第i件物品)
循环顺序非常关键：组 → j倒序 → 组内物品。
时间复杂度 O(组数 × 背包容量 × 每组物品数量)
*/

#include <bits/stdc++.h>
using namespace std;

//类型别名简化书写
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m,n;
    cin>>m>>n;
    // a[z]存储z组的所有物品，pair.first=重量，pair.second=价值
    vector<vector<pair<int,int>>> a(n+1);

    for(int i=1;i<=n;i++)
    {
        int x,y,z;
        cin>>x>>y>>z;
        a[z].push_back({x,y});
    }

    vi dp(m+1); // dp[j]：容量j下最大价值，默认初始为0

    // k遍历每一个组别
    for(int k=1;k<=n;k++)
    {
        // 当前组没有物品，直接跳过
        if(a[k].empty())
            continue;

        // j倒序！分组背包核心，防止同一组选取多个物品
        for(int j=m;j>=0;j--)
        {
            // 枚举本组内每一件物品
            for(int i=0;i<a[k].size();i++)
            {
                int w = a[k][i].first;   //物品重量
                int val = a[k][i].second;//物品价值
                if(j >= w)
                {
                    // 两种决策：不选该物品保持dp[j]；选该物品 dp[j‑w]+val
                    dp[j]=max(dp[j], dp[j-w]+val);
                }
            }
        }
    }
    //背包容量m时的最大价值
    cout<<dp[m];

    return 0;
}
