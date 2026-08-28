/*
题目：P2014 选课
题意：
N门课程，选恰好M门课，获取最大学分。
选课约束：选某一门课，必须选它的直接先修课；先修关系构成森林。
技巧：建立虚拟0号根，把所有没有先修课(k_i=0)的课程作为0的儿子，森林转单棵树。
虚拟节点0是必须选的，所以树上一共选 M+1 个点，答案 dp[0][m+1]

状态定义：
dp[u][j]：在u的子树中，**一共选j门课，并且u这门课必须选**，能够得到的最大学分。
    👉关键点：只要使用dp[u][*]，u就一定被选；不选u，子树一门都不能选。
dp[u][1] = s[u]：子树里面只选u自己，选1门课，学分等于u自己的学分。

转移方程：dp[u][j] = max(dp[u][j], dp[u][j‑k] + dp[v][k])
    u：当前父节点；v：u的一个子节点
    j：u子树总共选 j 门
    j‑k：u以及之前已经合并完的子树，一共选 j‑k 门
    k：当前v的子树里面选 k 门（v必须被选，k≥1）

循环说明：
1. dfs(v)：先把子树v全部计算完毕，子问题解决才能合并到父节点。
2. j 从 m+1 往下倒序遍历：和01背包一样，防止同一个子树被重复选取。
3. k ∈ [1, j‑1]：
    k>=1：v子树选k门，v必须选，k不能等于0；
    k<j：j‑k >= 1，保证u本身被选，u至少占1个名额。

数组说明：
const int N=305；节点编号0~300。
g[]：邻接表存树；s[i]代表i课程学分；s[0]默认0，虚拟根无学分。
dp[N][N]：dp[u][j]，u最多300，j最多m+1<=301。

易错点：
1. j必须倒序；正序会重复选同一个子树。
2. dp[u][j]的前提u必选；dp[v][k]前提v必选。
3. 答案 dp[0][m+1]，虚拟0占掉1个选课名额，真实课程选m门。
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

int n,m;
const int N=305;
vi g[N+1],s(N);         // g邻接表；s[i]第i门课学分；s[0]=0虚拟根
vvi dp(N,vi(N,0));      // dp[u][j] u子树选j门，u必选，最大学分

void dfs(int u)
{
    dp[u][1]=s[u];     // base：子树只选自己u，选1门课，学分s[u]

    // 遍历u每一个儿子v
    for(int v:g[u])
    {
        dfs(v);      // 递归，先完整算出v子树所有dp值

        /* ==========树上背包合并：把子树v合并进u ========== */
        // j倒序！！从大到小，防止重复复用v子树，和01背包道理一致
        for(int j=m+1;j>=1;j--)
        {
            // k：v子树选k门课
            for(int k=1;k<j;k++)
            {
                /*
                dp[u][j] = max(旧方案，新方案)
                旧dp[u][j]：不使用v这棵子树，保留原来的最优解
                dp[u][j‑k] + dp[v][k]：使用v子树，v子树拿k门；u+旧子树拿 j‑k门
                总课程数 = (j‑k)+k = j；学分相加。
                */
                dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k]);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        int k;  cin>>k>>s[i];
        g[k].push_back(i); // i的先修课是k；i作为k的儿子；k=0就挂到虚拟根0
    }
    dfs(0);
    cout<<dp[0][m+1];
    return 0;
}
