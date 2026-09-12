/*
题目：矩阵快速幂
算法标签：矩阵乘法、矩阵快速幂、二进制拆分
题目大意：给定 n*n 的方阵A，求A的k次幂，每个元素对 1e9+7取模
解题思路：
1.矩阵乘法满足结合律，因此可以用快速幂二进制拆分，把暴力O(k)次矩阵相乘优化为 O(n^3 log k)
2.矩阵快速幂初始答案res设置为单位矩阵，等价普通快速幂ans=1
3.二进制拆分k：
   若当前位为1：res = res * A，把当前底数乘入结果；
   A = A * A 底数平方；k右移；
4.循环顺序采用 i‑k‑j，CPU缓存局部性更好，运行更快；
   增加剪枝：a.c[i][k]==0时直接continue跳过内层循环，稀疏矩阵提速
注意事项：
①矩阵乘法不交换，res*A不能写成A*res；
②A是全局变量，qow函数会原地修改A，多组测试用例每组必须重新赋值矩阵A；
③隐患：a.c[i][k]*b.c[k][j]两个long long相乘，极端情况会溢出64位，稳妥写法用__int128承接中间乘积；
④下标全部从1开始。
时间复杂度：O(n^3 logk)，n<=100可以轻松通过。
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

const ll mod=1e9+7;   //模数 10^9+7
const int N=105;      //矩阵最大维度，n<=100

ll n;                 //全局：矩阵阶数

/*
matrix结构体
c[N][N]：存储矩阵元素，下标1开始
构造函数：调用memset把数组全部置0，构造零矩阵
*/
struct matrix
{
    ll c[N][N];
    matrix(){memset(c,0,sizeof(c));}
}A,res;  //A：输入的底数矩阵；res：保存矩阵幂结果

/**
 * @brief 重载矩阵乘法运算符 *
 * @param a 左矩阵
 * @param b 右矩阵
 * @return t = a * b，矩阵乘积，结果取模mod
 * 公式 t[i][j] = sum_{k=1..n} a[i][k] * b[k][j]
 * 循环顺序 i‑k‑j，缓存友好；a[i][k]=0直接剪枝跳过j循环
 */
matrix operator*(matrix &a,matrix &b)
{
    matrix t;   //临时矩阵，初始零矩阵，保存乘积
    for(int i=1;i<=n;i++)                 //枚举结果行i
    {
        for(int k=1;k<=n;k++)             //枚举a的列 / b的行
        {
            if(a.c[i][k]==0)   continue;  //a[i][k]为0，这一项全部无贡献，跳过内层循环
            for(int j=1;j<=n;j++)         //枚举结果列j
            {
                t.c[i][j]=(t.c[i][j]+a.c[i][k]*b.c[k][j])%mod;
            }
        }
    }
    return t;
}

/**
 * @brief 矩阵快速幂，计算 A^k，结果存入全局res
 * @param k 幂次
 * res初始化为单位矩阵（对角线=1其余0），矩阵乘法的单位元
 * 注意：函数会修改全局矩阵A！
 */
void qow(ll k)
{
    //res初始化为单位矩阵
    for(int i=1;i<=n;i++)   res.c[i][i]=1;
    while(k>0)
    {
        if(k&1) res=(res*A);  //当前二进制位为1，res = res * A
        A=A*A;                //底数矩阵平方
        k>>=1;                //k二进制右移一位
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll k; cin>>n>>k;
    //读入n阶矩阵A，输入直接取模
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>A.c[i][j];
            A.c[i][j]%=mod;
        }
    }
    qow(k); //计算A^k

    //输出结果矩阵res
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<res.c[i][j]<<" ";
        }
        cout<<'\n';
    }
    return 0;
}
