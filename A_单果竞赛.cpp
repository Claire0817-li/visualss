#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
string s;

bool check(int mid)
{
    ll L = 0, R = 0;
    for (int i = 0; i < n; i++) {
        ll nL, nR;
        if (s[i] == '+') {
            nL = max(1LL, L + 1);
            nR = R + mid;
        } else if (s[i] == '-') {
            nL = L - mid;
            nR = min(-1LL, R - 1);
        } else { // '0'
            // 检查能否跳到 0
            bool can = false;
            if (max(L, 1LL) <= min(R, (ll)mid)) can = true;
            if (max(L, -(ll)mid) <= min(R, -1LL)) can = true;
            if (!can) return false;
            nL = 0;
            nR = 0;
        }
        if (nL > nR) return false;
        L = nL;
        R = nR;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> s;
        if (s[0] == '0') {
            cout << -1 << '\n';
            continue;
        }
        
        int l = 1, r = n, ans = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (check(mid)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}