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
struct Time
{
    int h,m,s;
    bool operator <(const Time &other)const
    {
        if(h!=other.h)
        {
            return h<other.h;
        }
        if(m!= other.m)
        {
            return m<other.m;
        }
        return s<other.s;
    }
}p[5005];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;  cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>p[i].h>>p[i].m>>p[i].s;
    }
    sort(p,p+n);
    for(int i=0;i<n;i++)
    {
        cout<<p[i].h<<" "<<p[i].m<<" "<<p[i].s<<"\n";
    }
    return 0;
}