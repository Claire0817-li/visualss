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
    int t;      cin>>t;
    while(t--)
    {
        int n;  cin>>n;
        double r2,r3;   cin>>r2>>r3;
        vector<pair<double,double>> p(n);
        for(int i=0;i<n;i++)
        {
            cin>>p[i].first>>p[i].second;
        }
        cout<<fixed<<setprecision(15);
    }
    return 0;
}