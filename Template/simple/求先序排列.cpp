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
string pre,in,post;
void build(string in,string post)
{
    if(in.empty())  return;
    char root=post.back();
    cout<<root;
    int pos=in.find(root);
    build(in.substr(0,pos),post.substr(0,pos));
    build(in.substr(pos+1),post.substr(pos,post.size()-pos-1));
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>in>>post;
    build(in,post);
    return 0;
}