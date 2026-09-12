/*
【题目】洛谷 P3829 [SHOI2012]信用卡凸包
题目大意：
给定 n 张圆角矩形信用卡。
每张信用卡原始竖直长度 a，水平长度 b，四个角落圆角圆弧半径 r。
每张信用卡给出中心坐标(x,y)，以及绕中心逆时针旋转的弧度 θ。
求把所有信用卡整体包围起来的外轮廓的总周长。

算法标签：计算几何、Andrew凸包、旋转矩阵、平面几何

核心思路：
1. 信用卡四个角是半径 r 的1/4圆弧；多张卡片全部圆角拼接，恰好拼成一整个完整圆，圆周长 = 2*PI*r。
2. 把圆角向内收缩 r，得到一个小矩形，小矩形的4个顶点，正好就是四个圆角圆弧的圆心。
3. 将全部信用卡的所有圆角圆心收集起来，对这堆点跑凸包。
4. 该凸包的周长对应信用卡外轮廓上所有直线部分的长度。
5. 最终答案 = 圆心集合的凸包周长 + 完整圆周长 2*PI*r。
> 重点技巧：不对圆弧采样，只使用圆弧圆心做凸包，避免曲线处理，降低精度与时间开销。

流程：
① a = a/2‑r，b = b/2‑r：求出圆心所在小矩形的半高、半宽。
② 对每张信用卡，生成4个相对于卡片中心的局部偏移点。
③ 使用旋转矩阵，将局部点逆时针旋转θ；再平移到全局坐标，存入点数组。
④ Andrew算法求全部点的凸包，计算凸包周长。
⑤ 凸包周长加上2πr，输出保留两位小数。
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

const int MaxN=40010;    // 最多10000张信用卡，每张4个点：4*10000=40000
const double PI=acos(-1.0);
const double eps=1e-8;   // 浮点数精度阈值

int cnt,top;             // cnt：总点数；top：凸包手写栈的栈顶下标
// 点结构体
struct Point
{
    double x,y;
    Point(){}
    Point(double x_,double y_):x(x_),y(y_){}
}p[MaxN],s[MaxN];        // p[]原始点数组；s[]Andrew凸包手写栈

/**
 * @brief  将局部点(px,py)绕坐标原点逆时针旋转 z 弧度
 * @param  a 局部点x坐标
 * @param  b 局部点y坐标
 * @param  z 逆时针旋转弧度
 * @return 旋转之后的新点
 * 旋转矩阵公式：
 * x' = a*cos(z) - b*sin(z)
 * y' = a*sin(z) + b*cos(z)
*/
Point rotate(double a,double b,double z)
{
    return Point(a*cos(z)-b*sin(z),a*sin(z)+b*cos(z));
}

/**
 * @brief 求向量ab × 向量ac 的叉积
 * >0 : ac在ab的逆时针方向
 * <0 : ac在ab的顺时针方向
 * =0 : a,b,c三点共线
*/
double cross(Point a,Point b,Point c)
{
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

// 两点欧几里得距离
double dis(Point a,Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

/**
 * @brief Andrew算法求凸包，返回凸包周长
 * 输入点数组 p[1...cnt]，栈s保存凸包上点
*/
double Andrew()
{
    // 排序：优先x从小到大；x近似相等按y从小到大（浮点数用eps判断相等）
    sort(p+1,p+cnt+1,[](const Point &a,const Point &b){
        return (fabs(a.x-b.x)>eps)?(a.x<b.x):(a.y<b.y);
    });
    top=0;
    // 构造下凸包：从左向右扫描所有点
    for(int i=1;i<=cnt;i++)
    {
        // 栈内至少2个点；出现非左转，弹出栈顶
        while(top>1&&cross(s[top-1],s[top],p[i])<=eps)
            top--;
        s[++top]=p[i];
    }
    int t=top; // 记录下凸包结束位置；上凸包不能弹出下凸包的点
    // 构造上凸包：从右向左扫描剩余点
    for(int i=cnt-1;i>=1;i--)
    {
        while(top>t&&cross(s[top-1],s[top],p[i])<=eps)
            top--;
        s[++top]=p[i];
    }
    // 计算周长；i<top，跳过闭环重复点 s[top] == s[1]
    double res=0;
    for(int i=1;i<top;i++)
        res+=dis(s[i],s[i+1]);
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;  cin>>n;
    double a,b,r;   cin>>a>>b>>r;
    // a：信用卡竖直总长；b：信用卡水平总长；r圆角半径
    // 向内扣除圆角r，得到圆角圆心组成小矩形的半高、半宽
    a=a/2-r;
    b=b/2-r;

    cnt=0;
    // 小矩形四个角，相对于卡片中心的局部偏移量
    int dx[]={-1,-1,1,1},dy[]={-1,1,-1,1};

    for(int i=0;i<n;i++) // 遍历n张信用卡
    {
        double x,y,z;   cin>>x>>y>>z; // 卡片中心(x,y)，逆时针旋转z弧度
        for(int j=0;j<4;j++) // 每张信用卡生成4个圆角圆弧圆心
        {
            // 1.局部坐标绕原点旋转
            Point t=rotate(dx[j]*b,dy[j]*a,z);
            // 2.平移变换到全局坐标系，存入点集
            p[++cnt]=Point(x+t.x,y+t.y);
        }
    }
    // 总周长 = 圆心凸包周长(直线部分) + 全部圆角拼成完整圆的周长
    double ans=Andrew()+2*PI*r;
    cout<<fixed<<setprecision(2)<<ans;
    return 0;
}
