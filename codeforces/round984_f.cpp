#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<cmath>
#include<algorithm>
#include <iterator>
#include <random>
using namespace std;

typedef long long ll;

ll trans(ll x) {
    if (x % 4 == 0) {
        return x;
    } else if(x % 4 == 1) {
        return 1;
    } else if(x % 4 == 2) {
        return x + 1;
    } else {
        return 0;
    }
}

ll solve(ll base, ll i, ll k) {
    ll ans = trans(base);
    ll tail = base - k;
    // cout << "tail1: " << tail << ' ' << i << ' ' << k << "\n";
    for(int ind = 0; ind < i; ++ind) tail = (tail >> 1);
    // cout << "tail2: " << tail << ' ' << i << ' ' << k << "\n";
    if(tail > 0) {
        if(tail & 1) ans ^= k;
        ll tmp = trans(tail);
        for(int ind = 0; ind < i; ++ind) tmp = (tmp << 1);
        ans ^= tmp;
        // cout << "tmp: " << tmp << " " << tail << "\n";
    }
    if(base >= k) ans ^= k;
    // cout << "ans: " << base << " " << ans << "\n";
    return ans;
}

int main()
{
    int t;
    cin >> t;
    while(t--) {
        ll l, r, i, k;
        cin >> l >> r >> i >> k;
        cout << (solve(r, i, k) ^ solve(l - 1, i, k)) << "\n";
    }

    return 0;
}
