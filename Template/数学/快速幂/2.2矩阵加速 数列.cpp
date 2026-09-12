/*
【题目】线性递推数列
递推公式：
a₁ = 1, a₂ = 1, a₃ = 1
n ≥ 4: a[n] = a[n‑1] + a[n‑3]
T组询问，n最大 2e9，输出 a[n] mod 1e9+7

转移矩阵 M：
| 1 0 1 |
| 1 0 0 |
| 0 1 0 |

状态向量为列向量 Vₙ = [aₙ, a_{n‑1}, a_{n‑2}]ᵀ
Vₙ = M^{n‑3} * V₃，V₃=[a₃,a₂,a₁]ᵀ = [1,1,1]ᵀ
边界条件：n ≤3 直接输出1

算法：矩阵快速幂，时间复杂度 O(T * 3³ log n)
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

const ll mod=1e9+7;

//矩阵结构体，1下标，使用1~3，数组开4*4避免越界
struct matrix
{
    ll c[4][4];
    matrix(){memset(c,0,sizeof(c));}
}A,M;   //A:列向量；M:转移矩阵

/**
 * @brief 矩阵乘法 a * b
 * @param a 左矩阵
 * @param b 右矩阵
 * @return 返回乘积矩阵
 * 注意：需要改为const matrix &a, const matrix &b 支持临时对象运算；
 * a.c[i][k] * b.c[k][j] 建议套 __int128 防止long long乘法溢出
 */
matrix operator*(matrix &a,matrix &b)
{
    matrix t;
    for(int i=1;i<=3;i++)           //遍历结果矩阵的行
    {
        for(int k=1;k<=3;k++)       //中间维度，左矩阵列、右矩阵行
        {
            if(a.c[i][k]==0)        //剪枝，左矩阵该位置为0，跳过j循环
                continue;
            for(int j=1;j<=3;j++)   //遍历结果矩阵的列
            {
                // t[i][j] += a[i][k] * b[k][j]，模mod
                t.c[i][j]=(t.c[i][j]+a.c[i][k]*b.c[k][j])%mod;
            }
        }
    }
    return t;
}

/**
 * @brief 矩阵快速幂，求 base^k
 * @param base 底数矩阵，值拷贝传入，不会修改原始矩阵
 * @param k 幂次
 * @return 返回 base 的 k次幂矩阵
 */
matrix qow(matrix base,ll k)
{
    matrix res;
    //初始化结果为单位矩阵，单位矩阵乘矩阵不改变原矩阵
    for(int i=1;i<=3;i++)
        res.c[i][i]=1;
    while(k)                //快速幂倍增
    {
        if(k&1)             //k二进制最低位为1，res = res * base
            res=res*base;
        base=base*base;     //base平方
        k>>=1;              //k右移一位
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);  

    //构造转移矩阵M
    M.c[1][1]=1,M.c[1][3]=1;
    M.c[2][1]=1;
    M.c[3][2]=1;

    int t;  cin>>t;
    while(t--)
    {
        ll n;   cin>>n;
        if(n>3)
        {
            //重置列向量A，V3=[a3,a2,a1]^T
            memset(A.c,0,sizeof(A.c));
            A.c[1][1]=1,A.c[2][1]=1,A.c[3][1]=1;

            matrix P=qow(M,n-3);    //计算 M^{n‑3}
            matrix ans=P*A;         //矩阵 × 列向量
            cout<<ans.c[1][1]<<"\n";//结果矩阵第一行第一列即为a_n
        }
        else
        {
            //n为1、2、3，直接输出1
            cout<<"1\n";
        }
    }
    return 0;
}
