#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<cmath>
#include<cassert>
#include<algorithm>
#include <iterator>
#include <random>
using namespace std;

const int mod = 1e9 + 7;
typedef long long ll;

ll my_pow(int n) {
    if(n == 0) return 1;
    if(n == 1) return 2;
    ll base = my_pow(n / 2);
    base = 1LL * base * base % mod;
    if(n % 2 == 1) base = 1LL * base * 2 % mod;
    return base;
}
void debug(vector<pair<int, int> > & stack) {
    cout << "debug: \n";
    for(auto x: stack) {
        cout << x.first << ' ' << x.second << '\n';
    }
}

int main()
{
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> v(n);
        for(int i = 0; i < n; ++i) {
            cin >> v[i];
        }
        vector<pair<int, int> > stack;
        vector<ll> ans;
        ll cur_ans = 0, all_pow = 0;
        for(int i = 0; i < n; ++i) {
            int base = v[i], cur_pow = 0;
            while(base % 2 == 0) {
                ++all_pow;
                ++cur_pow;
                base /= 2;
            }
            if (stack.size() == 0 || stack.back().first > v[i]) {
                // push_back
                stack.push_back(make_pair(base, cur_pow));
                cur_ans += v[i];
                cur_ans %= mod;
            } else {
                while(stack.size() > 0 && (cur_pow >= 30 || 1LL * my_pow(cur_pow) * base >= stack.back().first)) {
                    int l1 = stack.back().first, l2 = stack.back().second;
                    stack.pop_back();
                    cur_ans -= 1LL * l1 * my_pow(l2) % mod;
                    cur_ans = (cur_ans + mod) % mod;
                    while(l1 % 2 == 0) {
                        ++l2;
                        l1 /= 2;
                    }
                    cur_ans += l1;
                    cur_ans %= mod;
                    cur_pow += l2;
                }
                stack.push_back(make_pair(base, cur_pow));
                cur_ans += my_pow(cur_pow) * 1LL * base % mod;
                cur_ans %= mod;
            }
            ans.push_back(cur_ans);
        }
        for(int i = 0; i < n; ++i) {
            cout << ans[i];
            if(i == n - 1) cout << "\n";
            else cout << ' ';
        }
    }
    return 0;
}
