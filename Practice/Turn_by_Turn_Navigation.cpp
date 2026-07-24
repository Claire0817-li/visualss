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
struct dote
{
    ll x,y;
}p[100005];
ll chacheng(dote a,dote b,dote c)
{
    ll ans=(b.x-a.x)*(c.y-b.y)-(b.y-a.y)*(c.x-b.x);
    return ans;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll t;  cin>>t;
    while(t--)   
    {
        ll n;  cin>>n;
        for(ll i=0;i<n;i++)
        {
            cin>>p[i].x>>p[i].y;
        }
        for(ll i=0;i+2<n;i++)
        {
            if(chacheng(p[i],p[i+1],p[i+2])>0)    {cout<<"LEFT"<<" ";}
            else if(chacheng(p[i],p[i+1],p[i+2])<0)   {cout<<"RIGHT"<<" ";}
            else{cout<<"STRAIGHT"<<" ";}
        }
        cout<<"\n";
    }
    return 0;
}