/*
算法标签：最小生成树 MST | 堆优化Prim | 贪心 | 优先队列
复杂度：O(m log n)
思路：
1. 维护已在生成树中的点集vis，d[x]代表x到树集合的最小边权
2. 小根堆存放pair<边权,点编号>，每次取出连接树的权最小的点
3. 取出点u，若已经在树中，直接跳过这条过时记录；否则加入树，累加边权
4. 遍历u的所有邻边，尝试更新邻点v到树的最小边权，更新后入堆
5. 最终判断选入树的点数量是否等于总点数，相等则存在MST
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
const int N=5005;
const int INF=1e9;
int n,m;
struct edge{int v,w;};
vector<edge> e[N];
priority_queue<pi,vector<pi>,greater<pi>> q;
int d[N],vis[N];
ll ans=0;
int cnt=0;

bool prim(int s)
{
    while(!q.empty()) q.pop(); // 清空堆内上一轮残留元素
    memset(vis,0,sizeof(vis));
    memset(d,0x3f,sizeof(d));
    d[s]=0;
    q.push({0,s});
    ans=0;cnt=0; // 重置答案、计数
    while(q.size())
    {
        int u=q.top().second; q.pop();
        if(vis[u])  continue; // 过时记录，跳过
        vis[u]=1;
        ans+=d[u];
        cnt++;
        for(auto ed:e[u])
        {
            int v=ed.v,w=ed.w;
            if(d[v]>w)
            {
                d[v]=w;
                q.push({d[v],v});
            }
        }
    }
    return cnt==n;
}

void solve()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) e[i].clear(); // 清空邻接表，适配多组样例
    for(int i=1;i<=m;i++)
    {
        int x,y,z;  cin>>x>>y>>z;
        e[x].push_back({y,z});
        e[y].push_back({x,z});
    }
    if(!prim(1))
        cout<<"orz\n";
    else
        cout<<ans<<'\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t=1;
    while(t--) solve();
    return 0;
}
