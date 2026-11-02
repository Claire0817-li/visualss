/*
算法标签：最小生成树 MST | Kruskal | 并查集(DSU) | 贪心 | 排序
时间复杂度：O(m log m)，瓶颈为边的排序
思路：
1. Kruskal贪心策略：把所有边按权值从小到大排序，依次尝试选边
2. 并查集判断边的两个端点是否连通：连通则选这条边会形成环，跳过；不连通就合并两点，把边加入MST
3. 一棵n个点的最小生成树恰好需要 n-1 条边，凑够n-1条可以提前break
4. 最后判断选中边数cnt是否等于n-1，等于代表存在MST，否则图不连通
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
using pi=pair<int,int>;
using pl=pair<ll,ll>;
using ULL=unsigned long long;

const int N=5005;            // 点的最大数量
struct edge
{
    int u,v,w;               // u起点，v终点，w边权
    bool operator<(const edge &t)const{return w<t.w;}
}e[200005];                   // 边数组，P3366边上限2e5

int n,m;                      // n点数，m边数
int fa[N];                    // 并查集父节点数组
int ans,cnt;                  // ans:MST总权值；cnt:已经选入MST的边数量

// 并查集查找函数，带路径压缩
int find(int x)
{
    if(fa[x]==x)    return x; // 找到根节点
    return fa[x]=find(fa[x]); // 路径压缩，直接指向根
}

bool kruskal()
{
    sort(e+1,e+m+1);          // 边下标从1开始，排序[1,m]
    for(int i=1;i<=n;i++) fa[i]=i; // 初始化并查集：每个点的父亲是自己
    ans=0; cnt=0;             // 每次跑Kruskal重置答案、计数
    for(int i=1;i<=m;i++)
    {
        int x=find(e[i].u),y=find(e[i].v);
        if(x!=y)              // 两点不在同一个连通块，可以选这条边
        {
            fa[x]=y;          // 合并两个连通块
            ans+=e[i].w;      // 累加边权
            cnt++;            // 选中边计数+1
            if(cnt==n-1) break; // 已经凑够生成树需要的边，提前退出
        }
    }
    return cnt==n-1;          // 选够n-1条边：存在最小生成树
}

void solve()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int x,y,z;  cin>>x>>y>>z;
        e[i]={x,y,z};        // 读入无向边存入边数组
    }
    if(!kruskal())
        cout<<"orz\n";       // 图不连通，输出orz
    else
        cout<<ans<<'\n';     // 输出最小生成树总权值
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);      
    int t=1;
    while(t--)  solve();
    return 0;
}
