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
    int n, k, q;
    cin >> n >> k >> q;
    vector<vector<int> > a(k, vector<int> (n));
    vector<vector<int> > b(k, vector<int> (n));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < k; ++j) {
            cin >> a[j][i];
        }
    }
    for(int i = 0; i < k; ++i) {
        for(int j = 0; j < n; ++j) {
            if (j == 0) b[i][j] = a[i][j];
            else b[i][j] = a[i][j] | b[i][j - 1];
            // cout << i << ' ' << j << ' ' << a[i][j] << '\n';
            // cout << i << ' ' << j << ' ' << b[i][j] << '\n';
        }
    }
    while(q--) {
        // cout << "\ndebug: \n";
        int m;
        cin >> m;
        int l = 0, r = n - 1;
        for(int _ = 0; _ < m; ++_) {
            int x, y;
            char c;
            cin >> x >> c >> y;
            x--;
            if(c == '>') {
                int ind = upper_bound(b[x].begin(), b[x].end(), y) - b[x].begin();
                l = max(l, ind);
            } else {
                int ind = lower_bound(b[x].begin(), b[x].end(), y) - b[x].begin() - 1;
                r = min(r, ind);
            }
            // cout << x << ' ' << c << ' ' << y << "\n";
            // cout << l << " " << r << '\n';
        }
        if(l <= r) cout << l + 1 << '\n';
        else cout << "-1\n";
    } 
    return 0;
}
