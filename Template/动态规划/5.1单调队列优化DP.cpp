/*
题目：P2627 / LOJ10177 修剪草坪
算法：单调队列优化DP
题意：n头牛，每头牛有权值a[i]，最多连续选k头牛。求选出牛的权值总和最大值。
思路转化：
  直接求最大选中和不好做，换思路：总和减去【最少舍弃的权值和】。
  约束：不能连续选k+1头牛 → 任意连续k+1头牛，至少舍弃一头。
状态定义：
  f[i]：前i头牛，**强制舍弃第i头牛**时，所有被舍弃牛的权值总和最小值。
转移方程：
  f[i] = min{ f[j] } + a[i]，其中 j ∈ [i−k , i−1]
  j是上一头舍弃的牛；j与i之间全部选，中间选中牛数量最多k头，满足题目限制。
单调队列作用：维护区间 [i−k, i−1] 内f[j]的最小值。队列存下标，f值单调递增。
收尾逻辑：
  最后一个舍弃的牛x必须落在区间 [n−k+1 , n]。
  原因：x舍弃，x+1~n全部选中，选中长度 n−x ≤ k；
  等价条件 i>n−k，枚举这一段所有f[i]，取最小值s。
答案 = 全部牛总权值和 − 最小舍弃代价 s
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,k;    cin>>n>>k;
    k++;    // 最多连续选k头牛 → 任意连续k+1头牛至少舍弃一头，区间长度变为k+1

    vi a(n+1);
    ll sum=0;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        sum+=a[i]; // sum：所有牛权值总和
    }

    vi q(n+1);  // 单调队列，存放f数组的下标
    int h=1,t=0;// h队头指针，t队尾指针，[h,t]为队列有效区间
    vl f(n+1,0);// f[i]：前i头牛，舍弃i，舍弃总和最小值
    ll s=LLONG_MAX; // s：记录合法最后舍弃点的最小舍弃代价

    for(int i=1;i<=n;i++)
    {
        // 维护单调递增队列：队尾f值 >= f[i-1]，直接弹出
        // i-1是新候选j；f[i-1]更小，队尾大的f[j]永远不会成为最优解
        while(h<=t&&f[q[t]]>=f[i-1])
            t--;
        q[++t]=i-1; // 将i-1这个下标入队

        // 弹出越界队头：j不能小于 i-k，超出窗口的下标失效
        if(q[h]<i-k)
            h++;

        // DP转移：取窗口内最小f[j] + 当前舍弃的a[i]
        f[i]=f[q[h]]+a[i];

        // i落在候选最后舍弃点区间 [n-k+1,n]，更新最小舍弃代价s
        if(i>n-k)
            s=min(s,f[i]);
    }

    cout<<sum-s;
    return 0;
}
