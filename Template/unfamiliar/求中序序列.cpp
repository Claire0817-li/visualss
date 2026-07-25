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
const int N=100005;
int pre[N],post[N];
int pos[N];
vi in;
void dfs(int p1,int p2,int len)
{
    if(len<=0)  return;
    if(len==1)  {in.push_back(pre[p1]); return;}

    int leftroot=pre[p1+1];
    int left_pos=pos[leftroot];
    int leftsize=left_pos-p2+1;
    dfs(p1+1,p2,leftsize);
    in.push_back(pre[p1]);
    dfs(p1+1+leftsize,p2+leftsize,len-leftsize-1);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;  cin>>n;
    for(int i=0;i<n;i++)    cin>>pre[i];
    for(int i=0;i<n;i++)
    {
        cin>>post[i];
        pos[post[i]]=i;
    }
    dfs(0,0,n);
    for(int x:in)
    {
        cout<<x<<" ";
    }
    return 0;
}