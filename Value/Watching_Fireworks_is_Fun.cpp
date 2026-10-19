/*
题目：烟花（单调队列优化DP）
状态定义：
f[i][j]：看完第 i 个烟花后，站在位置 j 时，能获得的最大快乐值
空间优化：滚动数组，只保存上一层last和当前层now
转移方程：
f[i][j] = max{ f[i-1][k] } + b[i] - abs( a[i] - j )
约束：k 需要满足 |k - j| ≤ D，D = (ti[i] - ti[i-1]) * d
也就是 k ∈ [ j-D , j+D ]
拆成两个窗口：
1. k ≤ j ：正向遍历j，窗口 [j-D , j]
2. k ≥ j ：反向遍历j，窗口 [j , j+D]
两个单调队列分别求区间最大值，取两者的max，再加上当前烟花收益代价
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
const ll INF=1e18;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // n:位置总数 m:烟花数量 d:单位时间最多移动距离
    ll n,m,d;  cin>>n>>m>>d;
    // a[i]:烟花i的位置，b[i]:烟花i快乐值，ti[i]:烟花i出现时刻
    vl a(m+1),b(m+1),ti(m+1);
    for(int i=1;i<=m;i++)    cin>>a[i]>>b[i]>>ti[i];

    // 滚动数组 f[0]上一层，f[1]当前层；初始值负无穷表示不可达
    vvl f(2,vl(n+1,-INF));
    // 初始：还没看任何烟花(i=0)，站任意位置j快乐值都是0
    for(int i=1;i<=n;i++)   f[0][i]=0;

    vl q(n+1); //单调队列，保存下标j，队列内f[last][下标]单调递减
    for(int i=1;i<=m;i++) //枚举第i个烟花
    {
        ll now=i&1;      //当前层，i奇数为1，偶数为0
        ll last=(i-1)&1; //上一层
        fill(f[now].begin(),f[now].end(),-INF); //当前层全部重置为负无穷

        ll h=1,t=0; //h队头，t队尾，q[h~t]是队列有效元素
        // =========正向循环：求 k <= j，窗口k ∈ [j-D , j] 的max f[last][k]=========
        for(int j=1;j<=n;j++)
        {
            //维护单调递减队列：队尾元素的值 ≤ 当前j的值，则弹出队尾
            while(h<=t&&f[last][q[t]]<=f[last][j])   t--;
            q[++t]=j; //当前下标入队

            ll D=(ti[i]-ti[i-1])*d; //两次烟花之间最多能移动的距离
            //窗口左边界：小于 j-D 的下标移出窗口（队头出队）
            if(q[h]<j-D)    h++;

            //此时队头q[h]就是窗口内f[last]最大值对应的下标
            f[now][j]=f[last][q[h]]; //先保存这个候选最大值，暂不加b和abs代价
        }

        h=1,t=0; //清空队列，准备反向遍历
        // =========反向循环：求 k >= j，窗口k ∈ [j , j+D] 的max f[last][k]=========
        for(int j=n;j>=1;j--)
        {
            //维护单调递减队列
            while(h<=t&&f[last][q[t]]<=f[last][j])   t--;
            q[++t]=j;

            ll D=(ti[i]-ti[i-1])*d;
            //窗口右边界：大于 j+D 的下标移出窗口
            if(q[h]>j+D)    h++;

            //两个候选取max，再加上当前烟花收益b[i]，减去移动代价abs(a[i]-j)
            f[now][j]=max(f[now][j],f[last][q[h]]) + b[i] - abs(a[i]-j);
        }
    }

    //答案：看完m个烟花后，所有位置的最大快乐值
    ll ans=-1e18;
    for(int i=1;i<=n;i++)   ans=max(f[m&1][i],ans);
    cout<<ans;
    return 0;
}
