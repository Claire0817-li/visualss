/*
DP+单调队列优化 分段问题
题意：
n个碎片，切恰好k个连续段；每段长度∈[l,r]。
最大化 sum_{i=1}^k [ (-1)^(i+1) * S_i ]，S_i为第i段的和。
pre[i] 前缀和，pre[0]=0，pre[i]=a1+a2+...+ai
dp[j]：前j个碎片，分成 t-1 段的最大答案
ndp[i]：前i个碎片，分成 t 段的最大答案

转移：
最后一段是 j+1 ~ i，段长 i-j，要求 l ≤ i-j ≤ r ⇒ i-r ≤ j ≤ i-l
t奇数：ndp[i] = pre[i] + max{ dp[j] - pre[j] }
t偶数：ndp[i] = -pre[i] + max{ dp[j] + pre[j] }
手写单调队列：q存下标，h队头，tail队尾，维护窗口最大值
复杂度O(nk)，题目限制n*k ≤ 2e6，可以通过
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
using pi=pair<int,int>;
using pl=pair<ll,ll>;
using ULL=unsigned long long;
const ll INF=1e18;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // n碎片总数，k段数，l每段最小长度，r每段最大长度
    ll n,k,l,r; 
    cin>>n>>k>>l>>r;

    vl a(n+1),pre(n+1,0);
    // 预处理前缀和 pre
    for(int i=1;i<=n;i++)   
    {
        cin>>a[i];
        pre[i]=pre[i-1]+a[i];
    }

    // dp[j]：t-1层状态。初始t=0：0个元素分0段值为0，其余不可达(-INF)
    vl dp(n+1,-INF);
    dp[0]=0;

    // t：当前一共划分t段
    for(int t=1;t<=k;t++)
    {
        vl ndp(n+1,-INF); // ndp[i]：当前t层，前i个分成t段的最大值
        vi q(n+1);        // 手写单调队列，保存候选j的下标
        int h=1,tail=0;   // h队头指针，tail队尾指针；[h,tail]为队列有效区间，初始空

        for(int i=1;i<=n;i++)
        {
            int jr=i-l; // j的上界：j最大取i-l，保证段长i-j >= l
            if(jr>=0)
            {
                ll val;
                // 根据t奇偶，计算jr对应的权值
                if(t&1) val=dp[jr]-pre[jr];
                else    val=dp[jr]+pre[jr];

                // 维护单调递减队列：队尾权值 <= 当前val，弹出队尾
                while(tail>=h)
                {
                    ll w=(t&1)?dp[q[tail]]-pre[q[tail]]:dp[q[tail]]+pre[q[tail]];
                    if(w<=val)    
                        tail--;
                    else    
                        break;
                }
                q[++tail]=jr; // 新下标入队
            }

            int jl=i-r; // j的下界：j不能小于i-r，保证段长i-j <= r
            // 把队头小于jl的过期下标弹出窗口
            while(tail>=h&&q[h]<jl) 
                h++;

            // 队列非空，取出窗口最大值，计算ndp[i]
            if(tail>=h)
            {
                ll best;
                if(t & 1) best=dp[q[h]]-pre[q[h]];
                else      best=dp[q[h]]+pre[q[h]];

                if(t & 1) ndp[i]=pre[i]+best;
                else      ndp[i]=-pre[i]+best;
            }
        }
        dp.swap(ndp); // 滚动数组，dp更新为本层t的结果，准备下一轮t+1
    }
    cout<<dp[n]; // 答案：前n个碎片恰好k段的最大值
    return 0;
}
