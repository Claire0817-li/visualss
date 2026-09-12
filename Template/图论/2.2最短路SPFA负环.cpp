/*
题型：SPFA 判断从起点1可达的负环
题目规则：
1. w >= 0：双向边 u<->v，权w
2. w < 0 ：单向边 u->v，权w
目标：检查图中是否存在从顶点1出发能够到达的负环
cnt[v]定义：从起点s到v，当前松弛路径经过的边的数量
抽屉原理：n个点的图，简单路径最多n-1条边。
如果路径边数 >= n，说明路径上一定存在重复顶点，存在环；
并且这个环可以持续松弛更新距离，即为负环。
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
const int N=2005;      // 点数量上限
const int INF=0x3f3f3f3f; // 无穷大
int n,m;               // n点数，m边数

// 邻接表边结构体：v目标点，w边权
struct edge{int v,w;};
vector<edge> e[N];     // 邻接表

vi d(N,INF);           // d[i]:起点到i的最短路距离
vi cnt(N);             // cnt[i]:起点到i的路径经过的边数
vi vis(N);             // vis[i]:标记i是否在队列中，防止重复入队

// spfa(s):从s出发跑最短路，若找到可达负环返回true，否则false
bool spfa(int s)
{
    queue<int> q;
    d[s]=0;          // 起点距离初始化为0
    vis[s]=1;        // 标记起点入队
    q.push(s);
    while(q.size())
    {
        int u=q.front();
        q.pop();
        vis[u]=0;    // 出队，取消标记
        
        // 遍历u的所有邻边
        for(auto ed:e[u])
        {
            int v=ed.v,w=ed.w;
            // 松弛操作：发现更短路径
            if(d[v]>d[u]+w)
            {
                d[v]=d[u]+w;          // 更新最短路
                cnt[v]=cnt[u]+1;      // 边数+1
                if(cnt[v]>=n)         // 边数>=n，存在可达负环
                    return true;
                if(!vis[v])           // v不在队列，则入队
                {
                    q.push(v);
                    vis[v]=1;
                }
            }
        }
    }
    return false; // 没有找到负环
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr); // 加速cin输入
    int t;  cin>>t;   // t组测试用例
    while(t--)
    {
        cin>>n>>m;
        // 多组数据，清空邻接表、距离、计数、入队标记数组
        for(int i=0;i<=n;i++) e[i].clear();
        fill(d.begin(),d.end(),INF);
        fill(cnt.begin(),cnt.end(),0);
        fill(vis.begin(),vis.end(),0);

        // 读入m条边
        for(int i=0;i<m;i++)
        {
            int u,v,w;  cin>>u>>v>>w;
            if(w>=0)
            {
                e[u].push_back({v,w});
                e[v].push_back({u,w});
            }
            else
            {
                e[u].push_back({v,w});
            }
        }
        // 只从1号点出发，只检测1能到达区域内的负环
        if(spfa(1)) 
            cout<<"YES\n";
        else    
            cout<<"NO\n";
    }
    return 0;
}
