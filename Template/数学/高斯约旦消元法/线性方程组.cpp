#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
const int N=55;
const double eps=1e-8;
int n;
double a[N][N];
/*
gauss函数：高斯-约旦消元，化成对角矩阵
返回值约定：
return 0 → 无穷多解
return 1 → 无解
return 2 → 唯一解
*/
int gauss()
{
    int r=1; // 当前主元行
    for(int i=1;i<=n;++i) // i是主元列
    {
        // 找主元行：从r行往下，找第i列绝对值>eps的行
        int t=r;
        for(int k=r;k<=n;++k)
        {
            if(fabs(a[k][i])>eps)
            {
                t=k;break;
            }
        }
        if(fabs(a[t][i])<eps) continue; // 这一列没有主元，自由变量

        if(t!=r) swap(a[t],a[r]); // 交换到当前主元行

        // 高斯约旦：消去所有行（上面+下面）的第i列，不是只消下面
        for(int k=1;k<=n;++k)
        {
            if(k==r) continue; // 跳过主元本行
            double div=a[k][i]/a[r][i];
            for(int j=i;j<=n+1;++j)
            {
                a[k][j]-=div*a[r][j];
            }
        }
        r++;
    }

    // 判无解：存在一行，系数全0，但常数项不为0
    for(int i=r;i<=n;++i)
    {
        if(fabs(a[i][n+1])>eps)
            return 1;
    }
    if(r-1<n) return 0; // 有效主元个数 < n，无穷多解
    return 2; // 唯一解
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n+1;j++)
        {
            cin>>a[i][j];
        }
    }
    int ok=gauss();
    if(ok==0) cout<<"0\n";
    else if(ok==1) cout<<"-1\n";
    else
    {
        cout<<fixed<<setprecision(2);
        for(int i=1;i<=n;i++)
        {
            double ans=a[i][n+1]/a[i][i];
            cout<<"x"<<i<<"="<<ans<<"\n";
        }
    }
    return 0;
}
