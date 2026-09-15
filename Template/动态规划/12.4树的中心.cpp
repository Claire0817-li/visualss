#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
const int N=1e4+5;
int n;
// 邻接表存边：v是邻接点，w是边权
struct edge{int v,w;};
vector<edge> e[N];

// d1[u]: u向子树内部走的最长距离
// d2[u]: u向子树内部走的次长距离
// p1[u]: u的最长子路径对应的子节点
// up[u]: u向父节点方向（向上）能走的最长距离
ll d1[N],d2[N];
int p1[N];
ll up[N];

// 第一遍DFS：自底向上，后序遍历，计算d1,d2,p1
void dfs_d(int u,int fat)
{
    // 初始化：u初始向下最长、次长都是0（没有子节点时）
    d1[u]=0;
    d2[u]=0;
    p1[u]=-1; // -1代表没有子节点

    // 遍历u所有邻边
    for(auto &p:e[u])
    {
        int v=p.v;
        int w=p.w;
        if(v==fat) continue; // 不能往父节点回走

        // 递归先处理子节点v，算出v的向下最长距离
        dfs_d(v,u);
        // 从u经过v向下走的距离 = v的向下最长 + u-v这条边权
        ll cur = d1[v] + w;

        // 更新最长、次长
        if(cur >= d1[u])
        {
            // 当前这条比原来最长还大：原来最长降级为次长
            d2[u] = d1[u];
            d1[u] = cur;
            p1[u] = v; // 标记u最长的子路径是走向v
        }
        else if(cur > d2[u])
        {
            // 比最长小，但比次长大：更新次长
            d2[u] = cur;
        }
    }
}

// 第二遍DFS：自顶向下，先序遍历，换根，计算up数组
void dfs_u(int u,int fat)
{
    // 遍历u所有邻边，处理u的子节点v
    for(auto &p:e[u])
    {
        int v=p.v;
        int w=p.w;
        if(v==fat) continue;

        // 核心转移公式
        if(p1[u]==v)
        {
            // u的最长子路径刚好就是v！
            // v向上走的时候不能复用u的最长子路径（走回去了）
            // 只能选：u向上最长up[u] OR u次长向下d2[u]，取max再加边权
            up[v] = max(up[u], d2[u]) + w;
        }
        else
        {
            // u最长子路径不是v，可以直接使用u的最长向下d1[u]
            up[v] = max(up[u], d1[u]) + w;
        }
        // 递归向下处理v的子节点
        dfs_u(v,u);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<n;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        e[a].push_back({b,c});
        e[b].push_back({a,c});
    }

    // 第一步：自底向上求d1,d2,p1，以1为根
    dfs_d(1,-1);
    up[1]=0; // 根节点没有父节点，向上距离为0
    // 第二步：自顶向下换根，求所有点的up值
    dfs_u(1,-1);

    ll ans=1e18;
    // 遍历每个点，算出该点全局最远点距离，取最小
    for(int i=1;i<=n;i++)
    {
        // 点i的全局最远 = max(向下子树最长d1[i],向上父侧最长up[i])
        ll far = max(d1[i], up[i]);
        ans = min(ans, far);
    }
    cout<<ans;
    return 0;
}
