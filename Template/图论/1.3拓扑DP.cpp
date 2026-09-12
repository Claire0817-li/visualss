/*
算法标签：DAG、拓扑排序、拓扑DP、有向无环图最长路
题目大意：
输入第一行 n,m，代表图的点数、边数。
之后 m 行每行三个整数 u,v,w(u<v)，表示一条 u→v 的有向边，边权 w。
保证 u<v，图天然为DAG（有向无环图）。
求：从1号点出发到n号点的最长路径总权值。
若1号点无法到达n号点，输出 -1。

解题思路：
1. DAG上求最长路，不能直接跑Bellman‑Ford/SPFA；标准做法是拓扑排序+DP。
2. dp[i]定义：从起点1到达i点的最长路径权值。
3. dp数组全部初始化为负无穷(-0x3f3f3f3f)，代表初始不可达；起点 dp[1] = 0。
4. Kahn拓扑排序：把所有入度为0的点放入队列。
5. 按拓扑序取出节点x，遍历x所有出边 x->y，边权weight：
    dp[y] = max(dp[y], dp[x] + weight);
    y的入度减一；入度变为0，代表y所有前驱已经处理完毕，y入队列。
6. 跑完拓扑后判断：
    如果 dp[n]仍然等于负无穷，说明1无法到达n，输出‑1；
    否则输出 dp[n]。

关键点：
1. 判环( cnt==n ) 和 判断起点可达终点 是两件事；本题用dp[n]的值判断可达。
2. u<v保证不会有环，不需要处理环输出-1。
3. 松弛更新必须按照拓扑序，保证更新y的时候所有前驱x都已经计算完成。
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

const int N=1510;
int n,m;
vi e[N];        // e[u]：存储u出发边的目标点
vi ew[N];       // ew[u]：存储u出发对应边的边权，ew[u][i]对应e[u][i]这条边的权
vi dp(N,-0x3f3f3f3f);   // dp[i]：1到i的最长路径，初始负无穷表示不可达
vi din(N,0);    // din[i]：i节点的入度

void toposort()
{
    queue<int>q;
    int cnt=0;  // cnt统计处理过的节点总数，本题图无环，cnt最终等于n
    // 将所有入度为0的点加入拓扑队列
    for(int i=1;i<=n;i++)
    {
        if(din[i]==0)
            q.push(i);
    }
    while(q.size())
    {
        int x=q.front();
        q.pop();
        cnt++;
        //遍历x所有出边
        for(int i = 0;i < e[x].size();i++)
        {
            int y=e[x][i];
            int weight=ew[x][i];
            //拓扑DP松弛：用x更新y的最长路
            dp[y]=max(dp[y],dp[x]+weight);
            din[y]--;               // y的前驱数目减一
            if(din[y]==0)           // y全部前驱处理完成，可以处理y
            {
                q.push(y);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    dp[1]=0;    //起点1，到自己路径权值为0

    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        e[u].push_back(v);
        ew[u].push_back(w);
        din[v]++;   //v的入度+1
    }
    toposort(); //执行拓扑排序+DP更新

    // dp[n]保持初始负无穷：1无法到达n
    if(dp[n]==-0x3f3f3f3f)
        cout<<-1;
    else
        cout<<dp[n];
    return 0;
}
