/*
题目：求数组的第 k 大元素
题目描述：
多组测试数据。
每组给定 n 个整数，求出这 n 个数里的第 k 大的值。
第1大 = 最大值，第2大 = 第二大，以此类推。

输入：
第一行 t，表示测试用例组数。
每组：第一行 n k；之后 n 个整数。

输出：
每组输出一个整数：该数组第 k 大元素。

算法思路：最小堆（小根堆）
目标：只保留整个数组中最大的 k 个元素。
1. 使用小根堆，堆顶是堆内部的最小值。
2. 遍历每一个数字，不断压入堆。
3. 一旦堆的元素数量超过 k，就弹出堆顶（堆内当前最小的数）。
   含义：只要堆里多于 k 个，就把较小的淘汰掉。
4. 遍历全部数字结束后，堆中恰好存着全局最大的 k 个数字。
   小根堆堆顶就是这 k 个大数里最小的那个，也就是全局第 k 大。

时间复杂度：O(n log k)
n是数组长度，堆最多维护k个元素，每次push/pop代价 log k。
适合 n 很大、k 相对不大的场景。
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
    ios::sync_with_stdio(false); // 关闭cin同步，加速输入输出
    cin.tie(nullptr);            // 解绑cin与cout，避免cout刷新拖慢速度

    int t;
    cin >> t;
    while(t--)
    {
        int n,k;
        cin >> n >> k;
        // priority_queue<类型,底层容器,比较器>
        // greater<int> → 小根堆，堆顶是堆内最小值
        priority_queue<int,vector<int>,greater<int>> a;

        for(int i=0;i<n;i++)
        {
            int x;
            cin >> x;
            a.push(x);                 // 将当前数字加入堆
            if(a.size()>k)  a.pop();   // 堆超过k个，把堆内最小的丢掉
        }
        // 堆内是全局最大k个数，堆顶 = 第k大
        cout << a.top() << '\n';
    }
    return 0;
}
