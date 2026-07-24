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
void buid(string in,string post)
{
    if(in.empty())  return;
    char root=post.back();
    cout<<root;
    int pos=in.find(root);
    string left_in=in.substr(0,pos);
    string right_in=in.substr(pos+1);
    string left_post=post.substr(0,pos);
    string right_post=post.substr(pos,post.size()-pos-1);
    buid(left_in,left_post);
    buid(right_in,right_post);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string in,post; cin>>in>>post;
    buid(in,post);
    return 0;
}