// 题型：DAG期望DP 反向拓扑
// 题意：有向无环图，从节点1出发，每个点等概率选择一条出边，求走到终点n的期望路径总长度
// 状态定义：dp[u] = 从u出发走到终点n的期望路径长度
// 转移方程：dp[u] = 1/outd[u] * sum( w + dp[v] )  其中u->v是原图的边
// 实现技巧：反向建图，从终点n开始按拓扑序逆推，保证计算u时所有后继节点的dp值已求出
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

const int N=1e5+5;
int n,m;
struct edge{int v,w;};      // 邻接表结构体：v=邻接点编号，w=边权
vector<edge> e[N];          // 反向图的邻接表
vi outd(N,0),indeg(N,0);
// outd[u]：原图中u的出度，DP转移的分母，全程只读不修改
// indeg[u]：反向图中u的入度，仅用于拓扑排序的入度计数与自减
double dp[N];               // dp[u]：u到终点n的期望路径长度

void topo()
{
    queue<int> q;q.push(n); // 拓扑起点为终点n，dp[n]=0（全局数组默认初始化为0）
    while(q.size())
    {
        int u=q.front();  q.pop();
        // 遍历反向图中u的所有邻边：原图中对应 y.v -> u，边权为y.w
        for(auto y:e[u])
        {
            // 累加一条出边的贡献：(后继节点期望 + 边权) / 当前节点的出度
            dp[y.v]+=(dp[u]+y.w)*1.0/outd[y.v];
            // 反向图入度自减，所有前驱都处理完毕后入队
            if(--indeg[y.v]==0)   q.push(y.v);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        int u,v,w;  cin>>u>>v>>w;
        e[v].push_back({u,w}); // 反向建边：原图u->v，存为v->u
        outd[u]++;   // 原图中u的出度+1
        indeg[u]++;  // 反向图中u的入度+1
    }
    topo();
    cout<<fixed<<setprecision(2)<<dp[1]; // 输出起点1到终点n的期望路径长度
    return 0;
}