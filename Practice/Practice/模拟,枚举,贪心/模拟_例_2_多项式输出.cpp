//     /ᐠ˶˶ᐟ\
//   (=•ㅅ < )
//  |￣∪∪￣|
//  |＿求AC＿|
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
int main()
{
    int n;
    cin>>n;
    vi a(n+1);
    for(int i=0;i<=n;i++)   cin>>a[i];
    for(int i=0;i<=n;i++)
    {
        if(a[i]==0) continue;
        int k=n-i;    
        // 符号
        if(i!=0&&a[i]>0)    cout<<"+";
        // 常数项
        if(k==0)
        {
            cout<<a[i];
        }
        // 一次项
        else if(k==1)
        {
            if(a[i]==1) cout<<"x";   
            else if(a[i]==-1)   cout<<"-x";   
            else    cout<<a[i]<<"x";
        }
        // 高次项
        else
        {
            if(a[i]==1) cout<<"x^"<<k;   
            else if(a[i]==-1)   cout<<"-x^"<<k;   
            else    cout<<a[i]<<"x^"<<k;
        }
    }

    return 0;
}