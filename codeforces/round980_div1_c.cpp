// https://codeforces.com/contest/2023/problem/C

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

typedef long long ll;


void dfs(int cur, int c_cur, int & k, vector<vector<int> > & g, vector<int> & c, vector<int> & f) {
    f[cur] = 1;
    c[cur] = c_cur;
    for(auto val: g[cur]) {
        if(f[val] == 0) {
            dfs(val, (c_cur + 1) % k, k, g, c, f);
        }
    }
}

void debug(vector<int> & v) {
    cout << "debug: \n";
    for(auto x: v) cout << x << ' ';
    cout << '\n';
}

vector<int> shift_cnt(vector<int> & c1, vector<int> & c2) {
    vector<int> ans;
    int s1 = 0, s2 = 0;
    for(int i = 0; i < c1.size(); ++i) {
        s1 += c1[i];
        s2 += c2[i];
    }
    if(s1 != s2) return ans;

    c2.insert(c2.end(), c2.begin(), c2.end());
    int n = c1.size(), cur = 0;
    vector<int> p(n + 1, 0);
    c1.push_back(-1);
    // kmp
    for(int i = 0; i < n; ++i) {
        while(cur > 0 && c1[i] != c1[cur]) cur = p[cur];
        if(i > 0 && c1[i] == c1[cur]) ++cur;
        p[i + 1] = cur;
    }
    int ind1 = 0, ind2 = 0;
    while(ind2 < n * 2) {
        while(ind1 > 0 && c1[ind1] != c2[ind2]) ind1 = p[ind1];
        if (c1[ind1] == c2[ind2]) {
            ++ind1;
        }
        ++ind2;
        if(ind1 == n) {
            ans.push_back(ind2 - n - 1);
        }
    }
    return ans;
}

void test() {
    vector<int> v1 = {1, 2, 1, 2};
    vector<int> v2 = {2, 1, 2, 1, 2};
    // cout << check(v1, v2) << "\n\n\n\n";
}

int main()
{
    // test();
    int t;
    cin >> t;
    int index = 0;
    while(t--) {
        int n, k;
        cin >> n >> k;
        vector<int> v1(n), v2(n);
        vector<vector<int> > g1(n);
        vector<vector<int> > g2(n);
        int m1, m2;

        for(int i = 0; i < n; ++i) cin >> v1[i];
        cin >> m1;
        for(int i = 0; i < m1; ++i) {
            int x, y;
            cin >> x >> y;
            --x;--y;
            g1[x].push_back(y);
        }

        for(int i = 0; i < n; ++i) cin >> v2[i];
        cin >> m2;
        for(int i = 0; i < m2; ++i) {
            int x, y;
            cin >> x >> y;
            --x;--y;
            g2[x].push_back(y);
        }
        vector<int> c1(n, -1), c2(n, -1);
        vector<int> f1(n, 0), f2(n, 0);
        dfs(0, 0, k, g1, c1, f1);
        dfs(0, 0, k, g2, c2, f2);

        vector<int> cnt11(k, 0), cnt12(k, 0), cnt21(k, 0), cnt22(k, 0);

        for(int i = 0; i < n; ++i) {
            assert(c1[i] != -1);
            assert(c2[i] != -1);
            if(c1[i] != -1) {
                if(v1[i] == 0) {
                    cnt11[c1[i]] += 1;
                } else {
                    cnt12[c1[i]] += 1;
                }
            }
            if(c2[i] != -1) {
                if(v2[i] == 0) {
                    cnt21[c2[i]] += 1;
                } else {
                    cnt22[c2[i]] += 1;
                }
            }
        }
        
        int flag = 0, cnt1 = 0, cnt2 = 0;
        // for specifical situation
        for(int i = 0; i < n; ++i) {
            cnt1 += v1[i];
            cnt2 += v2[i];
        }
        if ((cnt1 == n || cnt1 == 0) && cnt1 + cnt2 == n) flag = 1;

        vector<int> a1 = shift_cnt(cnt12, cnt21);
        vector<int> a2 = shift_cnt(cnt11, cnt22);

        for (auto & x: a2) x = (x + 2) % k;
        for (auto & x: a1) x = (x + k) % k;
        sort(a2.begin(), a2.end());
        sort(a1.begin(), a1.end());
        
        // find common shift_cnt
        int i1 = 0, i2 = 0;
        while(i1 < a1.size() && i2 < a2.size()) {
            if(a1[i1] == a2[i2]) {
                flag = 1;
                break;
            }
            else if (a1[i1] < a2[i2]) {
                ++i1;
            }
            else {
                ++i2;
            }
        }
        if(flag == 1) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
