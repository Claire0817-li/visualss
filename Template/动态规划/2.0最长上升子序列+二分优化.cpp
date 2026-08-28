/*
贪心+二分求LIS
【题目：P1040 [NOIP2004 提高组] 合唱队形】
题目描述：
给定n位同学的身高序列，要从中选出合唱队形：
队列先严格递增，到达最高点后严格递减（最高点可以是第一个或者最后一个元素）。
求最少需要删除多少人，才能构成合唱队形。

算法思路：
1. up[i]：以a[i]结尾，从左边开始的最长上升子序列LIS长度
2. down[i]：以a[i]结尾，从右边开始的最长上升子序列长度（等价原数组从i向右看的最长下降子序列）
3. 把i当做峰顶，合唱队形长度 = up[i] + down[i] - 1，减1是i被重复计算了两次
4. mx：整个数组最大合唱队形长度
5. 需要删除的人数 = 总人数n - mx

时间复杂度：O(n log n)，利用lower_bound二分优化LIS
注意：本题是严格上升，使用lower_bound；如果是非严格要用upper_bound
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    // 读入所有人身高
    for(int i = 0; i < n; i++)
        cin >> a[i];

    // up[i]: 以a[i]结尾，从左到右的最长上升子序列长度
    // down[i]: 以a[i]结尾，从右到左的最长上升子序列长度
    vector<int> up(n), down(n);

    vector<int> t;  // LIS贪心辅助数组，t始终保持严格升序

    // --------求左边每个位置的LIS长度 up[]--------
    for(int i = 0; i < n; i++)
    {
        // 在t中找到第一个 >= a[i] 的元素下标pos
        int pos = lower_bound(t.begin(), t.end(), a[i]) - t.begin();

        if(pos == t.size())
            // a[i]比t所有元素都大，直接追加到末尾，LIS长度+1
            t.push_back(a[i]);
        else
            // 替换t[pos]，贪心：让序列末尾尽可能小，方便后续接更长序列
            t[pos] = a[i];

        // pos从0开始，序列长度是pos+1
        up[i] = pos + 1;
    }

    t.clear(); // 清空辅助数组，重新计算

    // --------求右边每个位置反向LIS down[]--------
    // 倒序遍历数组，相当于从右往左求最长上升子序列
    // 等价于原数组从i往右看，最长下降子序列
    for(int i = n - 1; i >= 0; i--)
    {
        int pos = lower_bound(t.begin(), t.end(), a[i]) - t.begin();

        if(pos == t.size())
            t.push_back(a[i]);
        else
            t[pos] = a[i];

        down[i] = pos + 1;
    }

    int mx = 0;
    // 枚举每一个点i作为合唱队形的峰顶
    for(int i = 0; i < n; i++)
    {
        // up[i]峰顶左边上升长度 + down[i]峰顶右边下降长度 -1（i重复算一次）
        mx = max(mx, up[i] + down[i] - 1);
    }

    // 总人数减去能选出的最长合唱队形，就是最少删掉的人数
    cout << n - mx;

    return 0;
}
