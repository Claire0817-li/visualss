#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

const int N=105;        // 矩阵最大维度，n<=100足够
const double eps=1e-8;  // 浮点数精度阈值：绝对值小于eps就视为0
int n;                  // n个未知数，n个方程
double a[N][N];         // 增广矩阵 a[行][列]，第n+1列存放常数项b

//高斯-约旦消元
//返回true：存在唯一解；返回false：无唯一解（无解/无穷多解）
bool gauss()
{
    //i代表当前处理第i列（第i个未知数）
    for(int i=1;i<=n;i++)
    {
        int r=i;    // r记录主元所在行，初始设为当前i行
        //从i行向下，找第i列第一个非0元素的行作为主元行
        for(int k=i;k<=n;k++)
        {
            if(fabs(a[k][i])>eps)
            {
                r=k;break;
            }
        }
        if(r!=i)    swap(a[r],a[i]);//主元不在当前行，交换两行
        
        //主元位置是0，说明该列没有有效主元，不存在唯一解
        if(fabs(a[i][i])<eps)   return 0;

        //对角化：消去所有其他行的第i列
        for(int k=1;k<=n;k++)
        {
            if(k==i)    continue;; //跳过主元本行，不用消自己
            
            //t是消元倍数，用t乘主元行，可以把a[k][i]消为0
            double t=a[k][i]/a[i][i];
            //整行消元：第k行 = 第k行 - t * 主元行
            for(int j=1;j<=n+1;j++)
            {
                a[k][j]-=t*a[i][j];
            }
        }
    }
    // 对角线上是主元，解 = 常数项 / 本行主元
    for(int i=1;i<=n;++i)   a[i][n+1]/=a[i][i];
    return 1;
}

int main()
{
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);         
    cin>>n;
    //读入增广矩阵，每行n+1个数：n个系数 + 常数b
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n+1;j++)
        {
            cin>>a[i][j];
        }
    }

    bool ok=gauss();
    if(!ok) cout<<"No Solution\n";//无唯一解输出No Solution
    else
    {
        cout<<fixed<<setprecision(2);
        for(int i=1;i<=n;i++)
        {
            cout<<a[i][n+1]<<"\n";//依次输出每个未知数xi
        }
    }
    return 0;
}
