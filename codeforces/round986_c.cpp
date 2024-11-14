#include<iostream>
#include<map>
#include<vector>
#include<queue>
#include<set>
#include<cmath>
#include<cassert>
#include<algorithm>
#include <iterator>
#include <random>
using namespace std;

typedef long long ll;


int main()
{
    int t;
    cin >> t;
    while(t--) {
        int n, m, val; 
        cin >> n >> m >> val;
        vector<ll> v(n), pre, suf;
        for(int i = 0; i < n; ++i) {
            cin >> v[i];
        }
        ll sum = 0, total = 0;
        for(int i = 0; i < n; ++i) {
            if(sum >= val && pre.size() < m) {
                // cout << "i: " << i << ' ' << sum << "\n";
                if(pre.size() == 0) pre.push_back(sum);
                else pre.push_back(pre.back() + sum);
                sum = v[i];
            } else {
                sum += v[i];
            }
            total += v[i];
        }
        if(sum >= val && pre.size() < m) {
            if(pre.size() == 0) pre.push_back(sum);
            else pre.push_back(pre.back() + sum);
        }
        sum = 0;
        for(int i = 0; i < n; ++i) {
            if(sum >= val && suf.size() < m) {
                if(suf.size() == 0) suf.push_back(sum);
                else suf.push_back(suf.back() + sum);
                sum = v[n - i - 1];
            } else {
                sum += v[n - i - 1];
            }
        }
        if(sum >= val && suf.size() < m) {
            if(suf.size() == 0) suf.push_back(sum);
            else suf.push_back(suf.back() + sum);
        }
        // for(auto x: pre) cout << x << ' '; cout << "\n";
        // for(auto x: suf) cout << x << ' '; cout << "\n";
        if(pre.size() < m && suf.size() < m) {
            cout << "-1\n";
        } else {
            assert(pre.size() > 0 && suf.size() > 0);
            ll ans = 0;
            if(suf.size() >= m) ans = max(ans, total - suf.back());
            if(pre.size() >= m) ans = max(ans, total - pre.back());
            for(int i = 0; i < m - 1; ++i) {
                if(i < pre.size() && m - 2 - i < suf.size()) {
                    ans = max(ans, total - pre[i] - suf[m - 2 - i]);
                }
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
