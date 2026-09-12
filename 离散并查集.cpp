#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

/**
 * 题目：Kingdom of Flealand
 * 题意：
 *  有 n 个画布格子，编号 1~n，初始每个格子颜色互不相同，共 n 种颜色。
 *  给出 m 条咒语，每条咒语给出格子区间 [L0,R0]；
 *  施放该咒语：可以在区间内任选两个位置 u、v，令 a_u = a_v。
 *  m 条咒语必须全部使用，求操作结束后画布最少剩余多少种颜色。
 * 数据范围：
 *      n 最大可达 1e9，∑m ≤ 2e5
 *
 * 核心模型转化（本题关键点）
 *  格子 i 和 i+1 中间存在一条缝隙（边 i）。打通缝隙 i，则左右格子颜色统一，总颜色数 −1。
 *  n 个格子一共有 n‑1 条缝隙。打通 cnt 条缝隙，剩余颜色数量 = n − cnt。
 *
 *  咒语作用格子区间 [L0,R0]：可以打通缝隙区间 [L0 , R0‑1] 内任意一条缝隙。
 *  若 L0 == R0：缝隙区间 l > r，没有缝隙可以打通，咒语无效。
 *
 * 问题等价转换：
 *  给定 m 个边区间，每个区间最多选 1 个点（缝隙），每个点最多选一次，求最多选出点的数量 cnt。
 *  答案 ans = n − cnt。
 *
 * 贪心策略：区间选点
 *  1. 将所有边区间按照右端点从小到大排序。
 *  2. 依次处理每个区间，选取区间内 ≥ l 的第一条未被占用的缝隙。
 *  按右端点排序的原因：优先使用靠左空闲点，把靠右点留给后续区间，全局选取数量最大。
 *
 * 离散并查集(map实现)
 *  缝隙编号最大1e9，无法开数组；map只保存被占用过的缝隙。
 *      mp中不存在key：缝隙空闲；
 *      mp存在key：缝隙被占用，mp[key]为跳转目标位置。
 * find函数：递归实现路径压缩，返回 ≥ l 的第一条空闲缝隙编号。
 */

/**
 * @brief 离散并查集查找，带路径压缩
 * @param mp map存储被占用缝隙的跳转指针
 * @param l 查询起点
 * @return >= l 的第一条空闲缝隙编号
 */
ll find(map<ll,ll>&mp,ll l)
{
    if(!mp.count(l))
        return l;               // l不在map，缝隙空闲，直接返回
    else
        return mp[l]=find(mp,mp[l]); // 递归找根，路径压缩，修改跳转指针
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);   // 关闭同步，加速大量输入
    int t;  cin>>t;
    while(t--)
    {
        ll m,n; cin>>m>>n;  // m：咒语数量；n：画布格子数量
        vector<pair<ll,ll>> a;
        for(ll i=0;i<m;i++)
        {
            ll L0,R0;   cin>>L0>>R0;
            // 格子区间 [L0,R0] 转换为缝隙(边)区间 [L0, R0‑1]
            a.emplace_back(L0,R0-1);
        }
        // 边区间按照右端点从小到大排序，贪心核心
        sort(a.begin(),a.end(),[](const pair<ll,ll>&a,const pair<ll,ll>&b){
            return a.second<b.second;
        });

        ll cnt=0;           // cnt：成功打通的缝隙总条数
        map<ll,ll> mp;      // 离散并查集，存储被占用缝隙的跳转指针

        for(auto seg:a)
        {
            ll l=seg.first;
            ll r=seg.second;
            if(l>r) continue; // l>r：原始为单点咒语，无缝隙，直接跳过

            ll x=find(mp,l);  // 找到 >= l 的第一条空闲缝隙
            if(x<=r)          // 空闲缝隙落在当前边区间内部，可以打通
            {
                cnt++;
                // x缝隙被占用；设置x的跳转目标：x+1往后第一条空闲缝隙
                mp[x]=find(mp,x+1);
            }
            // x>r：区间内全部缝隙已占用，咒语空操作，cnt不变
        }
        cout<<n-cnt<<"\n"; // 初始n种颜色，打通cnt条缝隙，剩余颜色 n‑cnt
    }
    return 0;
}
