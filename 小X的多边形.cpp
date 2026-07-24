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
struct sjx
{
    int x,y;
};
double area(sjx a,sjx b,sjx c)
{
    double ans=0.5*((a.x-c.x)*(b.y-c.y)-(b.x-c.x)*(a.y-c.y));
    return  ans;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;  cin>>n;
    vector<sjx>p(n);
    for(int i=0;i<n;i++)    {cin>>p[i].x>>p[i].y;}
    double ans=0;
    for(int i=0;i+1<n;i++)
    {
        ans+=area(p[0],p[i],p[i+1]);
    }
    cout<<round(ans);
    return 0;
}