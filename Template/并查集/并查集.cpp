/**
 * @brief 并查集(Disjoint‑Set‑Union, DSU)模板
 * 功能：维护元素之间的连通关系，支持合并集合、查询两点是否同集合
 * 题目模型：
 *  给定 n 个元素，m 次操作
 *  操作1 z=1：把 x 和 y 所在集合合并
 *  操作2 z=2：查询 x,y 是否属于同一个集合，输出 Y / N
 *
 * 并查集两大核心优化：
 * 1.路径压缩 find：查询的时候把沿途节点直接指向根，降低后续查询时间
 * 2.按大小合并(启发式合并)unionset：小集合合并到大集合，保证树深度不会过大
 * 时间复杂度：单次操作几乎 O(1)，均摊 α(n)，α是阿克曼反函数，增长极慢
 *
 * 注意点：
 * 1.数组开 N=2e5+5，最多处理 2e5 个点
 * 2.注意下标：代码初始化 for(ll i=0;i<n;i++) fa[i]=i; 代表元素编号从 0 开始
 *   如果题目点编号是从 1 开始，循环要改成 i从1到n
 */
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

const int N=200005;   // 最大节点数量 2e5
vl fa(N);     // fa[x]：x的父节点，存储所属集合的父亲
vl siz(N,1);  // siz[x]：只有根节点才有意义，代表该集合内部元素总个数

/**
 * @brief find函数：查找x所在集合的根节点，附带路径压缩
 * @param x 查询的节点
 * @return x所在集合根编号
 */
ll find(ll x)
{
    // 如果自己的父是自己，说明是根节点，直接返回
    if(fa[x]==x)
        return x;
    // 路径压缩：递归向上找根，把x的父直接赋值为根，后续查询一步直达根
    return fa[x]=find(fa[x]);
}
/*unionset：合并x,y两个点所在的集合（按集合大小合并）*/
void unionset(ll x,ll y)
{
    ll a=find(x); // a:x的根
    ll b=find(y); // b:y的根
    if(a==b) return; // 已经在同一个集合，无需合并
    // 按大小合并：保证小集合挂到大集合下面，限制树高度
    if(siz[a]>siz[b])   swap(a,b);
    fa[a]=b;          // 把小集合的根a，父设置为大集合根b
    siz[b]+=siz[a];   // 更新大集合的大小，加上被合并集合的元素数量
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n,m;
    cin>>n>>m;

    // 初始化：每个点一开始自己独立成为一个集合，父节点是自己
    for(ll i=0;i<n;i++)
        fa[i]=i;

    while(m--)
    {
        ll z,x,y;
        cin>>z>>x>>y;
        if(z==1)
        {
            // 操作1：合并x,y所在集合
            unionset(x,y);
        }
        else
        {
            // 操作2：查询x,y是否连通，同根输出Y，不同输出N
            if(find(x)==find(y))
                cout<<"Y\n";
            else
                cout<<"N\n";
        }
    }
    return 0;
}
