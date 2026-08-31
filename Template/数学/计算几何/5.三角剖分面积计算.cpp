/*
算法题型：计算几何 多边形与圆相交面积
题目：给定三角形三个顶点，给定圆心坐标与半径，求三角形和圆相交的面积
核心思想：
1.坐标平移变换：把圆心平移到坐标原点，三角形所有点同步做偏移，简化计算
2.多边形拆分为若干原点出发的有向三角形，利用有向面积累加得到多边形面积
3.Area(a,b):计算原点O、点a、点b构成的三角形与圆(圆心原点，半径r)相交的有向面积
4.分4种情况：两点都在圆内；两点都在圆外；一点圆内一点圆外；两点圆外线段穿过圆
注意：浮点数全部使用eps容错，叉积求有向面积，atan2求扇形圆心角
*/
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;
using ll=long long;

const double PI=acos(-1.0);
const double eps=1e-8;
double r; //圆的半径

//点结构体，同时重载向量加减、数乘、叉积、点积
struct Point
{
    double x,y;
    Point(){}
    Point(double x_,double y_):x(x_),y(y_){}

    //向量加法
    Point operator+(const Point &b)const{return Point(x+b.x,y+b.y);}
    //向量减法
    Point operator-(const Point &b)const{return Point(x-b.x,y-b.y);}
    //向量数乘
    Point operator*(double k)const{return Point(x*k,y*k);}
    //向量数除
    Point operator/(double k)const{return Point(x/k,y/k);}

    //叉积 a × b ：返回double，几何意义平行四边形有向面积
    double operator*(const Point &b)const{return (x*b.y-y*b.x);}
    //点积 a & b ：a·b = x1x2+y1y2
    double operator&(const Point &b)const{return (x*b.x+y*b.y);}
};

//求向量a的模长
double len(Point a)
{
    return sqrt(a&a);
}

//求a,b两点之间欧式距离
double dis(Point a,Point b)
{
    return len(a-b);
}

//向量a逆时针旋转b弧度
Point rotate(Point a,double b)
{
    return Point(a.x*cos(b)-a.y*sin(b),a.y*cos(b)+a.x*sin(b));
}

//单位化向量：返回和a同向，长度为1的向量
Point norm(Point a)
{
    return a/len(a);
}

/*
判断点p是否落在线段ab上
条件1：向量(p‑a)与(p‑b)叉积等于0 →三点共线
条件2：向量(p‑a)和(p‑b)点积 ≤0 →p在a,b两点中间（投影在线段内）
浮点数比较，用eps代替等于0
*/
bool onSegment(Point p,Point a,Point b)
{
    return fabs((p-a)*(p-b))<eps&&((p-a)&(p-b))<=eps;
}

/*
求两条直线交点
直线1：过点A，方向向量u
直线2：过点B，方向向量v
返回交点Point
*/
Point getNode(Point A, Point u, Point B, Point v)
{
    double t=((B-A)*v)/(u*v);
    return A+u*t;
}

/*
getDP2：原点到线段ab，求垂足；计算线段ab和圆交点pa、pb
a,b：线段两个端点
pa,pb：传出参数，线段ab与圆的两个交点
返回值：原点到线段ab的垂直距离；如果垂足不在线段上返回到两个端点最小距离
*/
double getDP2(Point a, Point b, Point &pa, Point &pb)
{
    // b-a 线段方向；rotate旋转90度得到垂线方向；求原点向线段ab作垂线得到垂足e
    Point e=getNode(a,b-a,Point(0,0),rotate(b-a,PI/2));
    double d=dis(Point(0, 0),e); //原点到垂足距离

    //如果半径大于垂足距离：线段和圆有交点，计算两个交点pa pb
    if(r>d)
    {
        //max防止r*r‑d*d因为浮点误差出现极小负数传给sqrt报错
        double l=sqrt(max(0.0,r*r-d*d));
        //垂足e沿着线段ab两个相反方向移动半弦长l，得到圆与线段交点
        pa=e+norm(a-b)*l;
        pb=e+norm(b-a)*l;
    }
    //垂足不在线段ab上：最短距离取原点到a、b端点距离的最小值
    if (!onSegment(e, a, b))
        return min(dis(Point(0,0),a),dis(Point(0,0),b));

    //垂足在线段上，返回原点到线段垂直距离
    return d;
}

/*
sector(a,b)：求扇形Oab的有向面积
a,b是从原点出发的向量
atan2(cross,dot)得到从向量a转到向量b的有向弧度，范围[-π,π]
扇形面积公式：1/2 * r² * 圆心角
*/
double sector(Point a,Point b)
{
    double ang=atan2(a*b,a&b);
    return r*r*ang/2.0;
}

/*
Area(a,b)：计算△Oab（原点O，a,b）与圆相交的【有向面积】
a,b是原点出发的向量
分4种情况：
1.O,a,b三点共线：面积0
2.a、b全部在圆内部：直接返回三角形有向面积 cross(a,b)/2
3.a、b都圆外，线段ab离原点距离>=r：完全扇形
4.一个点在圆内，一个点圆外：三角形部分 + 扇形部分拼接
5.两点圆外，线段穿过圆：扇形+中间三角形+扇形拼接
*/
double Area(Point a,Point b)
{
    //o a b三点共线，面积为0
    if(fabs(a*b)<eps) return 0.0;

    double da=dis(Point(0,0),a); //原点到a距离
    double db=dis(Point(0,0),b); //原点到b距离

    //a,b两点全部落在圆内部：直接返回三角形Oab的有向面积
    if(r>=da&&r>=db)
        return a*b/2.0;

    Point pa,pb; //线段ab与圆的交点
    double d=getDP2(a,b,pa,pb);

    //线段ab距离原点>=半径，线段和圆没有相交，直接扇形面积
    if(r<=d)
        return sector(a,b);

    //a在圆内，b在圆外：O‑a‑pb三角形 + pb到b扇形
    if(r>=da)
    {
        return (a*pb)/2.0 + sector(pb,b);
    }
    //b在圆内，a在圆外：O‑pa‑b三角形 + a到pa扇形
    if(r>=db)
    {
        return (pa*b)/2.0+sector(a,pa);
    }
    //a,b两点都圆外，线段穿过圆：a→pa扇形 + pa‑O‑pb三角形 + pb→b扇形
    return sector(a,pa)+(pa*pb)/2.0+sector(pb,b);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    //输入：三角形三点(x1,y1)(x2,y2)(x3,y3)；圆心(x4,y4)；圆半径r
    double x1,y1,x2,y2,x3,y3,x4,y4;
    while(cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4>>r)
    {
        //坐标平移变换：把圆心(x4,y4)移动到原点，三角形顶点同步偏移
        Point A(x1-x4,y1-y4);
        Point B(x2-x4,y2-y4);
        Point C(x3-x4,y3-y4);

        double res=0;
        Point p[3]={A,B,C};
        /*
        多边形圆交面积经典技巧：多边形拆分成原点出发的有向三角形
        三角形ABC拆 OAB + OBC + OCA，有向面积累加；
        结果取绝对值得到实际相交面积
        */
        for(int i=0;i<3;i++)
        {
            int j=(i+1)%3;
            res+=Area(p[i],p[j]);
        }
        //保留2位小数输出，取绝对值消除有向面积正负
        cout<<fixed<<setprecision(2)<<fabs(res)<<"\n";
    }
    return 0;
}
