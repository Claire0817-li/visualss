/*
【题目】 Gym‑106072A Angry Birds 愤怒的小鸟
算法标签：计算几何、Andrew凸包、闵可夫斯基和、偏移膨胀(Offset)、Steiner立体体积公式

题目大意：
1. 在z=0平面，给出n个点构成闭合折线；每个点允许在平面内半径R2圆盘内任意偏移（传感器误差）。
2. 小鸟是半径R3球体；小鸟中心沿着扰动后的闭合折线运动。
3. S集合代表小鸟所有能扫到的三维空间点；求集合S的凸包体积。

核心几何转化：
① 所有原始点可以在R2圆盘扰动：等价于原始点集的凸包，做二维闵可夫斯基和一个半径R2圆盘。
> 也就是把凸多边形向外膨胀R2，得到新的平面图形。
② 将膨胀完的平面图形，向z轴正负方向膨胀R3，得到三维几何体，求该几何体体积。

————————————————————————————————————————
公式1：二维凸多边形向外膨胀半径R（闵可夫斯基和圆盘）
设原始凸包：S原始面积，C原始周长
膨胀之后新面积 S' = S + C * R2 + π * R2²
膨胀之后新周长 C' = C + 2 * π * R2
解释：
- S：原来多边形本身面积
- C*R2：每条边向外推R2生成矩形条带面积总和
- πR2²：所有凸多边形顶点外角圆弧拼起来恰好是一整个完整圆

膨胀之后周长：每条边向外平移长度不变；顶点处圆弧拼接为完整圆，增加2πR2。

————————————————————————————————————————
公式2：平面凸图形向z轴正负方向膨胀R3的三维体积（Steiner公式）
输入：平面图形面积S'，周长C'，膨胀半径R3
Volume = 2 * R3 * S'   +   (π * R3² / 2) * C'   +   (4.0/3.0)*π*R3³
分项拆解：
1. 2*R3*S'：平面图形向上+向下拉伸R3形成的棱柱主体体积
2. (π*R3²/2)*C'：沿着图形一圈侧面半圆柱的体积总和
3. 4/3πR3³：所有转角位置球面圆弧拼接，恰好凑成一整个完整球体体积

⚠️重要坑点：
R2是【二维平面膨胀】；R3是【三维空间膨胀】，二者不能直接相加合并半径！
要先做二维膨胀R2，拿膨胀后的S'、C'代入三维公式算体积。

————————————————————————————————————————
代码流程：
1. 读入n个平面点，跑Andrew凸包，得到原始凸包顶点
2. 计算原始凸包周长L(C)、原始凸包面积S
3. 套用二维膨胀公式，算出扰动R2之后的面积area、周长L
4. 将膨胀后的area、L代入三维Steiner公式，计算最终体积
5. 高精度输出答案

其他竞赛坑：
- top全局栈顶，每组测试样例求凸包必须手动top=0，不能依赖全局初始化！
- s数组 s[top] = s[1]，闭环重复点；计算周长、面积只用 [1, top‑1]
- n可以1e5，Andrew凸包O(n log n)满足时限
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

const double eps=1e-9;
const int MaxN=1e5+5;
const double PI=acos(-1.0);
int n;

// 二维点
struct Point
{
    double x,y;
    Point(){}
    Point(double x_,double y_):x(x_),y(y_){}
}p[MaxN],s[MaxN]; // p原始点；s凸包栈

// 向量ab × ac 叉积
double cross(Point a,Point b,Point c)
{
    return((b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x));
}
// 两点欧氏距离
double dis(Point a,Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

int top; // 凸包栈顶下标
/**
 * @brief Andrew凸包算法
 * 输入 p[0...n‑1]，结果存入s[1...top]；s[top]等于s[1]闭环
 */
void Andraw()
{
    sort(p,p+n,[](Point a,Point b){return (fabs(a.x-b.x)>eps)?(a.x<b.x):(a.y<b.y);});
    top=0; // ⚠️多组测试样例，每组必须重置栈顶！全局初始化只执行一次！
    for(int i=0;i<n;i++)
    {
        while(top>1&&cross(s[top-1],s[top],p[i])<eps) top--;
        s[++top]=p[i];
    }
    int t=top;
    for(int i=n-2;i>=0;i--)
    {
        while(top>t&&cross(s[top-1],s[top],p[i])<eps) top--;
        s[++top]=p[i];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout<<fixed<<setprecision(15);
    int t;  cin>>t;
    while(t--)
    {
        cin>>n;
        double R2,R3;   cin>>R2>>R3;
        double r=R2+R3; // 无用变量，仅占位，本题禁止直接合并R2与R3！

        for(int i=0;i<n;i++)   cin>>p[i].x>>p[i].y;
        Andraw();

        // 计算原始凸包周长 L，只用 s[1] ~ s[top‑1]，s[top]是闭环重复点
        double L=0;
        for(int i=1;i<=top-1;i++)
        {
            L+=dis(s[i],s[i+1]);
        }

        // 鞋带公式求原始凸包面积
        double area=0;
        for(int i=1;i<=top-1;i++)
        {
            int j=(i%(top-1))+1; // i到i+1；i=top‑1时j=1闭合多边形
            area+=s[i].x*s[j].y-s[i].y*s[j].x;
        }
        area=fabs(area)/2.0;

        // =========二维膨胀R2：闵可夫斯基和半径R2圆盘=========
        area=area+L*R2+PI*R2*R2; // S' = S + C*R2 + πR2²
        L=L+2*PI*R2;             // C' = C + 2πR2

        // =========三维Steiner膨胀R3，求体积=========
        double ans=2*R3*area + PI*R3*R3*L/2.0 + 4.0/3.0*PI*R3*R3*R3;
        cout<<ans<<"\n";
    }
    return 0;
}
