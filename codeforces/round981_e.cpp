// https://codeforces.com/contest/2033/problem/E 

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
 
void debug(vector<int> & v) {
    cout << "debug: \n";
    for(int i = 1; i < v.size(); ++i) {
        cout << v[i] << ' ';
    }
    cout << "\n\n";
}
 
int process(vector<int> & v, vector<int> & t, vector<int> & re, int cur) {
    if(v[cur] == cur || v[v[cur]] == cur) return 0;
    vector<int> c(2), g(2);
    c[0] = re[cur], c[1] = re[re[cur]], g[0] = v[cur], g[1] = v[v[cur]];
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 2; ++j) {
            if(c[i] != g[j]) continue;
            // cout << "swap: " << cur << ' ' << c[i] << "\n";
            swap(v[cur], v[c[i]]);
            t[cur] = 1;
            t[c[i]] = 1;
            return 1;
        }
    }
    return 0;
}
 
int main()
{
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> v(n + 1), t(n + 1, 0), l, re(n + 1, 0);
        for(int i = 1; i <= n; ++i) {
            cin >> v[i];
            re[v[i]] = i;
        }
        for(int i = 1; i <= n; ++i) {
            if(v[i] == i || v[v[i]] == i) {
                assert(v[v[v[i]]] == v[i]);
                t[i] = 1;
            }
            else l.push_back(i);
        }
        int cnt = 0;
        for(int i = 1; i <= n; ++i) {
            cnt += process(v, t, re, i);
        }
        // debug(v);
        while(l.size() > 0) {
            int cur = l.back();
            l.pop_back();
            if(v[cur] == cur || v[v[cur]] == cur) continue;
            // cout << "cur: " << cur << "\n";
            // cout << "swap: " << cur << ' ' << v[v[cur]] << '\n';
            if (t[cur] == 1) continue;
            int another_index = v[v[cur]];
            swap(v[another_index], v[cur]);
            // assert(t[cur] == 0);
            // assert(t[another_index] == 0);
            t[another_index] = 1;
            // t[cur] = 1;
            cnt += 1;
            l.push_back(cur);
            // debug(v);
            cnt += process(v, t, re, cur);
            // debug(v);
            // cout << "cnt: " << cnt << "\n\n\n";
        }
        cout << cnt << "\n";
    }
    return 0;
}
