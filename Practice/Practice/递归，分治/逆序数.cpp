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
vi a(N),b(N);
ll ans=0;
void msort(int l,int r)
{
    if(l>=r)    return;
    int mid=(l+r)/2;
    msort(l,mid);msort(mid+1,r);

    int i=l,j=mid+1,k=l;
    while(i<=mid&&j<=r)
    {
        if(a[i]>a[j])
        {
            b[k++]=a[j++];
            ans+=mid-i+1;
        }
        else    b[k++]=a[i++];
    }
    while(i<=mid)    {b[k++]=a[i++];}
    while(j<=r) {b[k++]=a[j++];}
    for(int i=l;i<=r;i++)
    {
        a[i]=b[i];
    }
}   
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;  cin>>n;
    for(int i=0;i<n;i++)    cin>>a[i];
    msort(0,n-1);
    cout<<ans;
    return 0;
}