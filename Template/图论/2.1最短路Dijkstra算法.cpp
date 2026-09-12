/*
 * 算法标签：单源最短路、Dijkstra算法、堆优化Dijkstra、邻接表
 * 题目背景：带非负权有向图，n≤1e5，m≤2e5，求起点s到全部点最短距离
 * 算法思路：
 * 1. 堆优化Dijkstra适用于**边权全部非负**的图，时间复杂度 O(m log n)，可以处理1e5规模的数据
 * 2. 使用邻接表 vector<edge> 存储有向图，节省空间，适配大数据
 * 3. d[]数组：记录起点s到每个点的最短距离，初始赋值无穷INF，起点d[s]=0
 * 4. vis[]数组：标记该点是否已经确定最短路；一旦出堆并且vis=false，代表拿到该点最终最短距离，标记vis=1，后续队列中该点旧记录直接跳过
 * 5. 小根优先队列(堆)：pair<距离, 点编号>，每次取出当前距离最小的点；松弛相邻边，如果可以更新最短距离，就把新状态压入堆
 * 6. 注意坑点：
 *    - 边权w最大1e9，距离累加会爆int，全部距离相关变量使用 long long
 *    - 数组大小 N >= 1e5+5，防止下标越界RE
 *    - 图为有向图，只添加单向 u->v 的边
 *    - 堆中会存在同一个点的多条旧的、无效记录，依靠vis数组过滤掉旧记录，不要尝试去堆中删除旧元素
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

const ll N=100005;          // 最大节点数 1e5
const ll INF=(1LL<<31)-1;   // 无穷大，2^31‑1

ll n,m,s;                   // n点数，m边数，s起点
vl d(N,INF);                // d[i]：s到i的最短距离
vl vis(N,0);                // vis[i]=1代表i点最短路已经确定

struct edge
{
    ll v,w;                 // v：邻接节点；w：边权
};
vector<edge> e[N];          // 邻接表 e[u]保存u出发所有边

// 小根堆 pair<距离,节点编号>
priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> q;

void dijkstra()
{
    d[s]=0; 
    q.push({0,s});         // 起点入堆，距离0

    while(q.size())
    {
        auto t=q.top(); 
        q.pop();
        ll u=t.second;     // 当前取出的节点u

        if(vis[u])  continue; // u已经得到最短路，跳过堆里旧的无效记录
        vis[u]=1;             // 标记u的最短路已经确定

        for(auto ed:e[u])     // 遍历u所有出边
        {
            ll v=ed.v,w=ed.w; 
            if(d[v]>d[u]+w)   // 松弛操作：如果经过u到v距离更短
            {
                d[v]=d[u]+w;  // 更新v的最短距离
                q.push({d[v],v}); // 将新距离压入优先队列
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 
    
    cin>>n>>m>>s;
    for(ll i=0;i<m;i++)
    {
        ll u,v,w; 
        cin>>u>>v>>w;
        e[u].push_back({v,w}); // 构建有向边 u -> v
    }

    dijkstra();

    for(ll i=1;i<=n;i++)
    {
        cout<<d[i]<<" ";
    }
    return 0;
}
