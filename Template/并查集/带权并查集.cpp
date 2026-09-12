#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
const int N=50005;
int fa[N],d[N]; // fa[]并查集父节点；d[x]：x到fa[x]的权值，表示x与父的关系
/*
d[x]含义（模3）：
0：x 和 fa[x] 是同类
1：x 吃 fa[x]
2：x 被 fa[x] 吃
*/
int find(int x)
{
    if(fa[x]==x)    return x; // 找到根节点，直接返回
    int root=find(fa[x]);     // 递归先找到fa[x]的根，路径压缩
    d[x]=(d[x]+d[fa[x]])%3;   // 权值更新：x -> fa[x] + fa[x] -> root，合并成x直接到root的距离
    fa[x]=root;               // 路径压缩，x直接指向根
    return fa[x];
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,k; cin>>n>>k;
    // 初始化：每个点自己是根；【这里有bug！初始d[i]应该是0，不是1】
    for(int i=1;i<=n;i++)   {fa[i]=i;d[i]=1;}
    int ans=0; // ans记录假话数量
    while(k--)
    {
        int o,x,y;   cin>>o>>x>>y;
        // 假话条件1：x或y超出范围；或者o=2（x吃y）且x==y，自己不能吃自己
        if(x>n||y>n||(o==2&&x==y))  {ans++;continue;}
        int rx=find(x),ry=find(y); // 查找x,y的根，同时完成路径压缩+权值更新
        if(rx==ry) // x,y在同一个集合，检查给出的关系是否矛盾
        {
            if(o==1) // 说法：x和y同类
            {
                // 同类要求d[x] == d[y]（x到根，y到根关系相等）
                if(d[x]%3!=d[y]%3)    ans++;
            }
            if(o==2) // 说法：x吃y
            {
                // x吃y 等价于 (d[x] - d[y]) mod3 =1
                if(((d[x]%3)-(d[y]%3))!=1) ans++;
            }
        }
        else // 不在同一集合，合并两棵树，计算rx的权值
        {
            fa[rx]=ry; // 把rx的父亲设为ry
            if(o==1) // x,y同类：d[x] = d[y]
                d[rx]=(d[y]-d[x]+3)%3;
            else // o==2，x吃y：(d[x] - d[rx] - d[y])%3 =1 → d[rx]=(d[y]-d[x]-1+3)%3
                d[rx]=(d[y]-d[x]-1+3)%3;
        }
    }
    cout<<ans;
    return 0;
}
