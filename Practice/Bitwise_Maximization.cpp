#include<bits/stdc++.h>
using namespace std;
using ll=long long;
void solve(){
int n;cin>>n;
    vector<int> a(n);int S=0;
    for(int i=0;i<n;i++)
    {
cin>>a[i]; S^=a[i];}
   int b=(((1<<30)-1)^S);
    int basis[30]={0};
    for(int i=0;i<n;i++)
    {
int x=a[i]&b;
    for(int j=29;j>=0;j--)
    {
  if((x>>j)&1)
  {
if(basis[j]==0)
{
    basis[j]=x;
    break;
}else{
x^=basis[j];}
  }
    }
    }
    int ma=0;
    for(int j=29;j>=0;j--)
    {
if(((ma^basis[j])>ma))
{
ma^=basis[j];
}}
    long long sum=S+2LL*ma;
    cout<<sum<<'\n';
}
int main()
{
ios::sync_with_stdio(false);
cin.tie(0);
int t;cin>>t;
while(t--)
{
    solve();
}
    return 0;
}