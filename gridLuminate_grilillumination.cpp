// gridLuminate_grilillumination.cpp 
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

vector<int> illuRes(int N, vector<vector<int>>& lamps, vector<vector<int>>& queries) {
    unordered_set<long> s;
    unordered_map<int, int> lx, ly, lp, lq;
    for (const auto& lamp : lamps) {
        const int x = lamp[0];
        const int y = lamp[1];
        s.insert(static_cast<long>(x) << 32 | y);
        ++lx[x];
        ++ly[y];
        ++lp[x + y];
        ++lq[x - y];
    }
    vector<int> ans;
    for (const auto& q : queries) {
        const int x = q[0];
        const int y = q[1];
        if (lx.count(x) || ly.count(y) || lp.count(x + y) || lq.count(x - y)) {
            ans.push_back(1);
            for (int tx = x - 1; tx <= x + 1; ++tx) {
                for (int ty = y - 1; ty <= y + 1; ++ty) {
                    if (tx < 0 || tx >= N || ty < 0 || ty >= N) continue;
                    const long key = static_cast<long>(tx) << 32 | ty;
                    if (!s.count(key)) continue;
                    s.erase(key);
                    if (--lx[tx] == 0) lx.erase(tx);
                    if (--ly[ty] == 0) ly.erase(ty);
                    if (--lp[tx + ty] == 0) lp.erase(tx + ty);
                    if (--lq[tx - ty] == 0) lq.erase(tx - ty);
                }
            }
        }
        else {
            ans.push_back(0);
        }
    }
    return ans;
    
}


int main()
{
    vector<vector<int>> lamps = { {0, 0},{4, 4} };
    vector<vector<int>> queries = { {1, 1},{1, 0} };

    auto ans = illuRes(5, lamps, queries);
    for (auto e : ans)
        cout << e << ",";

    return 0;
}
