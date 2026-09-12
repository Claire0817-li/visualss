/*
题目：求逆序对数量
题型：归并排序求逆序对
题目描述：
给定长度为 n 的数组，统计数组中逆序对的总个数。
逆序对定义：下标 i < j，且 a[i] > a[j]。

算法思路：归并排序分治
1. 分：把数组区间 [l,r]拆成 [l,mid] 和 [mid+1,r]，递归分别求左右区间内部的逆序对。
2. 治：归并合并两个有序子数组。
   当右半部分元素 a[j] < 左半部分 a[i] 时：
   左区间从 i ~ mid 的所有元素都大于 a[j]，一共 mid‑i+1 个，全部构成逆序对，累加到res。
3. 合并完成把辅助数组b的值拷贝回原数组a，完成本区间排序。

时间复杂度：O(n log n)
空间复杂度：O(n)，需要辅助数组b
注意点：
1. 逆序对数量可能很大，res必须用long long，int会溢出。
2. 数组下标这里从0开始。
3. a[i] <= a[j] 取等号，相等不算逆序对。
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

const int N=500010;
vl a(N),b(N);   // a原数组；b归并排序辅助数组
int n;
ll res=0;       // 存逆序对总数，一定要long long防止溢出

// msort：对区间[l,r]做归并排序，同时统计逆序对
void msort(int l,int r)
{
    if(l>=r)    return;                 // 区间只有一个或者空，递归终止
    int mid=(l+r)>>1;                   // 等价 mid = (l+r)/2
    msort(l,mid);       // 递归处理左半段
    msort(mid+1,r);     // 递归处理右半段

    int i=l,j=mid+1,k=l;
    // 双指针合并两个有序区间 [l,mid] 和 [mid+1,r]
    while(i<=mid&&j<=r)
    {
        if(a[i]<=a[j])
        {
            b[k++]=a[i++];  // 左边更小，直接放入辅助数组，无逆序对
        }
        else
        {
            b[k++]=a[j++];
            // a[j] < a[i]：i~mid全部都比a[j]大，全部形成逆序对
            res += mid - i + 1;
        }
    }
    // 把左区间剩下元素复制进辅助数组
    while(i<=mid)    b[k++]=a[i++];
    // 把右区间剩下元素复制进辅助数组
    while(j<=r)      b[k++]=a[j++];

    // 将辅助数组排好序的部分拷贝回原数组a
    for(int i=l;i<=r;i++)
    {
        a[i]=b[i];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    for(int i=0;i<n;i++)    cin>>a[i];
    msort(0,n-1);           // 对0~n‑1整个数组归并排序求逆序对
    cout<<res;
    return 0;
}
