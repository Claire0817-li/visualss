/*
题目算法标签：字符串、贪心、双指针、最小表示法
题目简述：给定长度n的字符串s，求s的最小循环同构串（最小表示）
核心思路：
    循环同构：将字符串不断把首字符移到末尾得到的所有串；最小表示就是其中字典序最小的串。
    常规s+s拼接写法需要2倍内存，n<=1e7会MLE；本版本用取模模拟环形，只保存原串，内存O(n)。
    双指针i,j作为两个候选起点，k记录当前连续相等的比较长度。
    若s[(i+k)%n]==s[(j+k)%n]，k++继续向后对比；
    字符不等时，字典序更大的那一侧起点段全部作废，起点直接 +=k+1；
    若i,j重合则j++错开，保证两个候选起点不同。
    最终min(i,j)就是最小表示的起始下标，循环取模输出n个字符。

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

int main()
{
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);         
    int n; cin>>n;
    string s; cin>>s;
    int i=0,j=1,k=0; // i,j：两个候选起点；k：当前连续相等字符的比较长度
    while(i<n && j<n && k<n) // i,j必须是原串合法起点；k最多比较n位
    {
        char a = s[(i+k)%n]; // 取模模拟环形，i起点向后偏移k位
        char b = s[(j+k)%n]; // 取模模拟环形，j起点向后偏移k位
        if(a == b)
        {
            k++; // 当前字符相等，继续往后比较
        }
        else
        {
            // a更大：i开头的串字典序更大，i~i+k全部不可能为答案，i直接跳到i+k+1
            if(a > b) i += k+1;
            // b更大：j开头的串字典序更大，j~j+k全部不可能为答案，j直接跳到j+k+1
            else j += k+1;

            if(i == j) j++; // 两候选下标重合，j后移一位，保证起点不同
            k = 0; // 本轮比较结束，重置比较长度k，准备下一轮对比
        }
    }
    int p = min(i,j); // 取两个候选中较小下标，即为最小表示的起点

    for(int t=0;t<n;t++)
    {
        cout<<s[(p + t)%n];
    }
    return 0;
}
