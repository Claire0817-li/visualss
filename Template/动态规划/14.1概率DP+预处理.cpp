/*
题目算法标签：动态规划(DP) + 滚动数组优化 + 预处理 + 二分查找
原题模型：赠券收集问题（经典概率DP）

【题意简述】
每次从1~k中等概率选一个数字加到序列末尾。
q次询问，每次给p，求最小n，使得抽n次后，[1,k]全部出现过的概率 >= (p−ε)/2000，ε<1e-7。
等价：概率 >= p/2000，ε极小，代码仅在比较时做浮点容错。

【核心思路】
1. DP状态定义
pre[j]：抽取 n-1 次，恰好收集到 j 种不同数字的概率。
cur[j]：抽取 n 次，恰好收集到 j 种不同数字的概率。

2. DP转移方程
cur[j] = pre[j] * (1.0*j/k) + pre[j-1] * (1.0*(k-j+1)/k)
① pre[j] * j/k：之前已经有j种，本次抽到旧数字，种类不变
② pre[j-1] * (k-j+1)/k：之前只有j-1种，本次抽到新数字，种类+1

3. 预处理
只跑一次DP，算出prob数组：prob[n]代表抽n次集齐全部k种数字的概率。
prob数组单调递增：n越大，集齐全部数字的概率只会越来越大。
当概率接近1（>1-1e-12），停止预处理，后面概率几乎不再变化。

4. 查询阶段
prob单调递增，对每个询问二分查找最小的n，满足 prob[n] >= target - 1e-12。
预处理只算一遍，q次询问只用二分，避免重复DP，解决TLE超时。
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
const double e=1e-7;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k,q;   cin>>k>>q;
    vector<double> prob;
    // pre[j]:上一轮n-1次抽取，恰好收集j种数字的概率
    vector<double> pre(k+1,0.0);
    pre[0]=1.0;prob.push_back(pre[0]); // prob[0]对应抽0次，0次抽取集齐概率为0

    // 预处理DP，预计算每个n对应的集齐全部k种数字的概率
    for(int n=1;;n++)
    {
        vector<double> cur(k+1,0.0);
        for(int j=1;j<=k;j++)
        {
            // DP转移：两种互斥情况概率相加
            cur[j]=pre[j]*(1.0*j/k)+pre[j-1]*(1.0*(k-j+1)/k);
        }
        // cur[k]就是抽n次集齐所有k个数的概率，存入prob
        prob.push_back(cur[k]);
        // 概率无限接近1，继续增加n几乎不会改变概率，提前终止预处理
        if(cur[k]>1-1e-12)  break;
        swap(pre,cur); // 当前cur作为下一轮的pre
    }

    // 处理q次询问
    while(q--)
    {
        int p;
        cin>>p;
        double target=1.0*p/2000; // 阈值：概率至少要达到这个值
        int l=k,r=prob.size()-1;
        int ans;
        // 二分找满足条件的最小n，prob单调递增
        while(l<=r)
        {
            int mid=l+r>>1;
            // -1e-12用来抵消浮点计算误差，对应题目给的极小ε
            if(prob[mid]>=target-1e-12)
            {
                ans=mid;
                r=mid-1; // 继续向左寻找更小合法n
            }
            else
            {
                l=mid+1; // 当前mid不够，需要更大n
            }
        }
        cout<<ans<<"\n";
    }
    return 0;
}
