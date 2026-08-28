#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

/*
题目：最大子序和
题意：给定n个数字，求一段连续子数组，子数组长度不能超过m，求子数组的最大总和。
思路：前缀和 + 单调递增队列
公式：区间[l,i]的和 = pre[i] - pre[l‑1]
    i：子数组右端点
    l‑1：前缀和数组的左端点下标
限制条件：子数组长度 i-(l‑1) ≤ m → l‑1 ≥ i‑m
对每个右端点i，要在窗口 [i‑m , i‑1] 中找到最小的pre[l‑1]，pre[i]减去最小pre，差值就最大。
注意：i不能作为自己的左端点，所以先计算答案，再把i压入队列留给后面使用。
时间复杂度 O(n)，每个元素最多入队一次、出队一次。
*/

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n,m; cin>>n>>m;   // n：数组元素个数，m：子数组允许的最大长度
    vl p(n+1),pre(n+1,0);// p[]原始数组；pre[]前缀和数组，pre[0]=0
    // 计算前缀和 pre[i] = p[1]+p[2]+...+p[i]
    for(ll i=1;i<=n;i++)
    {
        cin>>p[i];
        pre[i]=pre[i-1]+p[i];
    }

    ll h=0,t=0;          // h队头指针，t队尾指针；队列有效区间 [h,t]
    vl q(n+1);           // 单调队列，**存储pre数组的下标，不是存数值**
    q[0]=0;              // 预先把下标0入队，pre[0]=0，支持子数组从第一个元素开始选取
    ll ans=-1e18;        // 答案初始负无穷，防止数组全部是负数时出错

    for(ll i=1;i<=n;i++) // i代表子数组的右端点
    {
        // 1.清理过期队头：如果队头下标小于窗口下界i‑m，代表已经滑出合法窗口，队头后移
        if(h<=t&&q[h]<i-m)
            h++;

        // 2.更新答案：q[h]是窗口内pre最小的下标，pre[i]-pre[q[h]]就是以i为右端点的合法最大子段和
        ans=max(ans,pre[i]-pre[q[h]]);

        // 3.维护单调递增队列：队尾对应的pre值大于等于当前pre[i]，全部弹出
        // pre[i]数值更小，下标位置更靠后；后面所有右端点选i都会比选队尾更优，队尾直接舍弃
        while(h<=t&&pre[i]<=pre[q[t]])
            t--;

        // 4.把当前下标i加入队列，本轮i不作为本次的左端点，留给后续更大的i当作候选左端点
        q[++t]=i;
    }
    cout<<ans;
    return 0;
}