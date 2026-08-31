/*
题目：POJ 1106 Transmitters 半圆覆盖
题目大意：
给定一个圆的圆心坐标、半径，再给出n个平面上的点。
可以放置一个和该圆半径完全相同的半圆，半圆可以绕圆心任意旋转。
求这个半圆最多能够覆盖多少个给出的点（点落在圆弧/直径上也算被覆盖）。

核心几何结论：
最优位置的半圆，一定可以旋转到：半圆的直径上压着至少一个输入点。
所以不需要枚举全部角度，只需要枚举每一个圆内的点作为直径上的点，计算此时半圆能覆盖多少点即可。

解题思路：
1. 先筛点：只保留落在圆内部或者圆上的点，圆外面的点永远不可能被半圆覆盖，直接丢弃。
2. 枚举每一个圆内点P，让P落在半圆的直径上；过圆心O、P画出一条直径直线。
3. 使用叉积判断其余点在这条直径直线的哪一侧。
   cross >= 0：点在向量OP左侧或者落在直径上，属于朝左的半圆。
   cross < 0：点在向量OP右侧，属于朝右的半圆。
4. 同一条直径对应两个朝向相反的半圆：左边cnt个点，右边 sz‑cnt 个点，两者取最大值。
5. 所有枚举取全局最大值，即为答案。

注意坑：
① 距离比较使用距离平方，不开sqrt，规避浮点数精度问题。
② 叉积等于0（点落在直径）必须算入覆盖。
③ 不能只算左侧cnt，必须同时比较 max(cnt,sz‑cnt)，防止反向没有输入点漏掉最优解。
④ size()返回无符号size_t，转long long避免无符号数比较BUG。
*/
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

ll x,y;         // 圆心全局坐标
double r;       // 圆半径，可以是小数

/**
 * @brief 叉积运算，判断点b相对于向量 O->a 的位置
 * @param a 向量终点a
 * @param b 待判断点b
 * @return true：b在向量Oa左侧 或者 三点共线；false：b在向量Oa右侧
 * 向量 oa = (a.first‑x , a.second‑y)
 * 向量 ob = (b.first‑x , b.second‑y)
 * 叉积 cj = oa.x * ob.y - oa.y * ob.x
 * cj > 0  ：b在左侧
 * cj = 0  ：b落在直线OP上（直径上）
 * cj < 0  ：b在右侧
 */
bool cross(pair<ll,ll> &a,pair<ll,ll> &b)
{
    ll cj=(a.first-x)*(b.second-y)-(a.second-y)*(b.first-x);
    if(cj>=0)   return true;
    return false;
}

/**
 * @brief 计算两点之间距离的平方，避免sqrt浮点误差
 * @return 距离平方 long long
 */
ll dis(pair<ll,ll> &a,pair<ll,ll> &b)
{
    return (a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 多组输入，r<0作为结束标记
    while(cin>>x>>y>>r)
    {
        if(r<0)   break;

        ll n;  cin>>n;
        vector<pair<ll,ll>> dot;   // 存储所有在圆内/圆上的点
        pair<ll,ll> O={x,y};

        // 筛点：只保留圆内部、圆上的点，圆外直接丢弃
        for(ll i=0;i<n;i++)
        {
            ll cx,cy;    cin>>cx>>cy;
            pair<ll,ll> c={cx,cy};
            // dis(c,O) 距离平方； r*r半径平方，平方比较，不用开根号
            if(dis(c,O)<=(r*r))   dot.push_back(c);
        }

        ll ans=0;
        ll sz = (ll)dot.size(); // 圆内点总数，强转long long消除size_t无符号警告

        // 枚举：把dot[i]放在半圆的直径上
        for(ll i=0;i<sz;i++)
        {
            ll cnt=0;
            auto t=dot[i];
            // 统计有多少点在向量O‑t的左侧（含直径）
            for(ll j=0;j<sz;j++)
            {
                if(cross(t,dot[j])) cnt++;
            }
            // cnt：朝左半圆点数； sz‑cnt：朝右半圆点数，两个朝向都要考虑
            ans = max(ans, max(cnt, sz - cnt));
        }
        cout<<ans<<'\n';
    }
    return 0;
}
