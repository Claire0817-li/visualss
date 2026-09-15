/*
题目：Degree积蓄程度 换根DP
题意简述：
一棵带权无向树，选定一个起点u，从u向外"输送积蓄"。
对于一条边，积蓄最多只能传递 min(边权, 子节点能承受的积蓄)。
叶子节点(deg=1)只能接收积蓄，不能向外输送，记dp[叶子]=INF。
dp[u]：以u为根时，u向它所有子树能送出的总积蓄。
ans[u]：以u作为整棵树的起点，全局总共能送出的积蓄。
目标：求 ans[1~n] 的最大值（排除叶子节点，叶子不能作为起点）

算法：二次DFS换根DP
dfs1：后序遍历，自底向上算出dp[u]（只考虑u的子树）
dfs2：换根遍历，自顶向下，利用父节点ans[u]算出子节点ans[v]
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

const int N=2e5+5;
const ll INF=1e18;

int n;
// 邻接表存边：v是邻接点，w是边权
struct edge{int v,w;};
vector<edge> e[N];

ll dp[N];   // dp[u]:u只往子树方向可以送出的积蓄总和
ll ans[N];  // ans[u]:以u为全局起点，整棵树能送出的积蓄总和
int deg[N]; // deg[u]:节点u的度数

// dfs1：第一遍DFS，后序，计算dp数组（子树内贡献）
void dfs1(int u,int fa)
{
    dp[u]=0;
    // 遍历u所有邻边
    for(auto &p:e[u])
    {
        int v=p.v,w=p.w;
        if(v==fa) continue; // 不回父节点
        dfs1(v,u);         // 先递归处理子v
        // u传给v这条边，最多只能传递 min(边权w, v能承受的dp[v])
        dp[u]+=min(dp[v],(ll)w);
    }
    // 度数为1=叶子节点，叶子只能接收积蓄，无法向外输送，标记INF
    if(deg[u]==1) dp[u]=INF;
}

// dfs2：第二遍DFS，换根，由父节点ans[u]推导子节点ans[v]
void dfs2(int u,int fa)
{
    for(auto &p:e[u])
    {
        int v=p.v,w=p.w;
        if(v==fa) continue;
        // val：u往v子树方向原本贡献的值
        ll val=min((ll)w,dp[v]);
        ll up; // up代表：v反过来，向u方向（父侧那一大块树）能送出的积蓄

        if(deg[u]==1)
        {
            // u本身是叶子，u向外只能送出边权w
            up=w;
        }
        else
        {
            // rest = ans[u] - val：把u->v这部分扣除，剩下u向其它方向的积蓄
            ll rest=ans[u]-val;
            // v往u方向传递，上限是边权w和rest中小的那个
            up=min((ll)w,rest);
        }
        // ans[v] = v原来子树贡献dp[v] + 往父侧方向的贡献up
        ans[v]=dp[v]+up;
        dfs2(v,u); // 继续向下换根
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin>>t;
    while(t--)
    {
        cin>>n;
        // 多组数据：清空邻接表和度数数组
        for(int i=1;i<=n;i++) e[i].clear(),deg[i]=0;
        for(int i=1;i<n;i++)
        {
            int x,y,z; cin>>x>>y>>z;
            e[x].push_back({y,z});
            e[y].push_back({x,z});
            deg[x]++;
            deg[y]++;
        }
        dfs1(1,-1);      // 以1号点为临时根，计算dp
        ans[1]=dp[1];    // 根节点1的ans初始值等于dp[1]
        dfs2(1,-1);      // 换根DP，求出全部ans[u]

        ll res=0;
        for(int i=1;i<=n;i++)
        {
            if(ans[i]>=INF) continue; // 跳过叶子，叶子不能作为起点
            res=max(res,ans[i]);      // 寻找最大积蓄值
        }
        cout<<res<<'\n';
    }
    return 0;
}
