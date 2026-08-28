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
        ll n,x; cin>>n>>x;
        vl v(n+2);
        for(ll i=1;i<=n;i++)    cin>>v[i];
        ll ans=0;
        sort(v.begin()+1,v.begin()+n+1);
        v[n+1]=-1e9;
        ll l=1,r=1;
        while(r<=n+1)
        {
            if(v[l]==v[r])  r++;
            else    
            {
                ll c=r-l;
                if(c<=x)    ans+=c;
                l=r;
            }
        }
        cout<<ans<<"\n";
    }
    return 0;
}