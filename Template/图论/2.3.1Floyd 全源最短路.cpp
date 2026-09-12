/*
题型：Floyd 全源最短路
题目：无向连通图，求任意两点(i,j)之间的最短路径
算法原理：动态规划
状态定义：d[i][j] 代表从i到j的最短路长度
p[i][j] 记录i到j的最短路上i与j之间的中转点，用于后续路径还原
状态转移：d[i][j] = min(d[i][j], d[i][k] + d[k][j])
循环顺序：k（中转点）必须放在最外层
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

const int N=105;        // 点数量上限
int d[N][N];            // d[i][j]: i到j的最短路距离
int p[N][N];            // p[i][j]: i到j路径的中转插点，0代表无中间点
int n,m;                // n点数，m边数

void floyd()
{
    // k：枚举作为中转的节点，必须最外层
    for(int k=1;k<=n;k++)
    {
        // i：起点
        for(int i=1;i<=n;i++)
        {
            // j：终点
            for(int j=1;j<=n;j++)
            {
                // 松弛：i->k->j 比直接i->j更短，则更新
                if(d[i][j]>d[i][k]+d[k][j])
                {
                    d[i][j]=d[i][k]+d[k][j];
                    p[i][j]=k;        // 记录i到j的中间中转点k
                }
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin>>n>>m;
    memset(d,0x3f3f3f3f,sizeof(d)); // 距离数组初始化为无穷大
    memset(p,0,sizeof(p));           // 中转点数组初始化为0，代表无中间点
    
    for(int i=1;i<=n;i++)  
        d[i][i]=0;    // 自己到自己距离为0
    
    // 读入m条无向边
    for(int i=0;i<m;i++)
    {
        int u,v,w;  cin>>u>>v>>w;
        // 处理重边，只保留最小权值
        if(w<d[u][v])
        {
            d[u][v]=w;
            d[v][u]=w;
        }
    }

    floyd();  // 执行Floyd算法，计算所有点对最短路

    // 按题目要求输出：n行，每行n个数
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<d[i][j]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}
