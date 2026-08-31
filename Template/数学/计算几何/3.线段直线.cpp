/*
POJ 3304 Segments
题目大意：
给定 n 条二维平面线段。
问：是否存在一条直线，把所有线段投影到这条直线上之后，所有投影线段拥有一个公共交点。

----------几何转化（核心定理）----------
原问题等价于：是否存在一条【无限长直线】，能够和每一条输入线段都相交。

推论：
如果存在这样一条满足条件的无限长直线，那么一定存在一条可行直线，恰好经过某两个线段的端点。
所以不需要枚举无穷多条直线，只需要枚举全部线段端点两两组合，作为候选直线即可。

判断逻辑：
给定由 a,b 确定的无限长直线，以及一条线段 s‑e。
c1 = cross(a,b,s)，c2 = cross(a,b,e)
若 c1 * c2 > eps：s、e 在直线同一侧，线段和无限直线不相交。
否则：两点分居两侧 / 点落在直线上，无限直线穿过该线段。

边界：
n = 1 的时候，随便一条直线都满足条件，直接输出 Yes。
两个枚举端点重合，不能构成直线，跳过。

浮点数规则：
eps = 1e‑8，两个浮点数差值绝对值小于 eps，视为相等。

时间复杂度：
一共有 2n 个端点，枚举点对 O((2n)^2)，每次校验全部线段 O(n)，总复杂度 O(n^3)
n ≤ 100，完全可以通过。
*/

#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

// 浮点数精度阈值，题目要求 |a‑b|<1e‑8 视为相等
const double eps=1e-8;

// 平面上的点，存储x,y浮点数坐标
struct Point
{
    double x,y;
    // 默认无参构造，vector容器默认创建对象时调用
    Point(){}
    // 带参构造，Point p(1.5,2.5) 直接初始化点
    Point(double xx,double yy):x(xx),y(yy){}
};

/**
 * 判断两个点是否是同一个点
 */
bool samePoint(Point a, Point b)
{
    return fabs(a.x-b.x)<eps&&fabs(a.y-b.y)<eps;
}

/**
 * cross(a,b,c) 二维叉积，向量ab × 向量ac
 * 返回 >0 → c 在直线ab逆时针方向
 * 返回 <0 → c 在直线ab顺时针方向
 * 返回 =0 → a,b,c三点共线
 */
double cross(Point a,Point b,Point c)
{
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

/**
 * check函数：检验 a,b 确定的无限长直线，是否与所有线段相交
 * line：保存全部输入线段
 * 返回 true：该直线符合题目的要求
 * 返回 false：存在至少一条线段不和该直线相交
 */
bool check(Point a, Point b, vector<pair<Point,Point>> &line)
{
    // 遍历每一条线段
    for(auto &seg : line)
    {
        Point s = seg.first;  //线段起点
        Point e = seg.second; //线段终点
        //求线段两个端点相对于候选直线ab的叉积
        double c1 = cross(a, b, s);
        double c2 = cross(a, b, e);
        // c1*c2>eps：两点在直线同一侧，线段与无限直线不相交
        if(c1*c2>eps)
            return false;
    }
    //全部线段都可以被这条无限直线穿过
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;  cin>>t;
    while(t--)
    {
        int n;  cin>>n;
        vector<pair<Point,Point>> line; //存储所有输入线段
        vector<Point> pts;              //存储全部线段端点，用来枚举候选直线

        for(int i=0;i<n;i++)
        {
            double x1,y1,x2,y2;
            cin>>x1>>y1>>x2>>y2;
            Point a(x1,y1);
            Point b(x2,y2);
            line.push_back({a,b});
            pts.push_back(a);
            pts.push_back(b);
        }

        bool ok=false;
        // 只有一条线段，一定存在解
        if(n==1)
        {
            ok=true;
        }
        else
        {
            int sz=pts.size();
            // 双重循环枚举所有两个端点，组成候选直线
            for(int i=0;i<sz;i++)
            {
                for(int j=i+1;j<sz;j++)
                {
                    Point p1=pts[i];
                    Point p2=pts[j];
                    //两点重合，无法确定一条直线，跳过
                    if(samePoint(p1,p2))
                        continue;
                    //检验这条候选直线是否合法
                    if(check(p1,p2,line))
                    {
                        ok=true;
                        // 注意：这里没有break，依然会跑完循环，但ok已经置true
                    }
                }
            }
        }
        if(ok)
            cout<<"Yes!\n";
        else
            cout<<"No!\n";
    }
    return 0;
}
