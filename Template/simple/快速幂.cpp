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
const int mod=1e9+7;
ll quickpow(ll a,ll n)
{
    ll res=1;
    while(n)
    {
        if(n&1) res=res*a%mod;
        a=a*a%mod;
        n>>=1;
    }
    return res;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n;  cin>>n;
    if(n<2)
    {
        cout<<0<<endl;
        return 0;
    }
    ll ans1=(n%mod)*((n-1)%mod)%mod;
    ans1=ans1*quickpow(2,mod-2)%mod;
    ll ans2=quickpow(2,n-2)%mod;
    cout<<ans1*ans2%mod;
    return 0; 
}
//模质数下：
除以 k = 乘 k 的逆元，逆元用快速幂求 pow (k,mod-2)