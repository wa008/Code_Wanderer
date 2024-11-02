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
        queue<int> q;
        q.push(1);
        vector<int> ans(n, 0);
        int flag_stable = 0, cnt = 0;
        for(int i = 2; i < n; ++i) {
            if(flag_stable == 0) {
                cout << "? 1 " << i << "\n";
                cout.flush();
                ++cnt;
                int r;
                cin >> r;
                if(r == 1) {
                    q.push(i);
                    ans[i] = 0;
                } else {
                    ans[i] = 1;
                    q.pop();
                    q.push(i);
                    flag_stable = 1;
                }
            } else {
                while(true) {
                    int cur = q.front();
                    if(q.size() == 1) {
                        ans[i] = cur;
                        q.pop();
                        q.push(i);
                        break;
                    }
                    cout << "? " << cur << ' ' << i << "\n";
                    cout.flush();
                    ++cnt;
                    int r; cin >> r;
                    if(r == 1) {
                        q.pop();
                    } else {
                        ans[i] = cur;
                        q.pop();
                        q.push(i);
                        break;
                    }
                }
            }
        }
        assert(cnt <= 2 * n - 6);
        cout << "! ";
        for(int i = 1; i < n; ++i) {
            cout << ans[i]; 
            if (i == n - 1) cout << '\n';
            else cout << ' ';
        }
    }
    return 0;
}
