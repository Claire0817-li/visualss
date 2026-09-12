/*
算法标签：Floyd-Warshall 求无向图最小环
题目背景：在无向带权图中，找出权值和最小的简单环（环上顶点不重复）
核心思路：
1. 枚举环中编号最大的顶点 k。
2. 在更新 k 的松弛操作之前，此时 d[i][j] 保存的是 i 到 j，**只经过编号严格小于 k 的点**的最短路。
3. 构成一个环：i -> ... -> j -> k -> i。
   环总长度 = d[i][j]（i到j，仅<k点） + w[i][k]（i直接连k的原图边） + w[k][j]（k直接连j的原图边）
4. 枚举所有 i<k, j<k, i<j，不断更新全局最小环。
5. 【顺序关键】先算最小环，再执行Floyd松弛（用k做中转更新d矩阵）。一旦先松弛，d[i][j]就会允许经过k，算法失效。
6. w数组全程保留原图直接边，不能使用d[i][k]、d[k][j]，必须用原始邻接矩阵w。
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

const int N=105;
const ll INF=1e18;     // long long 无穷大，注意：1e18是double字面量，存在精度隐患

ll w[N][N];  // w：原图邻接矩阵，保存原始直接边，永不修改
ll d[N][N];  // d：Floyd最短路矩阵，会不断松弛更新

// 参数n：图中点的数量
ll floyd(ll n)
{
    ll ans=INF;  // 初始化最小环长度为无穷大
    for(int k=1;k<=n;k++)  // k：枚举环中编号最大的顶点
    {
        // 枚举i,j，i<k，j<k，i<j，保证i,j都比k编号小，避免重复枚举同一个环
        for(int i=1;i<k;i++)
        {
            for(int j=i+1;j<k;j++)
            {
                // 环：i到j的最短路（只走<k点） + i直接连k + k直接连j
                ans=min(ans,d[i][j]+w[i][k]+w[k][j]);
            }
        }

        // Floyd标准松弛：用k作为中转点，更新所有i,j之间的最短路
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
            }
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n,m;
    cin>>n>>m;

    // 初始化邻接矩阵w
    for(int i=1;i<=n;i++) 
    {
        for(int j=1;j<=n;j++)
        {
            if(i!=j)   w[i][j]=INF; // i≠j，初始无边，权值INF
            else       w[i][j]=0;   // 自己到自己距离0
        }
    }

    // 读入无向边，重边取最小权值
    for(int i=0;i<m;i++)
    {
        ll u,v,val;  
        cin>>u>>v>>val;
        w[u][v]=w[v][u]=min(w[u][v],val);
    }

    // 将原图矩阵拷贝到最短路矩阵d
    memcpy(d,w,sizeof(d));
    ll ans=floyd(n);

    if(ans==INF)   
        cout<<"No solution.\n"; // 不存在环
    else   
        cout<<ans<<"\n"; // 输出最小环长度

    return 0;
}
