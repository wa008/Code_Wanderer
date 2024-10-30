#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<cmath>
#include<cassert>
#include<algorithm>
#include<iterator>
#include<random>
using namespace std;

typedef long long ll;


void debug(vector<ll> & v) {
    cout << "debug: \n";
    for(auto x: v) {
        cout << x << ' ';
    }
    cout << "\n";
}


int main()
{
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<ll> cum(n, 0), cc(n, 0), simple_cum(n + 1, 0);
    vector<long long> cnt(n, 0);
    for(int i = 0; i < n; ++i) {
        simple_cum[i + 1] = simple_cum[i] + a[i];
    }
    cum[n - 1] = a[n - 1];
    for(int i = n - 2; i >= 0; --i) {
        cum[i] = cum[i + 1] + a[i] * (n - i);
    }
    cc[0] = cum[0];
    for(int i = 1; i < n; ++i) {
        cc[i] = cc[i - 1] + cum[i];
    }
    cnt[0] = n;
    for(int i = 1; i < n; ++i) {
        cnt[i] = cnt[i - 1] + (n - i);
    }

    // reserve 
    // debug(cum);
    reverse(cum.begin(), cum.end());
    // debug(cum);
    // debug(cc);
    // debug(cnt);
    
    ll x = 0;
    
    // query
    int q;
    cin >> q;
    while(q--) {
        ll l, r;
        cin >> l >> r;
        assert(r <= cnt.back());
        int i1 = lower_bound(cnt.begin(), cnt.end(), l) - cnt.begin();
        int i2 = lower_bound(cnt.begin(), cnt.end(), r) - cnt.begin();
        ll ans = cc[i2] - cc[i1];
        long long r1 = cnt[i1] - l + 1;
        long long r2 = cnt[i2] - r;
        // cout << "i1: " << i1 << " i2: " << i2 << "\n";
        // cout << "r1: " << r1 << " r2: " << r2 << "\n";
            
        ll add = cum[r1 - 1];
        add += (simple_cum[n - r1] - simple_cum[i1]) * (r1);

        ll sub = 0;
        if(r2 > 0) {
            sub += cum[r2 - 1];
            sub += (simple_cum[n - r2] - simple_cum[i2]) * (r2);
        }
        
        // cout << "add: " << add << " sub: " << sub << "\n";
        ans += add;
        ans -= sub;
        // cout << "l = " << l << " " << i1 << "\n";
        cout << ans << "\n";
    }

    return 0;
}
