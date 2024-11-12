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
        int n;
        cin >> n;
        vector<vector<int> > v(3, vector<int> (n));
        vector<vector<int> > p(3, vector<int> (n));
        for(int ind = 0; ind < 3; ++ind) {
            for(int i = 0; i < n; ++i) {
                cin >> v[ind][i];
                --v[ind][i];
                // cout << "v[i][ind]: " << i << " " << ind << ' ' << v[ind][i] << "\n";
                p[ind][v[ind][i]] = i;
            }
        }
        vector<vector<int> > pre(3, vector<int> (n));
        vector<int> pre_ind(n, -1), best(3, n), pre_pos(n, -1);
        best[0] = v[0][0];
        best[1] = v[1][0];
        best[2] = v[2][0];
        for(int i = 1; i < n; ++i) {
            int flag = 0;
            for(int ind = 0; ind < 3; ++ind) {
                if(v[ind][i] < best[ind]) {
                    flag = 1;
                    pre_ind[i] = ind;
                    pre_pos[i] = best[ind];
                    // cout << "update: " << ind << ' ' << p[ind][best[ind]] << ' ' << i << '\n';
                    // cout << "v[i][ind]: " << i << " " << ind << ' ' << v[ind][i] << "\n";
                    break;
                }
            }
            if(flag == 1) {
                for(int ind = 0; ind < 3; ++ind) {
                    best[ind] = max(best[ind], v[ind][i]);
                }
            }
        }
        if(pre_ind[n - 1] == -1) cout << "NO\n";
        else {
            cout << "YES\n";
            int cur = n - 1, ans = 0;
            vector<int> c, pos;
            while(cur > 0) {
                c.push_back(pre_ind[cur]);
                pos.push_back(cur);
                int last_pos = pre_pos[cur];
                cur = p[pre_ind[cur]][last_pos];
            }
            cout << c.size() << "\n";
            for(int i = c.size() - 1; i >= 0; --i) {
                if(c[i] == 0) cout << "q ";
                if(c[i] == 1) cout << "k ";
                if(c[i] == 2) cout << "j ";
                cout << pos[i] + 1 << '\n';
            }
        }
    }
    return 0;
}
