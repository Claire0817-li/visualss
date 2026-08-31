/*
题目：POJ 2653 Pick‑up sticks
题意：
按顺序把n根木棍扔到地面上，后扔的木棍会叠在先扔的木棍上方。
如果一根木棍和它之后任意一根木棍发生线段相交，那么它就会被盖住。
求所有没有被盖住、暴露在最顶层的木棍编号，编号从1开始。

算法思路：
1. 暴力O(n²)，题目特性保证顶层木棍最多1000根，实际不会超时。
2. 枚举每根木棍i，只和i之后的木棍j(j>i)做判断；前面的木棍在下层，无法盖住i。
3. 使用【跨立实验】判断两条线段是否相交，依靠叉积实现几何判断：
   cross(A,B,P) 计算向量AB × 向量AP的叉积。
   >0：P点在直线AB逆时针一侧；<0：顺时针一侧；=0：P落在直线AB上。
   跨立实验条件：
   ①线段b的两个端点不能同时在a所在直线的同一侧
   ②线段a的两个端点不能同时在b所在直线的同一侧
   两个条件同时满足，代表线段相交（包含端点接触、线段共线重叠）。
4. 若i与任意后面j相交 → i被盖住。如果i和所有后面木棍都不相交，就是答案。
5. 严格按照格式输出：Top sticks: x1, x2, x3.
注意：本代码为课件教学版本，直接使用>0比较，正式OJ提交建议加上eps浮点数修正。
*/

#include <bits/stdc++.h>
using namespace std;

using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

// 线段结构体：存储一条线段的两个端点坐标
struct Line
{
    double x1,y1,x2,y2;
};

/**
 * @brief 叉积 cross(A,B,P)
 * 向量AB 叉乘 向量AP
 * @param ax,ay 点A
 * @param bx,by 点B
 * @param px,py 点P
 * @return 叉积结果
 */
double cross(double ax,double ay,double bx,double by,double px,double py)
{
    return (bx-ax)*(py-ay) - (by-ay)*(px-ax);
}

/**
 * @brief 跨立实验判断两条线段是否相交
 * @param a 线段a
 * @param b 线段b
 * @return true相交，false不相交
 */
bool check(Line &a,Line &b)
{
    // b的两个端点都在a直线同一侧 → 一定不相交
    if(cross(a.x1,a.y1,a.x2,a.y2,b.x1,b.y1)*cross(a.x1,a.y1,a.x2,a.y2,b.x2,b.y2)>0)
        return false;
    // a的两个端点都在b直线同一侧 → 一定不相交
    if(cross(b.x1,b.y1,b.x2,b.y2,a.x1,a.y1)*cross(b.x1,b.y1,b.x2,b.y2,a.x2,a.y2)>0)
        return false;
    // 通过跨立条件，线段相交（包含端点触碰、共线重叠）
    return true;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr); // 关闭同步，加速cin读取浮点数

    int n;
    // 多组输入，n=0结束程序
    while(cin>>n)
    {
        if(n==0)   break;

        vector<Line> p(n);
        // 读入n根木棍的两个端点
        for(int i=0;i<n;i++)
            cin>>p[i].x1>>p[i].y1>>p[i].x2>>p[i].y2;

        cout<<"Top sticks: ";
        vi ans;
        int cnt=0;

        // 枚举每一根木棍i
        for(int i=0;i<n;i++)
        {
            bool ok=true; // ok=true代表i是顶层木棍，没有被盖住
            // j只遍历i后面的木棍，只有后扔的木棍可以压住i
            for(int j=i+1;j<n;j++)
            {
                // i与j相交，i被盖住，直接跳出内层循环
                if(check(p[i],p[j]))
                {
                    ok=false;
                    break;
                }
            }
            // i没有被后面任何木棍盖住，存入答案；题目编号从1开始，i+1
            if(ok)
                cnt++,ans.push_back(i+1);
        }

        // 格式化输出：数字, 数字, 数字.
        for(int i=0;i<ans.size();i++)
        {
            cout<<ans[i];
            if(i==ans.size()-1)
                cout<<'.';
            else
                cout<<", ";
        }
        cout<<'\n';
    }
    return 0;
}
