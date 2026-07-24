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
const int mod=998244353;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll t;  cin>>t;   
    while(t--)
    {
        ll n,m,c;double a,b;   cin>>n>>m>>c>>a>>b;
        if(n>m) {cout<<0<<"\n";return 0;}
        if(n==m)
        {
            double ab=(1-a/b)%mod;
            int ans=pow(ab,n)%mod;
            cout<<ans<<"\n";
            return 0;
        }
        if(n<m)
        {
            int cha=m-n;
            if(cha%c!=0)    {cout<<0<<"\n";return 0;}
            else
            {
                int k=cha/c;
                if(k>n) {cout<<0<<"\n";return 0;}
                if(k==n)
                {
                    double ab=(1-a/b)%mod;
                    int ans=pow(ab,n)%mod;
                    cout<<ans<<"\n";
                    return 0;
                }
                if(k<n)
                {
                    double ab=(1-a/b)%mod;
                    int ans=pow(ab,k)%mod+pow(ab,n-k)%mod;
                    cout<<ans<<"\n";
                    return 0;
                }
            }
        }
    } 
    return 0;
}