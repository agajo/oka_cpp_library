#include <string>
#include <iostream>
#include <stack>
#include <queue> // priority_queue も入ってる
#include <set>   // 要素数は size() で取得 multisetもある
#include <map>
#include <array> // sizeはコンパイル時定数で固定
#include <vector>
#include <numeric>   // accumulate, gcd
#include <algorithm> // count_ifに必要
#include <iomanip>   // cout << setprecision(15) << x で小数の出力精度を指定
#include <tuple>
#include <utility> //pair
#include <cmath>
#include <random>

using namespace std;
using ll = long long;

#define rep(i, n) for (int i = 0; i < (n); ++i)

// LIS(Longest Increasing Subsequence)
// LISのサイズを返します。実際にLISを構成することはこの方法ではできません！！
ll lis(vector<ll> &vec, bool strictly = true, bool increasing = true)
{
    vector<ll> colorMaxs;
    rep(i, vec.size())
    {
        ll needle = vec[i];
        vector<ll>::iterator itr;
        if (strictly)
        {
            if (increasing)
                itr = lower_bound(colorMaxs.begin(), colorMaxs.end(), needle, less<ll>());
            else
                itr = lower_bound(colorMaxs.begin(), colorMaxs.end(), needle, greater<ll>());
        }
        else
        {
            if (increasing)
                itr = upper_bound(colorMaxs.begin(), colorMaxs.end(), needle, less<ll>());
            else
                itr = upper_bound(colorMaxs.begin(), colorMaxs.end(), needle, greater<ll>());
        }
        if (itr == colorMaxs.end())
        {
            colorMaxs.push_back(needle);
        }
        else
        {
            (*itr) = needle;
        }
    }
    return colorMaxs.size();
}

int main()
{
    vector<ll> a{5, 6, 4, 7, 4, 5, 6, 3, 7, 2, 8};
    ll res0 = lis(a);               // Strictly Increasing 5 {4,5,6,7,8}など
    ll res1 = lis(a, false);        // Monotonically Increasing 6 {4,4,5,6,7,8}など
    ll res2 = lis(a, true, false);  // Strictly Decreasing 4 {6,5,3,2}など
    ll res3 = lis(a, false, false); // Monotonically Decreasing 5 {6,4,4,3,2}など
    cout << res0 << ' ' << res1 << ' ' << res2 << ' ' << res3 << endl;
    return 0;
}