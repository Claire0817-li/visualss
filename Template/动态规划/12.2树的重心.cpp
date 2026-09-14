#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
const int N=1e6+5; 
int n;             // n：树的总节点数量
vi e[N];           // e[u]：邻接表，保存u所有相连的节点，存无向树
int sz[N];         // sz[u]：以u作为根时，u这棵子树包含的节点总数
int ms[N];         // ms[u]：删掉节点u之后，拆分出来所有连通块里最大的那块的大小
// dfs函数：当前访问节点u，fa是u的父节点（用来防止往回走）
void dfs(int u,int fa)
{
    sz[u]=1;        // 子树大小初始为1，代表节点u本身
    int mx=0;       // mx：保存u所有子树中最大的子树节点数量
    for(int v:e[u]) // 遍历u所有相邻的节点v
    {
        if(v==fa) continue; // 如果v是父节点，跳过，避免回头递归死循环
        dfs(v,u);           // 递归访问子节点v，v的父节点是u
        sz[u]+=sz[v];       // 把子树v的节点数量累加进sz[u]
        mx=max(mx,sz[v]);   // 更新最大子树大小
    }
    // n-sz[u]：删掉u之后，父节点那一侧剩下的节点数量
    // mx现在是子树里最大块，和父侧那块比较，取较大值，就是删除u后的最大连通块
    mx=max(mx,n-sz[u]);
    ms[u]=mx; // 将这个最大值存入ms[u]
}

int main()
{
    ios::sync_with_stdio(false); // 关闭cin与stdio同步，加速cin读入大数据
    cin.tie(nullptr);           // 解绑cin和cout，进一步加快输入速度

    cin>>n; // 读入树的节点总数
    for(int i=1;i<n;i++) // 树一共有n-1条边，循环读入每条无向边
    {
        int u,v;cin>>u>>v;
        e[u].push_back(v); // u连v，邻接表添加
        e[v].push_back(u); // v连u，无向边双向存储
    }

    dfs(1,-1); // 从节点1开始DFS，根节点没有父节点，父参数写-1

    int as=0x3f3f3f3f; // as：记录所有ms里的最小值，初始值设为无穷大
    for(int i=1;i<=n;i++) as=min(as,ms[i]); // 遍历全部点，找到最小的ms值

    vi ans; // ans数组，用来存放所有重心节点编号
    for(int i=1;i<=n;i++)
    {
        if(ms[i]==as) ans.push_back(i); // 如果当前点ms等于最小值，就是重心
    }

    // 输出所有重心，每个数字后面跟空格（末尾会多出空格，大部分OJ可接受）
    for(int i=0;i<ans.size();i++)
    {
        cout<<ans[i]<<" ";
    }
    return 0;
}
