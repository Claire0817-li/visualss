/*
算法标签：倍增LCA、最近公共祖先、树上倍增、DFS
思路：
倍增LCA，利用二进制拆分思想预处理每个点向上跳2^k步的祖先。
查询分两步：
1. 将深度更深的点向上跳跃，两点对齐到同一深度；
2. 两点同步向上跳，尽可能跳大步，直到LCA的子节点，最后返回父节点。
复杂度：预处理O(n log n)，单次查询O(log n)
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

const int N=5e5+5;   // 最大节点数
int n,m,s;           // n点数，m查询次数，s根节点
vi e[N];             // 邻接表存树
int fa[N][20];       // fa[u][k]：u向上跳2^k步的祖先
int dep[N];          // dep[u]：u节点深度

// dfs预处理深度、倍增祖先表
void dfs(int u,int father)
{
    dep[u]=dep[father]+1;        // 当前节点深度 = 父节点深度+1
    fa[u][0]=father;             // 2^0=1步，直接父节点
    // 倍增递推：跳2^i步 = 先跳2^(i-1)，再跳2^(i-1)
    for(int i=1;i<=19;i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    // 遍历邻接点，递归子树，避开回向父节点
    for(int v:e[u])
    {
        if(v!=father)
            dfs(v,u);
    }
}

// 查询u和v的最近公共祖先
int lca(int u,int v)
{
    // 保证u是深度更大的点
    if(dep[u]<dep[v])
        swap(u,v);
    // 从最大步长往下，把u上提到和v深度一致
    for(int i=19;i>=0;i--)
    {
        if(dep[fa[u][i]]>=dep[v])
            u=fa[u][i];
    }
    // 对齐后两点重合，该点就是LCA
    if(u==v)
        return v;
    // 同步向上跳，祖先不同才跳，防止跳过LCA
    for(int i=19;i>=0;i--)
    {
        if(fa[u][i]!=fa[v][i])
        {
            u=fa[u][i],v=fa[v][i];
        }
    }
    // 循环结束，u、v停在LCA的两个子节点，父节点即为LCA
    return fa[u][0];
}

void solve()
{
    cin>>n>>m>>s;
    // 建无向树
    for(int i=1;i<n;i++)
    {
        int x,y; cin>>x>>y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    dfs(s,0); // 从根s开始预处理，根的父节点设为0
    // m次查询
    while(m--)
    {
        int a,b; cin>>a>>b;
        cout<<lca(a,b)<<'\n';
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t=1;
    while(t--) solve();
    return 0;
}
