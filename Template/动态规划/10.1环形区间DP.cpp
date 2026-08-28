/*
【算法题型：区间DP · 环形区间DP（破环成链）】
洛谷 P1063 能量项链
题目大意：
n颗珠子围成一个环形。每颗珠子有头标记、尾标记。
珠子 i 的头标记为 e[i]，尾标记为 e[i+1]。
合并两颗相邻珠子，释放的能量 = 左边珠子的头 × 中间公共标记 × 右边珠子的尾。
把一整串珠子全部合并成一颗，求可以释放的最大总能量。

破环成链：
环形不好处理，将原数组复制一份接在原数组后面 e[n+i]=e[i]，数组长度变为 2n。
这样环上任意一段连续n颗珠子，都等价于新数组上某一段长度为n的连续子串。

------------------------------------------
状态定义：
dp[l][r]：合并区间 [l , r‑1] 的所有珠子，得到的最大能量。
注意：dp[l][r] 区间下标是 [l,r]，但是实际珠子是 l ~ r‑1。
珠子数量 = r - l。
例：
dp[l][l+1]：珠子只有l，珠子数量1，不需要合并，能量为0。
dp[l][l+2]：珠子 l、l+1，两颗珠子，可以合并。

转移理解：
把 [l, r‑1] 的珠子，在k位置切分成两段：
第一段珠子：[l , k‑1]  对应dp[l][k]
第二段珠子：[k , r‑1]  对应dp[k][r]

合并完左右两部分之后，最后将这两大块合并，产生能量 e[l] * e[k] * e[r]
总能量 = 左边能量 + 右边能量 + 本次合并新增能量
dp[l][r] = max(dp[l][r], dp[l][k] + dp[k][r] + e[l] * e[k] * e[r])

循环len：代表dp数组的区间长度 r‑l+1
len=2：dp[l][l+1]，1颗珠子，不用合并；
len=3：dp[l][l+2]，2颗珠子，可以合并；
我们一共有n颗珠子，对应 dp区间长度 len = n+1。

答案：
我们要找所有连续n颗珠子，也就是 dp[i][i+n]，i从1~n，取最大值。

------------------------------------------
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

    int n;
    cin>>n;
    // 破环成链，数组开2n+2，避免下标越界
    vi e(2*n+2);
    for(int i=1;i<=n;i++)
    {
        cin>>e[i];
        e[n+i]=e[i];  // 复制一遍，接在后面
    }

    // dp[l][r]：合并珠子[l, r‑1]获得的最大能量
    vvi dp(2*n+2, vi(2*n+2,0));

    // len：dp数组上区间[l,r]的长度，r = l + len -1
    // len=2：1颗珠子，无合并；len=3：2颗珠子，开始合并；最大len=n+1：n颗珠子
    for(int len=3; len <= n+1; len++)
    {
        // l枚举dp区间左端点，保证右端不超过2n
        for(int l=1; l + len -1 <= 2*n; l++)
        {
            int r = l + len - 1;   // dp区间右端点

            // k是分割点，把[l,r]切分成 [l,k] 和 [k,r]
            // k不能等于l，也不能等于r
            for(int k = l+1; k < r; k++)
            {
                // dp[l][k]：左边珠子[l,k‑1]的能量
                // dp[k][r]：右边珠子[k,r‑1]的能量
                // e[l]*e[k]*e[r]：最后合并两大块释放的能量
                dp[l][r] = max(dp[l][r], dp[l][k] + dp[k][r] + e[l] * e[k] * e[r]);
            }
        }
    }

    int ans = 0;
    // 枚举所有起点i，取连续n颗珠子的最大能量 dp[i][i+n]
    for(int i = 1; i <= n; i++)
    {
        ans = max(ans, dp[i][i+n]);
    }
    cout << ans;

    return 0;
}