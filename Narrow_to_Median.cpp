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
        ll n,k;    cin>>n>>k;
        vl a(n+1);
        vl pre(n+1,0);
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
        }
        sort(a.begin()+1,a.begin()+n+1);
        for(ll i=1;i<=n;i++)
        {
            pre[i]=pre[i-1]+a[i];
        }
        ll maxx=-1e18;
        if(k%2!=0)
        {
            ll cnt=k/2;
            for(ll i=cnt+1;i<=n-cnt;i++)
            {
                ll l=i-cnt,r=i+cnt;
                ll cha=pre[r]-pre[l-1];
                ll ans=k*a[i]-cha;
                maxx=max(maxx,ans);
            }
        }
        else
        {
            ll cnt=k/2;
            for(ll i=cnt;i<=n-cnt;i++)
            {
                ll l=i-cnt+1,r=i+cnt;
                ll cha=pre[r]-pre[l-1];
                ll ans=cnt*(a[i]+a[i+1])-cha;
                maxx=max(maxx,ans);
            } 
        }
        cout<<pre[n]+maxx<<"\n";
    }

    return 0;
}