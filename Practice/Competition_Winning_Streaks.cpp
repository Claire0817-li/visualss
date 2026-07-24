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
        ll k,x1,y1,x2,y2; cin>>k>>x1>>y1>>x2>>y2;
        ll maxx=x2-x1,minn;
        if((y2-y1)==0)
        {
            minn=x2-x1;
        }
        else
        {
            minn=((x2-x1)+(y2-y1))/(y2-y1+1);
        }
        cout<<minn<<" "<<maxx<<"\n";
    }
    return 0;
}