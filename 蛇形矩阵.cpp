//     /ᐠ˶˶ᐟ\
//   (=•ㅅ < )
//  |￣∪∪￣|
//  |＿求AC＿|
// 猫神大人请赐我本世纪最难得的运气[^]_[^]
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;  cin>>n;
    vvi a(n,vi(n));
    int num=1;
    for(int s=0;s<=2*n-2;s++)
    {
        int st_i,end_i;
        if(s<n)
        {
            st_i=0,end_i=s;
        }
        else
        {
            st_i=s-n+1,end_i=n-1;
        }
        if(s%2==0)
        {
            for(int i=end_i;i>=st_i;i--)
            {
                a[i][s-i]=num++;
            }
        }
        else
        {
            for(int i=st_i;i<=end_i;i++)
            {
                a[i][s-i]=num++;
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}