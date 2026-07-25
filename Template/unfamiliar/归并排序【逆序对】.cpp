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
const int N=500010;
vl a(N),b(N);
int n;
ll res=0;
void msort(int l,int r)
{
    if(l>=r)    return;
    int mid=(l+r)>>1;
    msort(l,mid);msort(mid+1,r);

    int i=l,j=mid+1,k=l;
    while(i<=mid&&j<=r)
    {
        if(a[i]<=a[j])   b[k++]=a[i++];
        else    
        {
            b[k++]=a[j++];  
            res+=mid-i+1;
        }
    }
    while(i<=mid)    b[k++]=a[i++];
    while(j<=r)    b[k++]=a[j++];

    for(int i=l;i<=r;i++)
    {
        a[i]=b[i];
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=0;i<n;i++)    cin>>a[i];
    msort(0,n-1);
    cout<<res;
    return 0;
}