#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

const int N=500005;         
struct edge{int v,w;};       // 边结构体：v是邻接的目标点，w是这条边的权值
vector<edge> e[N];           // 邻接表 e[u]：保存u所有相连的边
int n;                       // n：树总节点数量
ll ans;                      // ans：全局变量，存树的直径（最长链总长度）

// dfs(u, fa)
// 参数 u：当前访问节点；fa：u的父节点（防止回溯）
// 返回值：从u向其子树方向能走出的最长距离
ll dfs(int u,int fa)
{
    ll mx1=0,mx2=0;          // mx1：u向下子树的最长链；mx2：u向下子树的次长链
    for(auto edg:e[u])       // 遍历u所有相连的边
    {
        int v=edg.v,w=edg.w; // 取出这条边的邻接点v、边权w
        if(v==fa) continue;  // 如果v是父节点，跳过，不能回头走，避免死递归

        ll d=dfs(v,u)+w;     // 递归得到v向下最长距离，加上u-v边权w，就是u走v这条分支的长度

        // 更新最长链mx1、次长链mx2
        if(d>mx1)
        {
            mx2=mx1;         // 原来的最长变成次长
            mx1=d;           // 当前d成为新的最长链
        }
        else if(d>mx2) 
        {
            mx2=d;           // d比次长大但小于最长，更新次长
        }
    }
    // 经过u点的最长路径 = u向下最长链 + u向下次长链
    // 用这个值更新全局直径ans
    ans=max(ans,mx1+mx2);
    return mx1;              // 返回u向下的最长链，给u的父节点使用
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);           

    cin>>n;                      // 读入节点总数
    for(int i=1;i<n;i++)         // 树有n-1条无向边，循环读入每条边
    {
        int u,v,w;  cin>>u>>v>>w;
        e[u].push_back({v,w});   // u添加一条到v、权w的边
        e[v].push_back({u,w});   // 无向边，v也要添加一条到u、权w的边
    }
    ans=0;                       // 初始化直径为0
    dfs(1,-1);                   // 从节点1开始DFS，根节点没有父节点，fa传-1
    cout<<ans<<"\n";             // 输出树的直径
    return 0;
}
