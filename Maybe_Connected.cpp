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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;  cin>>t;
    while(t--)   
    {
        ll n,m; cin>>n>>m;
        if(m==0)    {cout<<0<<"\n";}
        else if(m<=n-2)
        {
            cout<<m*(m-1)/2<<"\n";
        }
        else
        {
            cout<<n*(n-1)/2-m<<"\n";
        }
    }
    return 0;
}