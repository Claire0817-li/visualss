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

const int N=1e8+5;
bool vis[N];  // vis[i]=true 代表i是合数，false代表i是质数
vi prim;     // 按从小到大顺序存放筛出来的全部质数

// 欧拉筛(线性筛)：筛出2~n所有质数，存入prim
void getprim(int n)
{
    for(int i=2;i<=n;i++) // 依次枚举每一个数i
    {
        if(!vis[i]) prim.push_back(i); // i没被标记，说明i是质数，加入质数列表
        // 枚举已经找到的每个质数prim[j]，标记 i * prim[j] 为合数
        for(int j=0;1LL*i*prim[j]<=n;j++)
        {
            vis[i*prim[j]]=1; // i乘上这个质数，得到的数一定是合数，打上标记
            if(i%prim[j]==0) break; 
            // 核心：如果prim[j]是i的最小质因子，停止内层循环
            // 保证每个合数只会被【它自己的最小质因子】标记一次，实现O(n)线性复杂度
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 
    int n;  cin>>n;   // 筛质数的上界：只筛1~n范围内
    int q;  cin>>q;   // 查询次数
    getprim(n);       // 先预处理筛出全部质数
    while(q--)
    {
        int k;  cin>>k;        // 查询：第k小的质数
        cout<<prim[k-1]<<'\n'; // prim下标从0开始，第k个对应下标k-1
    }
    return 0;
}