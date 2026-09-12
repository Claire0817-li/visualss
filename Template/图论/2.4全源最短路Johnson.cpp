/*
算法标签：Johnson 全源最短路 + SPFA(负环判定+势函数) + Dijkstra
题目：P5905 【模板】Johnson 全源最短路
题目思路：
    问题：给定带负权有向图，求所有点对之间最短路；图存在负环则输出-1。
    要求：dis[i][j]为i到j最短路，不可达dis=1e9；i==j时dis=0；输出每行sum_{j=1~n} j * dis(i,j)。
    难点：普通Dijkstra不能处理负权边；n次SPFA会被卡时限。Johnson算法解决带负权图的全源最短路。
Johnson算法原理：
    1. 新增虚拟源点0，向所有1~n的点连一条权值为0的边。
    2. 使用SPFA从虚拟源点跑一遍最短路，得到势函数h[ ]，同时检测图中是否存在负环。
       h[u]：虚拟源点到u的最短路。若存在负环，直接输出-1结束程序。
    3. 对原图每条边 u->v, w，重新赋权：w' = w + h[u] - h[v]。
       可以证明重赋权之后所有边权 w' ≥ 0，此时可以使用Dijkstra。
    4. 依次以每个点 i(1~n)作为起点，跑Dijkstra，得到重赋权后的最短路d[j]。
    5. 还原真实最短路：dist(i,j) = d[j] + h[j] - h[i]。
    6. 按题目规则统计答案：不可达则dist=1e9，累加 j * dist(i,j)。
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

const ll INF=1e9;    //题目规定：不可达的距离值为1e9
const ll N=3005;     //节点上限，包含虚拟源点0
ll n,m;              //n原图节点数，m原图边数

//邻接表存边，edge结构体：目标点v，边权w
struct edge{ll v,w;};
vector<edge> e[N];
vl h(N,INF);    //势函数h，虚拟源点到各点最短路
vl d(N,INF);    //Dijkstra单源最短路数组，存重赋权图的距离
vl cnt(N);      //SPFA：记录到该点最短路经过的边数，用于负环判断
vl vis(N);      //SPFA / Dijkstra共用标记数组，标记节点是否在队列/是否已经出队
//SPFA：从虚拟源点0跑，求势函数h，同时检测负环
void spfa()
{
    queue<ll> q;
    h[0]=0;vis[0]=1;q.push(0);  //虚拟源点初始化入队
    while(q.size())
    {
        ll u=q.front();q.pop();
        vis[u]=0;   //出队，标记不在队列中
        for(auto ed:e[u])
        {
            ll v=ed.v,w=ed.w;
            //松弛操作
            if(h[v]>h[u]+w)
            {
                h[v]=h[u]+w;
                cnt[v]=cnt[u]+1;    //经过边数+1
                //总节点是0~n共n+1个；若边数>=n+1，说明存在负环
                if(cnt[v]>=n+1)   {cout<<"-1";exit(0);}
                //不在队列才入队
                if(!vis[v]) 
                {
                    q.push(v);
                    vis[v]=1;
                }
            }
        }
    }
}
//Dijkstra：在重赋权后的非负权图，求起点s的单源最短路
void dijkstra(int s)
{
    //小根堆 pair(距离,节点编号)
    priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> q;
    fill(vis.begin(), vis.end(), 0); //清空访问标记
    fill(d.begin(),d.end(),INF);      //距离数组重置为INF
    d[s]=0;q.push({0,s});
    while(q.size())
    {
        auto t=q.top();
        q.pop();
        ll u=t.second;
        if(vis[u])  continue; //该点已经处理过，跳过冗余堆元素
        vis[u]=1;
        for(auto ed:e[u])
        {
            ll v=ed.v,w=ed.w;
            if(d[v]>d[u]+w)
            {
                d[v]=d[u]+w; 
                q.push({d[v],v}); 
            }
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
        ll u,v,w;  cin>>u>>v>>w;
        e[u].push_back({v,w});
    }
    //虚拟源点0，向所有原图点1~n连权值0的边
    for(int i=1;i<=n;i++)
    {
        e[0].push_back({i,0});
    }

    spfa(); //SPFA求h，负环检测
    
    //原图边重赋权 w' = w + h[u] - h[v]，保证w' >= 0
    for(int u=1;u<=n;u++)
    {
        for(auto &ed:e[u])
        {
            ed.w+=h[u]-h[ed.v];
        }
    }

    //枚举每一个起点i，跑Dijkstra求点i到所有点的最短路
    for(int i=1;i<=n;i++)
    {
        dijkstra(i);
        ll ans=0;
        for(int j=1;j<=n;j++)
        {
            if(d[j]==INF)
            {
                //不可达，dis=1e9
                ans+=j*INF;
            }
            else
            {
                //还原真实最短路公式 dist(i,j) = d[j] + h[j] - h[i]
                ans+=j*(d[j]+h[j]-h[i]);
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
