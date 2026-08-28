/*
题目：P1352 没有上司的舞会
题目大意：
给定一棵员工关系树，每个员工有快乐值r[i]。
规则：如果选某个人参加舞会，则他的直接上司不能参加。
求选出一批员工，快乐值总和的最大值。

树形DP思路：
dp[u][0]：不选u节点，u的子树能得到的最大快乐值
dp[u][1]：选择u节点，u的子树能得到的最大快乐值

转移：
1.选u(dp[u][1])：所有直接子节点v都不能选，只能加dp[v][0]
  dp[u][1] = r[u] + sum(dp[v][0])
2.不选u(dp[u][0])：子节点v可以选也可以不选，取两者最大值累加
  dp[u][0] = sum(max(dp[v][0], dp[v][1]))

答案：max(dp[root][0], dp[root][1])

*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
const int N=6005;
vi r(N+1);        // r[i]：第i个员工的快乐值
vi g[N+2];        // 邻接表，存储树边
vvi dp(N+1,vi(2,0)); // dp[u][0]不选u；dp[u][1]选u

// dfs：计算root为根的子树dp值
void dfs(int root)
{
    dp[root][1]=r[root]; // 选root，初始快乐值为自己的快乐值
    // 遍历root的所有邻接点
    for(int v:g[root])
    {
        dfs(v);  // 递归处理子节点
        // root不选：子节点可选可不选，取max累加
        dp[root][0]+=max(dp[v][0],dp[v][1]);
        // root选：子节点不能选，只能加上子节点不选的情况
        dp[root][1]+=dp[v][0];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;  cin>>n;
    // 读入每个人的快乐值
    for(int i=1;i<=n;i++)   cin>>r[i];
    vector<bool> fa(n+1,false); // fa[x]=true 表示x有上司(有父节点)
    // n个节点的树，共n‑1条边
    for(int i=0;i<n-1;i++)
    {
        int l,k;   cin>>l>>k;
        // l是k的上司，k是l的下属
        g[k].push_back(l);
        fa[l]=true;
    }
    
    // 寻找根节点：没有上司的点，fa[i]==false
    int root;
    for(int i=1;i<=n;i++)
    {
        if(!fa[i])  {root=i;break;}
    }
    dfs(root);
    // 根节点选或者不选，取最大值作为答案
    cout<<max(dp[root][1],dp[root][0]);
    return 0;
}
