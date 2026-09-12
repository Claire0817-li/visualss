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
    int n,k;    cin>>n>>k;
    map<int,bool> mp;
    priority_queue<int,vi> q;
    for(int i=0;i<n;i++)   
    {
        int x;  cin>>x;
        if(mp[x]==true) continue;
        else
        {mp[x]=true;
        if(q.size()<k)  q.push(x);
        else
        {
            if(x<q.top())   {q.pop();q.push(x);}
        }}
    }
    if(q.size()==k) cout<<q.top(); 
    else    cout<<"NO RESULT";
    return 0;
}